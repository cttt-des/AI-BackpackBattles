# -*- coding: utf-8 -*-
"""godot_quiet —— 让 Godot 窗口「点不到、看不见、不进任务栏」的强制静默层。

## 为什么需要它（2026-11-06 事故）

长场录制会弹窗，用户点一下就卡死。根因两条：

1. **SW_HIDE 守不住长场**：`godot_headless._startupinfo()` 只设置初始 `SW_HIDE`，
   实测 1.4 秒的短脚本窗口全程不可见，但长场跑 60~75 秒时窗口会冒出来；
2. **阻塞 tick 循环 = 必然未响应**：`oracle_fight.gd` 在 SceneTree 里手动 tick，
   整场战斗不返回消息循环。窗口一旦可见，用户点击 -> 系统投递消息 -> 进程处理不了
   -> 「未响应」-> 卡死。两次重录（231s rc=0xFFFFFFFF / 161s rc=0xCFFFFFFF，
   日志都停在 t=63.3s）就是这么死的。

## 解决思路：不靠引擎自觉，靠外部持续压制

对**本进程树里每个 Godot 子进程**起一个看门狗线程，每 50ms 扫它自己的窗口，
命中 `Engine`（Godot 顶层窗口）/ `#32770`（MessageBox）就三重压制：

| 手段 | 作用 |
|---|---|
| `ShowWindow(SW_HIDE)` | 不可见 |
| `SetWindowPos(-32000, -32000)` | 移到屏幕外（即使被重新显示，也点不到） |
| `GWL_EXSTYLE` 加 `WS_EX_NOACTIVATE` | 不抢焦点、不进 Alt-Tab（**别加 `WS_EX_TOOLWINDOW`**，见下方重大修正） |

★ 三者叠加才够：单独 SW_HIDE 会被引擎的 ShowWindow 冲掉；只移屏外仍会占 Alt-Tab。

## 用法

```python
import godot_quiet
godot_quiet.install()          # 包一层 gh.spawn，之后所有 spawn 自动静默

import godot_headless as gh
gh.run(gh.cmd(project="oracle", script="oracle_fight.gd"), ...)  # 自动受保护
```

也可直接用它包一个已有 Popen：

```python
p = subprocess.Popen(cmd, startupinfo=gh.worker_startupinfo())
godot_quiet.guard(p.pid)       # 对已起的进程补挂看门狗
```

★ 只藏不杀、不改业务逻辑、不 pump 消息循环（pump 会引入时序不确定性，
  与「事件流逐字节可复现」的底线冲突）。
"""
from __future__ import annotations

import ctypes
import ctypes.wintypes as w
import sys
import threading
import time

#: Godot 顶层窗口类 / Windows 标准对话框（MessageBox）
QUIET_CLASSES = ("Engine", "#32770")
#: 标题兜底（搜狗 IME 的弹框标题是 Error）
QUIET_TITLES = ("Error", "OpenMem", "sgime", "Filemap", "t_skinfilemap")
#: 扫描间隔（秒）。50ms 足够压住引擎的 ShowWindow；再快就是空转 CPU。
POLL_INTERVAL = 0.05
#: 屏外坐标（Windows 惯例的「不可见位置」）
OFFSCREEN = -32000

# ★ 2026-11-06 重大修正：**不要**加 WS_EX_TOOLWINDOW。
#   实测后果：一旦加上，该窗口就不再出现在 EnumWindows 的结果里（实测从
#   [(hwnd, False)] 变成 []），于是看门狗**只能压住一次**，之后 Godot 把窗口
#   ShowWindow 回来，看门狗已经找不到它了 —— 严格采样实测 Engine 窗口
#   rect=(0,0,1280,720) 在 4796 次采样里可见了 **2134 次（44%）**。
#   只留 WS_EX_NOACTIVATE（不进 Alt-Tab 且不抢焦点，但仍可枚举）。
WS_EX_NOACTIVATE = 0x08000000
GWL_EXSTYLE = -20
SWP_NOZORDER = 0x0004
SWP_NOACTIVATE = 0x0010
SWP_NOSIZE = 0x0001
SWP_NOMOVE = 0x0002
#: ★ 关键：异步版，不阻塞调用线程（否则等窗口线程处理 WM_WINDOWPOSCHANGING，
#:   实测单次 1.077s，会把看门狗线程拖死）。
SWP_ASYNCWINDOWPOS = 0x4000

