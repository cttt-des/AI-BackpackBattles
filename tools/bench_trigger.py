# -*- coding: utf-8 -*-
"""trigger 链成本占比：这是「单场 212 ms 花在哪」的最大一块（45%）的度量工具。

用法：
    python -X utf8 tools/bench_trigger.py              # 1 场，报占比
    python -X utf8 tools/bench_trigger.py --n 5        # 多场取中位

输出：
    trigger_calls        每场触发次数（R19 约 215）
    per_trigger_us       单次触发耗时（编译臂约 1380 µs）
    trigger_share_pct    触发链占 run 的比例（约 45%）

为什么用纯 py 臂：需要在 Python 层包 `CoreItem.trigger` 计时，编译态 cdef 类
不可打补丁。纯 py 臂的**绝对时间**不可外推（约慢 4 倍），但**同行占比**与编译臂
同构——占比才是这个工具要的答案。
"""
import argparse
import json
import os
import statistics
import sys
import time

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

PL = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_player.json")
OP = os.path.join(_ROOT, "lineups", "truth_20261001_220653_R19_opponent.json")


def main() -> int:
    ap = argparse.ArgumentParser(description="trigger 链成本占比")
    ap.add_argument("--n", type=int, default=3, help="场数（取中位）")
    ap.add_argument("--seed", type=int, default=20260923)
    ap.add_argument("--json", default="")
    args = ap.parse_args()

    os.environ["GD_PURE_PY"] = "1"
    import tools._purepy_arm  # noqa: F401  —— 必须在 gd_core_py 导入前

    from simulator.gd_core_engine import GDCoreEngine
    from gd_core_py.gd_core import CoreItem as CI

    plj = json.load(open(PL, encoding="utf-8"))
    opj = json.load(open(OP, encoding="utf-8"))
    copy = __import__("copy").deepcopy

    cls = CI.CoreItem
    orig = cls.trigger
    acc = {"t": 0.0, "n": 0}
    clock = time.process_time

    def trigger(self, *a, **kw):
        t0 = clock()
        try:
            return orig(self, *a, **kw)
        finally:
            acc["t"] += clock() - t0
            acc["n"] += 1

    cls.trigger = trigger
    rows = []
    try:
        for i in range(args.n):
            acc["t"] = 0.0
            acc["n"] = 0
            e = GDCoreEngine(copy(plj), copy(opj), {}, {},
                             seed=args.seed + i, max_time=180.0)
            t0 = clock()
            e.run()
            total = clock() - t0
            rows.append({
                "seed": args.seed + i, "ticks": int(e._ticks),
                "run_total_s": round(total, 4),
                "trigger_calls": acc["n"],
                "per_trigger_us": round(acc["t"] / acc["n"] * 1e6, 1) if acc["n"] else None,
                "trigger_share_pct": round(acc["t"] / total * 100, 1),
            })
            print(json.dumps(rows[-1], ensure_ascii=False), flush=True)
    finally:
        cls.trigger = orig

    out = {
        "n": len(rows),
        "trigger_calls_median": statistics.median(r["trigger_calls"] for r in rows),
        "per_trigger_us_median": statistics.median(r["per_trigger_us"] for r in rows),
        "trigger_share_pct_median": statistics.median(r["trigger_share_pct"] for r in rows),
        "rows": rows,
    }
    print()
    print("中位: 触发 %d 次/场, %.1f us/次, 占 run %.1f%%"
          % (out["trigger_calls_median"], out["per_trigger_us_median"],
             out["trigger_share_pct_median"]))
    if args.json:
        json.dump(out, open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=2)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
