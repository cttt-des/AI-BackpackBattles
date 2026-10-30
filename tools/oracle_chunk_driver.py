# -*- coding: utf-8 -*-
"""受控神谕批量驱动（并行版，2026-10-30 重写）。

为什么分块：oracle_fight.gd 的批量在 SceneTree 脚本里以阻塞循环手动 tick，
MessageQueue 只能在帧末 flush，call_deferred/queue_free/request_ready 消息跨场
累积（实测 ~116 场后队列溢出内刷，陈旧目标逐条报错，单场 532s/831MB）。
ORACLE_FIGHT_CHUNK=N 让每个进程跑满 N 场即优雅退出（帧末一次干净 flush），
本驱动反复重入直到用例全部完成（resume 幂等：events.json 非空即跳过）。

为什么并行：每场是完全独立的录制（seed/run/round 都来自用例本身，写各自的
output/oracle/fights/<case_id>/），进程间无数据依赖，只有 CPU 与 IO 成本。
故按 pending 均分 N 片、每片一个 Godot 进程，各片用例经 ORACLE_ONLY_CASES
下发（该变量按 fights.json 顺序保序过滤，正是我们要的语义）。

★ 三条硬约束（照抄别改）：
  1. Godot 3.6 **没有 --headless**（4.x 才有）。写了会被当位置参数忽略、走
     普通窗口路径——屏幕上真出窗口，还更容易被搜狗输入法注入弹
     "OpenMem failed" 模态框。统一走 tools/godot_headless.py（--no-window）。
  2. 本沙箱**禁止匿名管道**，capture_output/PIPE 都会 CreatePipe 失败
     （PermissionError [WinError 5]）；输出一律重定向到文件再读回。
  3. 并行时每个 Godot 必须**独立 APPDATA**：user:// 落在其下，共享会互踩
     日志句柄（叠加上面第 1 条的 IME 弹窗）。godot_headless.env(tag) 负责隔离。

★ 已知限制：oracle_fight.gd 会把"预检剔除"的场写进
  output/oracle/fights/_preflight_dropped.txt（整文件覆盖写），并行时后写者
  覆盖先写者。现网该文件为空（914 场全部录成），故不影响；若将来出现非空
  剔除，本驱动的"连续两轮无进展即停"会兜底报错，不会静默产出假语料。

用法：python tools/oracle_chunk_driver.py [chunk_size] [max_rounds] [jobs]
      jobs 省略或 0 = 按当时机器资源自动决定
"""
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import godot_headless as gh  # noqa: E402

REPO = gh.ROOT
ROOT = os.path.join(REPO, "output", "oracle", "fights")
CASES = os.path.join(REPO, "oracle", "fights.json")

CHUNK = int(sys.argv[1]) if len(sys.argv) > 1 else 60
MAX_ROUNDS = int(sys.argv[2]) if len(sys.argv) > 2 else 12
REQ_JOBS = int(sys.argv[3]) if len(sys.argv) > 3 else 0

# 并行度：oracle 单进程比 gd_core 重得多（整局仿真 + SQLite + 大量文件写），
# 内存预算按 1.5 GB 一份（实测单进程常驻远低于此，长战峰值约 1 GB）、
# 上限 4 路（再多是磁盘写争用，收益递减）。
ORACLE_PER_JOB_MEM_GB = 1.5
ORACLE_MAX_JOBS = 4
PER_CHUNK_TIMEOUT = 100 * 60  # 单块墙钟上限（秒）


def avail_mem_gb():
    try:
        import ctypes

        class M(ctypes.Structure):
            _fields_ = [("dwLength", ctypes.c_ulong), ("dwMemoryLoad", ctypes.c_ulong),
                        ("ullTotalPhys", ctypes.c_ulonglong), ("ullAvailPhys", ctypes.c_ulonglong),
                        ("ullTotalPageFile", ctypes.c_ulonglong), ("ullAvailPageFile", ctypes.c_ulonglong),
                        ("ullTotalVirtual", ctypes.c_ulonglong), ("ullAvailVirtual", ctypes.c_ulonglong),
                        ("ullAvailExtendedVirtual", ctypes.c_ulonglong)]

        st = M()
        st.dwLength = ctypes.sizeof(M)
        if not ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(st)):
            return 8.0
        return float(st.ullAvailPhys) / (1024.0 ** 3)
    except Exception:
        return 8.0


