# -*- coding: utf-8 -*-
"""并行吞吐基准：用 CPU 口径归一化，排除外部负载对场/s 的污染。

用法：
    python -X utf8 tools/bench_parallel.py                    # 1/2/4 worker 三档 + 绑核对照
    python -X utf8 tools/bench_parallel.py --n 64 --workers 4
    python -X utf8 tools/bench_parallel.py --aff 0,2,4,6 --aff 4,5,6,7

为什么必须归一化（§12.2 实测）：本机负载常在 30–96% 之间跳动，同一命令的场/s
能差 2 倍（5.5–11.7），历史上据此得出的「4w 饱和」「绑核无收益」都被污染过。

本工具同时报三个量：
  core_fps   单进程 CPU 口径吞吐（process_time，与外部负载无关）
  cores_eff  总 CPU 秒 / 墙钟 = 实际拿到的核数（外部负载的直接度量）
  pool_eff   real_tput / (core_fps × workers) = 归一化并行效率
pool_eff 才是可比指标：它已把「机器被别的进程占了」除掉了。
"""
import argparse
import json
import os
import sys
import time
from concurrent.futures import ProcessPoolExecutor

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

PL = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_player.json")
OP = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_opponent.json")


def _one(payload):
    seed, pl, op = payload
    from simulator.gd_core_engine import GDCoreEngine
    t0 = time.process_time()
    eng = GDCoreEngine(pl, op, {}, {}, seed=seed, max_time=180.0)
    eng.run()
    return time.process_time() - t0


def _aff_init(cpus):
    try:
        import multiprocessing as mp
        import psutil
        ident = getattr(mp.current_process(), "_identity", None)
        idx = (ident[0] - 1) % len(cpus) if ident else 0
        psutil.Process().cpu_affinity([cpus[idx]])
    except Exception:  # noqa: BLE001
        pass


def measure(jobs, workers, cpus):
    t0 = time.perf_counter()
    if workers == 1:
        cpu = [_one(j) for j in jobs]
    else:
        with ProcessPoolExecutor(max_workers=workers,
                                 initializer=_aff_init if cpus else None,
                                 initargs=(cpus,) if cpus else ()) as ex:
            cpu = list(ex.map(_one, jobs, chunksize=4))
    wall = time.perf_counter() - t0
    cpu.sort()
    n = len(jobs)
    return {"workers": workers, "affinity": ",".join(map(str, cpus)) if cpus else "none",
            "n": n, "p50_cpu_ms": round(cpu[n // 2] * 1000, 1),
            "total_cpu_s": round(sum(cpu), 3), "wall_s": round(wall, 3),
            "tput": round(n / wall, 2), "cores_eff": round(sum(cpu) / wall, 2)}


def main() -> int:
    ap = argparse.ArgumentParser(description="并行吞吐基准（CPU 口径归一化）")
    ap.add_argument("--n", type=int, default=32, help="场数")
    ap.add_argument("--workers", type=int, default=0, help="0=扫 1/2/4")
    ap.add_argument("--aff", action="append", default=[],
                    help="绑核集合，可多次给，如 --aff 0,2,4,6")
    ap.add_argument("--json", default="")
    args = ap.parse_args()

    pl = json.load(open(PL, encoding="utf-8"))
    op = json.load(open(OP, encoding="utf-8"))
    jobs = [(20260923 + i, pl, op) for i in range(args.n)]

    rows = []
    base = measure(jobs[:min(16, args.n)], 1, None)
    core_fps = min(16, args.n) / base["total_cpu_s"]
    rows.append(dict(base, role="single"))
    print(json.dumps(base, ensure_ascii=False), flush=True)

    workers = [args.workers] if args.workers else [1, 2, 4]
    affs = [tuple(int(x) for x in a.split(",")) for a in args.aff] or [None]
    for w in workers:
        for cpus in affs:
            if w == 1 and cpus:
                continue
            m = measure(jobs, w, cpus)
            m["pool_eff"] = round(m["tput"] / (core_fps * w), 3)
            m["core_fps_basis"] = round(core_fps, 3)
            rows.append(m)
            print(json.dumps(m, ensure_ascii=False), flush=True)

    out = {"core_fps": round(core_fps, 3), "rows": rows}
    if args.json:
        json.dump(out, open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=2)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
