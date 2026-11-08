"""在运行中的游戏里点一次"历史"按钮，触发排行榜缓存刷新。

原理：游戏 window/size = 1920x1080 + stretch 2d/keep，
所以场景坐标可直接按「客户区尺寸 / 1920x1080」等比换算成屏幕坐标。
历史按钮场景矩形：margin_left=1724, margin_top=325, right=1889, bottom=433。
"""
from __future__ import annotations

import ctypes
import ctypes.wintypes as wt
import time

_user32 = ctypes.WinDLL("user32", use_last_error=True)

BASE_W, BASE_H = 1920.0, 1080.0
HISTORY_CENTER = (1806.0, 379.0)   # 按钮中心（场景坐标）

SW_RESTORE = 9
SW_SHOW = 5


class RECT(ctypes.Structure):
    _fields_ = [("left", wt.LONG), ("top", wt.LONG), ("right", wt.LONG), ("bottom", wt.LONG)]


class POINT(ctypes.Structure):
    _fields_ = [("x", wt.LONG), ("y", wt.LONG)]


def find_window(title_keyword: str = "Backpack Battles"):
    hwnd = _user32.FindWindowW(None, None)
    while hwnd:
        buf = ctypes.create_unicode_buffer(256)
        _user32.GetWindowTextW(hwnd, buf, 256)
        if buf.value and title_keyword.lower() in buf.value.lower():
            if _user32.IsWindowVisible(hwnd):
                return hwnd
        hwnd = _user32.GetWindow(hwnd, 2)
    return None


def client_rect_screen(hwnd: int) -> tuple[int, int, int, int]:
    """返回客户区在屏幕上的 (left, top, width, height)。"""
    rect = RECT()
    _user32.GetClientRect(hwnd, ctypes.byref(rect))
    origin = POINT(0, 0)
    _user32.ClientToScreen(hwnd, ctypes.byref(origin))
    return origin.x, origin.y, rect.right - rect.left, rect.bottom - rect.top


def click(x: int, y: int) -> None:
    _user32.SetCursorPos(x, y)
    time.sleep(0.05)
    _user32.mouse_event(0x0002, 0, 0, 0, 0)  # LEFTDOWN
    time.sleep(0.05)
    _user32.mouse_event(0x0004, 0, 0, 0, 0)  # LEFTUP


def click_history(*, keyword: str = "Backpack Battles", settle: float = 1.0) -> dict:
    """把游戏窗口拉到前台并点击历史按钮。返回诊断信息。"""
    hwnd = find_window(keyword)
    if not hwnd:
        return {"ok": False, "reason": "未找到游戏窗口"}
    _user32.ShowWindow(hwnd, SW_RESTORE)
    _user32.ShowWindow(hwnd, SW_SHOW)
    _user32.SetForegroundWindow(hwnd)
    time.sleep(settle)

    left, top, width, height = client_rect_screen(hwnd)
    if width <= 0 or height <= 0:
        return {"ok": False, "reason": "客户区尺寸异常", "hwnd": hwnd}

    sx = width / BASE_W
    sy = height / BASE_H
    cx = left + int(HISTORY_CENTER[0] * sx)
    cy = top + int(HISTORY_CENTER[1] * sy)
    click(cx, cy)
    return {
        "ok": True, "hwnd": hwnd, "client": (left, top, width, height),
        "scale": (round(sx, 4), round(sy, 4)), "clicked": (cx, cy),
    }


if __name__ == "__main__":
    import json
    print(json.dumps(click_history(), ensure_ascii=False, indent=2))
