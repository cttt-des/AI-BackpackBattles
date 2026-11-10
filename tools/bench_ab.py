# -*- coding: utf-8 -*-
"""交错 A/B 基准（M0-3）：方差免疫的优化验证工具。

为什么需要：本机（HP ProBook 440 G6，4P/8L，基准 1.6~1.8GHz + 睿频抖动）
单臂 6 轮 p50 散布可达 68%，任何 before/after 绝对值都不可信。交错 A/B 每轮
交替跑两个臂（各自独立子进程），只比**配对差值**，把频率漂移摊到两边。

臂的切换手段：
  · --arm-name 直接写两个臂的环境名（如 py/cy），配 --arm-env
  · 默认臂：cy（编译 .pyd）vs py（GD_PURE_PY=1 强制源码）

用法：
  python -X utf8 tools/bench_ab.py --rounds 5 --n 20
  python -X utf8 tools/bench_ab.py --rounds 5 --n 20 --json output/perf/ab_x.json
"""
from __future__ import annotations

import argparse
import io
import json
import os
import statistics
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BENCH = os.path.join(ROOT, "tools", "bench_sim.py")
ARM_ENV = {"cy": {}, "py": {"GD_PURE_PY": "1"}}


def _run_arm(arm: str, n: int, seed: int, lineup_p: str, lineup_o: str,
             cpu_time: bool = False, warmup: int = 0) -> dict:
    """跑一个臂（独立子进程），返回该轮指标。"""
    out = os.path.join(ROOT, "output", "perf", "_ab_%s_tmp.json" % arm)
    env = dict(os.environ)
    env.update(ARM_ENV.get(arm, {}))
    env["PYTHONHASHSEED"] = "0"
    cmd = [sys.executable, "-X", "utf8", BENCH,
           "--n", str(n), "--rounds", "1", "--seed", str(seed),
           "--json", out, "--label", "ab_" + arm]
    if cpu_time:
        cmd.append("--cpu-time")
    if warmup:
        cmd += ["--warmup", str(warmup)]
    if lineup_p:
        cmd += ["--lineup-p", lineup_p, "--lineup-o", lineup_o]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, env=env)
    if r.returncode != 0:
        raise RuntimeError("arm %s 失败:\n%s\n%s" % (arm, r.stdout[-800:], r.stderr[-800:]))
    with io.open(out, encoding="utf-8") as fh:
        d = json.load(fh)
    try:
        os.remove(out)
    except OSError:
        pass
    return d


def _median(xs):
    return statistics.median(xs) if xs else None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--rounds", type=int, default=5)
    ap.add_argument("--n", type=int, default=20)
    ap.add_argument("--seed", type=int, default=20260923)
    ap.add_argument("--arm-a", default="cy")
    ap.add_argument("--arm-b", default="py")
    ap.add_argument("--lineup-p", default="")
    ap.add_argument("--lineup-o", default="")
    ap.add_argument("--cpu-time", action="store_true",
                    help="用 process_time 计时（推荐：降频机唯一可信口径）")
    ap.add_argument("--warmup", type=int, default=2,
                    help="每臂热身场数（丢弃）")
    ap.add_argument("--json", default="")
    a = ap.parse_args()

    arm_a, arm_b = a.arm_a, a.arm_b
    pairs = []
    rows_a, rows_b = [], []
    for i in range(a.rounds):
        # 顺序交替：偶数轮 A→B，奇数轮 B→A（抵消轮内漂移）
        order = (arm_a, arm_b) if i % 2 == 0 else (arm_b, arm_a)
        got = {}
        for arm in order:
            got[arm] = _run_arm(arm, a.n, a.seed, a.lineup_p, a.lineup_o,
                                a.cpu_time, a.warmup)
        pa, pb = got[arm_a]["p50_ms"], got[arm_b]["p50_ms"]
        rows_a.append(pa)
        rows_b.append(pb)
        pairs.append(round(pb / pa, 4) if pa else None)
        print("[ab] round %d  %s=%.1fms  %s=%.1fms  ratio(%s/%s)=%.3f"
              % (i + 1, arm_a, pa, arm_b, pb, arm_b, arm_a, pb / pa if pa else 0),
              flush=True)

    ratios = [p for p in pairs if p]
    med_ratio = _median(ratios)
    spread_a = (max(rows_a) - min(rows_a)) / _median(rows_a) * 100 if len(rows_a) > 1 else 0
    spread_b = (max(rows_b) - min(rows_b)) / _median(rows_b) * 100 if len(rows_b) > 1 else 0
    spread_r = (max(ratios) - min(ratios)) / med_ratio * 100 if len(ratios) > 1 and med_ratio else 0

    print()
    print("=" * 64)
    print("A(%s) p50 中位 %.1fms  单臂散布 %.1f%%" % (arm_a, _median(rows_a), spread_a))
    print("B(%s) p50 中位 %.1fms  单臂散布 %.1f%%" % (arm_b, _median(rows_b), spread_b))
    print("配对比值 B/A: 中位 %.3f   配对散布 %.1f%%" % (med_ratio, spread_r))
    print("→ 比值口径的散布（%.1f%%）应显著小于单臂（%.1f%% / %.1f%%）"
          % (spread_r, spread_a, spread_b))
    print("=" * 64)

    out = {
        "tool": "bench_ab/v1",
        "n": a.n, "rounds": a.rounds, "seed": a.seed,
        "arm_a": arm_a, "arm_b": arm_b,
        "clock": "process_time" if a.cpu_time else "perf_counter",
        "warmup": a.warmup,
        "p50_a": rows_a, "p50_b": rows_b,
        "ratio_b_over_a": pairs,
        "median_ratio": med_ratio,
        "spread_a_pct": round(spread_a, 2),
        "spread_b_pct": round(spread_b, 2),
        "spread_ratio_pct": round(spread_r, 2),
        "verdict": "ratio_ok" if spread_r <= 5.0 else "ratio_unstable",
    }
    if a.json:
        os.makedirs(os.path.dirname(a.json), exist_ok=True)
        with io.open(a.json, "w", encoding="utf-8") as fh:
            json.dump(out, fh, ensure_ascii=False, indent=1)
        print("→", a.json)
    return 0 if spread_r <= 5.0 else 1


if __name__ == "__main__":
    sys.exit(main())