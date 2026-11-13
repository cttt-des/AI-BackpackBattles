# -*- coding: utf-8 -*-
"""装配段性能基准：拆分「构造 vs run」并给出累计口径的装配耗时。

用法：
    python -X utf8 tools/bench_assemble.py                 # 12 场，7 轮取中位
    python -X utf8 tools/bench_assemble.py --n 20 --rounds 9
    python -X utf8 tools/bench_assemble.py --profile       # 加 cProfile 逐函数拆分

为什么不用 process_time：本机粒度 15.62 ms（1/64 s），装配 28 ms 的改善在它下面
根本分不出来。装配口径一律用 perf_counter 累计（N 场总时间 / N）。

输出：assemble_p50_ms / run_p50_ms / asm_share_pct / load_for_ms（--profile 时附 top 表）。
"""
import argparse
import copy
import json
import os
import sys
import time

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

PL = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_player.json")
OP = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_opponent.json")


def _scripts(plj, opj):
    out = []
    for side in (plj, opj):
        for it in (side.get("backpack") or {}).get("items", []) or []:
            out.append(it.get("id", ""))
            for g in it.get("gems", []) or []:
                out.append(g.get("id", ""))
    return [s.replace(" ", "") for s in out]


def _profile(n, plj, opj, eng_cls):
    import cProfile
    import io
    import pstats
    pr = cProfile.Profile()
    pr.enable()
    for i in range(n):
        eng_cls(copy.deepcopy(plj), copy.deepcopy(opj), {}, {},
                seed=20260923 + i, max_time=180.0)
    pr.disable()
    st = pstats.Stats(pr, stream=io.StringIO())
    st.sort_stats("tottime")
    rows = []
    for (fn, lineno, name), (cc, nc, tt, ct, _) in st.stats.items():
        if "simulator" in fn or "_bootstrap" in fn:
            rows.append((tt / n * 1000, ct / n * 1000, nc // n, name,
                         os.path.basename(fn) + ":" + str(lineno)))
    rows.sort(reverse=True)
    print()
    print("{:>13} {:>11} {:>7}  func".format("tottime/场", "cumtime", "calls"))
    for tt, ct, nc, name, loc in rows[:18]:
        print("{:13.2f} {:11.2f} {:7d}  {} @ {}".format(tt, ct, nc, name, loc))


def main() -> int:
    ap = argparse.ArgumentParser(description="装配段性能基准")
    ap.add_argument("--n", type=int, default=12, help="每轮场数")
    ap.add_argument("--rounds", type=int, default=7, help="轮数（取中位）")
    ap.add_argument("--profile", action="store_true", help="附 cProfile 逐函数拆分")
    ap.add_argument("--json", default="", help="结果落盘")
    args = ap.parse_args()

    from simulator.gd_core_engine import GDCoreEngine
    plj = json.load(open(PL, encoding="utf-8"))
    opj = json.load(open(OP, encoding="utf-8"))

    asm, runs = [], []
    clock = time.perf_counter
    for i in range(args.n):
        a0 = clock()
        eng = GDCoreEngine(copy.deepcopy(plj), copy.deepcopy(opj), {}, {},
                           seed=20260923 + i, max_time=180.0)
        a1 = clock()
        eng.run()
        a2 = clock()
        asm.append((a1 - a0) * 1000)
        runs.append((a2 - a1) * 1000)

    per_round = []
    for _ in range(args.rounds):
        t0 = clock()
        for i in range(args.n):
            GDCoreEngine(copy.deepcopy(plj), copy.deepcopy(opj), {}, {},
                         seed=20260923 + i, max_time=180.0)
        per_round.append((clock() - t0) * 1000 / args.n)
    per_round.sort()
    asm.sort()
    runs.sort()
    med = lambda x: x[len(x) // 2]  # noqa: E731

    out = {"n": args.n, "rounds": args.rounds,
           "assemble_p50_ms": round(med(asm), 2),
           "assemble_cumulative_ms": round(med(per_round), 2),
           "run_p50_ms": round(med(runs), 2),
           "asm_share_pct": round(med(asm) / (med(asm) + med(runs)) * 100, 1),
           "all_rounds": [round(x, 2) for x in per_round]}

    # load_for 边际成本（每场都付，不是冷启动摊薄）
    try:
        from gd_core_py import _bootstrap as B
        scripts = _scripts(plj, opj)
        B.load_core()
        B.load_for(scripts)
        N = 300
        t0 = time.perf_counter()
        for _ in range(N):
            B.load_for(scripts)
        out["load_for_ms"] = round((clock() - t0) * 1000 / N, 4)
    except Exception as exc:  # noqa: BLE001
        out["load_for_ms"] = None
        out["load_for_err"] = repr(exc)

    print(json.dumps(out, ensure_ascii=False, indent=2))
    if args.json:
        os.makedirs(os.path.dirname(os.path.abspath(args.json)), exist_ok=True)
        json.dump(out, open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=2)
    if args.profile:
        _profile(args.n, plj, opj, GDCoreEngine)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