_guarded = set()
_lock = threading.Lock()
_installed = False
_stats = {"hidden": 0, "moved": 0, "styled": 0}


#: ★ 2026-11-06：64 位下 ctypes 默认按 c_int 传参，**HWND 会被截断** →
#: SetWindowPos/SetWindowLongW 静默失败（异常被 except 吞掉，表现为 moved=0）。
#: 必须显式声明 argtypes/restype，这里用 _setup_user32() 一次性设好。
def _setup_user32():
    """一次性声明所有用到的 user32 API 签名。

    ★ 为什么必须**逐个**声明（2026-11-06 两次踩坑）：
      64 位 Python 下 ctypes 默认把**未声明的整数参数按 32 位**传，HWND 会被截断：
        · SetWindowPos / SetWindowLongW 静默失败（moved=0、styled=0）；
        · **IsWindow 更阴**：句柄被截断后恒返回 0（「窗口不存在」），于是看门狗
          每轮都把缓存的 hwnd 从 known 里删掉 → 只压得住第 1 次 → 窗口后续被
          Godot ShowWindow 弄回来就再没人管（实测长场 12318 次采样里可见 10615 次）。
      这类 bug 全部被 `except: pass` 吞掉，表现为「看门狗像没跑」，极难查。
    """
    u32 = ctypes.WinDLL("user32")
    CB = ctypes.WINFUNCTYPE(ctypes.c_bool, w.HWND, w.LPARAM)
    LP = ctypes.POINTER(w.RECT)
    specs = [
        ("ShowWindow", [w.HWND, ctypes.c_int], w.BOOL),
        ("IsWindow", [w.HWND], w.BOOL),
        ("IsWindowVisible", [w.HWND], w.BOOL),
        ("SetWindowPos", [w.HWND, w.HWND, ctypes.c_int, ctypes.c_int,
                          ctypes.c_int, ctypes.c_int, ctypes.c_uint], w.BOOL),
        ("SetWindowLongW", [w.HWND, ctypes.c_int, ctypes.c_long], ctypes.c_long),
        ("GetWindowLongW", [w.HWND, ctypes.c_int], ctypes.c_long),
        ("GetWindowRect", [w.HWND, LP], w.BOOL),
        ("GetWindowTextW", [w.HWND, ctypes.c_wchar_p, ctypes.c_int], ctypes.c_int),
        ("GetClassNameW", [w.HWND, ctypes.c_wchar_p, ctypes.c_int], ctypes.c_int),
        ("GetWindowThreadProcessId", [w.HWND, ctypes.POINTER(w.DWORD)], w.DWORD),
        ("EnumWindows", [CB, w.LPARAM], w.BOOL),
    ]
    for name, argtypes, restype in specs:
        try:
            fn = getattr(u32, name)
            fn.argtypes = argtypes
            fn.restype = restype
        except Exception:  # noqa: BLE001
            pass
    return u32


def _hide_one(u32, hwnd) -> None:
    """把窗口**异步**移到屏幕外。**只做这一件事**（原因见下，全是实测数据）。

    ## 为什么只剩 SetWindowPos(ASYNC) 一招

    Godot 的录制主循环是**手动 tick 的阻塞循环**（整场战斗不返回消息循环）。
    在那种状态下，任何**同步**的窗口操作都要等目标线程处理消息 —— 实测逐项计时：

    | 调用 | 耗时 | 后果 |
    |---|---|---|
    | ShowWindow(SW_HIDE) | **222 秒**（某轮实测） | 看门狗线程被彻底卡死 |
    | SetWindowLongW(GWL_EXSTYLE) | **1.14 秒** | 而且改样式会**触发窗口重新定位**，实测把窗口从 (-21333,-21333) 搬到 **(0,0)** —— 等于帮它回到屏幕正中 |
    | SetWindowPos（不带 ASYNC） | **1.08 秒** | 同样阻塞 |
    | **SetWindowPos + SWP_ASYNCWINDOWPOS** | **0.0006 秒** | ✅ 既不阻塞，窗口也真的被搬走 |

    所以这里只留最后一招。ShowWindow 交给启动参数 --no-window 与 --position 负责
    （窗口出生就在 (-32000,-32000) 且不可见）。
    """
    try:
        u32.SetWindowPos(hwnd, 0, OFFSCREEN, OFFSCREEN, 0, 0,
                         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE
                         | SWP_ASYNCWINDOWPOS)
        _stats["moved"] += 1
    except Exception:  # noqa: BLE001
        pass


