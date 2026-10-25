# -*- coding: utf-8 -*-
"""capture_replay.py — 无头捕获驱动器（内存驱动 UI 自动化，采集确定性重放输入包）

把 docs/deterministic_replay_workflow.md P3 的「用户手动操作」自动化：
全程只走历史记录（BuildHistory）功能开历史对战，每场战斗结束由
combatlog_exporter.Exporter 自动落盘 output/replay/<id>/（rng_state.txt
earliest_state + 双方阵容 v4 + events.json），产出重放三元组。

全部内存驱动，不用截图识别：
  * UI 自动化 = core.godot_reader.read_control_rect（Control 全局矩形）
    → 视口坐标映射客户区屏幕像素（pyautogui 点击）；
  * 每步点击前后都用内存读数验证状态（Game.curMode / buildHistory.isOpen /
    curData / curRunId / fighting），任何验证不符立即停止点击并报告。

安全红线（详见 docs/deterministic_replay_workflow.md §1）：
  * 开场校验 Game.curMode==3(Unselected) 或历史 UI 已开；
    Game.runStarted==true（正在普通对局中）立即退出报错，绝不操作；
  * 点击只允许四类节点：TitleScreen/ButtonsNode/HistoryButton、
    BuildHistory 条目（BuildEntry）、BuildHistory 的 FightButton；
  * 历史战斗结束后的结果回放界面需跳过一次才能回历史记录（Combat.gd:333-341
    _unhandled_input → skipRoundResult → switchBackToBuildHistory →
    buildHistory.open(true)，Combat.gd:356-357/:420-424）：仅在内存验证
    Combat.phase==RoundResultSkippable 后，点画布左下空白背景（无按钮）；
    实测键盘 Enter 因 Windows 前台锁不可靠。该路径确定性地只回历史记录
    界面，不触碰 继续游戏/放弃/排名 等任何按钮；
  * 绝不点击 继续游戏/放弃对局/其他模式/排名按钮，绝不进入 Ranked/Unranked。

用法：
    python tools/capture_replay.py --probe          # 只读检查（不点击）
    python tools/capture_replay.py --fights 3       # 真实捕获 3 场
"""
from __future__ import annotations

import argparse
import ctypes
import ctypes.wintypes
import logging
import math
import sys
import threading
import time
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))

from combatlog_exporter import Exporter, load_godot_offsets  # noqa: E402

logger = logging.getLogger("capture_replay")

# Godot 视口设计分辨率（project.godot:500-506：1920×1080，stretch mode="2d"、
# aspect="keep" → 画布坐标按 min(客户区宽/1920, 客户区高/1080) 等比缩放居中）
VIEW_W, VIEW_H = 1920.0, 1080.0

# --- BuildHistory.gd 成员槽位（声明序 = 32 个 onready var 之后；
#     BuildHistory.gd:9-42 + core/build_history.py:424-430 活体标定同源）---
BH_MEMBER_IS_OPEN = 32     # isOpen（BuildHistory.gd:42）
BH_MEMBER_ROUND = 34       # curRoundNum（BuildHistory.gd:44）
BH_MEMBER_DATA = 35        # curData（BuildHistory.gd:45，OBJECT/NIL）
BH_MEMBER_RUN = 36         # curRunId（BuildHistory.gd:46）
BH_MEMBER_FIGHTING = 37    # fighting（BuildHistory.gd:47）
# --- Game.gd 成员槽位（声明序=槽位链，docs/rng_truth.md §2.2：curRound=65/
#     curClass=83 活体标定；curClass=83 → runStarted(Game.gd:325)=82、
#     curMode(Game.gd:327)=84）---
GAME_MEMBER_RUN_STARTED = 82
GAME_MEMBER_CUR_MODE = 84
# Game.Mode 枚举（Game.gd:148-154）：Ranked=0 Unranked=1 Lobbies=2
# Unselected=3 History=4
MODE_UNSELECTED = 3
MODE_HISTORY = 4
# Combat.gd phase 成员槽位（Combat.gd:90 `var phase = Phase.Combat`，声明序 =
# 62 个 onready var + lobbyResultsReceived(62)/buildViewer(63) 之后 = 64）
# ——2026-10-05 活体验证（PID 7996）：结果界面可跳过时 members[64]=3，跳过
# 点击瞬间变 1（Phase 枚举 Combat=0 OffScreen=1 RoundResult=2
# RoundResultSkippable=3，Combat.gd:100-107），且 members[68]=1 与本场
# Loss 结果（RoundResult）吻合，与源码语义逐位一致。
COMBAT_MEMBER_PHASE = 64
PHASE_OFFSCREEN = 1
PHASE_RESULT_SKIPPABLE = 3
# 结果界面跳过点击的画布坐标（左下角空白背景：无按钮/无物品，
# 左键落入 Combat._unhandled_input → skipIfPossible）
SKIP_CANVAS_POINT = (100.0, 950.0)

# Godot 3 Variant::Type（variant.h）：NIL=0 BOOL=1 INT=2 REAL=3 OBJECT=17
VT_NIL, VT_BOOL, VT_INT, VT_OBJECT = 0, 1, 2, 17

BH_SCRIPT = "res://Interface/BuildHistory/BuildHistory.gd"
ENTRY_SCRIPT = "res://Interface/BuildHistory/BuildEntry.gd"

HISTORY_OPEN_TIMEOUT = 10.0     # a) 点 HistoryButton 后等 isOpen
ENTRY_SELECT_TIMEOUT = 10.0     # b) 点条目后等 curData/curRunId
FIGHT_START_TIMEOUT = 20.0      # c) 点 FightButton 后等开战
BATTLE_EXPORT_TIMEOUT = 180.0   # d) 等战斗结束落盘
POST_BATTLE_TIMEOUT = 45.0      # e) 等结果界面跳过/回到历史 UI 或标题
# 上一场战斗结束后回历史 UI 的稳定等待（跳过点击时战斗场景/动画尚在收尾；
# 2026-10-05 实测：跳过后 0.4s 就点 FightButton 会让新战斗事件追加到上一场
# 未清空的事件流上（导出包混入两场战斗），且疑似触发游戏崩溃）
HISTORY_SETTLE_WAIT = 3.0
# FightButton 点击前等战斗事件流清空（导出包纯净性闸：count>0 时点击
# 会把上一场尾巴混进本场导出，fail-fast）
LOG_CLEAR_TIMEOUT = 20.0


class CaptureAborted(Exception):
    """任一步验证重试 1 次后仍失败——携带已完成场数与卡点。"""

    def __init__(self, fights_done: int, blocker: str):
        super().__init__(blocker)
        self.fights_done = fights_done
        self.blocker = blocker


class CaptureError(Exception):
    """单步失败（可重试一次）。"""


