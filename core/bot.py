"""
主机器人 — 外置模式
不修改游戏文件，通过内存读取 + 坐标操作控制游戏
"""

import os
import sys
import time
import json
import re
import logging
import threading
from typing import Optional
from pathlib import Path

import yaml

from .window_manager import WindowManager
from .memory_reader import MemoryReader, MemoryGameState, MemoryScanner
from .godot_reader import GodotReader
from .item_reader import ItemReader
from .godot_probe import discover_os_singleton_rva, read_game_members, match_member_indices
from .state_tracker import GameStateTracker, Item, ItemCategory
from .actions import GameActions
from .ai_interface import HeuristicStrategy, LLMStrategy, Action, ActionType
from .paths import get_base_dir, get_config_path

logger = logging.getLogger(__name__)


class BackpackBot:
    """背包乱斗 AI 机器人（外置版）"""

    def __init__(self, config_path: str = None):
        if config_path is None:
            config_path = get_config_path()
        self.config_path = config_path
        with open(config_path, "r", encoding="utf-8") as f:
            self.config = yaml.safe_load(f)

        self.max_rounds = self.config.get("game", {}).get("max_rounds", 18)
        self.action_delay = self.config.get("game", {}).get("action_delay", 0.2)
        self.combat_timeout = self.config.get("game", {}).get("combat_timeout", 120)

        # 核心模块
        self.window_mgr = WindowManager()
        self.memory_reader: Optional[MemoryReader] = None
        self.memory_state: Optional[MemoryGameState] = None
        self.godot_reader: Optional[GodotReader] = None
        self.item_reader: Optional[ItemReader] = None
        self.tracker = GameStateTracker()
        self.actions: Optional[GameActions] = None

        # AI 策略
        strategy_cfg = self.config.get("ai", {})
        strategy_type = strategy_cfg.get("strategy", "heuristic")
        if strategy_type == "llm":
            self.strategy = LLMStrategy(strategy_cfg)
        else:
            self.strategy = HeuristicStrategy(strategy_cfg)

        # 运行状态
        self.running = False
        self.paused = False
        self.step_mode = False
        self.needs_auto_calibration = False
        self._stop_event = threading.Event()

        # 内存校准扫描器（每个字段一个）field ∈ {gold, hp, round}
        self._scanners: dict = {}

        # 日志回调（供 GUI 使用）
        self.log_callbacks = []

        # 数据目录
        self.log_dir = get_base_dir() / "logs"
        self.log_dir.mkdir(exist_ok=True)
        self.screenshot_dir = get_base_dir() / "screenshots"

    def log(self, level: str, msg: str):
        """统一日志（同时输出到 logger 和 GUI 回调）"""
        getattr(logger, level)(msg)
        for cb in self.log_callbacks:
            cb(level, msg)

    def on_log(self, callback):
        """注册日志回调"""
        self.log_callbacks.append(callback)

    def initialize(self) -> bool:
        """
        初始化：查找游戏窗口 → 打开进程 → 初始化内存读取 → 初始化操作
        """
        # Step 1: 查找窗口
        self.log("info", "正在查找游戏窗口...")
        if not self.window_mgr.refresh():
            self.log("error", "未找到游戏窗口！请启动 Backpack Battles")
            return False
        w = self.window_mgr.window
        self.log("info", f"找到窗口: {w.title} (PID={w.pid}, {w.width}x{w.height})")

        # Step 2: 打开进程
        self.log("info", f"正在连接进程 PID={w.pid}...")
        try:
            self.memory_reader = MemoryReader(w.pid)
            self.memory_state = MemoryGameState(self.memory_reader)
            # 结构性读取：若 config 已完整标定（RVA + 三个成员下标），直接启用
            godot_cfg = self.config.setdefault("godot", {})
            rva = godot_cfg.get("os_singleton_rva")
            members_ok = all(
                godot_cfg.get(k, -1) >= 0 for k in ("member_gold", "member_hp", "member_round")
            )
            if rva and members_ok:
                self.godot_reader = GodotReader(self.memory_reader, godot_cfg)
                self.item_reader = ItemReader(self.godot_reader)
                self.log("info", "[结构] 已启用 Godot 直接读取（无需手动校准）")
            else:
                self.needs_auto_calibration = True
                self.log("info", "[结构] 未校准，启动后将自动标定（一次性）")
        except OSError as e:
            self.log("error", f"无法打开进程: {e}")
            self.log("error", "请以管理员权限运行本程序")
            return False

        # Step 3: 初始化操作模块
        self.actions = GameActions(self.window_mgr)

        # Step 4: 将游戏窗口带到前台
        self.window_mgr.bring_to_foreground()
        time.sleep(0.5)

        self.log("info", "✓ 初始化完成")
        return True

    def scan_memory_values(self) -> bool:
        """
        旧的"单轮自动扫描"会随机命中错误地址，导致数值全错，现已弃用。
        请改用交互式校准：cal_first_scan / cal_next_scan / cal_lock。
        """
        self.log("info", "内存数值需要手动校准（单轮自动扫描不可靠）。")
        self.log("info", "请在「内存校准」面板输入游戏中实际看到的数值进行扫描与缩小。")
        return False

    # ---------------- 交互式内存校准 ----------------
    def cal_first_scan(self, field: str, value: int) -> int:
        """首次扫描某字段。返回候选数量，-1 表示未连接进程。"""
        if not self.memory_reader:
            return -1
        sc = MemoryScanner(self.memory_reader)
        cnt = sc.first_scan(int(value))
        self._scanners[field] = sc
        self.log("info", f"[校准/{field}] 首次扫描 = {value} → {cnt} 个候选")
        return cnt

    def cal_next_scan(self, field: str, value: int) -> int:
        """缩小扫描。返回剩余候选数量，-1 表示尚未首次扫描。"""
        sc = self._scanners.get(field)
        if not sc:
            return -1
        cnt = sc.next_scan(int(value))
        self.log("info", f"[校准/{field}] 缩小到 = {value} → 剩余 {cnt} 个候选")
        return cnt

    def cal_count(self, field: str) -> int:
        sc = self._scanners.get(field)
        return sc.count if sc else 0

    def cal_lock(self, field: str) -> Optional[int]:
        """把当前首个候选锁定为该字段的真实地址。"""
        sc = self._scanners.get(field)
        if not sc or not sc.candidates:
            return None
        addr = sc.best_address()
        tname = sc.candidates[addr]
        self.memory_state.set_field(field, addr, tname)
        self.memory_state.update()
        self.log("info", f"[校准/{field}] 已锁定地址 {hex(addr)} ({tname})")
        return addr

    def cal_reset(self, field: str):
        self._scanners.pop(field, None)
        self.memory_state.clear_field(field)
        self.log("info", f"[校准/{field}] 已重置")

    # ---------------- 自动标定（免手动，一次性）----------------
    def discover_godot_rva(self) -> Optional[int]:
        """自动定位 OS::singleton 的 RVA（免手动扫描）。返回 None 表示未找到。

        使用正向链路校验（OS::singleton -> SceneTree -> root -> Game），不依赖字符串/虚函数名。
        失败时记录诊断信息（last_diag），便于排查偏移问题。
        """
        if not self.memory_reader:
            return None
        godot_cfg = self.config.setdefault("godot", {})
        rva, d = discover_os_singleton_rva(self.memory_reader, godot_cfg, diag=True)
        if rva is None:
            self.log("warn", f"[结构] 自动定位 OS::singleton 失败，诊断: {d}")
        else:
            self.log("info", f"[结构] 已定位 OS::singleton RVA={hex(rva)} (偏移组合 {d.get('variant_used')})")
        return rva

    def read_game_members(self, rva: int) -> list:
        """读取 Game 单例的成员整数列表（用于反推下标）。"""
        if not self.memory_reader:
            return []
        child = self.config.get("godot", {}).get("game_child_index", -1)
        return read_game_members(self.memory_reader, rva, child)

    def apply_godot_calibration(self, rva: int, gold: int, hp: int, round_: int) -> dict:
        """匹配成员下标、写回 config.yaml、重实例化 godot_reader。

        返回 match_member_indices 的结果（未匹配到的字段下标为 -1）。
        """
        members = self.read_game_members(rva)
        idx = match_member_indices(members, gold, hp, round_)
        godot_cfg = self.config.setdefault("godot", {})
        godot_cfg["os_singleton_rva"] = rva
        godot_cfg["member_gold"] = idx["gold"]
        godot_cfg["member_hp"] = idx["hp"]
        godot_cfg["member_round"] = idx["round"]
        self._save_godot_config(godot_cfg)
        self.godot_reader = GodotReader(self.memory_reader, godot_cfg)
        self.item_reader = ItemReader(self.godot_reader)
        self.needs_auto_calibration = False
        return idx

    def _save_godot_config(self, godot_cfg: dict):
        """把 godot 段的关键值写回 config.yaml（保留注释，仅替换对应行）。"""
        try:
            path = self.config_path
            text = path.read_text(encoding="utf-8")
            for key in ("os_singleton_rva", "member_gold", "member_hp", "member_round"):
                val = godot_cfg.get(key)
                if val is None:
                    continue
                pat = rf"^(\s*{key}:\s*).*$"
                text, _ = re.subn(pat, lambda m, v=val: f"{m.group(1)}{v}", text, count=1, flags=re.M)
            path.write_text(text, encoding="utf-8")
        except Exception as e:  # noqa: BLE001
            logger.warning("写回 config.yaml 失败: %s", e)

    def update_state(self):
        """更新游戏状态（内存读取 + 状态追踪）"""
        if self.memory_state:
            self.memory_state.update()
            self.tracker.sync_from_memory(self.memory_state.to_dict())
        # 结构性读取优先：直接从 Game 单例读取，覆盖 tracker 的占位值
        if self.godot_reader and self.godot_reader.is_ready():
            stats = self.godot_reader.read_stats()
            if stats.get("gold") is not None:
                self.tracker.gold = stats["gold"]
            if stats.get("hp") is not None:
                self.tracker.hp = stats["hp"]
            if stats.get("round") is not None:
                self.tracker.current_round = stats["round"]

    def get_state(self) -> dict:
        """获取完整游戏状态"""
        self.update_state()
        state = self.tracker.get_summary()
        if self.memory_state:
            mem = self.memory_state.to_dict()
            state["memory"] = {
                "gold_raw": mem.get("gold"),
                "hp_raw": mem.get("hp"),
                "round_raw": mem.get("round"),
            }
            # 每个字段是否已完成校准（地址已锁定 或 结构性读取已启用）
            struct_ok = bool(self.godot_reader and self.godot_reader.is_ready())
            state["calibrated"] = {
                "gold": self.memory_state.gold_addr is not None or struct_ok,
                "hp": self.memory_state.hp_addr is not None or struct_ok,
                "round": self.memory_state.round_addr is not None or struct_ok,
            }
            state["structural"] = struct_ok
        # 结构性物品读取：当前摆盘 / 储物箱 / 商店在售
        if self.item_reader:
            try:
                items = self.item_reader.read_items()
                state["live_items"] = items
                state["live_backpack_count"] = len(items["backpack"])
                state["live_storage_count"] = len(items["storage"])
            except Exception:  # noqa: BLE001
                state["live_items"] = {"backpack": [], "storage": [], "shop": []}
        return state

    def run_round(self) -> bool:
        """执行一个完整的购买+放置回合"""

        if not self.actions:
            return False

        # 确保窗口在前台
        self.window_mgr.bring_to_foreground()
        time.sleep(0.3)

        # 第 1 步：更新状态
        self.update_state()
        state = self.get_state()
        self.log("info", f"--- 第 {self.tracker.current_round} 回合 ---")
        self.log("info", f"HP: {self.tracker.hp}/{self.tracker.max_hp} 金币: {self.tracker.gold}")

        # 第 2 步：AI 决策
        context = {
            "gold": self.tracker.gold,
            "hp": self.tracker.hp,
            "current_round": self.tracker.current_round,
            "max_rounds": self.tracker.max_rounds,
            "backpack": self.tracker.backpack.to_dict(),
            "storage_count": len(self.tracker.storage),
            "owned_items": list(self.tracker.owned_items.keys()),
        }

        plan = self.strategy.decide(context)
        if not plan:
            self.log("info", "AI 返回空计划，跳过本回合购买")
        else:
            self.log("info", f"AI 决策: {len(plan)} 步操作 — {[a.type.value for a in plan]}")

            # 第 3 步：执行操作计划
            for action in plan:
                if self._stop_event.is_set():
                    return False
                if self.paused:
                    self._wait_unpause()

                self._execute_action(action)

        # 第 4 步：开始战斗
        if self._stop_event.is_set():
            return False

        self.tracker.start_combat()
        self.actions.start_combat()
        time.sleep(1.0)

        # 第 5 步：等待战斗结束
        self.log("info", f"等待战斗结束（最多 {self.combat_timeout} 秒）...")
        self.actions.wait_for_combat(timeout=self.combat_timeout)

        # 第 6 步：更新状态
        time.sleep(1.0)
        self.update_state()
        self.tracker.end_combat()

        # 检查是否游戏结束
        if self.tracker.hp <= 0:
            self.log("warning", f"游戏结束！HP 降至 {self.tracker.hp}")
            return False

        if self.tracker.current_round > self.max_rounds:
            self.log("info", f"已完成全部 {self.max_rounds} 回合！")
            return False

        return True

    def _execute_action(self, action: Action):
        """执行单个 AI 动作"""
        at = action.type
        params = action.params

        if at == ActionType.BUY:
            slot = params.get("slot", 0)
            item_name = params.get("item", "unknown")
            cost = params.get("cost", 0)
            self.actions.buy_item(slot)
            # 更新状态追踪
            item = Item(name=item_name, category=ItemCategory.UNKNOWN, cost=cost, sell_value=cost // 2)
            self.tracker.buy_item(item, cost, slot)

        elif at == ActionType.PLACE:
            row = params.get("row", 0)
            col = params.get("col", 0)
            item_name = params.get("item", "")
            rotated = params.get("rotated", False)
            if rotated:
                self.actions.rotate_item()
            self.actions.place_item(row, col)
            self.tracker.place_item(item_name, row, col, rotated)

        elif at == ActionType.SELL:
            item_name = params.get("item", "")
            pos = self.tracker.backpack.get_item_pos(item_name)
            if pos:
                self.actions.sell_from_grid(pos[0], pos[1])
            else:
                self.actions.sell_from_storage()
            self.tracker.sell_item(item_name)

        elif at == ActionType.REROLL:
            self.actions.reroll_shop()

        elif at == ActionType.MOVE:
            fr, fc = params.get("from_row", 0), params.get("from_col", 0)
            tr, tc = params.get("to_row", 0), params.get("to_col", 0)
            self.actions.move_in_backpack(fr, fc, tr, tc)

        elif at == ActionType.ROTATE:
            self.actions.rotate_item()

        elif at == ActionType.WAIT:
            time.sleep(params.get("seconds", 1.0))

        elif at == ActionType.COMBAT:
            pass  # combat is handled by run_round

        time.sleep(self.action_delay)

    def _wait_unpause(self):
        """等待解除暂停"""
        while self.paused and not self._stop_event.is_set():
            time.sleep(0.2)

    def start(self):
        """启动机器人主循环"""
        self.running = True
        self._stop_event.clear()
        self.log("info", "=" * 50)
        self.log("info", "背包乱斗 AI 机器人启动（外置模式）")
        self.log("info", "=" * 50)

        try:
            while self.running and not self._stop_event.is_set():
                if self.paused:
                    self._wait_unpause()
                    continue

                if self.step_mode:
                    # 单步模式：执行一步后暂停
                    self.run_round()
                    self.paused = True
                    continue

                success = self.run_round()
                if not success:
                    break

        except KeyboardInterrupt:
            self.log("info", "收到中断信号")
        except Exception as e:
            self.log("error", f"运行错误: {e}")
            import traceback
            self.log("error", traceback.format_exc())
        finally:
            self.stop()

    def stop(self):
        """停止机器人"""
        self.running = False
        self._stop_event.set()
        self.log("info", "机器人已停止")
        if self.memory_reader:
            self.memory_reader.close()

    def pause(self):
        """暂停"""
        self.paused = True
        self.log("info", "⏸ 已暂停")

    def resume(self):
        """继续"""
        self.paused = False
        self.log("info", "▶ 继续运行")

    def step(self):
        """单步执行"""
        self.step_mode = False
        self.paused = False
        if not self.running:
            # 启动并执行一步
            self.running = True
        self.run_round()
        self.paused = True  # 执行完一步后暂停


def main():
    """命令行入口"""
    import argparse
    parser = argparse.ArgumentParser(description="背包乱斗 AI 机器人")
    parser.add_argument("--config", default=None, help="配置文件路径")
    parser.add_argument("--verbose", "-v", action="store_true", help="详细日志")
    parser.add_argument("--scan-only", action="store_true", help="仅扫描内存后退出")
    args = parser.parse_args()

    logging.basicConfig(
        level=logging.DEBUG if args.verbose else logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
    )

    bot = BackpackBot(args.config)

    if not bot.initialize():
        return 1

    if not bot.scan_memory_values():
        print("警告: 内存扫描失败，将使用状态追踪模式")

    if args.scan_only:
        state = bot.get_state()
        print(json.dumps(state, indent=2, ensure_ascii=False))
        return 0

    bot.start()
    return 0


if __name__ == "__main__":
    sys.exit(main())
