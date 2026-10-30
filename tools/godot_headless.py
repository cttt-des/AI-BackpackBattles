# -*- coding: utf-8 -*-
"""Godot 3.6 无窗口 + 无弹窗启动器（沙箱安全）。所有启动 Godot 的脚本都应走这里。

## 为什么必须这么绕（四条硬约束，均有实证）

1. **Godot 3.6 没有 --headless**（那是 4.x 的参数）。写了它不报错、被当位置
   参数忽略，引擎于是走**普通窗口路径**——屏幕上真的会多一个窗口。

2. **--no-window 也不够**（2026-10-30 实测）：3.6 在 Windows 下仍会创建
   可见的 [Engine] <项目名> 窗口。--video-driver Dummy 更不行——
   3.6 的合法值只有 GLES3/GLES2，写 Dummy 直接报
   "Unknown video driver 'Dummy', aborting." rc=255。

3. **弹窗不是 Godot 弹的**：那是搜狗输入法注入的 DLL 在**宿进程内**调的
   MessageBox（窗口类 #32770、标题 "Error"、内容 t_skinfilemap.cpp /
   OpenMem failed）。它在每台宿进程里都会注入，脚本侧改参数关不掉。

4. **本沙箱禁止匿名管道**：subprocess 的 capture_output=True / PIPE 都在
   CreatePipe 处抛 PermissionError [WinError 5]。输出必须重定向到**文件**。

## 解法：独立隐藏桌面

CreateDesktopW 建一个非交互桌面，STARTUPINFO.lpDesktop 指过去再启动 Godot。
该进程的一切窗口——引擎窗口和 IME 的 MessageBox——都只出现在那个桌面上，
用户桌面一条都看不到（实测：跑完整场，用户桌面泄漏窗口 0 条，产物正常，
rc=0，事件数与冻结语料一致）。这是唯一同时根治"占屏幕"和"弹窗"的办法。

## 用法

    import godot_headless as gh

    rc, out, log = gh.run(gh.cmd(project="oracle", script="oracle_fight.gd"),
                          label="oracle")
    # 需要多个并发时用 env(tag=...) 隔离 APPDATA，或直接用 env_extra 传变量

返回的 out 已解码（UTF-8 优先、回退 CP936——Godot 3 在 Windows 控制台按
本地编码输出中文）。
"""
import ctypes
import ctypes.wintypes as _w
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GODOT = os.path.join(ROOT, "output", "godot36", "Godot_v3.6-stable_win64.exe")
TEST_PROJ = os.path.join(ROOT, "gd_core_test")
ORACLE_PROJ = os.path.join(ROOT, "oracle")

#: 无窗口 + 静音音频。**不要**换回 --headless（3.6 不认）。
BASE_ARGS = ["--no-window", "--audio-driver", "Dummy"]

#: 日志与 cwd 落点。cwd 设到这里，搜狗注入的 debug.log 就不落进仓库根目录。
LOG_DIR = os.path.join(ROOT, "output", "_recovery", "godot_logs")
CWD_DIR = os.path.join(ROOT, "output", "_recovery", "cwd")

#: 隐藏桌面名（同一进程复用同一个桌面，避免每场建一个）
DESKTOP_NAME = "dsh_godot_hidden"

_SEQ = 0
_DESK_HANDLE = None
_DESK_TRIED = False

#: 与结论无关的启动/退出噪声（Godot 会加 "ERROR: "/"WARNING: " 前缀，故用子串匹配）
NOISE_KEYS = (
    "Godot Engine v", "OpenGL ES", "Async. shader",
    "ObjectDB instances leaked", "Resources still in use",
    "_first != nullptr", "at: ~List", "at: cleanup", "at: clear",
    # 搜狗 IME 注入（t_skinfilemap.cpp）：抢共享内存失败→自动重建成功，纯噪声
    "SGRenderLog", "OpenMem", "t_skinfilemap", "sgime_", "打开Filemap失败",
)


def decode(raw: bytes) -> str:
    """Godot 3 在 Windows 控制台按 CP936 输出中文，写文件走 UTF-8。"""
    for enc in ("utf-8", "cp936"):
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


