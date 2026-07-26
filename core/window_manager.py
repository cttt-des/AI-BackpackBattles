"""
窗口管理器 — 查找、定位、激活游戏窗口
计算游戏内各 UI 区域的屏幕坐标
"""

import ctypes
import ctypes.wintypes
from typing import Optional, Tuple
from dataclasses import dataclass

# Windows API
user32 = ctypes.windll.user32
kernel32 = ctypes.windll.kernel32

SW_RESTORE = 9
SW_SHOW = 5


@dataclass
class WindowInfo:
    """窗口信息"""
    hwnd: int
    title: str
    pid: int
    rect: Tuple[int, int, int, int]  # left, top, right, bottom
    width: int
    height: int


class WindowManager:
    """游戏窗口管理器"""

    GAME_WINDOW_TITLE = "Backpack Battles"

    def __init__(self):
        self.window: Optional[WindowInfo] = None

    def find_game_window(self) -> Optional[WindowInfo]:
        """查找游戏窗口"""
        hwnd = user32.FindWindowW(None, self.GAME_WINDOW_TITLE)
        if not hwnd:
            # 尝试部分匹配
            def enum_callback(hwnd, lparam):
                title = ctypes.create_unicode_buffer(256)
                user32.GetWindowTextW(hwnd, title, 256)
                if self.GAME_WINDOW_TITLE.lower() in title.value.lower():
                    return False  # 找到了
                return True

            # 暴力枚举所有顶层窗口
            hwnd = user32.FindWindowW(None, None)
            # 遍历同级窗口
            found = None
            while hwnd:
                title = ctypes.create_unicode_buffer(256)
                user32.GetWindowTextW(hwnd, title, 256)
                if title.value and self.GAME_WINDOW_TITLE.lower() in title.value.lower():
                    found = hwnd
                    break
                hwnd = user32.GetWindow(hwnd, 2)  # GW_HWNDNEXT

            if found:
                hwnd = found
            else:
                return None

        return self._get_window_info(hwnd)

    def _get_window_info(self, hwnd: int) -> WindowInfo:
        """获取窗口详细信息"""
        title = ctypes.create_unicode_buffer(256)
        user32.GetWindowTextW(hwnd, title, 256)

        pid = ctypes.c_ulong()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(pid))

        rect = ctypes.wintypes.RECT()
        user32.GetWindowRect(hwnd, ctypes.byref(rect))

        # 获取客户区大小
        client_rect = ctypes.wintypes.RECT()
        user32.GetClientRect(hwnd, ctypes.byref(client_rect))

        return WindowInfo(
            hwnd=hwnd,
            title=title.value,
            pid=pid.value,
            rect=(rect.left, rect.top, rect.right, rect.bottom),
            width=client_rect.right - client_rect.left,
            height=client_rect.bottom - client_rect.top,
        )

    def refresh(self) -> bool:
        """刷新窗口信息，返回是否找到"""
        self.window = self.find_game_window()
        return self.window is not None

    def bring_to_foreground(self) -> bool:
        """将游戏窗口带到前台"""
        if not self.window:
            return False
        # 恢复最小化窗口
        user32.ShowWindow(self.window.hwnd, SW_RESTORE)
        user32.ShowWindow(self.window.hwnd, SW_SHOW)
        user32.SetForegroundWindow(self.window.hwnd)
        return True

    def get_title_bar_height(self) -> int:
        """估算标题栏高度"""
        if not self.window:
            return 30
        # 窗口总高度 - 客户区高度 = 标题栏 + 边框
        window_height = self.window.rect[3] - self.window.rect[1]
        title_bar = window_height - self.window.height
        return max(title_bar - 8, 0)  # 减去边框

    @property
    def left(self) -> int:
        return self.window.rect[0] if self.window else 0

    @property
    def top(self) -> int:
        title_bar = self.get_title_bar_height()
        return self.window.rect[1] + title_bar if self.window else 0

    @property
    def client_width(self) -> int:
        return self.window.width if self.window else 1280

    @property
    def client_height(self) -> int:
        return self.window.height if self.window else 720


class GameLayout:
    """
    游戏 UI 布局坐标计算器
    基于已知的游戏布局，将逻辑位置转换为屏幕像素坐标
    """

    def __init__(self, window: WindowManager):
        self.wm = window

    # === 坐标计算 ===

    def client_to_screen(self, x_ratio: float, y_ratio: float) -> Tuple[int, int]:
        """将客户区比例坐标 (0.0-1.0) 转换为屏幕绝对坐标"""
        screen_x = self.wm.left + int(x_ratio * self.wm.client_width)
        screen_y = self.wm.top + int(y_ratio * self.wm.client_height)
        return screen_x, screen_y

    def grid_cell(self, row: int, col: int, grid_rows: int = 7, grid_cols: int = 9) -> Tuple[int, int]:
        """
        计算背包网格指定格子的屏幕坐标（7 行 × 9 列，宽矩形）
        假设背包区域在客户区左半部分的中央
        """
        # 背包区域大约在客户区左侧 4%-48% 范围内（9 列较宽）
        grid_left = 0.04
        grid_right = 0.48
        grid_top = 0.20
        grid_bottom = 0.82

        cell_width = (grid_right - grid_left) / grid_cols
        cell_height = (grid_bottom - grid_top) / grid_rows

        x_ratio = grid_left + (col + 0.5) * cell_width
        y_ratio = grid_top + (row + 0.5) * cell_height

        return self.client_to_screen(x_ratio, y_ratio)

    def shop_slot(self, slot: int) -> Tuple[int, int]:
        """计算商店第 slot 个商品位置 (0-4)"""
        # 商店右侧区域
        y_ratio = 0.12 + slot * 0.16
        return self.client_to_screen(0.85, y_ratio)

    def storage_box(self) -> Tuple[int, int]:
        """储存箱位置"""
        return self.client_to_screen(0.55, 0.50)

    def sell_box(self) -> Tuple[int, int]:
        """出售区位置"""
        return self.client_to_screen(0.80, 0.88)

    def start_combat_button(self) -> Tuple[int, int]:
        """开始战斗按钮"""
        return self.client_to_screen(0.50, 0.04)

    def reroll_button(self) -> Tuple[int, int]:
        """刷新商店按钮"""
        return self.client_to_screen(0.92, 0.06)

    def drag(self, from_pos: Tuple[int, int], to_pos: Tuple[int, int]):
        """拖拽操作（从 from 拖到 to）"""
        return from_pos, to_pos