class CaptureDriver:
    """导出器 + 内存状态读取 + 历史界面内四类节点的自动点击。"""

    def __init__(self, fights: int):
        self.fights = fights
        self.fights_done = 0
        self.completed: list = []      # 已落盘 replay 包路径
        self.exporter: Exporter | None = None
        self.gr = None
        self.wm = None
        self._poll_lock = threading.Lock()
        self._poll_status: dict = {}
        self._stop = threading.Event()
        self._poll_thread: threading.Thread | None = None
        self._fight_t0 = 0.0
        self._last_entry_idx: int | None = None   # 最近点击的 BuildEntry 下标

    # ---------------- 启动 / 导出器轮询 ----------------
    def setup(self) -> None:
        # 先把 config.yaml 的 RVA 标定并入默认表，再实例化读取器
        # （GodotReader.__init__ 会拷贝 GODOT_OFFSETS，必须先合并）
        from core.godot_reader import GODOT_OFFSETS
        for k, v in load_godot_offsets().items():
            GODOT_OFFSETS.setdefault(k, v)
        self.exporter = Exporter()
        self.exporter.auto_export = True   # 不询问直接写盘
        if not self.exporter.reader.connect():
            raise CaptureAborted(0, "无法连接游戏进程（请先启动 Backpack Battles）")
        self.gr = self.exporter.reader.gr
        self.wm = self.exporter.reader.wm if \
            hasattr(self.exporter.reader, "wm") else None
        self._poll_thread = threading.Thread(
            target=self._poll_loop, daemon=True, name="capture-poll")
        self._poll_thread.start()
        logger.info("已连接游戏 PID %s，导出器轮询已启动（auto_export=True）",
                    self.exporter.reader.pid)

    def _poll_loop(self) -> None:
        """战斗外 0.8s / 战斗内 0.1s 间隔循环 poll_and_autoexport（复用 Exporter）。"""
        while not self._stop.is_set():
            try:
                st = self.exporter.poll_and_autoexport()
            except Exception as e:  # noqa: BLE001
                st = {"status": "error", "error": str(e)}
            with self._poll_lock:
                self._poll_status = st
            # 战斗进行中 100ms 级密集轮询（rng 采样窗口，docs/rng_truth.md §4.2）
            interval = 0.1 if getattr(self.exporter, "_fight_active", False) \
                else 0.8
            self._stop.wait(interval)

    def status(self) -> dict:
        with self._poll_lock:
            return dict(self._poll_status)

    # ---------------- 内存读数（验证用）----------------
    def read_variant(self, node: int, idx: int):
        """读 GDScript 成员 Variant → (type, value)。

        BOOL 存于 union 首字节（1B@+8），INT 为 i64@+8，OBJECT 指针经
        gr._variant_object（combatlog_reader/build_history 同款间址）。
        失败返回 (None, None)。
        """
        gr = self.gr
        si = gr._script_instance(node)
        if not si:
            return (None, None)
        mptr = gr._ptr(si + gr.off["gdscript_members_off"])
        cnt = gr._cow_count(mptr)
        if not mptr or cnt is None or idx >= cnt:
            return (None, None)
        va = mptr + idx * gr.off["variant_size"]
        vt = gr._read_int(va, 4)
        if vt == VT_BOOL:
            b = gr.reader.read(va + 8, 1)
            return (vt, bool(b[0]) if b else None)
        if vt == VT_INT:
            return (vt, gr._read_int(va + 8, 8))
        if vt == VT_OBJECT:
            return (vt, gr._variant_object(va))
        return (vt, None)

    def find_build_history(self) -> int | None:
        """BFS 按脚本路径定位 BuildHistory 节点（core/build_history.py:433 同款）。"""
        root = self.gr.get_root()
        if not root:
            return None
        from collections import deque
        dq = deque([(root, 0)])
        seen = {root}
        while dq:
            node, depth = dq.popleft()
            try:
                sp = self.gr.node_script_path(node)
            except Exception:  # noqa: BLE001
                sp = None
            if sp and sp == BH_SCRIPT:
                return node
            if depth < 8:
                for c in self.gr.get_children(node):
                    if c not in seen:
                        seen.add(c)
                        dq.append((c, depth + 1))
        return None

    def bh_is_open(self, bh: int | None) -> bool | None:
        if not bh:
            return None
        vt, v = self.read_variant(bh, BH_MEMBER_IS_OPEN)
        return v if vt == VT_BOOL else None

    def bh_fighting(self, bh: int | None) -> bool | None:
        if not bh:
            return None
        vt, v = self.read_variant(bh, BH_MEMBER_FIGHTING)
        return v if vt == VT_BOOL else None

    def bh_selection(self, bh: int | None) -> dict:
        """读历史界面选中态：{data_nonnull, run_id, round_num}。"""
        if not bh:
            return {"data_nonnull": None, "run_id": None, "round_num": None}
        vt, obj = self.read_variant(bh, BH_MEMBER_DATA)
        data_nonnull = None if vt is None else (vt != VT_NIL)
        _, run_id = self.read_variant(bh, BH_MEMBER_RUN)
        _, round_num = self.read_variant(bh, BH_MEMBER_ROUND)
        return {"data_nonnull": data_nonnull, "run_id": run_id,
                "round_num": round_num}

    def game_cur_mode(self) -> int | None:
        game = self.gr.get_game_node()
        if not game:
            return None
        vt, v = self.read_variant(game, GAME_MEMBER_CUR_MODE)
        return v if vt == VT_INT else None

    def game_run_started(self) -> bool | None:
        game = self.gr.get_game_node()
        if not game:
            return None
        vt, v = self.read_variant(game, GAME_MEMBER_RUN_STARTED)
        return v if vt == VT_BOOL else None

    # ---------------- 坐标映射与点击 ----------------
    def _force_foreground(self) -> None:
        """把游戏窗口强制带到前台并验证，失败即抛错——绝不向被遮挡的窗口点击。

        2026-10-05 实测根因：游戏被 Chrome/ZCode 覆盖且失焦时，后台进程的
        SetForegroundWindow 被 Windows 前台锁拒绝，点击/滚轮全部落在覆盖
        窗口上（WindowFromPoint 验证）。解法：AttachThreadInput + Alt 键
        技巧（Windows 层标准焦点绕过；Alt 不构成游戏输入）+ HWND_TOP 置顶，
        之后必须验证 GetForegroundWindow==游戏窗口，否则抛错终止。
        """
        user32 = ctypes.windll.user32
        win = self._window()
        hwnd = win.hwnd
        user32.ShowWindow(hwnd, 9)          # SW_RESTORE
        fg = user32.GetForegroundWindow()
        if fg != hwnd:
            fg_tid = user32.GetWindowThreadProcessId(fg, None)
            cur_tid = ctypes.windll.kernel32.GetCurrentThreadId()
            attached = False
            if fg and fg_tid and fg_tid != cur_tid:
                attached = bool(user32.AttachThreadInput(cur_tid, fg_tid,
                                                         True))
            try:
                user32.BringWindowToTop(hwnd)
                user32.SetForegroundWindow(hwnd)
            finally:
                if attached:
                    user32.AttachThreadInput(cur_tid, fg_tid, False)
        if user32.GetForegroundWindow() != hwnd:
            # Alt 技巧兜底（按一下 Alt 解除前台锁再 SetForegroundWindow）
            user32.keybd_event(0x12, 0, 0, 0)       # Alt down
            user32.SetForegroundWindow(hwnd)
            user32.keybd_event(0x12, 0, 2, 0)       # Alt up (KEYEVENTF_KEYUP)
        user32.SetWindowPos(hwnd, 0, 0, 0, 0, 0, 0x1 | 0x2 | 0x40)
        time.sleep(0.2)
        if user32.GetForegroundWindow() != hwnd:
            raise CaptureError(
                "游戏窗口无法置前（GetForegroundWindow != 游戏窗口）——"
                "存在覆盖窗口时拒绝点击，绝不盲点")

    def _window(self):
        """刷新并返回游戏窗口；找不到即终止（内存与点击必须是同一进程）。"""
        if self.wm is None:
            from core.window_manager import WindowManager
            self.wm = WindowManager()
        if not self.wm.refresh() or not self.wm.window:
            raise CaptureError("未找到游戏窗口（Backpack Battles）")
        if self.exporter and self.wm.window.pid != self.exporter.reader.pid:
            raise CaptureError(
                f"窗口 PID {self.wm.window.pid} 与内存连接 PID "
                f"{self.exporter.reader.pid} 不一致")
        return self.wm.window

    def viewport_to_screen(self, x: float, y: float) -> tuple:
        """画布坐标(1920×1080 设计分辨率) → 屏幕物理像素。

        客户区原点用 ClientToScreen；stretch 2d + aspect keep（project.godot
        :500-506）→ 等比缩放居中（letterbox）。
        """
        win = self._window()
        pt = ctypes.wintypes.POINT(0, 0)
        if not ctypes.windll.user32.ClientToScreen(win.hwnd,
                                                   ctypes.byref(pt)):
            raise CaptureError("ClientToScreen 失败")
        cw, ch = win.width, win.height
        scale = min(cw / VIEW_W, ch / VIEW_H)
        offx = (cw - VIEW_W * scale) / 2.0
        offy = (ch - VIEW_H * scale) / 2.0
        sx = pt.x + offx + x * scale
        sy = pt.y + offy + y * scale
        # 映射自检：必须落在客户区内
        if not (pt.x <= sx <= pt.x + cw and pt.y <= sy <= pt.y + ch):
            raise CaptureError(
                f"映射坐标 ({sx:.0f},{sy:.0f}) 超出客户区 "
                f"({pt.x},{pt.y})+{cw}×{ch}")
        return (int(round(sx)), int(round(sy)))

    def click_control_center(self, node: int, label: str) -> tuple:
        """read_control_rect 取中心 → 视口映射 → pyautogui 点击。

        只接受已核实的四类允许节点（调用方保证）；矩形读取失败即抛错，
        绝不盲点。rect_rotation≠0 的按钮（如 NextRound，BuildHistory.tscn
        :301 rect_rotation=90）：内存裸矩形不是可点击 quad，中心须绕
        rect_pivot_offset 旋转——四个目标按钮在 tscn 中均无 pivot 行
        （pivot=(0,0)，Godot 默认），故 center = pos + R(θ)·(w/2, h/2)。
        """
        import pyautogui
        rect = self.gr.read_control_rect(node)
        if not rect:
            raise CaptureError(f"{label} 矩形读取失败（read_control_rect=None）")
        (x, y), (w, h) = rect
        rot = self.gr.read_control_rotation(node)
        if rot is None:
            logger.warning("%s: rotation 读取失败，按 0 处理", label)
            rot = 0.0
        if abs(rot) > 0.01:
            th = math.radians(rot)
            dx, dy = w / 2.0, h / 2.0
            cx = x + dx * math.cos(th) - dy * math.sin(th)
            cy = y + dx * math.sin(th) + dy * math.cos(th)
            logger.info("%s: rect_rotation=%.0f°，裸中心(%0.f,%0.f) → 旋转后"
                        "可点击 quad 中心(%.1f,%.1f)", label, rot,
                        x + dx, y + dy, cx, cy)
        else:
            cx, cy = x + w / 2.0, y + h / 2.0
        self._window()
        self.wm.bring_to_foreground()
        time.sleep(0.15)
        sx, sy = self.viewport_to_screen(cx, cy)
        logger.info("点击 %s: rect=(%.1f,%.1f)+(%.1f×%.1f) rot=%.0f° "
                    "中心=(%.1f,%.1f) → 屏幕(%d,%d)",
                    label, x, y, w, h, rot, cx, cy, sx, sy)
        pyautogui.click(sx, sy)
        return (sx, sy)

    # ---------------- 流程步骤（每步带内存验证）----------------
    def poll_until(self, check, timeout: float, interval: float = 0.25,
                   desc: str = "") -> object:
        """轮询内存条件直到满足；超时抛 CaptureError。check 返回真值即通过。"""
        deadline = time.monotonic() + timeout
        last = None
        while time.monotonic() < deadline:
            last = check()
            if last:
                return last
            time.sleep(interval)
        raise CaptureError(f"轮询超时（{timeout:.0f}s）: {desc}，最后读数={last}")

    def step_open_history(self) -> int:
        """a) 历史 UI 未开 → 点 TitleScreen/ButtonsNode/HistoryButton → 等 isOpen。"""
        bh = self.find_build_history()
        if bh and self.bh_is_open(bh) is True:
            logger.info("历史 UI 已开（BuildHistory 节点 %#x），复用", bh)
            return bh
        # 点击前内存验证：标题界面（curMode=Unselected）才允许点 HistoryButton
        mode = self.game_cur_mode()
        rs = self.game_run_started()
        if rs is True:
            raise CaptureError("Game.runStarted=true（正在普通对局中）——红线禁止操作")
        if mode != MODE_UNSELECTED:
            raise CaptureError(f"curMode={mode} ≠ 3(Unselected)，"
                               "不在标题界面，禁止点 HistoryButton")
        main = self.gr.find_main_node()
        btn = self.gr.find_control_node(
            ["TitleScreen", "ButtonsNode", "HistoryButton"], start=main)
        if not btn:
            raise CaptureError("未找到 TitleScreen/ButtonsNode/HistoryButton 节点")
        self.click_control_center(btn, "HistoryButton")
        # 点击后验证：isOpen==True（≤10s）
        def opened():
            b = self.find_build_history()
            if b and self.bh_is_open(b) is True:
                return b
            return None
        bh = self.poll_until(opened, HISTORY_OPEN_TIMEOUT,
                             desc="等待 buildHistory.isOpen==True")
        logger.info("历史 UI 已打开（BuildHistory 节点 %#x）", bh)
        return bh

    def _control_global_pos(self, node: int) -> tuple:
        """沿父链累加 Control/Node2D 的 raw pos（0x270，父相对坐标）。

        read_control_rect 读到的 pos 是「相对父节点」的——HistoryButton/
        FightButton 所在链的祖先都在原点故恰好等于全局，但列表行条目
        （entry 在占位符内 (0,0)，占位符 y=行号×128，VBox y=滚动偏移，
        ScrollContainer (44,174)）必须累加才是画布坐标。BuildHistory 链上
        无旋转节点（tscn 已核实）；祖先 pos 不可读（Node2D 非 Control 等）
        按 (0,0) 处理（UI/Main/BuildHistory 均在原点）。
        """
        total_x, total_y = 0.0, 0.0
        cur = node
        root = self.gr.get_root()
        for _ in range(16):
            if not cur or cur == root:
                break
            p = self.gr.node_pos(cur, use_global=False)
            if p and abs(p[0]) < 1e5 and abs(p[1]) < 1e5:
                total_x += p[0]
                total_y += p[1]
            cur = self.gr._ptr(cur + self.gr.off["node_parent_off"])
        return (total_x, total_y)

    def _click_entry(self, entry: int, label: str = "对局条目",
                     origin: tuple = (0.0, 0.0)) -> None:
        """点击 BuildEntry（允许节点类：对局条目）。

        点击点 = 条目矩形中心（entry 自身坐标系）；origin = 条目全局位置
        （父链累加，见 _control_global_pos）——行条目在占位符内局部
        (0,0)，必须加占位符链的全局偏移。若中心不落在可点击 Button
        （BuildEntry.tscn:432 pressed→onEntryPressed）子矩形内（同一
        entry 坐标系），改用该 Button 中心。点击前内存验证红线。
        """
        rect = self.gr.read_control_rect(entry)
        if not rect:
            raise CaptureError(f"{label} 矩形读取失败")
        (x, y), (w, h) = rect
        cx, cy = x + w / 2.0, y + h / 2.0
        btn = self.gr.child_by_name(entry, "Button")
        if btn:
            brect = self.gr.read_control_rect(btn)
            if brect:
                (bx, by), (bw, bh2) = brect
                if not (bx <= cx <= bx + bw and by <= cy <= by + bh2):
                    cx, cy = bx + bw / 2.0, by + bh2 / 2.0
                    logger.info("条目中心不在 Button 内，改点 Button 中心")
        if self.game_run_started() is True:
            raise CaptureError("runStarted=true——红线禁止操作")
        gx, gy = origin[0] + cx, origin[1] + cy
        self._window()
        self.wm.bring_to_foreground()
        time.sleep(0.15)
        sx, sy = self.viewport_to_screen(gx, gy)
        import pyautogui
        logger.info("点击 %s（节点 %#x）: 局部中心=(%.1f,%.1f)+全局偏移"
                    "(%.1f,%.1f) → 画布(%.1f,%.1f) → 屏幕(%d,%d)",
                    label, entry, cx, cy, origin[0], origin[1], gx, gy,
                    sx, sy)
        pyautogui.click(sx, sy)

    def step_select_first_entry(self, bh: int) -> dict:
        """b) 取列表第一个 BuildEntry 点其矩形中心 → 等 curData/curRunId。

        真条目在行占位符第二层（见 _walk_rows）；行 0 无实例（不可见）时
        列表区滚轮上滚触发实例化后重扫（≤8 次）。
        """
        def selection_ok():
            sel = self.bh_selection(bh)
            if sel["data_nonnull"] and (sel["run_id"] or 0) > 0:
                return sel
            return None
        if selection_ok():
            logger.info("选中已保留: %s（跳过选条目）", self.bh_selection(bh))
            return selection_ok()
        sc = self.gr.child_by_name(bh, "ScrollContainer")
        if not sc:
            raise CaptureError("未找到 BuildHistory/ScrollContainer")
        sgx, sgy = self._control_global_pos(sc)
        srect = self.gr.read_control_rect(sc)
        if not srect:
            raise CaptureError("ScrollContainer 矩形读取失败")
        (sw, sh) = srect[1]
        entry = None
        import pyautogui
        for attempt in range(10):
            rows = self._walk_rows(bh)
            gpos = self._control_global_pos(rows[0]["placeholder"]) if rows \
                else (0.0, 0.0)
            if rows and rows[0]["entry"]:
                entry = rows[0]["entry"]
                erect = self.gr.read_control_rect(entry)
                if erect:
                    gcy = gpos[1] + erect[0][1] + erect[1][1] / 2.0
                    if sgy <= gcy <= sgy + sh:
                        break
            self._window()
            self.wm.bring_to_foreground()
            time.sleep(0.1)
            mx, my = self.viewport_to_screen(sgx + sw / 2.0, sgy + sh / 2.0)
            prow = self.gr.read_control_rect(rows[0]["placeholder"]) if rows \
                else None
            row_cy = gpos[1] + (prow[0][1] + prow[1][1] / 2.0
                                if prow else 0.0)
            direction = 3 if row_cy < sgy else -3
            logger.info("行[0] 无可点击实例或不在可视区（行全局中心 y=%.1f, "
                        "列表 %.1f..%.1f）→ 列表区滚轮%s（第 %d 次）",
                        row_cy, sgy, sgy + sh,
                        "上滚" if direction > 0 else "下滚", attempt + 1)
            pyautogui.moveTo(mx, my)
            pyautogui.scroll(direction)
            time.sleep(0.8)
        else:
            raise CaptureError("行[0] 滚动 10 次后仍无可视区内实例")
        if self.bh_is_open(bh) is not True:
            raise CaptureError("点击条目前历史 UI 已关闭")
        self._click_entry(entry, label="对局条目[0]",
                          origin=self._control_global_pos(entry))
        # 点击后验证：curData 非空且 curRunId>0（≤10s）
        sel = self.poll_until(selection_ok, ENTRY_SELECT_TIMEOUT,
                              desc="等待 curData 非空且 curRunId>0")
        self._last_entry_idx = 0
        logger.info("已选中对局: runId=%s roundNum=%s", sel["run_id"],
                    sel["round_num"])
        return sel

    def step_change_round(self, bh: int, prev_round: int) -> int:
        """--diversity 1) 同 run 换回合：点 Build/NextRound → 轮询 curRoundNum 变化。

        onNextRoundPressed = (curRoundNum % numRounds) + 1（BuildHistory.gd:
        489-493，环绕取模，numRounds>1 时必然变化）。NextRound 是
        TextureButton（BuildHistory.tscn:296，Control 子类）。
        """
        if self.game_run_started() is True:
            raise CaptureError("runStarted=true——红线禁止操作")
        if self.bh_is_open(bh) is not True:
            raise CaptureError("换回合前历史 UI 未开")
        build = self.gr.child_by_name(bh, "Build")
        nr = self.gr.child_by_name(build, "NextRound") if build else None
        if not nr:
            raise CaptureError("未找到 BuildHistory/Build/NextRound 节点")
        self.click_control_center(nr, "NextRound(换回合)")
        def changed():
            v = self.bh_selection(bh)["round_num"]
            return v if (v is not None and v != prev_round) else None
        new = self.poll_until(changed, ENTRY_SELECT_TIMEOUT,
                              desc=f"等待 curRoundNum 离开 {prev_round}")
        logger.info("回合已换: %s -> %s", prev_round, new)
        return new

    def _walk_rows(self, bh: int) -> list:
        """历史列表行扫描：返回 [{row, placeholder, entry}]（row 0 起）。

        VBoxContainer 直接子节点 = Cursor/OpponentMark + 每行一个
        BuildEntryPlaceholder（BuildHistory.gd:205-213，addEntries 用
        ObjectPool.instance(placeholderScene) 建全部行）；真 BuildEntry
        只在行可见时作为占位符的子节点存在（BuildEntryPlaceholder.gd
        onVisible→initEntry / onInvisible→回对象池），因此必须在占位符
        第二层找可点击条目，仅过滤直接子节点会漏掉全部行。
        """
        sc = self.gr.child_by_name(bh, "ScrollContainer")
        vbox = self.gr.child_by_name(sc, "VBoxContainer") if sc else None
        if not vbox:
            raise CaptureError("未找到 BuildHistory/ScrollContainer/VBoxContainer")
        rows = []
        for c in self.gr.get_children(vbox):
            sp = self.gr.node_script_path(c)
            if sp == ENTRY_SCRIPT:          # 兼容：直接子节点即真条目
                rows.append({"placeholder": c, "entry": c})
                continue
            if sp and sp.endswith("BuildEntryPlaceholder.gd"):
                entry = None
                for cc in self.gr.get_children(c):
                    if self.gr.node_script_path(cc) == ENTRY_SCRIPT:
                        entry = cc
                        break
                rows.append({"placeholder": c, "entry": entry})
        return rows

    def step_next_entry(self, bh: int, prev_run: int) -> int:
        """--diversity 2) 换不同 run：点相邻下一个 BuildEntry。

        目标行没有已实例化的真条目（不可见）时，把鼠标移到列表区中心
        pyautogui.scroll(-3) 下滚——滚入可视区的行经 VisibilityNotifier
        自动实例化真条目——然后重扫（≤8 次）。
        """
        sc = self.gr.child_by_name(bh, "ScrollContainer")
        if not sc:
            raise CaptureError("未找到 BuildHistory/ScrollContainer")
        sgx, sgy = self._control_global_pos(sc)
        srect = self.gr.read_control_rect(sc)
        if not srect:
            raise CaptureError("ScrollContainer 矩形读取失败")
        (sw, sh) = srect[1]
        rows = self._walk_rows(bh)
        nxt = (self._last_entry_idx if self._last_entry_idx is not None else 0) + 1
        if nxt >= len(rows):
            raise CaptureError(f"没有相邻的下一个条目：当前下标 "
                               f"{self._last_entry_idx}，共 {len(rows)} 行")
        entry = None
        import pyautogui
        for attempt in range(10):
            rows = self._walk_rows(bh)
            gpos = self._control_global_pos(rows[nxt]["placeholder"])
            erect = None
            if rows[nxt]["entry"]:
                entry = rows[nxt]["entry"]
                erect = self.gr.read_control_rect(entry)
            if entry and erect:
                gcy = gpos[1] + erect[0][1] + erect[1][1] / 2.0
                if sgy <= gcy <= sgy + sh:
                    break
            # 目标行不可见/未实例化：按行全局 y 决定滚动方向
            self._window()
            self.wm.bring_to_foreground()
            time.sleep(0.1)
            mx, my = self.viewport_to_screen(sgx + sw / 2.0, sgy + sh / 2.0)
            prow = self.gr.read_control_rect(rows[nxt]["placeholder"])
            row_cy = gpos[1] + (prow[0][1] + prow[1][1] / 2.0
                                if prow else 0.0)
            direction = 3 if row_cy < sgy else -3   # 行在视口上方→滚轮向上
            logger.info("行[%d] 无可点击实例或不在可视区（行全局中心 y=%.1f, "
                        "列表 %.1f..%.1f）→ 列表区滚轮%s（第 %d 次）",
                        nxt, row_cy, sgy, sgy + sh,
                        "上滚" if direction > 0 else "下滚", attempt + 1)
            pyautogui.moveTo(mx, my)
            pyautogui.scroll(direction)
            time.sleep(0.8)
        else:
            raise CaptureError(f"条目[{nxt}] 滚动 10 次后仍无可视区内实例")
        if self.bh_is_open(bh) is not True:
            raise CaptureError("点击条目前历史 UI 已关闭")
        self._click_entry(entry, label=f"对局条目[{nxt}](换run)",
                          origin=self._control_global_pos(entry))
        def run_changed():
            v = self.bh_selection(bh)["run_id"]
            return v if (v is not None and v != prev_run) else None
        new = self.poll_until(run_changed, ENTRY_SELECT_TIMEOUT,
                              desc=f"等待 curRunId 离开 {prev_run}")
        self._last_entry_idx = nxt
        logger.info("run 已换: %s -> %s（行[%d]）", prev_run, new, nxt)
        return new

    def _write_selection(self, replay_dir: Path, sel: dict) -> None:
        """把战前内存读到的 (curRunId, curRoundNum) 写入 replay 包 selection.txt。

        只增文件不改既有内容——供跨会话 (curRunId, curRoundNum) 去重统计；
        写失败不影响捕获本体。
        """
        try:
            (replay_dir / "selection.txt").write_text(
                f"cur_run_id={sel['run_id']}\n"
                f"cur_round_num={sel['round_num']}\n"
                f"captured_at={datetime.now().isoformat(timespec='seconds')}\n",
                encoding="utf-8")
            logger.info("selection.txt 已写入: run_id=%s round_num=%s",
                        sel["run_id"], sel["round_num"])
        except Exception as e:  # noqa: BLE001
            logger.warning("selection.txt 写入失败（不影响捕获本体）: %s", e)

    def step_start_fight(self, bh: int) -> None:
        """c) 点 Build/FightButton → 确认开战（in_fight 或 fighting=true）。"""
        if self.game_run_started() is True:
            raise CaptureError("runStarted=true——红线禁止操作")
        if self.bh_fighting(bh) is True:
            raise CaptureError("fighting 已为 true（上场战斗未结束？）禁止重复点击")
        # 纯净性闸：等上一场战斗的事件流清空再点（混流会让导出包作废）
        def log_cleared():
            st = self.status()
            return st if st.get("count", 0) == 0 else None
        self.poll_until(log_cleared, LOG_CLEAR_TIMEOUT, interval=0.5,
                        desc="等待战斗事件流清空（count==0）")
        self._fight_t0 = time.time()   # 供 exported_done 兜底找本场的 replay 包
        build = self.gr.child_by_name(bh, "Build")
        fb = self.gr.child_by_name(build, "FightButton") if build else None
        if not fb:
            raise CaptureError("未找到 BuildHistory/Build/FightButton 节点")
        sel = self.bh_selection(bh)
        if not sel["data_nonnull"]:
            raise CaptureError("curData 为空——fightBuild 守卫不满足，禁止点击")
        self.click_control_center(fb, "FightButton")
        # 点击后验证：Exporter poll 状态 in_fight 或 fighting=true（≤20s）
        def fighting():
            if self.bh_fighting(bh) is True:
                return "fighting_member"
            st = self.status()
            if st.get("status") in ("in_fight", "ended_no_result"):
                return f"exporter:{st.get('status')}"
            return None
        how = self.poll_until(fighting, FIGHT_START_TIMEOUT, interval=0.1,
                              desc="等待开战（in_fight / fighting）")
        logger.info("已开战（%s），导出器转入 0.1s 密集轮询", how)

    def _replay_dir_for(self, exported_base: Path) -> Path:
        """由战斗日志目录名推出 replay 包目录（同一时间戳，_write/_write_replay
        共用 ts：CombatLog_<ts>_<rnd>_<result> → replay_<ts>_<rnd>_<result>）。"""
        from combatlog_exporter import REPLAY_DIR
        name = exported_base.name
        if name.startswith("CombatLog_"):
            return REPLAY_DIR / ("replay_" + name[len("CombatLog_"):])
        return exported_base.parent

    def step_wait_exported(self) -> Path:
        """d) 等战斗结束（poll 状态 exported，超时 180s）→ 返回 replay 包目录。

        exported 只出现一次，错过（如验证瞬时失败）后状态变 exported_done，
        此时按本场开打时间戳找 output/replay/ 下最新的包兜底。
        """
        deadline = time.monotonic() + BATTLE_EXPORT_TIMEOUT
        last_log = 0.0
        while time.monotonic() < deadline:
            st = self.status()
            s = st.get("status")
            if s == "exported" and st.get("exported_path"):
                p = Path(str(st["exported_path"]))
                self._validate_package(p)
                replay_dir = self._replay_dir_for(p.parent / p.name)
                logger.info("战斗已结束并落盘: %s", replay_dir)
                return replay_dir
            if s == "exported_done":
                # 兜底：找本场开打（_fight_t0）之后生成的 replay 包
                import glob
                from combatlog_exporter import REPLAY_DIR
                cands = [Path(d) for d in
                         glob.glob(str(REPLAY_DIR / "replay_*"))]
                cands = [d for d in cands
                         if d.stat().st_mtime >= self._fight_t0 - 2]
                if cands:
                    d = max(cands, key=lambda x: x.stat().st_mtime)
                    events_json = next(d.glob("*.events.json"), None)
                    if events_json:
                        self._validate_package(events_json)
                        logger.info("战斗已结束并落盘（exported_done 兜底）: %s", d)
                        return d
            if s == "error":
                raise CaptureError(f"导出器错误: {st.get('error')}")
            now = time.monotonic()
            if now - last_log > 10:
                last_log = now
                logger.info("战斗进行中: status=%s 事件=%s round=%s",
                            s, st.get("count"), st.get("round"))
            time.sleep(0.2)
        raise CaptureError("等战斗结束超时（180s）且未见 exported")

    def combat_phase(self) -> int | None:
        """读 Combat 节点的 phase 成员（COMBAT_MEMBER_PHASE，活体校验见注释）。"""
        main = self.gr.find_main_node()
        combat = self.gr.child_by_name(main, "Combat") if main else None
        if not combat:
            return None
        vt, v = self.read_variant(combat, COMBAT_MEMBER_PHASE)
        return v if vt == VT_INT else None

    def click_canvas_point(self, x: float, y: float, label: str) -> tuple:
        """画布坐标直接映射并点击（跳过点击等非 Control 锚点用）。"""
        import pyautogui
        self._window()
        self.wm.bring_to_foreground()
        time.sleep(0.15)
        sx, sy = self.viewport_to_screen(x, y)
        logger.info("点击 %s: 画布(%.0f,%.0f) → 屏幕(%d,%d)",
                    label, x, y, sx, sy)
        pyautogui.click(sx, sy)
        return (sx, sy)

    @staticmethod
    def _validate_package(log_json_path: Path) -> None:
        """导出包纯净性验证：事件流必须是单场战斗（t 单调，无重置）。

        2026-10-05 实测反例：上一场未清空就开下一场 → 导出事件在 index 1865
        处 t 从 10.7 重置到 0（两场混流），该包不可作重放输入。
        注：Exporter._write 返回的 base 不带 .json 后缀（combatlog_exporter
        .py:183 return base），这里自动补。
        """
        import json
        p = log_json_path
        if not str(p).endswith(".json"):
            p = Path(str(p) + ".json")
        try:
            d = json.loads(p.read_text(encoding="utf-8"))
            events = d.get("events") or []
        except Exception as e:  # noqa: BLE001
            raise CaptureError(f"导出包读取失败 {log_json_path}: {e}")
        if not events:
            raise CaptureError("导出包事件为空")
        for i in range(1, len(events)):
            if events[i].get("t", 0) < events[i - 1].get("t", 0) - 0.5:
                raise CaptureError(
                    f"导出包混入多场战斗（index {i} 处 t 重置 "
                    f"{events[i-1]['t']}→{events[i]['t']}）——本场捕获作废")
        last = events[-1].get("type")
        if last not in (111, 112):
            raise CaptureError(f"导出包末事件 type={last} 不是 Win/Loss")

    def step_after_battle(self) -> str:
        """e) 战后回导航：历史 UI 开→"history_open"；回标题→"title"。

        History 模式战斗结束后的结果回放界面唯一出路 = 跳过一次：
        左键/ui_accept 落入 Combat._unhandled_input（Combat.gd:333-341）
        → skipIfPossible → skipRoundResult → switchBackToBuildHistory →
        buildHistory.open(true)（Combat.gd:356-357/:420-424）——该路径
        在 History 模式下确定性地只回历史记录界面。
        实测（2026-10-05，PID 7996）：键盘 Enter 因 Windows 前台锁
        （SetForegroundWindow 受限）进不了游戏窗口，phase 不变；物理点击
        可靠（点击同时激活窗口）。因此用与其它步骤同一条内存映射链，
        点画布左下 (100,950) 空白背景（无按钮/无物品），且仅在内存验证
        Combat.phase == RoundResultSkippable(3) 后才点——非盲点，且不触碰
        继续游戏/放弃/排名等任何按钮。
        """
        deadline = time.monotonic() + POST_BATTLE_TIMEOUT
        last_skip = 0.0
        while time.monotonic() < deadline:
            if self.game_run_started() is True:
                raise CaptureError("runStarted=true——红线禁止操作")
            mode = self.game_cur_mode()
            bh = self.find_build_history()
            open_ = self.bh_is_open(bh)
            if open_ is True and bh:
                sel = self.bh_selection(bh)
                logger.info("已回到历史 UI（isOpen=True, runId=%s）",
                            sel["run_id"])
                return "history_open"
            if mode == MODE_UNSELECTED:
                logger.info("已回到标题界面（curMode=3）")
                return "title"
            # 结果界面（curMode=4 且历史 UI 未开）→ phase==3 验证后点击跳过
            if mode == MODE_HISTORY and open_ is not True \
                    and time.monotonic() - last_skip >= 3.0:
                phase = self.combat_phase()
                if phase == PHASE_RESULT_SKIPPABLE:
                    last_skip = time.monotonic()
                    self.click_canvas_point(*SKIP_CANVAS_POINT,
                                            label="结果界面跳过")
            time.sleep(0.5)
        raise CaptureError(f"战后导航超时（{POST_BATTLE_TIMEOUT:.0f}s）："
                           "既未回历史 UI 也未回标题")

    def _step_with_retry(self, name: str, fn):
        """任一步失败重试 1 次；仍失败 → CaptureAborted（终止并报告卡点）。"""
        try:
            return fn()
        except CaptureError as e:
            logger.warning("%s 失败（%s），重试 1 次", name, e)
            time.sleep(1.0)
            try:
                return fn()
            except CaptureError as e2:
                raise CaptureAborted(self.fights_done,
                                     f"{name}: {e2}") from e2

    # ---------------- 主循环 ----------------
    def safety_gate(self) -> None:
        """开场安全闸：runStarted=true（普通对局中）立即退出；
        允许继续 = curMode==3(Unselected) 或历史 UI 已开（或可验证恢复的
        结果界面）。"""
        rs = self.game_run_started()
        mode = self.game_cur_mode()
        bh = self.find_build_history()
        open_ = self.bh_is_open(bh)
        logger.info("安全闸: curMode=%s runStarted=%s buildHistory.isOpen=%s",
                    mode, rs, open_)
        if rs is True:
            raise CaptureAborted(0, "Game.runStarted=true（正在普通对局中）"
                                    "——红线禁止操作，立即退出")
        if mode == MODE_HISTORY and open_ is not True:
            # 上次运行中断在结果回放界面的恢复路径：仅当 Combat.phase 为
            # RoundResult(2)/RoundResultSkippable(3)（内存验证）才走同一条
            # 已验证的跳过流程回历史记录界面，否则一律拒绝启动
            phase = self.combat_phase()
            logger.info("启动时处于 History 模式且历史 UI 未开（Combat.phase=%s）",
                        phase)
            if phase not in (2, 3):
                raise CaptureAborted(
                    0, f"开场校验失败: curMode={mode} 历史 UI 未开且 "
                       f"Combat.phase={phase} 不是结果界面——拒绝操作")
            where = self._step_with_retry("战后导航恢复", self.step_after_battle)
            logger.info("已恢复到: %s", where)
        elif mode != MODE_UNSELECTED and open_ is not True:
            raise CaptureAborted(
                0, f"开场校验失败: curMode={mode}（预期 3=Unselected）且历史 UI "
                   "未开——为避免误操作仅允许标题界面或历史界面启动")

    def _one_fight(self, bh: int, sel: dict) -> Path:
        """单场公共体：开战 → 等落盘（+写 selection.txt）→ 战后导航。

        sel 必须是开战前从内存读到的选中态（fightBuild→close(true) 会释放
        BuildHistory 节点——活体实测战后节点换址，战后重读=读悬垂指针）。
        """
        self._step_with_retry("开战", lambda: self.step_start_fight(bh))
        replay_dir = self._step_with_retry("等战斗结束", self.step_wait_exported)
        self._write_selection(replay_dir, sel)
        self.fights_done += 1
        self.completed.append(str(replay_dir))
        where = self._step_with_retry("战后导航", self.step_after_battle)
        logger.info("第 %d 场完成: %s（战后: %s, runId=%s roundNum=%s）",
                    self.fights_done, replay_dir, where,
                    sel["run_id"], sel["round_num"])
        if where != "title":
            # history_open：战斗场景/动画收尾需要时间；稳定等待后再连打
            # （实测跳过后立即点 FightButton 会导致事件混流甚至游戏崩溃）
            time.sleep(HISTORY_SETTLE_WAIT)
        return where

    def run(self) -> dict:
        self.safety_gate()
        for i in range(self.fights):
            logger.info("=== 第 %d/%d 场 ===", i + 1, self.fights)
            bh = self._step_with_retry("打开历史UI", self.step_open_history)
            sel = self._step_with_retry(
                "选对局", lambda: self.step_select_first_entry(bh))
            self._one_fight(bh, sel)
        return {"fights_done": self.fights_done, "completed": self.completed,
                "blocker": ""}

    def run_diversity(self, n: int) -> dict:
        """--diversity N：基础捕获后补充 N 场，取材顺序：
        1) 同 run 换回合（前 2 场）：Build/NextRound → curRoundNum 变化 → 开战；
        2) 换不同 run（其后）：相邻下一个 BuildEntry（不可见先滚轮）→
           curRunId 变化 → 开战。"""
        self.safety_gate()
        for i in range(n):
            logger.info("=== diversity 第 %d/%d 场 ===", i + 1, n)
            bh = self._step_with_retry("打开历史UI", self.step_open_history)
            self._step_with_retry(
                "选对局", lambda: self.step_select_first_entry(bh))
            sel = self.bh_selection(bh)
            if i < 2:
                self._step_with_retry(
                    "换回合",
                    lambda: self.step_change_round(bh, sel["round_num"]))
            else:
                self._step_with_retry(
                    "换run",
                    lambda: self.step_next_entry(bh, sel["run_id"]))
            sel = self.bh_selection(bh)   # 变更后重读（战前基准，节点仍存活）
            self._one_fight(bh, sel)
        return {"fights_done": self.fights_done, "completed": self.completed,
                "blocker": ""}


