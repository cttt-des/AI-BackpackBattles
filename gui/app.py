"""
背包乱斗 AI — 原生 GUI 控制台应用
基于 tkinter，无需浏览器，点击即用

布局（2026-07-26 二次重构，落实用户 8 项需求）
--------------------------------------------------
* 左侧窄栏：游戏状态 + 控制按钮（2×3 网格，避免被裁切）+ 渲染模式切换。
  手动标定金币/HP/回合的面板已移除（结构性读取自动完成）。
* 右侧主区：
  - 背包摆盘（放大 · 仿游戏渲染：格子素材 Slot/FilledSlot + 物品贴图/染色）
  - 储物箱 / 商店在售：纯文字分区；商店物品显示价格。
  - 运行日志。

背包渲染（仿游戏：进程读状态 → GUI 复现）
  图层顺序（底→顶）：背包底框 → 背包(容器)贴图 → 格子素材(每个格子一张 FilledSlot) → 普通物品
    （格子叠在背包之上，便于分辨同一背包占用的不同格子）
  模式 A（贴图）：每个物品用游戏内贴图渲染，中文名标注；背包允许略超出格子(不变形)，普通物品严格不超出。
  模式 B（染色）：每个物品占用的每一格用同色半透明填充(stipple) + 居中文字（自动换行/字号），
                  相邻物品自动分配不同颜色；背包用贴图渲染。

  ┌─────────────── 标题栏 + 状态灯 ───────────────┐
  ├───────────┬──────────────────────────────────┤
  │  游戏状态 │  背包摆盘（放大 · 仿游戏渲染）      │
  │  控制按钮 ├──────────────┬───────────────────┤
  │  渲染模式 │  储物箱(文字) │  商店在售(文字+价格) │
  │           ├──────────────┴───────────────────┤
  │           │  运行日志                          │
  └───────────┴──────────────────────────────────┘
"""

import os
import sys
import json
import math
import time
import queue
import logging
import threading
from datetime import datetime
from collections import defaultdict
from pathlib import Path
from itertools import product

import tkinter as tk
from tkinter import ttk, messagebox, filedialog, font as tkfont

# 允许以脚本或模块方式运行
if not getattr(sys, "frozen", False):
    sys.path.insert(0, str(Path(__file__).parent.parent))

from gui.theme import COLORS, CATEGORY_COLORS, FONTS, FONT_FAMILY
from core.bot import BackpackBot
from core.paths import get_config_path, get_base_dir, get_resource_dir
from core.item_db import ItemDB
from core.window_manager import WindowManager

logger = logging.getLogger(__name__)

# 贴图渲染依赖 PIL；若运行环境缺失则退化为纯色块 + 文字。
try:
    from PIL import Image, ImageTk
    _HAS_PIL = True
except Exception:  # noqa: BLE001
    _HAS_PIL = False


class QueueLogHandler(logging.Handler):
    """把日志记录推入队列，供 GUI 主线程消费"""

    def __init__(self, log_queue):
        super().__init__()
        self.log_queue = log_queue

    def emit(self, record):
        try:
            msg = self.format(record)
            self.log_queue.put(("log", record.levelname.lower(), msg))
        except Exception:
            pass


# 渲染模式 B（染色）用的调色板（相邻物品不会同色，靠邻接图着色保证）
_PALETTE = [
    (242, 114, 84), (95, 201, 104), (97, 175, 239), (188, 140, 255),
    (235, 159, 57), (236, 99, 156), (110, 200, 190), (200, 170, 90),
    (150, 200, 120), (230, 120, 120), (120, 150, 230), (180, 180, 200),
    (160, 120, 200), (100, 190, 160), (210, 160, 90), (140, 210, 140),
]
# 背包空格底色（COLORS["grid_empty"] = #2a2f3a）
_BG_RGB = (0x2A, 0x2F, 0x3A)


