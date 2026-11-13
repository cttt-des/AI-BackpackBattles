# -*- coding: utf-8 -*-
"""训练侧标准吞吐基准（`--bench` 入口，§10.5 工具化 / §12.5 P3）。

为什么必须固定批量：§10.6 实证小批量读数被池启动摊销污染（~78% → 3.3 场/s，
常驻后 8-9 场/s），且场/s 随外部负载能差 2 倍（§12.2）。本入口把三件事钉死：
  ① 固定 200 场批量（默认；训练真实评估批量），走真实评估路径
     （`evaluator.eval_vs_pool` → `_run_jobs` → `_battle`，同 seeds CRN 结构）；
 ② 场/s 必须与负载同时报出：`load_pct`（采样 CPU 负载 %）+ `cores_eff`
   （子进程 CPU 秒合计 / 墙钟 = 实际拿到的核数）；
 ③ `cores_eff/workers < 0.85` 时显式打「读数不可直接引用」警告——
   引用吞吐结论必须带这两列，否则视为无效口径。

用法：
    python -X utf8 trainer/bench.py                 # 200 场 @ 8 worker
    python -X utf8 trainer/bench.py --n 400 --workers 4
    python -X utf8 trainer/bench.py --json output/perf/trainer_bench.json
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from trainer.evaluator import OpponentPool, eval_vs_pool  # noqa: E402


def _load_pct() -> float:
    try:
        import psutil
        return psutil.cpu_percent(interval=0.5)
    except Exception:  # noqa: BLE001
        return -1.0


def _cores_sampler(stop_evt, acc, interval=0.15):
    """后台线程:对子进程 CPU 做时间积分 → cores_eff(实际在用的核数)。

    Windows 的 os.times().children_* 恒为 0(文档口径),不能用于子进程 CPU;
    psutil 逐 pid 累计值做差分,对已退出 worker 的欠计 ≤1 个采样窗
    (8 worker × 0.15s 上限 ≈ 总 CPU 的 ~2-6%,系统性略低估——按保守取用)。
    """
    import psutil
    me = psutil.Process()
    prev = {}
    while not stop_evt.is_set():
        cur = {}
        try:
            for ch in me.children(recursive=True):
                try:
                    t = ch.cpu_times()
                    cur[ch.pid] = t.user + t.system
                except psutil.NoSuchProcess:
                    pass
        except Exception:  # noqa: BLE001
            pass
        delta = 0.0
        for pid, cpu in cur.items():
            p = prev.get(pid)
            if p is not None and cpu >= p:
                delta += cpu - p
        acc.append(delta)
        prev = cur
        stop_evt.wait(interval)


def main() -> int:
    ap = argparse.ArgumentParser(description="训练侧标准吞吐基准（固定批量+负载列）")
    ap.add_argument("--n", type=int, default=200, help="总场数（默认 200，固定批量纪律）")
    ap.add_argument("--seeds", type=int, default=8, help="每对手种子数（CRN 结构）")
    ap.add_argument("--pool", type=int, default=50, help="对手池采样上限")
    ap.add_argument("--target", type=float, default=450.0,
                    help="对手 rating 段起点（与 p2_search 同段，450–650）")
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--json", default="", help="结果落盘路径")
    args = ap.parse_args()

    n_opp = max(1, args.n // args.seeds)
    pool = OpponentPool().sample((args.target, args.target + 200),
                                 max(args.pool, n_opp), seed=42)
    if len(pool) < n_opp:
        print(f"[bench] 池只有 {len(pool)} 个对手，不足 {n_opp}——降级为 "
              f"{len(pool) * args.seeds} 场", flush=True)
        n_opp = len(pool)

    jobs_total = n_opp * args.seeds
    print(f"[bench] 固定批量 {jobs_total} 场（{n_opp} 对手 × {args.seeds} seeds，"
          f"rating {args.target}+，workers={args.workers}）", flush=True)

    import threading
    stop_evt = threading.Event()
    acc = []
    th = threading.Thread(target=_cores_sampler, args=(stop_evt, acc),
                          daemon=True)
    th.start()

    load_before = _load_pct()
    t0 = time.perf_counter()
    r = eval_vs_pool(pool[0], pool[:n_opp], seeds_per_opp=args.seeds,
                     base_seed=2026_11_11, workers=args.workers)
    wall = time.perf_counter() - t0
    load_after = _load_pct()
    stop_evt.set()
    th.join(timeout=2)

    children_cpu = sum(acc)
    tput = jobs_total / wall
    cores_eff = children_cpu / wall if wall > 0 else 0.0
    out = {
        "fights": jobs_total, "workers": args.workers,
        "wall_s": round(wall, 2),
        "tput": round(tput, 2),
        "load_pct_before": load_before, "load_pct_after": load_after,
        "cores_eff": round(cores_eff, 2),
        "cores_eff_ratio": round(cores_eff / args.workers, 3),
        "sim_errors": r["sim_errors"],
        "mean_wr": round(r["mean_wr"], 4),   # 语义完整性旁证（非基准目标）
    }
    print(json.dumps(out, ensure_ascii=False), flush=True)
    if out["cores_eff_ratio"] < 0.85:
        print("⚠ cores_eff/workers < 0.85：外部负载吃掉了核——场/s 不可直接引用，"
              "结论须按 cores_eff 归一（§12.2 纪律）", flush=True)

    if args.json:
        json.dump(out, open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=1)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