# ---------------- --probe 只读检查 ----------------
def probe() -> int:
    """只读检查：连接、各节点定位、矩形读取、成员读数。不点击不按键。"""
    from core.godot_reader import GODOT_OFFSETS
    for k, v in load_godot_offsets().items():
        GODOT_OFFSETS.setdefault(k, v)
    drv = CaptureDriver(fights=0)
    drv.exporter = Exporter()
    if not drv.exporter.reader.connect():
        print("[probe] FAIL 无法连接游戏进程")
        return 1
    drv.gr = drv.exporter.reader.gr
    gr = drv.gr
    ok = True

    print(f"[probe] 游戏已连接 PID={drv.exporter.reader.pid}")
    d = gr.read_rng_state()
    print(f"[probe] Util.rng state={d and hex(d['state'])} "
          f"seed={d and hex(d['seed'])}（LCG 校验 mode={None}）")

    game = gr.get_game_node()
    print(f"[probe] Game 节点 = {game and hex(game)}")
    drv_w = CaptureDriver(0)
    drv_w.gr = gr
    drv_w.exporter = drv.exporter
    mode = drv_w.game_cur_mode()
    rs = drv_w.game_run_started()
    print(f"[probe] Game.curMode (members[84]) = {mode} "
          f"{'(Unselected)' if mode == 3 else '(!!)'}")
    print(f"[probe] Game.runStarted (members[82]) = {rs}")

    bh = drv_w.find_build_history()
    print(f"[probe] BuildHistory 节点 = {bh and hex(bh)}")
    if bh:
        print(f"[probe]   isOpen(members[32])={drv_w.bh_is_open(bh)} "
              f"curData非空={drv_w.bh_selection(bh)['data_nonnull']} "
              f"curRoundNum(members[34])={drv_w.bh_selection(bh)['round_num']} "
              f"curRunId(members[36])={drv_w.bh_selection(bh)['run_id']} "
              f"fighting={drv_w.bh_fighting(bh)}")
        sc = gr.child_by_name(bh, "ScrollContainer")
        vbox = gr.child_by_name(sc, "VBoxContainer") if sc else None
        entries = [c for c in gr.get_children(vbox)] if vbox else []
        n_entry = sum(1 for c in entries
                      if gr.node_script_path(c) == ENTRY_SCRIPT)
        print(f"[probe]   entryContainer 子节点={len(entries)} "
              f"其中 BuildEntry={n_entry}")

    main = gr.find_main_node()
    print(f"[probe] Main 节点 = {main and hex(main)}")
    for path in (("TitleScreen", "ButtonsNode", "HistoryButton"),
                 ("TitleScreen", "ButtonsNode", "ItemLibraryButton"),
                 ("TitleScreen", "ButtonsNode", "RecipeBookButton")):
        node = gr.find_control_node(list(path), start=main)
        rect = gr.read_control_rect(node) if node else None
        expect = {("TitleScreen", "ButtonsNode", "HistoryButton"):
                  ((1724.0, 325.0), (165.0, 108.0)),
                  ("TitleScreen", "ButtonsNode", "ItemLibraryButton"):
                  ((1714.0, 114.0), (178.0, 109.0))}.get(path)
        verdict = ""
        if expect and rect:
            tol = 3.0
            hit = all(abs(a - b) <= tol
                      for p, q in zip(rect, expect) for a, b in zip(p, q))
            verdict = f"  对比设计矩形 {expect} → {'PASS' if hit else 'FAIL'}"
            ok = ok and hit
        elif not rect:
            verdict = "  （矩形不可读——偏移未标定或节点缺失）"
            if expect:
                ok = False
        print(f"[probe] {'/'.join(path)} = {node and hex(node)} "
              f"rect={rect}{verdict}")

    bhn = bh
    if bhn:
        build = gr.child_by_name(bhn, "Build")
        fb = gr.child_by_name(build, "FightButton") if build else None
        frect = gr.read_control_rect(fb) if fb else None
        print(f"[probe] BuildHistory/Build/FightButton = {fb and hex(fb)} "
              f"rect={frect}")

    st = drv.exporter.poll_and_autoexport()
    print(f"[probe] Exporter poll: status={st.get('status')} "
          f"connected={st.get('connected')} round={st.get('round')} "
          f"count={st.get('count')}")
    print(f"[probe] {'ALL PASS' if ok else '存在问题（见上）'}——未执行任何点击")
    return 0 if ok else 2