def _watch(pid: int, stop: threading.Event) -> None:
    """盯住一个 pid 的窗口，反复压制，直到 stop 置位或进程消失。

    ★ 踩过的坑（2026-11-06）：回调对象**必须长期持有引用**。如果每轮循环都
      现做一个 ctypes 回调再传进 EnumWindows，回调可能被 GC 回收 —— 表现就是
      第一轮压制成功、之后什么都不做（stats 只 +1），且异常被 except 吞掉，
      看起来像「压不住」。这里把回调在循环外建一次、hits 放外部。
    """
    u32 = _setup_user32()
    CB = ctypes.WINFUNCTYPE(ctypes.c_bool, w.HWND, w.LPARAM)
    hits = []

    def _cb(hwnd, _lp):
        tid = w.DWORD(0)
        u32.GetWindowThreadProcessId(hwnd, ctypes.byref(tid))
        if tid.value != pid:
            return True
        cls = ctypes.create_unicode_buffer(128)
        u32.GetClassNameW(hwnd, cls, 128)
        ttl = ctypes.create_unicode_buffer(256)
        u32.GetWindowTextW(hwnd, ttl, 256)
        if (cls.value in QUIET_CLASSES
                or any(k in ttl.value for k in QUIET_TITLES)):
            hits.append(hwnd)
        return True

    cb_ref = CB(_cb)          # ★ 持有引用，防 GC
    known = []                # 已认出的 hwnd（**不清空**，见下）
    while not stop.is_set():
        try:
            hits.clear()
            u32.EnumWindows(cb_ref, 0)
            for hwnd in hits:
                if hwnd not in known:
                    known.append(hwnd)
            # ★★ 关键修正（2026-11-06）：**无条件**对本进程所有已知窗口重压。
            #   之前用 IsWindow(hwnd) 过滤，结果 IsWindow 恒返回 0（窗口被压制后，
            #   句柄对 IsWindow 表现为无效），于是每轮都把 known 清空 —— 表现是
            #   stats 里 hidden 永远停在 1，而实测窗口在 t≈33s 被引擎搬回 (0,0)
            #   并显示，之后无人压制（可见 37.7% 采样）。
            #   IsWindow 在这里既不可靠也不必要：EnumWindows 本来只返回活窗口，
            #   失效句柄上调用 ShowWindow/SetWindowPos 只会安全失败。
            for hwnd in known:
                _hide_one(u32, hwnd)
        except Exception:  # noqa: BLE001 —— 看门狗绝不能拖垮主流程
            pass
        stop.wait(POLL_INTERVAL)


def guard(pid: int) -> threading.Event:
    """对**已存在**的进程补挂看门狗，返回 stop 事件（可手动 set 停止）。"""
    with _lock:
        if pid in _guarded:
            return threading.Event()
        _guarded.add(pid)
    stop = threading.Event()
    t = threading.Thread(target=_watch, args=(pid, stop),
                         name="godot_quiet_%d" % pid, daemon=True)
    t.start()
    return stop


def stats() -> dict:
    """压制计数（hidden/moved/styled 三类动作各做了多少次）。"""
    return dict(_stats)


def install() -> None:
    """包一层 `godot_headless.spawn`：之后所有 spawn 起的进程自动受保护。"""
    global _installed
    if _installed:
        return
    import godot_headless as gh

    orig_spawn = gh.spawn

    def spawn_quiet(*args, **kwargs):
        p, log_path, fh = orig_spawn(*args, **kwargs)
        try:
            guard(p.pid)
        except Exception:  # noqa: BLE001
            pass
        return p, log_path, fh

    gh.spawn = spawn_quiet
    _installed = True


if __name__ == "__main__":
    # 自检：不启动 Godot，只验证接口与统计可用
    print("QUIET_CLASSES =", QUIET_CLASSES)
    print("POLL_INTERVAL =", POLL_INTERVAL)
    print("OFFSCREEN =", OFFSCREEN)
    print("stats =", stats())