def is_noise(line: str) -> bool:
    return any(k in line for k in NOISE_KEYS)


def _hidden_desktop():
    """建（或复用）隐藏桌面，返回句柄；失败返回 None（调用方回退普通启动）。"""
    global _DESK_HANDLE, _DESK_TRIED
    if _DESK_HANDLE is not None or _DESK_TRIED:
        return _DESK_HANDLE
    _DESK_TRIED = True
    if not sys.platform.startswith("win"):
        return None
    try:
        GENERIC_ALL = 0x10000000
        user32 = ctypes.windll.user32
        h = user32.CreateDesktopW(DESKTOP_NAME, None, None, 0, GENERIC_ALL, None)
        _DESK_HANDLE = h or None
    except Exception:  # noqa: BLE001 —— 建桌面失败不影响正确性，只是又会出窗口
        _DESK_HANDLE = None
    return _DESK_HANDLE


def _startupinfo(desktop=True):
    """lpDesktop 指到隐藏桌面 + SW_HIDE，双保险。"""
    if not sys.platform.startswith("win"):
        return None
    si = subprocess.STARTUPINFO()
    si.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    si.wShowWindow = 0  # SW_HIDE
    if desktop and _hidden_desktop() is not None:
        si.lpDesktop = DESKTOP_NAME
    return si


def env(tag=None) -> dict:
    """子进程环境：按调用方 PID（可选再带 tag）隔离 APPDATA。"""
    e = dict(os.environ)
    name = str(os.getpid()) if not tag else "%d_%s" % (os.getpid(), tag)
    appdata = os.path.join(ROOT, "output", "_recovery", "appdata_p", name)
    os.makedirs(appdata, exist_ok=True)
    e["APPDATA"] = appdata
    return e


def cmd(*extra, project=None, script=None) -> list:
    """拼命令行。project 可传绝对路径或工作区内的相对名（'oracle'/'gd_core_test'）。"""
    out = [GODOT] + list(BASE_ARGS)
    if project:
        proj = project if os.path.isabs(project) else os.path.join(ROOT, project)
        out += ["--path", proj]
    if script:
        out += ["--script", script]
    out += [str(a) for a in extra]
    return out


def spawn(cmdline, label="godot", cwd=None, tag=None, env_extra=None):
    """异步起一个 Godot（隐藏桌面 + 文件重定向），返回 (Popen, 日志路径, 文件句柄)。

    调用方负责 wait() 并 close() 句柄。这样就绪后即可并行做别的事。
    """
    global _SEQ
    _SEQ += 1
    os.makedirs(LOG_DIR, exist_ok=True)
    os.makedirs(CWD_DIR, exist_ok=True)
    log_path = os.path.join(LOG_DIR, "%s_%d_%d.log" % (label, os.getpid(), _SEQ))
    e = env(tag)
    if env_extra:
        e.update({k: str(v) for k, v in env_extra.items()})
    fh = open(log_path, "wb")
    p = subprocess.Popen(cmdline, cwd=cwd or CWD_DIR, env=e, stdout=fh,
                         stderr=subprocess.STDOUT, startupinfo=_startupinfo())
    return p, log_path, fh


def read_log(log_path: str) -> str:
    try:
        with open(log_path, "rb") as lf:
            return decode(lf.read())
    except OSError:
        return ""


def run(cmdline, label="godot", cwd=None, timeout=None, tag=None, env_extra=None):
    """跑一次 Godot，返回 (rc, 解码后的输出, 日志路径)。

    cwd 默认 CWD_DIR（**不是**工作区根）——搜狗注入会在 cwd 下写 debug.log，
    放这里就不污染仓库；Godot 的项目定位靠 --path，与 cwd 无关。
    timeout 超时返回 rc=-9（日志仍可读）。
    """
    p, log_path, fh = spawn(cmdline, label=label, cwd=cwd, tag=tag, env_extra=env_extra)
    try:
        rc = p.wait(timeout=timeout) if timeout else p.wait()
    except subprocess.TimeoutExpired:
        p.kill()
        p.wait()
        rc = -9
    finally:
        fh.close()
    return rc, read_log(log_path), log_path