# ---------------- --diversity 统计 ----------------
# 旧包（无 selection.txt，本工具加入该文件前产生）的 (curRunId, curRoundNum)
# 归因依据：会话捕获日志（outputcapture_replay_run.log / capture_replay_run2-4.log）
# ——这些包全部由历史列表首个条目产生，日志可见「选中保留: run_id 1562，
# round_num 18」（updateBuild(data.getRounds()) 即 18，BuildHistory.gd:334-355）。
LEGACY_PAIRS = {
    "20261005_181924": (1562, 18),
    "20261005_182816": (1562, 18),
    "20261005_182826": (1562, 18),
    "20261005_184042": (1562, 18),
    "20261005_184421": (1562, 18),
}


def _lineup_key(d: Path):
    """双方阵容指纹（id+at+r+gems 排序序列），用于旧包的比对归因。"""
    import json
    parts = []
    for pat in ("*.Player.json", "*.Opponent.json"):
        f = next(d.glob(pat), None)
        if not f:
            return None
        items = json.loads(f.read_text(encoding="utf-8")).get("items") or []
        parts.append(tuple(sorted(
            (it.get("id"), tuple(it.get("at") or ()),
             it.get("r"), tuple(it.get("gems") or ()))
            for it in items)))
    return tuple(parts)


