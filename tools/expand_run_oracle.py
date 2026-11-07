#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_run_oracle.py — 扩样语料跑批（神谕 oracle_fight.gd，隔离工程 + 并行分片）

为什么用隔离工程副本：
  oracle_fight.gd 固定读 res://fights.json 与 res://data/history.db。扩样用例表
  与合并库不能塞进 oracle/（真值面红线，且会破坏 914 场口径），故把整个工程复制到
  output/_expand/oracle_proj/，只在副本里替换这两个数据文件，脚本一字不改，
  输出用 ORACLE_FIGHTS_ROOT 重定向到 output/oracle/expand/fights/。

硬约束（照抄 tools/oracle_chunk_driver.py / docs/parallel_workflow.md）：
  1) Godot 3.6 没有 --headless，统一走 tools/godot_headless.py（隐藏桌面 + 无窗口）。
  2) 禁匿名管道：输出一律文件重定向（gh.spawn 已处理）。
  3) 并行时每个进程独立 APPDATA（gh.env(tag) 已处理）。
  4) ORACLE_FIGHT_CHUNK 必须小（默认 60）：MessageQueue 跨场累积，约 116 场后
     单场可劣化到 500s+。

resume 幂等：<fights_root>/<case_id>/events.json 存在且 event_count>0 即视为完成。

用法：
    python -X utf8 tools/expand_run_oracle.py --smoke            # 前 20 场冒烟
    python -X utf8 tools/expand_run_oracle.py --cases sub.json   # 指定用例表
    python -X utf8 tools/expand_run_oracle.py                    # 全量（自动分片并行）
环境变量：
    ORACLE_FIGHTS_ROOT   输出根（默认 output/oracle/expand/fights）
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import godot_headless as gh  # noqa: E402

REPO = gh.ROOT
CASES_DEFAULT = os.path.join(REPO, "output", "oracle", "expand", "cases.json")
DB_DEFAULT = os.path.join(REPO, "output", "oracle", "expand", "data", "history.db")
ROOT_DEFAULT = os.path.join(REPO, "output", "oracle", "expand", "fights")
PROJ_SRC = os.path.join(REPO, "oracle")
PROJ_DST = os.path.join(REPO, "output", "_expand", "oracle_proj")
PER_JOB_MEM_GB = 1.5
MAX_JOBS = 4
PER_CHUNK_TIMEOUT = 100 * 60
CHUNK_DEFAULT = 60


def avail_mem_gb() -> float:
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


def ensure_project(cases_path: str, db_path: str, rebuild: bool = False) -> str:
    """把 oracle/ 复制成隔离副本，并只替换副本里的 fights.json 与 data/history.db。"""
    proj = PROJ_DST
    if rebuild or not os.path.isdir(proj):
        if os.path.isdir(proj):
            print("[proj] 清理旧副本 %s" % proj, flush=True)
            shutil.rmtree(proj)
        t0 = time.time()
        print("[proj] 复制工程 %s -> %s" % (PROJ_SRC, proj), flush=True)
        shutil.copytree(PROJ_SRC, proj)
        print("[proj] 复制完成 %.1fs" % (time.time() - t0), flush=True)
    shutil.copyfile(cases_path, os.path.join(proj, "fights.json"))
    os.makedirs(os.path.join(proj, "data"), exist_ok=True)
    shutil.copyfile(db_path, os.path.join(proj, "data", "history.db"))
    print("[proj] 已注入副本数据集: fights.json <- %s / data/history.db <- %s"
          % (os.path.relpath(cases_path, REPO), os.path.relpath(db_path, REPO)), flush=True)
    return proj


def fights_root() -> str:
    env = os.environ.get("ORACLE_FIGHTS_ROOT", "")
    return os.path.abspath(env) if env else ROOT_DEFAULT


def load_cases(path: str):
    with open(path, encoding="utf-8") as f:
        doc = json.load(f)
    return doc, [c["case_id"] for c in doc["cases"]]


def case_done(root: str, cid: str) -> bool:
    ev = os.path.join(root, cid, "events.json")
    if not os.path.exists(ev):
        return False
    try:
        with open(ev, encoding="utf-8") as f:
            return int(json.load(f).get("event_count", 0)) > 0
    except Exception:
        return False


def dropped_ids(root: str) -> set:
    p = os.path.join(root, "_preflight_dropped.txt")
    if not os.path.exists(p):
        return set()
    try:
        with open(p, encoding="utf-8") as f:
            return set(f.read().split())
    except OSError:
        return set()


def pending(root: str, all_ids):
    dropped = dropped_ids(root)
    return [cid for cid in all_ids if cid not in dropped and not case_done(root, cid)]