class BackpackAIApp(tk.Tk):
    """背包乱斗 AI 主窗口"""

    GRID_ROWS = 7
    GRID_COLS = 9
    CELL = 52          # 每格像素（放大显示，便于观察；与游戏 80px 格子成比例）
    GAP = 4
    COLOR_ALPHA = 0.5   # 模式 B 半透明填充强度（不遮住后面的背包/格子素材）

    def __init__(self):
        super().__init__()
        self.title("背包乱斗 AI 控制台")
        self.configure(bg=COLORS["bg"])
        self.geometry("1360x900")
        self.minsize(1180, 800)

        # 运行时状态
        self.bot: BackpackBot | None = None
        self.bot_thread: threading.Thread | None = None
        self.ui_queue: queue.Queue = queue.Queue()
        self._initialized = False
        self._closing = False
        self._state_thread: threading.Thread | None = None
        self._heartbeat = time.time()  # 主线程存活心跳（看门狗用）
        self._last_live = None          # 最近一次读取到的物品快照（导出阵容用）
        self._last_round = None         # 最近一次读取到的回合（导出阵容用）

        # 物品资源库（贴图 + 中文名 + 占格形状 + 格子素材）
        self.item_db = ItemDB()
        self._img_cache: dict = {}      # sprite 路径 -> PIL.Image
        self._bp_refs: list = []        # 背包贴图 PhotoImage 引用（防 GC）
        self._cell_cache: dict = {}     # "empty"/"filled" -> PhotoImage

        self._setup_style()
        self._build_layout()
        self._bind_keys()

        self.after(100, self._process_queue)
        self._start_state_poller()
        self._start_exit_watchdog()

        self.protocol("WM_DELETE_WINDOW", self._on_close)
        if _HAS_PIL:
            self._log("info", "欢迎使用背包乱斗 AI 控制台。检测到游戏窗口后将自动连接（也可手动点击「初始化」）。")
        else:
            self._log("warning", "未检测到 PIL，贴图将退化为色块显示（请安装 Pillow 后重试）。")

        # 自动连接：启动后后台轮询，检测到游戏窗口即自动初始化
        self._auto_connect_attempts = 0
        self.after(600, self._auto_connect_tick)

    # ---------- 自动连接 ----------
    def _auto_connect_tick(self):
        """未连接状态下轮询游戏窗口，出现即自动初始化（无需手动点初始化）。"""
        if self._closing or self._initialized or (self.bot and self.bot.memory_reader):
            return
        self._auto_connect_attempts += 1
        # 轻量预检：窗口未出现则不创建 bot（避免无谓的句柄开销）
        try:
            w = self.bot.window_mgr.find_game_window() if self.bot \
                else WindowManager().find_game_window()
        except Exception:  # noqa: BLE001
            w = None
        if w is None:
            if self._auto_connect_attempts in (1, 3, 10):
                self._log("info", "自动连接：未检测到游戏窗口，持续等待中...")
            self.after(2500, self._auto_connect_tick)
            return
        self._log("info", f"自动连接：检测到游戏窗口 (PID={w.pid})，正在初始化...")
        self._on_init()

    # ---------- 样式 ----------
    def _setup_style(self):
        style = ttk.Style(self)
        try:
            style.theme_use("clam")
        except Exception:
            pass
        style.configure("TCombobox",
                        fieldbackground=COLORS["panel_light"],
                        background=COLORS["panel_light"],
                        foreground=COLORS["text"],
                        arrowcolor=COLORS["text"],
                        borderwidth=0)
        style.map("TCombobox",
                  fieldbackground=[("readonly", COLORS["panel_light"])],
                  foreground=[("readonly", COLORS["text"])])

    # ---------- 布局 ----------
    def _build_layout(self):
        header = tk.Frame(self, bg=COLORS["panel"], height=54)
        header.pack(fill="x", side="top")
        header.pack_propagate(False)

        tk.Label(header, text="背包乱斗 AI", font=FONTS["title"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left", padx=18)

        self.status_dot = tk.Canvas(header, width=14, height=14, bg=COLORS["panel"],
                                    highlightthickness=0)
        self.status_dot.pack(side="right", padx=(6, 18))
        self._dot = self.status_dot.create_oval(2, 2, 12, 12,
                                                fill=COLORS["text_dim"], outline="")
        self.status_text = tk.Label(header, text="未连接", font=FONTS["small"],
                                    bg=COLORS["panel"], fg=COLORS["text_dim"])
        self.status_text.pack(side="right")

        body = tk.Frame(self, bg=COLORS["bg"])
        body.pack(fill="both", expand=True, padx=10, pady=10)

        left = tk.Frame(body, bg=COLORS["bg"], width=370)
        left.pack(side="left", fill="y")
        left.pack_propagate(False)

        right = tk.Frame(body, bg=COLORS["bg"])
        right.pack(side="left", fill="both", expand=True, padx=(10, 0))

        self._build_stats(left)
        self._build_controls(left)
        self._build_backpack(right)
        self._build_storage_shop(right)
        self._build_log(right)

    def _build_stats(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="x", pady=(0, 8))

        tk.Label(panel, text="游戏状态", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(anchor="w", padx=12, pady=(10, 4))

        row = tk.Frame(panel, bg=COLORS["panel"])
        row.pack(fill="x", padx=8, pady=(0, 8))

        self.stat_vars = {}
        for key, label, color in [
            ("gold", "金币", COLORS["warning"]),
            ("hp", "生命", COLORS["danger"]),
            ("round", "回合", COLORS["accent"]),
        ]:
            cell = tk.Frame(row, bg=COLORS["panel_light"])
            cell.pack(side="left", expand=True, fill="both", padx=3)
            var = tk.StringVar(value="—")
            self.stat_vars[key] = var
            tk.Label(cell, textvariable=var, font=FONTS["stat_value"],
                     bg=COLORS["panel_light"], fg=color).pack(pady=(8, 0))
            tk.Label(cell, text=label, font=FONTS["stat_label"],
                     bg=COLORS["panel_light"], fg=COLORS["text_dim"]).pack(pady=(0, 8))

        info = tk.Frame(panel, bg=COLORS["panel"])
        info.pack(fill="x", padx=12, pady=(0, 8))
        self.phase_var = tk.StringVar(value="阶段: —")
        tk.Label(info, textvariable=self.phase_var, font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left")

    # ---------- 控制按钮（2×3 网格，避免被宽度裁切）----------
    def _build_controls(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="x", pady=(8, 0))

        tk.Label(panel, text="控制", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(anchor="w", padx=12, pady=(10, 4))

        # 策略选择
        top = tk.Frame(panel, bg=COLORS["panel"])
        top.pack(fill="x", padx=12, pady=(0, 6))
        tk.Label(top, text="AI 策略:", font=FONTS["body"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left")
        self.strategy_var = tk.StringVar(value="heuristic")
        combo = ttk.Combobox(top, textvariable=self.strategy_var, state="readonly",
                             values=["heuristic", "llm"], width=12)
        combo.pack(side="left", padx=(8, 0))

        # 渲染模式切换（请求 #8）
        mrow = tk.Frame(panel, bg=COLORS["panel"])
        mrow.pack(fill="x", padx=12, pady=(0, 6))
        tk.Label(mrow, text="背包渲染:", font=FONTS["body"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left")
        self.render_mode_var = tk.StringVar(value="sprite")
        mcombo = ttk.Combobox(mrow, textvariable=self.render_mode_var, state="readonly",
                              values=["sprite", "color"], width=12)
        mcombo.pack(side="left", padx=(8, 0))
        tk.Label(mrow, text="贴图 / 染色", font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="left", padx=(6, 0))

        # 按钮 2×3 网格
        btns = tk.Frame(panel, bg=COLORS["panel"])
        btns.pack(fill="x", padx=10, pady=(4, 6))
        specs = [
            ("init", "初始化", COLORS["accent"], self._on_init),
            ("start", "开始", COLORS["success"], self._on_start),
            ("pause", "暂停", COLORS["warning"], self._on_pause),
            ("step", "单步", COLORS["accent"], self._on_step),
            ("stop", "停止", COLORS["border"], self._on_stop),
            ("estop", "紧急停止", COLORS["danger"], self._on_emergency),
        ]
        self.buttons = {}
        for i, (key, label, color, cmd) in enumerate(specs):
            r, c = divmod(i, 3)
            b = tk.Button(btns, text=label, font=FONTS["button"], relief="flat",
                          bg=color, fg="#ffffff", cursor="hand2",
                          activebackground=color, activeforeground="#ffffff",
                          command=cmd, padx=6, pady=7)
            b.grid(row=r, column=c, padx=3, pady=3, sticky="nsew")
            btns.columnconfigure(c, weight=1)
            btns.rowconfigure(r, weight=1)
            self.buttons[key] = b

        # 导出阵容（整行按钮）：把当前读取到的摆盘保存为模拟器兼容的 JSON
        export_btn = tk.Button(
            panel, text="导出阵容 (模拟器 JSON)", font=FONTS["button"], relief="flat",
            bg=COLORS["panel_light"], fg=COLORS["text"], cursor="hand2",
            activebackground=COLORS["border"], activeforeground=COLORS["text"],
            command=self._on_export_lineup, padx=6, pady=8)
        export_btn.pack(fill="x", padx=13, pady=(0, 8))
        self.buttons["export"] = export_btn

        # 历史记录导出：从游戏 history.db（BuildHistoryDB）导出任一回合摆盘
        history_btn = tk.Button(
            panel, text="从历史记录导出阵容", font=FONTS["button"], relief="flat",
            bg=COLORS["panel_light"], fg=COLORS["text"], cursor="hand2",
            activebackground=COLORS["border"], activeforeground=COLORS["text"],
            command=self._on_export_history, padx=6, pady=8)
        history_btn.pack(fill="x", padx=13, pady=(0, 12))
        self.buttons["history"] = history_btn

        self._set_buttons_state(running=False, initialized=False)

    # ---------- 背包大图（仿游戏：格子素材 + 物品）----------
    def _build_backpack(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="both", expand=True)

        head = tk.Frame(panel, bg=COLORS["panel"])
        head.pack(fill="x", padx=12, pady=(10, 4))
        tk.Label(head, text="背包摆盘  9×7", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left")
        self.bp_count_var = tk.StringVar(value="物品 0")
        tk.Label(head, textvariable=self.bp_count_var, font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["accent"]).pack(side="right")

        cw = self.GRID_COLS * (self.CELL + self.GAP) + self.GAP
        ch = self.GRID_ROWS * (self.CELL + self.GAP) + self.GAP
        self.grid_canvas = tk.Canvas(panel, width=cw, height=ch,
                                     bg=COLORS["panel"], highlightthickness=0)
        self.grid_canvas.pack(padx=12, pady=(0, 6))

        self.legend = tk.Label(panel, text="", font=FONTS["small"],
                               bg=COLORS["panel"], fg=COLORS["text_dim"])
        self.legend.pack(anchor="w", padx=12, pady=(0, 6))

    def _cell_img(self, kind: str):
        """缓存的格子素材 PhotoImage（Slot / FilledSlot），尺寸对齐 CELL。"""
        if kind in self._cell_cache:
            return self._cell_cache[kind]
        path = (self.item_db.cell_empty_path() if kind == "empty"
                else self.item_db.cell_filled_path())
        if path and _HAS_PIL:
            try:
                img = Image.open(path).convert("RGBA").resize(
                    (self.CELL, self.CELL), Image.LANCZOS)
                photo = ImageTk.PhotoImage(img)
                self._cell_cache[kind] = photo
                return photo
            except Exception:
                pass
        self._cell_cache[kind] = None
        return None

    def _draw_backpack(self, items):
        """仿游戏渲染，严格分层（底→顶）：背包底框 → 背包(容器) → 格子素材 → 普通物品。

        渲染顺序即 z 序：
          1) 背包底框（每个格子底色）
          2) 背包(容器)贴图 —— 放在最底层，使其上能叠出它占用的每一个格子
          3) 格子素材(FilledSlot) —— 渲染在容器之上，所有占用格均显示，药水的多层渲染为正常效果
          4) 普通物品（贴图 / 半透明染色） —— 显示在最上层
        """
        self._bp_refs = []
        self.grid_canvas.delete("all")

        # 收集被占用的格子
        occupied = set()
        for it in items:
            for (r, c) in (it.get("cells") or []):
                if 0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS:
                    occupied.add((r, c))

        # 图层 1：背包底框（所有格子底色）
        self._draw_base_layer()

        mode = self.render_mode_var.get()
        bags = [it for it in items if it.get("is_bag")]
        regulars = [it for it in items if not it.get("is_bag")]

        # 图层 2：背包(容器)贴图 —— 画在格子之下
        for it in bags:
            self._draw_bag(it, mode)

        # 图层 3：格子素材 —— 所有被占用的格子画 FilledSlot（含药水正常多层渲染）
        self._draw_cell_layer(occupied)

        # 图层 4：普通物品
        if mode == "color":
            self.legend.configure(text="染色模式：背包用贴图、物品用半透明同色+文字（相邻不同色）")
            self._draw_items_color(regulars)
        else:
            self.legend.configure(text="贴图模式：游戏内资源渲染（按旋转对齐网格）")
            self._draw_items_sprite(regulars)

    def _draw_base_layer(self):
        """背包底框：所有格子的底色框（最底层）。"""
        for r in range(self.GRID_ROWS):
            for c in range(self.GRID_COLS):
                x0 = self.GAP + c * (self.CELL + self.GAP)
                y0 = self.GAP + r * (self.CELL + self.GAP)
                x1 = x0 + self.CELL
                y1 = y0 + self.CELL
                self.grid_canvas.create_rectangle(
                    x0, y0, x1, y1, fill=COLORS["grid_empty"],
                    outline=COLORS["grid_border"])

    def _draw_cell_layer(self, occupied):
        """格子素材：仅对「被物品占用的格子」渲染 FilledSlot；空格子不渲染。
        渲染在背包(容器)之上，便于分辨同一背包占用的不同格子。"""
        filled = self._cell_img("filled")
        if not filled:
            return
        for (r, c) in occupied:
            if not (0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS):
                continue
            x0 = self.GAP + c * (self.CELL + self.GAP)
            y0 = self.GAP + r * (self.CELL + self.GAP)
            self.grid_canvas.create_image(
                x0 + self.CELL / 2, y0 + self.CELL / 2, image=filled)

    def _draw_bag(self, it, mode):
        """绘制背包(容器)：贴图渲染，允许略微超出格子(不变形)；小标签放底部。"""
        reg = self._item_region(it)
        if not reg:
            return
        cells, x0, y0, bw, bh = reg
        # 背包允许稍微超出格子（仍等比不变形），普通物品 overflow_px=0 严格不超出
        self._draw_sprite_scaled(it, x0, y0, bw, bh,
                                 overflow_px=max(8, int(self.CELL * 0.3)))
        self._draw_name_label(x0, y0, bw, bh, it.get("zh") or it["name"],
                              bold=(mode == "color"), pos="bottom")

    def _item_region(self, it):
        cells = [(r, c) for (r, c) in (it.get("cells") or [])
                 if 0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS]
        if not cells:
            a = it.get("row"), it.get("col")
            if a and 0 <= a[0] < self.GRID_ROWS and 0 <= a[1] < self.GRID_COLS:
                cells = [a]
            else:
                return None
        rs = [r for r, _ in cells]
        cs = [c for _, c in cells]
        minr, maxr = min(rs), max(rs)
        minc, maxc = min(cs), max(cs)
        x0 = self.GAP + minc * (self.CELL + self.GAP)
        y0 = self.GAP + minr * (self.CELL + self.GAP)
        bw = (maxc - minc + 1) * self.CELL + (maxc - minc) * self.GAP
        bh = (maxr - minr + 1) * self.CELL + (maxr - minr) * self.GAP
        return cells, x0, y0, bw, bh

    def _draw_sprite_scaled(self, it, x0, y0, bw, bh, overflow_px=0):
        """绘制单个物品的贴图：按内存 rotation 旋转、等比缩放(contain，不变形)、居中。"""
        sp = self.item_db.sprite_path(it["name"])
        if not (sp and sp.exists() and _HAS_PIL):
            self._draw_fallback_tile(x0, y0, bw, bh, it.get("is_bag"), name=it.get("zh") or it["name"])
            return
        img = self._load_image(sp)
        if img is None:
            self._draw_fallback_tile(x0, y0, bw, bh, it.get("is_bag"), name=it.get("zh") or it["name"])
            return
        rot = it.get("rotation") or 0.0
        if abs(rot) > 1e-4:
            # 负号：与 Godot 顺时针旋转一致（PIL rotate 默认逆时针）
            img = img.rotate(-math.degrees(rot), expand=True, resample=Image.BICUBIC)
            bb = img.getbbox()
            if bb:
                img = img.crop(bb)
        # 等比缩放（contain，不变形）；overflow 时允许稍微超出格子
        box_w = bw + overflow_px * 2
        box_h = bh + overflow_px * 2
        iw, ih = img.size
        if iw > 0 and ih > 0:
            scale = min(box_w / iw, box_h / ih)
            if scale > 0 and abs(scale - 1.0) > 1e-3:
                nw = max(1, int(round(iw * scale)))
                nh = max(1, int(round(ih * scale)))
                img = img.resize((nw, nh), Image.LANCZOS)
        photo = ImageTk.PhotoImage(img)
        self._bp_refs.append(photo)
        # 始终以原包围盒中心为锚点居中（overflow 时向外略微溢出，仍不变形）
        self.grid_canvas.create_image(x0 + bw / 2, y0 + bh / 2, image=photo)

    def _draw_items_sprite(self, items):
        for it in items:
            reg = self._item_region(it)
            if not reg:
                continue
            cells, x0, y0, bw, bh = reg
            # 贴图（旋转 + 对齐网格，严格在格子内）；不绘制占用格边框高亮
            self._draw_sprite_scaled(it, x0, y0, bw, bh)
            self._draw_name_label(x0, y0, bw, bh, it.get("zh") or it["name"])

    def _draw_items_color(self, items):
        colors = self._assign_colors(items)
        for it in items:
            reg = self._item_region(it)
            if not reg:
                continue
            cells, x0, y0, bw, bh = reg
            rgb = _PALETTE[colors.get(it["name"], 0)]
            fill_hex = "#%02x%02x%02x" % rgb
            stroke = self._blend(_BG_RGB, rgb, 0.85)
            # 每个占用的格子：半透明同色填充(stipple 让底下的背包/格子素材透出) + 描边
            for (r, c) in cells:
                cx0 = self.GAP + c * (self.CELL + self.GAP)
                cy0 = self.GAP + r * (self.CELL + self.GAP)
                self.grid_canvas.create_rectangle(
                    cx0 + 1, cy0 + 1, cx0 + self.CELL - 1, cy0 + self.CELL - 1,
                    fill=fill_hex, stipple="gray50",
                    outline=stroke, width=1)
            # 居中文字（自动换行/字号）
            zh = it.get("zh") or it["name"]
            self._draw_name_label(x0, y0, bw, bh, zh, bold=True)

    def _draw_name_label(self, x0, y0, bw, bh, zh, bold=False, pos="center"):
        label = zh[:10]
        size, lines = self._fit_text(label, bw - 6, bh - 6, base=7)
        line_h = size + 2
        total_h = line_h * len(lines)
        if pos == "bottom":
            ty = y0 + bh - total_h / 2 - 2
        else:
            ty = y0 + bh / 2 - total_h / 2 + line_h / 2
        # 半透明底提高可读性
        self.grid_canvas.create_rectangle(
            x0 + 2, ty - line_h / 2 - 1, x0 + bw - 2, ty + total_h / 2 + 1,
            fill=COLORS["bg"], outline="", stipple="gray50")
        for ln in lines:
            self.grid_canvas.create_text(x0 + bw / 2, ty, text=ln,
                                         fill=COLORS["text"],
                                         font=(FONT_FAMILY, size, "bold" if bold else "normal"),
                                         anchor="center")
            ty += line_h

    def _draw_fallback_tile(self, x0, y0, bw, bh, is_bag, name=""):
        """无贴图时的后备渲染：彩色填充矩形 + 物品名首字符。"""
        color = CATEGORY_COLORS["bag"] if is_bag else CATEGORY_COLORS["unknown"]
        # 填充背景
        self.grid_canvas.create_rectangle(x0 + 1, y0 + 1, x0 + bw - 1, y0 + bh - 1,
                                          fill=color, outline=COLORS["grid_border"], width=1)
        # 显示物品名缩写（中文前2字或英文首字母）
        if name:
            short = name[:2] if any('\u4e00' <= c <= '\u9fff' for c in name[:2]) else name[0].upper()
            cx, cy = x0 + bw // 2, y0 + bh // 2
            self.grid_canvas.create_text(cx, cy, text=short, fill="#ffffff",
                                         font=("Segoe UI", max(8, bw // 3), "bold"))

    # ---------- 邻接着色（保证相邻物品不同色）----------
    def _assign_colors(self, items):
        occ = {}
        for it in items:
            for (r, c) in (it.get("cells") or []):
                if 0 <= r < self.GRID_ROWS and 0 <= c < self.GRID_COLS:
                    occ[(r, c)] = it["name"]
        neigh = defaultdict(set)
        for (r, c), nm in occ.items():
            for dr, dc in product((-1, 0, 1), (-1, 0, 1)):
                if dr == 0 and dc == 0:
                    continue
                o = occ.get((r + dr, c + dc))
                if o and o != nm:
                    neigh[nm].add(o)
                    neigh[o].add(nm)
        assigned = {}
        for nm in sorted(neigh, key=lambda n: -len(neigh[n])):
            used = {assigned.get(x) for x in neigh[nm] if x in assigned}
            for i in range(len(_PALETTE)):
                if i not in used:
                    assigned[nm] = i
                    break
            else:
                assigned[nm] = 0
        return assigned

    @staticmethod
    def _blend(bg, fg, a):
        return "#%02x%02x%02x" % tuple(
            int(bg[i] * (1 - a) + fg[i] * a) for i in range(3))

    # ---------- 自动字号 / 换行 ----------
    def _fit_text(self, text, box_w, box_h, base=7):
        for size in range(base, 6, -1):
            f = tkfont.Font(family=FONT_FAMILY, size=size)
            lines, cur = [], ""
            for ch in text:
                if f.measure(cur + ch) > box_w * 0.94 and cur:
                    lines.append(cur)
                    cur = ch
                else:
                    cur += ch
            if cur:
                lines.append(cur)
            if lines and len(lines) * (size + 2) <= box_h * 0.94:
                return size, lines
        # 兜底：最小字号，强制换行
        f = tkfont.Font(family=FONT_FAMILY, size=7)
        lines, cur = [], ""
        for ch in text:
            if f.measure(cur + ch) > box_w * 0.94 and cur:
                lines.append(cur)
                cur = ch
            else:
                cur += ch
        if cur:
            lines.append(cur)
        return 7, lines

    def _load_image(self, path: Path):
        if not _HAS_PIL:
            return None
        p = str(path)
        img = self._img_cache.get(p)
        if img is None:
            try:
                img = Image.open(path).convert("RGBA")
                self._img_cache[p] = img
            except Exception:
                return None
        return img

    # ---------- 储物箱 / 商店（纯文字分区；商店显示价格）----------
    def _build_storage_shop(self, parent):
        # 专门区域：固定高度 + 强调边框，确保不会被背包/日志挤压到不可见
        row = tk.Frame(parent, bg=COLORS["bg"], height=200)
        row.pack(fill="x", pady=(0, 6))
        row.pack_propagate(False)

        self.storage_text, self.storage_count = self._make_text_panel(
            row, "储物箱", COLORS["warning"])
        self.shop_text, self.shop_count = self._make_text_panel(
            row, "商店在售", COLORS["success"])

    def _make_text_panel(self, parent, title, accent):
        panel = tk.Frame(parent, bg=COLORS["panel"],
                         highlightbackground=accent, highlightthickness=1)
        panel.pack(side="left", fill="both", expand=True, padx=(0, 6))
        panel.pack_propagate(False)

        head = tk.Frame(panel, bg=COLORS["panel"])
        head.pack(fill="x", padx=12, pady=(8, 4))
        tk.Label(head, text=title, font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=accent).pack(side="left")
        count_var = tk.StringVar(value="0")
        tk.Label(head, textvariable=count_var, font=FONTS["small"],
                 bg=COLORS["panel"], fg=COLORS["text_dim"]).pack(side="right")

        wrap = tk.Frame(panel, bg=COLORS["border"])
        wrap.pack(fill="both", expand=True, padx=12, pady=(0, 8))
        txt = tk.Text(wrap, bg=COLORS["bg"], fg=COLORS["text"],
                      font=FONTS["body"], relief="flat", wrap="word",
                      insertbackground=COLORS["bg"], padx=8, pady=6,
                      state="disabled")
        scroll = tk.Scrollbar(wrap, command=txt.yview)
        txt.configure(yscrollcommand=scroll.set)
        scroll.pack(side="right", fill="y")
        txt.pack(side="left", fill="both", expand=True)
        txt.tag_config("bag", foreground=COLORS["accent"])
        txt.tag_config("dim", foreground=COLORS["text_dim"])
        return txt, count_var

    def _refresh_text_panel(self, txt, items, count_var):
        txt.configure(state="normal")
        txt.delete("1.0", "end")
        if not items:
            txt.insert("end", "（暂无物品）\n", "dim")
            txt.configure(state="disabled")
            count_var.set("0")
            return
        for it in items:
            zh = it.get("zh") or it["name"]
            line = zh
            if it.get("is_bag"):
                line += "  [容器]"
            txt.insert("end", line + "\n")
        txt.configure(state="disabled")
        count_var.set(str(len(items)))

    # ---------- 日志 ----------
    def _build_log(self, parent):
        panel = tk.Frame(parent, bg=COLORS["panel"])
        panel.pack(fill="both", expand=True)

        bar = tk.Frame(panel, bg=COLORS["panel"])
        bar.pack(fill="x", padx=12, pady=(10, 4))
        tk.Label(bar, text="运行日志", font=FONTS["subtitle"],
                 bg=COLORS["panel"], fg=COLORS["text"]).pack(side="left")
        tk.Button(bar, text="清空", font=FONTS["small"], relief="flat",
                  bg=COLORS["panel_light"], fg=COLORS["text_dim"],
                  activebackground=COLORS["border"], activeforeground=COLORS["text"],
                  cursor="hand2", command=self._clear_log).pack(side="right")

        wrap = tk.Frame(panel, bg=COLORS["border"])
        wrap.pack(fill="both", expand=True, padx=12, pady=(0, 12))
        self.log_text = tk.Text(wrap, bg=COLORS["bg"], fg=COLORS["text"],
                                font=FONTS["mono"], relief="flat", wrap="word",
                                insertbackground=COLORS["text"], padx=8, pady=6,
                                state="disabled")
        scroll = tk.Scrollbar(wrap, command=self.log_text.yview)
        self.log_text.configure(yscrollcommand=scroll.set)
        scroll.pack(side="right", fill="y")
        self.log_text.pack(side="left", fill="both", expand=True)

        self.log_text.tag_config("info", foreground=COLORS["text"])
        self.log_text.tag_config("warning", foreground=COLORS["warning"])
        self.log_text.tag_config("error", foreground=COLORS["danger"])
        self.log_text.tag_config("debug", foreground=COLORS["text_dim"])
        self.log_text.tag_config("success", foreground=COLORS["success"])

    # ---------- 按钮状态 ----------
    def _set_buttons_state(self, running: bool, initialized: bool):
        def en(b, ok):
            b.configure(state="normal" if ok else "disabled")
        en(self.buttons["init"], not running)
        en(self.buttons["start"], initialized and not running)
        en(self.buttons["pause"], running)
        en(self.buttons["step"], initialized and not running)
        en(self.buttons["stop"], running)
        en(self.buttons["estop"], True)

    def _set_status(self, text: str, color: str):
        self.status_text.configure(text=text, fg=color)
        self.status_dot.itemconfig(self._dot, fill=color)

    # ---------- 控制回调 ----------
    def _on_init(self):
        # bot 构造放主线程（读取本地 config.yaml，极快），出错可立即弹窗
        if self.bot is None:
            try:
                self.bot = BackpackBot(get_config_path())
            except Exception as e:
                messagebox.showerror("错误", f"创建机器人失败:\n{e}")
                return
        self._apply_strategy()

        self._set_status("初始化中...", COLORS["warning"])
        self._log("info", "开始初始化...")

        def worker():
            try:
                ok = self.bot.initialize()
                if ok and not self.bot.needs_auto_calibration:
                    self.bot.scan_memory_values()
                self.ui_queue.put(("init_done", ok, None))
            except Exception as e:
                import traceback
                self.ui_queue.put(("init_done", False, traceback.format_exc()))

        threading.Thread(target=worker, daemon=True).start()

    def _apply_strategy(self):
        from core.ai_interface import HeuristicStrategy, LLMStrategy
        if not self.bot:
            return
        cfg = self.bot.config.get("ai", {})
        if self.strategy_var.get() == "llm":
            self.bot.strategy = LLMStrategy(cfg)
        else:
            self.bot.strategy = HeuristicStrategy(cfg)

    def _on_start(self):
        if not self.bot or not self._initialized:
            messagebox.showwarning("提示", "请先初始化")
            return
        if self.bot_thread and self.bot_thread.is_alive():
            return
        self._apply_strategy()
        self.bot.step_mode = False
        self.bot.paused = False

        def worker():
            try:
                self.bot.start()
            except Exception as e:
                import traceback
                self.ui_queue.put(("log", "error", traceback.format_exc()))
            finally:
                self.ui_queue.put(("bot_stopped", None, None))

        self.bot_thread = threading.Thread(target=worker, daemon=True)
        self.bot_thread.start()
        self._set_status("运行中", COLORS["success"])
        self._set_buttons_state(running=True, initialized=True)

    def _on_pause(self):
        if not self.bot:
            return
        if self.bot.paused:
            self.bot.resume()
            self.buttons["pause"].configure(text="暂停")
            self._set_status("运行中", COLORS["success"])
        else:
            self.bot.pause()
            self.buttons["pause"].configure(text="继续")
            self._set_status("已暂停", COLORS["warning"])

    def _toggle_pause(self):
        if self.bot and self.bot.running:
            self._on_pause()

    def _on_step(self):
        if not self.bot or not self._initialized:
            messagebox.showwarning("提示", "请先初始化")
            return
        if self.bot_thread and self.bot_thread.is_alive():
            self._log("warning", "机器人正在运行，无法单步")
            return
        self._apply_strategy()
        self._log("info", "执行单步...")

        def worker():
            try:
                self.bot.running = True
                self.bot._stop_event.clear()
                self.bot.run_round()
            except Exception as e:
                import traceback
                self.ui_queue.put(("log", "error", traceback.format_exc()))
            finally:
                self.bot.running = False
                self.ui_queue.put(("bot_stopped", None, None))

        self.bot_thread = threading.Thread(target=worker, daemon=True)
        self.bot_thread.start()
        self._set_status("单步执行", COLORS["accent"])

    def _on_stop(self):
        if self.bot:
            self.bot.stop()
        self._set_status("已停止", COLORS["text_dim"])
        self._set_buttons_state(running=False, initialized=self._initialized)
        self.buttons["pause"].configure(text="暂停")

    def _on_emergency(self):
        if self.bot:
            self.bot.stop()
        try:
            import pyautogui
            pyautogui.mouseUp()
        except Exception:
            pass
        self._set_status("紧急停止", COLORS["danger"])
        self._set_buttons_state(running=False, initialized=self._initialized)
        self.buttons["pause"].configure(text="暂停")
        self._log("warning", "⚠ 紧急停止已触发")

    # ---------- 导出阵容（模拟器兼容 JSON）----------
    def _sim_db_names(self):
        """加载战斗模拟器 items_db.json 的物品/角色名集合（用于导出校验）。

        开发模式: <项目根>/simulator/items_db.json
        exe 模式: _MEIPASS/simulator/items_db.json（打包时 --add-data 带入）
        加载失败时返回 (None, None)，导出照常进行、只是跳过校验。
        """
        for base in (get_resource_dir(), get_base_dir()):
            p = base / "assets" / "items_db_sim.json"
            try:
                if p.exists():
                    with open(p, "r", encoding="utf-8") as f:
                        db = json.load(f)
                    return set(db.get("items", {})), set(db.get("characters", {}))
            except Exception:
                continue
        return None, None

    def _sim_char_db(self):
        """加载战斗模拟器 characters.json 的角色库（用于导出 class_modifiers）。

        开发模式: <项目根>/assets/characters.json
        exe 模式: _MEIPASS/assets/characters.json（打包时 --add-data 带入）
        加载失败时返回 None，导出时用默认值兜底。
        """
        for base in (get_resource_dir(), get_base_dir()):
            p = base / "assets" / "characters.json"
            try:
                if p.exists():
                    with open(p, "r", encoding="utf-8") as f:
                        db = json.load(f)
                    return db.get("characters", db)
            except Exception:
                continue
        return None

    def _on_export_lineup(self):
        """把当前读取到的背包摆盘导出为战斗模拟器 v4 阵容 JSON（简洁平铺格式）。

        对齐 simulator/lineup.py 的 v4 格式：
          - version = 4
          - name: 阵容名（meta 拍平）
          - character: 职业名字符串
          - round: 当前回合
          - grid: [rows, cols]
          - items: 平铺数组；物品与承载背包的关系用 `in`（袋子的数组下标）显式表达；
            条目字段 id / at:[row,col] / r:旋转 / in / gems（宝石 id 字符串数组）
          - storage / unknown_items 可选
        """
        live = self._last_live
        if not live or not live.get("backpack"):
            messagebox.showwarning(
                "提示", "当前没有读取到背包物品。\n请先初始化并等待摆盘数据出现后再导出。")
            return

        known_items, known_chars = self._sim_db_names()

        items_out = []
        unknown = []

        def item_entry(it, bag_index=None):
            """生成单个物品的 v4 平铺条目；袋内物品带 `in` 指向承载袋下标。"""
            cells = [(r, c) for (r, c) in (it.get("cells") or [])]
            if cells:
                row = min(r for r, _ in cells)
                col = min(c for _, c in cells)
            else:
                row = it.get("row", 0) or 0
                col = it.get("col", 0) or 0
            name = it.get("name", "")
            entry = {
                "id": name,
                "at": [int(row), int(col)],
                "r": int(round(it.get("rotation", 0.0) * 180 / 3.14159 / 90) * 90) % 360,
            }
            if bag_index is not None:
                entry["in"] = bag_index
            gems = [g.get("id") for g in (it.get("gems") or []) if g.get("id")]
            if gems:
                entry["gems"] = gems
            items_out.append(entry)
            if known_items is not None and name not in known_items:
                unknown.append(name)
            # 袋内物品递归：其 `in` 指向刚登记的袋子下标
            sub_index = len(items_out) - 1
            for sub in (it.get("contents") or []):
                item_entry(sub, bag_index=sub_index)

        for it in live.get("backpack", []):
            item_entry(it)

        character = "Adventurer"
        # 优先读取游戏内真实职业（Game.curClass → Classes 枚举名）
        if self.bot is not None:
            ch = self.bot.read_character()
            if ch:
                character = ch
        if known_chars is not None and character not in known_chars:
            character = next(iter(known_chars), character)

        data = {
            "version": 4,
            "name": "实时导出阵容",
            "character": character,
            "round": self._last_round if self._last_round is not None else 1,
            "grid": [10, 10],
            "items": items_out,
            "storage": [],
        }
        if unknown:
            data["unknown_items"] = sorted(set(unknown))

        default_name = datetime.now().strftime("lineup_%Y%m%d_%H%M%S.json")
        path = filedialog.asksaveasfilename(
            title="保存阵容 JSON（战斗模拟器输入格式）",
            defaultextension=".json",
            initialfile=default_name,
            initialdir=str(get_base_dir()),
            filetypes=[("JSON 文件", "*.json"), ("所有文件", "*.*")],
        )
        if not path:
            return
        try:
            with open(path, "w", encoding="utf-8") as f:
                json.dump(data, f, ensure_ascii=False, indent=2)
        except Exception as e:  # noqa: BLE001
            messagebox.showerror("错误", f"保存失败:\n{e}")
            return

        self._log("success", f"✓ 已导出阵容（{len(items_out)} 件物品，职业 {character}）→ {path}")
        if unknown:
            self._log("warning",
                      "⚠ 以下物品暂未收录进模拟器物品库，模拟前需在 items_db.json 中补充: "
                      + ", ".join(sorted(set(unknown))))
        self._log("info",
                  "用法: python -m simulator.simulate 本文件.json 对手阵容.json")

    # ---------- 历史记录导出 ----------
    def _on_export_history(self):
        """从游戏 history.db 导出历史回合摆盘为 v4 阵容 JSON。

        BuildHistoryDB（SQLite）里每回合的 buildInfo 位流按
        RunData.deserializeStream 解码；物品索引映射优先用活体 ItemBook
        （见 core/build_history.live_item_index_map）。
        """
        from core import build_history as bh

        # 活体刷新映射（游戏连接时索引表与游戏版本严格一致）
        if self.bot is not None and self.bot.godot_reader is not None \
                and self.bot.godot_reader.is_ready() and self.bot.memory_reader:
            try:
                m = bh.live_item_index_map(self.bot.godot_reader,
                                           self.bot.memory_reader)
                if m:
                    self._log("info",
                              f"已刷新物品索引映射（{len(m['index_to_name'])} 项，live）")
            except Exception as e:  # noqa: BLE001
                self._log("warning", f"活体索引刷新失败（将用缓存映射）: {e}")

        db_path = bh.find_history_db()
        if not db_path:
            messagebox.showwarning(
                "提示", "未找到 history.db。\n请先在游戏里至少完成一个回合（历史记录才有数据）。")
            return

        try:
            runs = bh.list_runs(db_path)
        except Exception as e:  # noqa: BLE001
            messagebox.showerror("错误", f"读取历史数据库失败:\n{e}")
            return
        if not runs:
            messagebox.showwarning("提示", "历史数据库为空。")
            return

        dlg = tk.Toplevel(self)
        dlg.title("从历史记录导出阵容")
        dlg.configure(bg=COLORS["bg"])
        dlg.geometry("900x680")
        dlg.minsize(760, 560)
        dlg.transient(self)

        def _listbox_with_scroll(parent, height=14):
            """带竖向滚动条的 Listbox 容器。"""
            box = tk.Frame(parent, bg=COLORS["bg"])
            box.pack(fill="both", expand=True)
            lb = tk.Listbox(box, font=FONTS["small"], height=height,
                            bg=COLORS["panel_light"], fg=COLORS["text"],
                            selectbackground=COLORS["accent"],
                            exportselection=False)
            sb = tk.Scrollbar(box, orient="vertical", command=lb.yview,
                              troughcolor=COLORS["panel"], bg=COLORS["panel"])
            lb.configure(yscrollcommand=sb.set)
            lb.pack(side="left", fill="both", expand=True)
            sb.pack(side="right", fill="y")
            return lb

        tk.Label(dlg, text="选择 Run（对局）", font=FONTS["small"],
                 bg=COLORS["bg"], fg=COLORS["text"]).pack(anchor="w", padx=10,
                                                          pady=(8, 2))
        run_lb = _listbox_with_scroll(dlg, height=14)

        tk.Label(dlg, text="选择回合（每回合结束时的摆盘）", font=FONTS["small"],
                 bg=COLORS["bg"], fg=COLORS["text"]).pack(anchor="w", padx=10,
                                                          pady=(8, 2))
        round_lb = _listbox_with_scroll(dlg, height=14)

        # 阵容名称（可自定义；默认名随所选 Run/回合联动）
        tk.Label(dlg, text="阵容名称", font=FONTS["small"],
                 bg=COLORS["bg"], fg=COLORS["text"]).pack(anchor="w", padx=10,
                                                          pady=(8, 2))
        name_var = tk.StringVar(value="")
        name_entry = tk.Entry(dlg, textvariable=name_var, font=FONTS["small"],
                              bg=COLORS["panel_light"], fg=COLORS["text"],
                              insertbackground=COLORS["text"], relief="flat")
        name_entry.pack(fill="x", padx=10)

        rounds_cache: list = []

        def load_rounds(_ev=None):
            sel = run_lb.curselection()
            if not sel:
                return
            run = runs[sel[0]]
            round_lb.delete(0, "end")
            rounds_cache.clear()
            try:
                rounds_cache.extend(bh.list_rounds(db_path, run["run_id"]))
            except Exception as e:  # noqa: BLE001
                self._log("error", f"读取回合失败: {e}")
                return
            for r in rounds_cache:
                res = {0: "胜", 1: "败", 2: "平"}.get(r["result"], f"r{r['result']}")
                # roundID 即游戏回合号（1..18，BuildHistoryDB addRoundEntry）
                round_lb.insert(
                    "end", f"第 {r['round_id']} 回合  [{res}]  "
                           f"血量 {r['health']}  体力 {r['stamina']}")
            if rounds_cache:
                _sync_default_name()

        def _sync_default_name(*_a):
            sel_r = run_lb.curselection()
            sel_rd = round_lb.curselection()
            # 只在用户未手动改名时联动默认名（记录是否编辑过）
            if getattr(name_entry, "_user_edited", False):
                return
            if sel_r and sel_rd:
                run = runs[sel_r[0]]
                rd = rounds_cache[sel_rd[0]]
                name_var.set(f"历史 Run{run['run_id']} 第{rd['round_id']}回合")

        def _mark_edited(_ev=None):
            name_entry._user_edited = True

        name_entry.bind("<KeyRelease>", _mark_edited)

        def do_export():
            sel_r = run_lb.curselection()
            sel_rd = round_lb.curselection()
            if not sel_r or not sel_rd:
                messagebox.showinfo("提示", "请先选择 Run 与回合。", parent=dlg)
                return
            run = runs[sel_r[0]]
            rd = rounds_cache[sel_rd[0]]
            lineup_name = name_var.get().strip() or \
                f"历史 Run{run['run_id']} 第{rd['round_id']}回合"
            default_name = lineup_name + ".json"
            path = filedialog.asksaveasfilename(
                title="保存历史阵容 JSON", defaultextension=".json",
                initialfile=default_name,
                initialdir=str(get_base_dir()),
                filetypes=[("JSON 文件", "*.json")], parent=dlg)
            if not path:
                return
            try:
                data = bh.export_round(run["run_id"], rd["round_id"], path,
                                       db_path=db_path, name=lineup_name)
            except Exception as e:  # noqa: BLE001
                messagebox.showerror("错误", f"导出失败:\n{e}", parent=dlg)
                return
            self._log("success",
                      f"✓ 已导出历史阵容「{lineup_name}」（Run{run['run_id']} "
                      f"第{rd['round_id']}回合，{len(data['items'])} 件物品）→ {path}")
            self._log("info", "用法: python -m simulator.simulate 本文件.json 对手阵容.json")
            dlg.destroy()

        run_lb.bind("<<ListboxSelect>>", load_rounds)
        round_lb.bind("<<ListboxSelect>>", _sync_default_name)
        for run in runs:
            run_lb.insert("end", f"Run {run['run_id']}  [{run['character']}]  "
                                 f"{run['num_rounds']} 回合  "
                                 f"{datetime.fromtimestamp(run['time']).strftime('%m-%d %H:%M')}")

        # 底部确认区（固定可见）
        btns = tk.Frame(dlg, bg=COLORS["bg"])
        btns.pack(fill="x", padx=10, pady=(4, 10), side="bottom")
        tk.Button(btns, text="确 认 导 出", font=FONTS["button"], relief="flat",
                  bg=COLORS["accent"], fg="#ffffff", command=do_export,
                  padx=18, pady=8, cursor="hand2").pack(side="right")
        tk.Button(btns, text="关闭", font=FONTS["button"], relief="flat",
                  bg=COLORS["panel_light"], fg=COLORS["text"],
                  command=dlg.destroy, padx=14, pady=8,
                  cursor="hand2").pack(side="right", padx=(0, 8))

    # ---------- 日志 ----------
    def _log(self, level: str, msg: str):
        self.log_text.configure(state="normal")
        self.log_text.insert("end", msg + "\n", level)
        self.log_text.see("end")
        self.log_text.configure(state="disabled")

    def _clear_log(self):
        self.log_text.configure(state="normal")
        self.log_text.delete("1.0", "end")
        self.log_text.configure(state="disabled")

    # ---------- 队列消费 ----------
    def _process_queue(self):
        """消费 UI 消息队列。

        关键优化：state 消息只处理最新的一条，丢弃中间的积压。
        否则重绘太频繁会导致主线程长时间卡在 _draw_backpack 上，UI 失去响应。
        """
        self._heartbeat = time.time()  # 主线程存活心跳（看门狗用）
        latest_state = None
        try:
            while True:
                kind, a, b = self.ui_queue.get_nowait()
                if kind == "state":
                    # state 消息：只保留最新的，跳过中间积压
                    latest_state = (a,)
                    continue
                # 非 state 消息立即处理
                if kind == "log":
                    self._log(a, b)
                elif kind == "init_done":
                    self._on_init_done(a, b)
                elif kind == "bot_stopped":
                    self._on_bot_stopped()
                elif kind == "auto_cal_rva":
                    self._on_auto_cal_rva(a)
        except queue.Empty:
            pass

        # 最后只处理最新的一条 state
        if latest_state:
            self._apply_state(latest_state[0])

        self.after(100, self._process_queue)

    def _on_init_done(self, ok: bool, err: str):
        if ok:
            self._initialized = True
            self._log("success", "✓ 初始化完成，可以开始")
            if self.bot and self.bot.godot_reader and self.bot.godot_reader.is_ready():
                self._set_status("已就绪", COLORS["success"])
                self._log("success", "✓ 结构性读取已启用：金币/血量/回合自动读取")
                self._set_buttons_state(running=False, initialized=True)
            elif self.bot and self.bot.needs_auto_calibration:
                self._start_auto_calibration()
            else:
                self._set_status("已就绪", COLORS["success"])
                self._set_buttons_state(running=False, initialized=True)
        else:
            self._initialized = False
            self._set_status("初始化失败", COLORS["danger"])
            if err:
                self._log("error", err)
            self._log("error", "初始化失败：请确认游戏已启动，并以管理员权限运行本程序")
            self._set_buttons_state(running=False, initialized=False)
            # 自动连接模式下稍后重试（游戏中途启动/权限就绪后可自愈）
            self.after(5000, self._auto_connect_tick)

    # ---------- 自动标定（仅定位 OS 结构，无需手动填金币等值）----------
    def _start_auto_calibration(self):
        self._set_status("自动标定中...", COLORS["warning"])
        self._set_buttons_state(running=False, initialized=False)
        self._log("info", "正在自动定位游戏数据结构（OS::singleton）...")

        def worker():
            try:
                rva = self.bot.discover_godot_rva()
            except Exception as e:  # noqa: BLE001
                rva = None
                self.ui_queue.put(("log", "error", f"自动标定失败: {e}"))
            self.ui_queue.put(("auto_cal_rva", rva, None))

        threading.Thread(target=worker, daemon=True).start()

    def _on_auto_cal_rva(self, rva):
        if not rva:
            self._log("error", "自动标定失败：未能定位 OS::singleton，统计值将不可用（无需手动填值）。")
            self._set_status("已就绪（无统计）", COLORS["text_dim"])
            self._set_buttons_state(running=False, initialized=True)
            return
        self._log("success", f"✓ 已定位游戏数据结构 (RVA={hex(rva)})，统计值将自动读取")
        self._set_status("已就绪", COLORS["success"])
        self._set_buttons_state(running=False, initialized=True)

    def _on_bot_stopped(self):
        self._set_status("已停止", COLORS["text_dim"])
        self._set_buttons_state(running=False, initialized=self._initialized)

    # ---------- 状态刷新（后台线程轮询，避免阻塞主线程导致无法响应关闭）----------
    def _start_state_poller(self):
        """启动后台守护线程周期性读取游戏状态并推入 UI 队列。

        关键：get_state() 内部会调用 ReadProcessMemory，可能阻塞；
        若在主线程上阻塞，窗口事件循环卡死，点击关闭(X)无法触发 _on_close，
        进程便残留。改到后台线程后，主线程事件循环永远可响应关闭。
        """
        if self._state_thread and self._state_thread.is_alive():
            return

        def _poll():
            while not self._closing:
                try:
                    if self.bot and self._initialized:
                        state = self.bot.get_state()
                        self.ui_queue.put(("state", state, None))
                except Exception:
                    # 单次读取失败不应终止轮询线程
                    pass
                try:
                    time.sleep(0.5)
                except Exception:
                    pass

        self._state_thread = threading.Thread(target=_poll, daemon=True)
        self._state_thread.start()

    def _start_exit_watchdog(self):
        """『生命看门狗』守护线程：作为进程退出的终极兜底。

        即便 _on_close 因任何原因未被触发（事件循环卡死、WM_DELETE_WINDOW 未派发
        等），只要出现以下任一情况就强制 os._exit(0) 终止整个进程，杜绝残留：
          1) 已请求关闭（_closing 为真）；
          2) 主窗口已被销毁（winfo_exists() 为假）——无论因何种方式关闭；
          3) 主线程心跳超时（>8s 未更新）——说明主线程疑似卡死（如绘制/读取异常），
             此时强制退出，避免进程变成僵尸。
        看门狗本身不依赖任何 GUI 调用能否成功，异常也照常退出。
        """
        def _watch():
            while True:
                try:
                    time.sleep(0.3)
                except Exception:
                    pass
                try:
                    if self._closing:
                        os._exit(0)
                    if not self.winfo_exists():
                        os._exit(0)
                    if time.time() - self._heartbeat > 15:
                        os._exit(0)
                except Exception:
                    # 连 winfo_exists 都抛异常（窗口已半销毁）→ 直接退出
                    try:
                        os._exit(0)
                    except Exception:
                        pass
        threading.Thread(target=_watch, daemon=True).start()

    def _apply_state(self, state):
        cal = state.get("calibrated", {})
        gold = state.get("gold") if cal.get("gold") else "—"
        hp = state.get("hp") if cal.get("hp") else "—"
        rnd = state.get("round") if cal.get("round") else "—"
        self.stat_vars["gold"].set(str(gold))
        self.stat_vars["hp"].set(
            f"{hp}/{state.get('max_hp', 5)}" if hp != "—" else "—/5")
        self.stat_vars["round"].set(
            f"{rnd}/{state.get('max_rounds', 18)}" if rnd != "—" else "—/18")
        phase = "商店" if state.get("phase") == "shop" else "战斗"
        live = state.get("live_items")
        if live is not None:
            self._last_live = live
            rnd = state.get("round", 1)
            self._last_round = int(rnd) if rnd is not None else 1
            n_bp = state.get("live_backpack_count", 0)
            n_st = state.get("live_storage_count", 0)
            self.phase_var.set(f"阶段: {phase}  |  摆盘: {n_bp}  储物箱: {n_st}")
            self.bp_count_var.set(f"物品 {n_bp}")
            bp = live.get("backpack", [])
            self._draw_backpack(bp)
            self._refresh_text_panel(self.storage_text, live.get("storage", []),
                                     self.storage_count)
            self._refresh_text_panel(self.shop_text, live.get("shop", []),
                                     self.shop_count)

    def _on_close(self):
        # 1) 立刻置关闭标志（生命看门狗会据此在 0.3s 内强制退出）
        self._closing = True
        # 2) 看门狗：独立 daemon 线程，短延时后无条件 os._exit(0)。
        #    即使本函数后续任何步骤卡死/抛错，进程也必然终止。
        def _kill():
            try:
                time.sleep(0.25)
            except Exception:
                pass
            os._exit(0)
        threading.Thread(target=_kill, daemon=True).start()
        # 3) bot.stop() 放到【独立后台线程】，绝不让主线程阻塞
        #    （避免 CloseHandle / 等待游戏进程 等任何意外卡死主线程，进而卡死看门狗）。
        def _stop_bot():
            try:
                if self.bot:
                    self.bot.stop()
            except Exception:
                pass
        threading.Thread(target=_stop_bot, daemon=True).start()
        # 4) 主线程只做轻量退出（不调用任何可能阻塞的操作）
        try:
            self.quit()
        except Exception:
            pass
        try:
            self.destroy()
        except Exception:
            pass
        # 5) 同步兜底：主线程若顺利走到这里，立刻结束。
        os._exit(0)

    def _bind_keys(self):
        self.bind("<space>", lambda e: self._toggle_pause())
        self.bind("<Escape>", lambda e: self._on_emergency())


def run():
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(message)s",
        datefmt="%H:%M:%S",
    )
    app = BackpackAIApp()

    handler = QueueLogHandler(app.ui_queue)
    handler.setFormatter(logging.Formatter("%(asctime)s %(message)s", datefmt="%H:%M:%S"))
    logging.getLogger().addHandler(handler)

    app.mainloop()


if __name__ == "__main__":
    run()