def report_stats(new_fights: int) -> None:
    """统计写入 stdout：本次新增场数 + 全部有效捕获的去重
    (curRunId, curRoundNum) 对数。有效性判据：rng_state.txt earliest_state
    非 NONE 且事件数>100；混流（t 重置）单独标注。"""
    import json
    import re
    from combatlog_exporter import REPLAY_DIR
    rows = []
    pairs = set()
    unknown = []
    for d in sorted(REPLAY_DIR.glob("replay_*")):
        rs = d / "rng_state.txt"
        evf = next(d.glob("*.events.json"), None)
        rng_ok, source = False, None
        if rs.exists():
            txt = rs.read_text(encoding="utf-8")
            rng_ok = re.search(r"earliest_state=\d+", txt) is not None
            sm = re.search(r"earliest_source=(\S+)", txt)
            source = sm.group(1) if sm else None
        ev_n, rnd, mixed = 0, None, False
        if evf:
            data = json.loads(evf.read_text(encoding="utf-8"))
            ev = data.get("events") or []
            ev_n = len(ev)
            rnd = data.get("meta", {}).get("round")
            mixed = any(ev[i].get("t", 0) < ev[i - 1].get("t", 0) - 0.5
                        for i in range(1, len(ev)))
        valid = rng_ok and ev_n > 100
        pair, how = None, None
        st = d / "selection.txt"
        if st.exists():
            t = st.read_text(encoding="utf-8")
            rid = re.search(r"cur_run_id=(\d+)", t)
            rrn = re.search(r"cur_round_num=(\d+)", t)
            if rid and rrn:
                pair = (int(rid.group(1)), int(rrn.group(1)))
                how = "selection.txt"
        else:
            for k, v in LEGACY_PAIRS.items():
                if d.name.startswith("replay_" + k):
                    pair, how = v, "日志归因"
        key = _lineup_key(d)
        if pair is None and valid and key:
            for r in rows:
                if r["valid"] and r["pair"] and r["key"] == key:
                    pair, how = r["pair"], "阵容比对归因"
                    break
        if valid and pair:
            pairs.add(pair)
        if valid and pair is None:
            unknown.append(d.name)
        rows.append({"name": d.name, "valid": valid, "ev": ev_n, "rnd": rnd,
                     "source": source, "pair": pair, "how": how,
                     "mixed": mixed, "key": key})
    print(f"\n===== diversity 统计 =====")
    print(f"本次新增场数: {new_fights}")
    print(f"有效捕获总数（rng 非 NONE 且事件>100）: "
          f"{sum(1 for r in rows if r['valid'])} / {len(rows)} 个目录")
    for r in rows:
        flag = "（混流作废）" if r["mixed"] else ""
        print(f"  {r['name']}: round={r['rnd']} 事件={r['ev']} "
              f"source={r['source']} pair={r['pair']}({r['how']}) "
              f"{'有效' if r['valid'] else '无效'}{flag}")
    print(f"去重 (curRunId, curRoundNum) 对数 = {len(pairs)}: "
          f"{sorted(pairs)}")
    if unknown:
        print(f"无法归因 pair 的有效包: {unknown}")