def auto_jobs(n_cases: int, req: int) -> int:
    if n_cases <= 0:
        return 1
    if req > 0:
        return max(1, min(req, MAX_JOBS, n_cases))
    cpu = os.cpu_count() or 1
    return max(1, min(MAX_JOBS, max(1, cpu - 1),
                      max(1, int(avail_mem_gb() // PER_JOB_MEM_GB)), n_cases))


def main() -> int:
    ap = argparse.ArgumentParser(description="扩样语料跑批（隔离工程 + 并行分片）")
    ap.add_argument("--cases", default=CASES_DEFAULT)
    ap.add_argument("--db", default=DB_DEFAULT, help="合并后的历史库（含扩样 run）")
    ap.add_argument("--root", default="", help="输出根（默认 output/oracle/expand/fights）")
    ap.add_argument("--chunk", type=int, default=CHUNK_DEFAULT)
    ap.add_argument("--jobs", type=int, default=0, help="并行度（0=自动，上限 %d）" % MAX_JOBS)
    ap.add_argument("--smoke", type=int, default=0, help="只跑前 N 场（冒烟）")
    ap.add_argument("--max-rounds", type=int, default=40)
    ap.add_argument("--rebuild-proj", action="store_true", help="强制重复制工程副本")
    args = ap.parse_args()

    root = os.path.abspath(args.root) if args.root else ROOT_DEFAULT
    os.makedirs(root, exist_ok=True)
    proj = ensure_project(args.cases, args.db, rebuild=args.rebuild_proj)
    doc, all_ids = load_cases(args.cases)
    if args.smoke:
        # 冒烟挑分布最散的前 N 场：等距抽样，避免全是高稀有长场
        step = max(1, len(all_ids) // args.smoke)
        all_ids = all_ids[::step][: args.smoke]
        print("[smoke] 抽样 %d 场：%s" % (len(all_ids), all_ids[:5]), flush=True)

    print("[cfg] cases=%d chunk=%d jobs=%s CPU=%d 可用内存=%.1fGB root=%s"
          % (len(all_ids), args.chunk, args.jobs or "auto", os.cpu_count() or 1,
             avail_mem_gb(), root), flush=True)

    no_progress = 0
    for rnd in range(1, args.max_rounds + 1):
        pend = pending(root, all_ids)
        if not pend:
            print("DRIVER: all cases done", flush=True)
            print_summary(root, doc, all_ids)
            return 0
        jobs = auto_jobs(len(pend), args.jobs)
        buckets = [pend[i::jobs] for i in range(jobs)]
        buckets = [b for b in buckets if b]
        jobs = len(buckets)
        print("[%s] round %d: pending=%d jobs=%d chunk=%d 片大小=%s"
              % (time.strftime("%H:%M:%S"), rnd, len(pend), jobs, args.chunk,
                 [len(b) for b in buckets]), flush=True)
        before = len(pend)
        t0 = time.time()
        procs = []
        for i, shard in enumerate(buckets):
            p, log_path, fh = gh.spawn(
                gh.cmd(project=proj, script="oracle_fight.gd"),
                label="expand_r%d_s%d" % (rnd, i), tag="exp%d" % i,
                env_extra={"ORACLE_FIGHT_CHUNK": args.chunk,
                           "ORACLE_ONLY_CASES": ",".join(shard),
                           "ORACLE_FIGHTS_ROOT": root})
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
            print("[%s]   shard %d: n=%d rc=%s" % (time.strftime("%H:%M:%S"), i, n, rc), flush=True)
            if rc != 0:
                tail = [ln for ln in gh.read_log(log_path).splitlines()
                        if ln.strip() and not gh.is_noise(ln)][-4:]
                for t in tail:
                    print("      " + t[:160], flush=True)
        after = len(pending(root, all_ids))
        print("[%s] round %d done: wall=%.0fs pending %d -> %d"
              % (time.strftime("%H:%M:%S"), rnd, time.time() - t0, before, after), flush=True)
        if after == 0:
            print("DRIVER: all cases done", flush=True)
            print_summary(root, doc, all_ids)
            return 0
        if after >= before:
            no_progress += 1
            print("DRIVER: no progress this round (%d)" % no_progress, flush=True)
            if no_progress >= 2:
                print("DRIVER: 连续两轮无进展，停止待人工排查", flush=True)
                print_summary(root, doc, all_ids)
                return 2
        else:
            no_progress = 0

    print("DRIVER: max rounds reached, pending=%d" % len(pending(root, all_ids)), flush=True)
    print_summary(root, doc, all_ids)
    return 1


def print_summary(root: str, doc, all_ids) -> None:
    done = [cid for cid in all_ids if case_done(root, cid)]
    dropped = dropped_ids(root)
    rows = []
    winners = {"player": 0, "opponent": 0, "draw": 0, "-": 0}
    for cid in all_ids:
        p = os.path.join(root, cid, "result.txt")
        if not os.path.exists(p):
            continue
        kv = {}
        try:
            with open(p, encoding="utf-8", errors="replace") as f:
                for line in f:
                    if "=" in line:
                        k, v = line.strip().split("=", 1)
                        kv[k] = v
        except OSError:
            continue
        w = kv.get("winner", "-")
        winners[w] = winners.get(w, 0) + 1
        rows.append({"case_id": cid, "status": kv.get("status"), "winner": w,
                     "ticks": kv.get("ticks"), "event_count": kv.get("event_count"),
                     "player_hp": kv.get("player_hp"), "opponent_hp": kv.get("opponent_hp")})
    summary = {
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "cases_total": len(all_ids),
        "cases_done": len(done),
        "cases_missing": len(all_ids) - len(done),
        "preflight_dropped": sorted(dropped),
        "winners": winners,
        "rows": rows,
    }
    with open(os.path.join(root, "_batch_summary.json"), "w", encoding="utf-8", newline="\n") as f:
        json.dump(summary, f, ensure_ascii=False, indent=1)
        f.write("\n")
    txt = ["status=%s" % ("PASS" if len(done) == len(all_ids) else "PARTIAL"),
           "cases_total=%d cases_done=%d preflight_dropped=%d"
           % (len(all_ids), len(done), len(dropped)),
           "winners=%s" % winners]
    with open(os.path.join(root, "_batch_summary.txt"), "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(txt) + "\n")
    print("[summary] done=%d/%d dropped=%d winners=%s"
          % (len(done), len(all_ids), len(dropped), winners), flush=True)


if __name__ == "__main__":
    sys.exit(main())
