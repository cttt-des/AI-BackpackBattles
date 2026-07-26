"""
游戏操作模块 — 通过 pyautogui 发送鼠标/键盘输入到游戏窗口
纯外置方式，不修改任何游戏文件
"""

import time
import logging
from typing import Optional, Tuple
import pyautogui

from .window_manager import WindowManager, GameLayout

logger = logging.getLogger(__name__)

# 安全设置
pyautogui.FAILSAFE = True
pyautogui.PAUSE = 0.05


class GameActions:
    """高层游戏操作：购买、放置、出售、开始战斗等"""

    def __init__(self, window_mgr: WindowManager):
        self.wm = window_mgr
        self.layout = GameLayout(window_mgr)
        self.action_delay = 0.15

        # 商店槽位映射（每个槽位的已知物品名）
        self.shop_slots: dict = {}  # slot_index -> item_name

        # 背包占用状态：（row, col）-> item_name
        self.grid_state: dict = {}

    def _move_to(self, x: int, y: int, duration: float = 0.1):
        """移动鼠标到指定位置"""
        pyautogui.moveTo(x, y, duration=duration)

    def _click(self, x: int, y: int):
        """在指定位置点击"""
        self._move_to(x, y)
        pyautogui.click()
        time.sleep(self.action_delay)

    def _right_click(self, x: int, y: int):
        """右键点击"""
        self._move_to(x, y)
        pyautogui.rightClick()
        time.sleep(self.action_delay)

    def _drag(
        self, from_x: int, from_y: int, to_x: int, to_y: int, duration: float = 0.3
    ):
        """从 from 拖拽到 to"""
        self._move_to(from_x, from_y)
        pyautogui.mouseDown()
        time.sleep(0.05)
        pyautogui.moveTo(to_x, to_y, duration=duration)
        time.sleep(0.05)
        pyautogui.mouseUp()
        time.sleep(self.action_delay * 1.5)

    def _press_key(self, key: str):
        """按下按键"""
        pyautogui.press(key)
        time.sleep(0.05)

    def refresh_layout(self):
        """刷新窗口信息并更新布局计算器"""
        self.wm.refresh()
        self.layout = GameLayout(self.wm)

    # === 高层操作 ===

    def buy_item(self, shop_slot: int):
        """
        购买商店第 shop_slot 个商品 (0-4)
        点击商品 → 自动进入储存箱
        """
        x, y = self.layout.shop_slot(shop_slot)
        logger.info(f"[购买] 商店槽位 {shop_slot} → 屏幕坐标 ({x}, {y})")
        self._click(x, y)

    def sell_from_storage(self):
        """
        出售储存箱中当前选中的物品
        点击储存箱 → 拖到出售区
        """
        sx, sy = self.layout.storage_box()
        dx, dy = self.layout.sell_box()
        logger.info(f"[出售] 储存箱 → 出售区")
        self._drag(sx, sy, dx, dy)

    def sell_from_grid(self, row: int, col: int):
        """出售背包中指定格子的物品"""
        gx, gy = self.layout.grid_cell(row, col)
        dx, dy = self.layout.sell_box()
        logger.info(f"[出售] 背包 ({row},{col}) → 出售区")
        self._drag(gx, gy, dx, dy)

    def place_item(self, to_row: int, to_col: int):
        """
        将储存箱中当前物品放置到背包指定格子
        物品在储存箱中 → 拖到背包格子
        """
        sx, sy = self.layout.storage_box()
        gx, gy = self.layout.grid_cell(to_row, to_col)
        logger.info(f"[放置] 储存箱 → 背包 ({to_row}, {to_col})")
        self._drag(sx, sy, gx, gy)

    def move_in_backpack(self, from_row: int, from_col: int, to_row: int, to_col: int):
        """在背包内移动物品"""
        fx, fy = self.layout.grid_cell(from_row, from_col)
        tx, ty = self.layout.grid_cell(to_row, to_col)
        logger.info(f"[移动] 背包 ({from_row},{from_col}) → ({to_row},{to_col})")
        self._drag(fx, fy, tx, ty)

    def start_combat(self):
        """点击「开始战斗」按钮"""
        x, y = self.layout.start_combat_button()
        logger.info(f"[战斗] 点击开始战斗")
        self._click(x, y)

    def reroll_shop(self):
        """点击刷新商店按钮"""
        x, y = self.layout.reroll_button()
        logger.info(f"[刷新] 点击刷新商店")
        self._click(x, y)

    def rotate_item(self):
        """旋转当前持有的物品（按 R 键）"""
        logger.info("[旋转] 按 R 键")
        self._press_key("r")

    def wait_for_combat(self, timeout: float = 120.0) -> bool:
        """
        等待战斗结束回到商店阶段
        通过检测「开始战斗」按钮是否重新出现来判断
        """
        import time as _time
        start = _time.time()
        while _time.time() - start < timeout:
            _time.sleep(2.0)
            # 简单策略：等待固定时间（战斗通常很快）
            # 实际中可通过检测"开始战斗"按钮区域颜色变化来判断
            logger.debug("等待战斗结束...")
            # TODO: 实际检测——截图检查按钮区域
        return True

    # === 批量操作 ===

    def execute_plan(self, plan: list) -> bool:
        """
        执行一个操作计划
        plan 是操作字典列表，每项：
        {"action": "buy", "slot": 0}
        {"action": "place", "row": 0, "col": 0}
        {"action": "sell_grid", "row": 0, "col": 0}
        {"action": "reroll"}
        {"action": "combat"}
        {"action": "rotate"}
        {"action": "move", "from_row": 0, "from_col": 0, "to_row": 1, "to_col": 1}
        """
        for step in plan:
            action = step.get("action", "")
            try:
                if action == "buy":
                    self.buy_item(step["slot"])
                elif action == "place":
                    self.place_item(step["row"], step["col"])
                elif action == "sell_grid":
                    self.sell_from_grid(step["row"], step["col"])
                elif action == "reroll":
                    self.reroll_shop()
                elif action == "combat":
                    self.start_combat()
                elif action == "rotate":
                    self.rotate_item()
                elif action == "move":
                    self.move_in_backpack(
                        step["from_row"], step["from_col"],
                        step["to_row"], step["to_col"]
                    )
                elif action == "wait":
                    time.sleep(step.get("seconds", 1.0))
                elif action == "sell_storage":
                    self.sell_from_storage()
                else:
                    logger.warning(f"未知操作: {action}")
            except Exception as e:
                logger.error(f"操作执行失败 [{action}]: {e}")
                return False
        return True

    def emergency_stop(self):
        """紧急停止：移动鼠标到安全角落并释放所有按键"""
        pyautogui.moveTo(10, 10, duration=0.2)
        pyautogui.mouseUp()
        for key in ["shift", "ctrl", "alt", "r"]:
            pyautogui.keyUp(key)
        logger.warning("紧急停止已触发")