def main() -> int:
    logging.basicConfig(level=logging.INFO,
                        format="%(asctime)s %(levelname)s %(message)s",
                        datefmt="%H:%M:%S")
    ap = argparse.ArgumentParser(description="无头捕获驱动器（历史界面内自动开战采集重放三元组）")
    ap.add_argument("--fights", type=int, default=3,
                    help="基础捕获场数（默认 3）")
    ap.add_argument("--diversity", type=int, default=0,
                    help="基础捕获后补充 N 场多样性取材：前 2 场同 run 换回合"
                         "（Build/NextRound），其后换相邻下一 run 条目")
    ap.add_argument("--probe", action="store_true",
                    help="只读检查（连接、节点定位、矩形读取），不点击")
    args = ap.parse_args()

    if args.probe:
        return probe()

    drv = CaptureDriver(fights=max(1, args.fights) if args.diversity == 0
                        else 0)
    try:
        drv.setup()
        if args.fights > 0:
            result = drv.run()
            print(f"\n完成 {result['fights_done']} 场基础捕获:")
            for p in result["completed"]:
                print(f"  {p}")
        if args.diversity > 0:
            result = drv.run_diversity(args.diversity)
            print(f"\n完成 {result['fights_done']} 场 diversity 捕获:")
            for p in result["completed"]:
                print(f"  {p}")
            report_stats(result["fights_done"])
        return 0
    except CaptureAborted as e:
        print(f"\n[终止] 已完成 {e.fights_done} 场；卡点: {e.blocker}")
        for p in drv.completed:
            print(f"  已完成: {p}")
        return 1
    finally:
        drv._stop.set()


if __name__ == "__main__":
    sys.exit(main())
