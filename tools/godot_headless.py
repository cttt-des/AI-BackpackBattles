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
import time
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
# ★ 2026-10-31：桌面名按进程唯一化（_pid 后缀）——desktop heap 是有限资源，
#   单日数百场 Godot 的泄漏对象会撑爆共享桌面的堆 ⇒ 并发子进程挂载失败被
#   Windows 摔回默认桌面=漏窗（np25 重录实测：单发恒静默、4 路并发必漏）。
#   每 driver 进程私有新桌面=新堆；进程退出、桌面随灭、堆自动回收。
DESKTOP_NAME = "dsh_godot_hidden_%d" % os.getpid()

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
    """建（或复用）隐藏桌面，返回句柄。

    ★ 2026-10-31 订正：旧版「每进程只试一次、失败静默回退默认桌面」——
      np25 全量重录实测 driver 首次 CreateDesktopW 瞬态失败 ⇒ 整批 Godot
      全部漏到用户桌面（Engine 类窗口 ×4 实枚举）。铁令=无窗，静默回退
      违规：改为重试 3 次（间隔 0.5s），仍失败**抛 RuntimeError 响亮死**，
      绝不带窗运行。句柄跨调用缓存不变。"""
    global _DESK_HANDLE
    if _DESK_HANDLE is not None:
        return _DESK_HANDLE
    if not sys.platform.startswith("win"):
        return None
    err = None
    for _attempt in range(3):
        try:
            GENERIC_ALL = 0x10000000
            user32 = ctypes.windll.user32
            h = user32.CreateDesktopW(DESKTOP_NAME, None, None, 0, GENERIC_ALL, None)
            if h:
                _DESK_HANDLE = h
                return _DESK_HANDLE
        except Exception as e:  # noqa: BLE001
            err = e
        time.sleep(0.5)
    raise RuntimeError(
        "CreateDesktopW(%s) 连续 3 次失败（err=%r）——拒绝静默回退到可见桌面"
        "（铁令：无窗无弹窗）。请排查 window station 状态后重试。"
        % (DESKTOP_NAME, err))


def _startupinfo(desktop=True):
    """lpDesktop 指到隐藏桌面 + SW_HIDE，双保险。"""
    if not sys.platform.startswith("win"):
        return None
    si = subprocess.STARTUPINFO()
    si.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    si.wShowWindow = 0  # SW_HIDE
    if desktop and _hidden_desktop() is not None:
        si.lpDesktop = "WinSta0\\" + DESKTOP_NAME
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
    si = _startupinfo()
    try:
        k32 = ctypes.WinDLL("kernel32")
        hws = k32.GetProcessWindowStation()
        name = ctypes.create_unicode_buffer(64)
        u32 = ctypes.WinDLL("user32")
        u32.GetUserObjectInformationW(hws, 2, name, 64, None)  # UOI_NAME=2
        winsta = name.value
    except Exception:  # noqa: BLE001
        winsta = "?"
    fh.write(("[gh] provenance pid=%d label=%s lpDesktop=%r deskHandle=%r winsta=%s"
              % (os.getpid(), label,
                 (si.lpDesktop if si is not None else None), _DESK_HANDLE, winsta)).encode())
    fh.flush()
    p = subprocess.Popen(cmdline, cwd=cwd or CWD_DIR, env=e, stdout=fh,
                         stderr=subprocess.STDOUT, startupinfo=si)
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


# ======================= 并行原语（docs/parallel_workflow.md 口径） =======================
#
# 为什么把这些放在模块里而不是每个工具各写一份：
#   docs/parallel_workflow.md §2 规定并行度**每次运行按当时 CPU 与可用内存实时决定**、
#   §3 规定分桶用 LPT、§4 规定禁匿名管道（一律文件重定向）。
#   这几条是环境硬约束，四处复制就会四处漂移（历史上 _np25_tape_run / run_item_parse
#   就是各拼一份 subprocess 且漏了隐藏桌面）。

#: 并行度硬上限。收益递减 + 内存峰值随路数线性放大（实测 5 路上限）。
PARALLEL_MAX_JOBS = 5
#: 单个 Godot worker 的峰值内存预算（GB）。gd_core 与 oracle 长战实测峰值约 1GB。
PER_JOB_MEM_GB = 1.2


