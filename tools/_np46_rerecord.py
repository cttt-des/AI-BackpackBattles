#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""_np46_rerecord.py — np46 净化重录批量包装器（台账 §6m85）。

使命：以净化版 harness（oracle/oracle_fight.gd，np46 逐案隔离 §6m82 + 事件闸
全长 §6m83）重录语料全集，使「语料每场战斗=全新状态的确定性执行：单场复放
≡ 语料 by construction」（§6m82-84 已单例验证：run986_r12 三方一致翻绿零键控、
run894_r18 长场全长复现逐事件全等）。

与 tools/oracle_chunk_driver.py 的关系：同一批量入口语义（fights.json 全集 +
ORACLE_FIGHT_CHUNK 配额 + ORACLE_ONLY_CASES 分片 + godot_headless 隐藏桌面/
独立 APPDATA/文件重定向 + resume 幂等），差异：
  1) ORACLE_FIGHTS_ROOT 默认 <repo>/output/oracle/fights（语料写授权面，
     用户 2026-11-06 批准；主脚本已备份 output/oracle/fights_pre_npur_20261106）；
  2) 事件闸全长由 harness 内置（[M14]：事件闸 200000/墙钟 1200s），无需 env；
  3) 收尾写 output/oracle/fights/_batch_summary.txt：status=PASS 仅当
     fights.json 全部用例 events.json 非空且本进程零失败；
  4) 前置安全检查：备份目录缺失即拒绝开跑（防无备份重录）。

用法：
  python -X utf8 tools/_np46_rerecord.py              # 全量（自动分片并行）
  python -X utf8 tools/_np46_rerecord.py 60 12 4      # chunk=60 rounds=12 jobs=4
  python -X utf8 tools/_np46_rerecord.py --check      # 只做前置检查与 pending 统计
  python -X utf8 tools/_np46_rerecord.py --cases run986_r12,run894_r18   # 定向
环境变量：
  ORACLE_FIGHTS_ROOT   输出根（默认 output/oracle/fights，绝对路径）
  ORACLE_FIGHT_CHUNK   单进程配额（默认 60；0=不限——不推荐，MessageQueue 溢出面）