def auto_jobs(n_cases):
    if n_cases <= 0:
        return 1
    if REQ_JOBS > 0:
        return max(1, min(REQ_JOBS, ORACLE_MAX_JOBS, n_cases))
    cpu = os.cpu_count() or 1
    return max(1, min(ORACLE_MAX_JOBS, max(1, cpu - 1),
                      max(1, int(avail_mem_gb() // ORACLE_PER_JOB_MEM_GB)), n_cases))


def dropped_ids():
    p = os.path.join(ROOT, "_preflight_dropped.txt")
    if not os.path.exists(p):
        return set()
    try:
        return set(open(p, encoding="utf-8").read().split())
    except OSError:
        return set()


def pending_cases():
    d = json.load(open(CASES, encoding="utf-8"))
    dropped = dropped_ids()
    out = []
    for c in d["cases"]:
        cid = c["case_id"]
        if cid in dropped:
            continue
        ev = os.path.join(ROOT, cid, "events.json")
        if not os.path.exists(ev):
            out.append(cid)
            continue
        try:
            if json.load(open(ev, encoding="utf-8")).get("event_count", 0) <= 0:
                out.append(cid)
        except Exception:
            out.append(cid)
    return out


def split_even(ids, jobs):
    """保序均分：第 i 片拿 ids[i::jobs]。录制时长与用例顺序无关，均分即可。"""
    return [ids[i::jobs] for i in range(jobs)]


def main():
    print("[cfg] chunk=%d max_rounds=%d jobs=%s CPU=%d 可用内存=%.1fGB"
          % (CHUNK, MAX_ROUNDS, REQ_JOBS or "auto", os.cpu_count() or 1, avail_mem_gb()),
          flush=True)
    no_progress_rounds = 0
    for rnd in range(1, MAX_ROUNDS + 1):
        pend = pending_cases()
        if not pend:
            print("DRIVER: all cases done")
            return 0
        jobs = auto_jobs(len(pend))
        buckets = [b for b in split_even(pend, jobs) if b]
        jobs = len(buckets)
        print("[%s] round %d: pending=%d jobs=%d chunk=%d 片大小=%s"
              % (time.strftime("%H:%M:%S"), rnd, len(pend), jobs, CHUNK,
                 [len(b) for b in buckets]), flush=True)
        before = len(pend)
        t0 = time.time()

        # 各片一次起齐（隐藏桌面 + 各自 APPDATA，互不干扰），再统一收尾
        procs = []
        for i, shard in enumerate(buckets):
            p, log_path, fh = gh.spawn(
                gh.cmd(project="oracle", script="oracle_fight.gd"),
                label="oracle_r%d_s%d" % (rnd, i), tag="orc%d" % i,
                env_extra={"ORACLE_FIGHT_CHUNK": CHUNK,
                           "ORACLE_ONLY_CASES": ",".join(shard)})
            procs.append((i, len(shard), p, fh, log_path))

        rcs = []
        for i, n, p, fh, log_path in procs:
            try:
                rc = p.wait(timeout=PER_CHUNK_TIMEOUT)
            except Exception:
                p.kill()
                p.wait()
                rc = -9
            fh.close()
            rcs.append(rc)
            print("[%s]   shard %d: n=%d rc=%s" % (time.strftime("%H:%M:%S"), i, n, rc),
                  flush=True)
            if rc != 0:
                tail = [l for l in gh.read_log(log_path).splitlines()
                        if l.strip() and not gh.is_noise(l)][-3:]
                for t in tail:
                    print("      " + t[:150])

        after = len(pending_cases())
        print("[%s] round %d done: wall=%.0fs pending %d -> %d%s"
              % (time.strftime("%H:%M:%S"), rnd, time.time() - t0, before, after,
                 "" if not any(rcs) else " (rc=%s)" % rcs), flush=True)
        if after == 0:
            print("DRIVER: all cases done")
            return 0
        if after >= before:
            no_progress_rounds += 1
            print("DRIVER: no progress this round (%d)" % no_progress_rounds, flush=True)
            if no_progress_rounds >= 2:
                print("DRIVER: two rounds without progress — stop for manual triage")
                return 2
        else:
            no_progress_rounds = 0
    print("DRIVER: max rounds reached, pending=%d" % len(pending_cases()))
    return 1


if __name__ == "__main__":
    sys.exit(main())