def avail_mem_gb() -> float:
    """当前可用物理内存（GB）。Windows 走 GlobalMemoryStatusEx，探测失败退回 8GB。"""
    try:
        class _M(ctypes.Structure):
            _fields_ = [("dwLength", ctypes.c_ulong), ("dwMemoryLoad", ctypes.c_ulong),
                        ("ullTotalPhys", ctypes.c_ulonglong),
                        ("ullAvailPhys", ctypes.c_ulonglong),
                        ("ullTotalPageFile", ctypes.c_ulonglong),
                        ("ullAvailPageFile", ctypes.c_ulonglong),
                        ("ullTotalVirtual", ctypes.c_ulonglong),
                        ("ullAvailVirtual", ctypes.c_ulonglong),
                        ("ullAvailExtendedVirtual", ctypes.c_ulonglong)]

        _st = _M()
        _st.dwLength = ctypes.sizeof(_M)
        if not ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(_st)):
            return 8.0
        return float(_st.ullAvailPhys) / (1024.0 ** 3)
    except Exception:  # noqa: BLE001 —— 探测失败不影响正确性
        return 8.0


def auto_jobs(n_items, requested=0, per_job_mem_gb=None, cap=None):
    """并行度决策：requested>0 时按请求（仍受上限约束），0=按机器资源自动。

    jobs = min( 上限, cpu_count-1, 可用内存//per_job, 任务数 )
    """
    n_items = int(n_items or 0)
    if n_items <= 0:
        return 1
    cap = min(PARALLEL_MAX_JOBS, int(cap or PARALLEL_MAX_JOBS))
    if requested and int(requested) > 0:
        return max(1, min(int(requested), cap, n_items))
    per = float(per_job_mem_gb or PER_JOB_MEM_GB)
    by_cpu = max(1, (os.cpu_count() or 1) - 1)
    by_mem = max(1, int(avail_mem_gb() // per))
    return max(1, min(cap, by_cpu, by_mem, n_items))


def lpt_buckets(items, jobs, weight=None):
    """LPT（Longest Processing Time first）分桶：重活先投，依次投给当前最轻的桶。

    weight: {item: 数值}；不给则按等权（均分）。返回 (桶列表, 每桶负载)。
    为什么不是 items[i::jobs] 轮转：长件会挤进同一片，该片决定总时长
    （实测 914 场 5 片：轮转 384s vs LPT 242s，差 37%）。
    """
    items = list(items)
    jobs = max(1, min(int(jobs), len(items) or 1))
    if weight is None:
        weight = {}
    buckets = [[] for _ in range(jobs)]
    load = [0.0] * jobs
    for it in sorted(items, key=lambda x: -float(weight.get(x, 1))):
        k = load.index(min(load))
        buckets[k].append(it)
        load[k] += float(weight.get(it, 1))
    return [b for b in buckets if b], load


def run_many(specs, label="godot", timeout=None):
    """并行起 N 个 Godot（每个独立 APPDATA + 各自日志），等齐后返回结果表。

    specs: [{"cmd": [...], "tag": "s0", "env_extra": {...}, "timeout": 秒?}, ...]
    返回 [{"index","tag","rc","log","tail"}...]（顺序同 specs）。
    ★ 每片 tag 不同 → env() 按 pid+tag 隔离 APPDATA，多进程不共享 user://。
    ★ 输出一律重定向到文件（沙箱禁匿名管道，PIPE 会 CreatePipe WinError 5）。
    ★ 每个进程都走 _startupinfo() 的隐藏桌面：窗口与 IME 弹窗都不落用户桌面。
    """
    procs = []
    for i, sp in enumerate(specs):
        tag = sp.get("tag") or ("w%d" % i)
        p, log_path, fh = spawn(sp["cmd"], label="%s_%s" % (label, tag), tag=tag,
                                cwd=sp.get("cwd"), env_extra=sp.get("env_extra"))
        procs.append((i, tag, p, fh, log_path, sp.get("timeout") or timeout))
    out = []
    for i, tag, p, fh, log_path, tmo in procs:
        try:
            rc = p.wait(timeout=tmo) if tmo else p.wait()
        except subprocess.TimeoutExpired:
            p.kill()
            p.wait()
            rc = -9
        finally:
            fh.close()
        text = read_log(log_path)
        tail = [l for l in text.splitlines() if l.strip() and not is_noise(l)][-5:]
        out.append({"index": i, "tag": tag, "rc": rc, "log": log_path, "tail": tail})
    return out