"""
import argparse
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import godot_headless as gh  # noqa: E402

REPO = gh.ROOT
CASES = os.path.join(REPO, "oracle", "fights.json")
DEFAULT_ROOT = os.path.join(REPO, "output", "oracle", "fights")
BACKUP_DIR = os.path.join(REPO, "output", "oracle", "fights_pre_npur_20261106")
PER_JOB_MEM_GB = 1.5
MAX_JOBS = 4
PER_CHUNK_TIMEOUT = 100 * 60  # 单块墙钟上限（秒）——事件闸全长后长场更久，故取上限


def fights_root():
    env = os.environ.get("ORACLE_FIGHTS_ROOT", "")
    if env:
        return os.path.abspath(env)
    return DEFAULT_ROOT


def all_cases():
    d = json.load(open(CASES, encoding="utf-8"))
    return [c["case_id"] for c in d["cases"]]


def dropped_ids():
    p = os.path.join(fights_root(), "_preflight_dropped.txt")
    if not os.path.exists(p):
        return set()
    try:
        return set(open(p, encoding="utf-8").read().split())
    except OSError:
        return set()


def case_done(cid):
    ev = os.path.join(fights_root(), cid, "events.json")
    if not os.path.exists(ev):
        return False
    try:
        if json.load(open(ev, encoding="utf-8")).get("event_count", 0) <= 0:
            return False
    except Exception:
        return False
    # 与 harness case_events_done 同判据：还要求 rng_state.txt 已导出
    if not os.path.exists(os.path.join(fights_root(), cid, "rng_state.txt")):
        return False
    # ★ np46 修正（2026-11-06 假门实锤后补，台账 §6m86）：还要求 result.txt 带
    #   净化 harness 标记（[M13]）——否则 10-31 旧语料的 events.json/rng_state.txt
    #   会被 resume 视为已完成，包装器 10 秒假 PASS（output/oracle/fights/
    #   _batch_summary.txt wall_seconds=10 实证），完成度门放行了未重录的语料。
    res = os.path.join(fights_root(), cid, "result.txt")
    if not os.path.exists(res):
        return False
    try:
        with open(res, encoding="utf-8", errors="replace") as fh:
            return "[M13]" in fh.read()
    except OSError:
        return False


def pending_cases(only=None):
    dropped = dropped_ids()
    out = []
    for cid in (only if only is not None else all_cases()):
        if cid in dropped:
            continue
        if not case_done(cid):
            out.append(cid)
    return out


def auto_jobs(n):
    cpu = os.cpu_count() or 1
    try:
        import ctypes

        class M(ctypes.Structure):
            _fields_ = [("dwLength", ctypes.c_ulong), ("dwMemoryLoad", ctypes.c_ulong),
                        ("ullTotalPhys", ctypes.c_ulonglong), ("ullAvailPhys", ctypes.c_ulonglong),
                        ("ullTotalPageFile", ctypes.c_ulonglong), ("ullAvailVirtual", ctypes.c_ulonglong)]

        st = M()
        st.dwLength = ctypes.sizeof(M)
        avail = (float(st.ullAvailPhys) / (1024.0 ** 3)
                 if ctypes.windll.kernel32.GlobalMemoryStatusEx(ctypes.byref(st)) else 8.0)
    except Exception:
        avail = 8.0
    return max(1, min(MAX_JOBS, max(1, cpu - 1), max(1, int(avail // PER_JOB_MEM_GB)), max(1, n)))


def split_even(ids, jobs):
    return [[b for b in ids[i::jobs]] for i in range(jobs)]


def write_summary(ok, extra_lines, jobs_rc, wall, scope_ids=None):
    """收尾写 _batch_summary.txt：status=PASS 仅当本轮范围全部用例完成。

    scope_ids=本轮范围（--cases 定向时为定向清单）；None=全量口径。"""
    cases = all_cases()
    dropped = dropped_ids()
    scope = (scope_ids if scope_ids is not None else cases)
    done = sum(1 for c in scope if case_done(c))
    pend_scope = [c for c in scope if not case_done(c) and c not in dropped]
    lines = [
        "np46 净化重录批量结果（tools/_np46_rerecord.py）",
        "status=%s" % ("PASS" if ok else "FAIL"),
        "cases_total=%d" % len(cases),
        "scope_total=%d" % len(scope),
        "scope_done=%d" % done,
        "preflight_dropped=%d" % len(dropped),
        "pending=%d" % len(pend_scope),
        "wall_seconds=%.0f" % wall,
        "shard_rc=%s" % jobs_rc,
        "harness=oracle/oracle_fight.gd np46（逐案隔离 §6m82 + 事件闸全长 [M14] §6m83）",
        "backup=fights_pre_npur_20261106",
    ]
    lines.extend(extra_lines)
    fh = open(os.path.join(fights_root(), "_batch_summary.txt"), "w", encoding="utf-8")
    fh.write("\n".join(lines) + "\n")
    fh.close()


def main() -> int:
    ap = argparse.ArgumentParser(description="np46 净化重录批量包装器")
    ap.add_argument("chunk", nargs="?", type=int, default=60)
    ap.add_argument("max_rounds", nargs="?", type=int, default=12)
    ap.add_argument("jobs", nargs="?", type=int, default=0, help="0=自动（≤4）")
    ap.add_argument("--cases", default="", help="逗号分隔定向清单（保 fights.json 顺序）")
    ap.add_argument("--check", action="store_true", help="只做前置检查与 pending 统计，不开跑")
    args = ap.parse_args()

    root = fights_root()
    print("[cfg] fights_root=%s" % root)
    print("[cfg] chunk=%d max_rounds=%d jobs=%s" % (args.chunk, args.max_rounds,
                                                   args.jobs or "auto"))
    # 前置安全检查 1：备份在位
    if not os.path.isdir(BACKUP_DIR):
        print("[ABORT] 备份目录缺失：%s——无备份不重录" % BACKUP_DIR, file=sys.stderr)
        return 2
    n_backup = sum(1 for _ in os.listdir(BACKUP_DIR))
    print("[check] 备份目录在位：%s（%d 项）" % (BACKUP_DIR, n_backup))
    # 前置安全检查 2：harness 即净化版（np46 标记在文件内）
    harness = os.path.join(REPO, "oracle", "oracle_fight.gd")
    with open(harness, encoding="utf-8") as fh:
        htxt = fh.read()
    if "reset_residual_state" not in htxt or "np46" not in htxt:
        print("[ABORT] harness 无 np46 逐案隔离标记（reset_residual_state）——拒绝用旧 harness 重录",
              file=sys.stderr)
        return 2
    if "> 200000" not in htxt:
        print("[ABORT] harness 事件闸非全长（200000）——拒绝重录", file=sys.stderr)
        return 2
    print("[check] harness 净化版标记 OK（逐案隔离 + 事件闸 200000）")

    only = [c for c in args.cases.split(",") if c.strip()] or None
    cases = all_cases()
    if only:
        unknown = [c for c in only if c not in set(cases)]
        if unknown:
            print("[ABORT] 未知 case_id：%s" % ",".join(unknown), file=sys.stderr)
            return 2
    pend = pending_cases(only)
    print("[check] 用例 %d 场（fights.json）；pending=%d；preflight_dropped=%d"
          % (len(cases), len(pend), len(dropped_ids())))
    if args.check:
        # ★ 不写 _batch_summary.txt——该文件是真实批量收尾的 PASS/FAIL 口径，
        #   --check 若覆写会把上次真实批量的结论污染掉。
        if pend and os.path.abspath(root) == os.path.abspath(DEFAULT_ROOT):
            print("[hint] pending=%d 且输出根=冻结语料目录：全新重录请改用新目录"
                  "（ORACLE_FIGHTS_ROOT=<repo>/output/oracle/fights_np46）跑满后由主脚本"
                  "原子换目录；resume 幂等只用于中断续跑，不能充当重录开关。" % len(pend))
        print("[check] --check 完成（未写 summary）")
        return 0

    t0 = time.time()
    jobs_rc = []
    no_progress = 0
    for rnd in range(1, args.max_rounds + 1):
        pend = pending_cases(only)
        if not pend:
            break
        n_jobs = args.jobs if args.jobs > 0 else auto_jobs(len(pend))
        buckets = [b for b in split_even(pend, n_jobs) if b]
        print("[%s] round %d: pending=%d jobs=%d chunk=%d 片=%s"
              % (time.strftime("%H:%M:%S"), rnd, len(pend), len(buckets), args.chunk,
                 [len(b) for b in buckets]), flush=True)
        before = len(pend)
        procs = []
        for i, shard in enumerate(buckets):
            env_extra = {
                "ORACLE_FIGHTS_ROOT": root,
                "ORACLE_FIGHT_CHUNK": str(args.chunk),
                "ORACLE_ONLY_CASES": ",".join(shard),
            }
            p, log_path, fh = gh.spawn(
                gh.cmd(project="oracle", script="oracle_fight.gd"),
                label="np46_r%d_s%d" % (rnd, i), tag="np46_%d" % i, env_extra=env_extra)
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
        jobs_rc = rcs
        after = len(pending_cases(only))
        print("[%s] round %d done: wall=%.0fs pending %d -> %d"
              % (time.strftime("%H:%M:%S"), rnd, time.time() - t0, before, after), flush=True)
        if after == 0:
            break
        if after >= before:
            no_progress += 1
            print("DRIVER: no progress (%d)" % no_progress, flush=True)
            if no_progress >= 2:
                print("DRIVER: 两轮无进展——停（人工排查）", flush=True)
                break
        else:
            no_progress = 0

    wall = time.time() - t0
    pend = pending_cases(only)
    ok = (len(pend) == 0) and (not jobs_rc or all(rc == 0 for rc in jobs_rc))
    extra = ["定向=%s" % (",".join(only) if only else "全量")]
    write_summary(ok, extra, jobs_rc, wall, scope_ids=(only if only else None))
    print("NP46-RERECORD: %s（pending=%d，wall=%.0fs）→ %s"
          % ("PASS" if ok else "FAIL", len(pend), wall,
             os.path.join(fights_root(), "_batch_summary.txt")))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
