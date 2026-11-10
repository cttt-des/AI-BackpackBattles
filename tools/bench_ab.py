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
ARM_ENV = {"cy": {}, "py": {"GD_PURE_PY": "1"}}


def _run_arm(arm: str, n: int, seed: int, lineup_p: str, lineup_o: str,
             cpu_time: bool = False, warmup: int = 0,
             root: str = "", pure_py: bool = False) -> dict:
    """跑一个臂块（独立子进程），返回该块指标。

    root：臂的工作树（默认本仓库根）。跨树 A/B（M2 前后对比）时 A/B 各指
    一棵树——bench_sim 以 __file__ 定位自己的树，imports/lineups 都取臂侧。
    pure_py：两臂都强制 GD_PURE_PY=1（只比源码差异，隔离 .pyd 产物差异）。
    """
    arm_root = root or ROOT
    bench = os.path.join(arm_root, "tools", "bench_sim.py")
    out = os.path.join(ROOT, "output", "perf", "_ab_%s_tmp.json" % arm)
    env = dict(os.environ)
    env.update(ARM_ENV.get(arm, {}))
    if pure_py:
        env["GD_PURE_PY"] = "1"
    env["PYTHONHASHSEED"] = "0"
    cmd = [sys.executable, "-X", "utf8", bench,
           "--n", str(n), "--rounds", "1", "--seed", str(seed),
           "--json", out, "--label", "ab_" + arm, "--no-evidence"]
    if cpu_time:
        cmd.append("--cpu-time")
    if warmup:
        cmd += ["--warmup", str(warmup)]
    if lineup_p:
        cmd += ["--lineup-p", lineup_p, "--lineup-o", lineup_o]
    r = subprocess.run(cmd, cwd=arm_root, capture_output=True, text=True, env=env)
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
    ap.add_argument("--root-a", default="", help="臂 A 的工作树（默认本仓库根）")
    ap.add_argument("--root-b", default="", help="臂 B 的工作树（默认本仓库根）")
    ap.add_argument("--pure-py", action="store_true",
                    help="两臂都强制 GD_PURE_PY=1（跨树源码 A/B 用）")
    ap.add_argument("--chunks", type=int, default=4,
                    help="每臂每轮的块数（ABBA 块级交错，抗阵发漂移）")
    ap.add_argument("--json", default="")
    a = ap.parse_args()

    arm_a, arm_b = a.arm_a, a.arm_b
    pairs = []
    mean_pairs = []
    rows_a, rows_b = [], []
    chunks = max(2, a.chunks - (a.chunks % 2))   # ABBA 需偶数块
    chunk_n = max(5, a.n // chunks)
    for i in range(a.rounds):
        # ABBA 块级交错：偶数轮 A B B A，奇数轮 B A A B——线性漂移被
        # 镜像抵消，~5s 尺度的阵发漂移也被块配对摊薄（轮级 A→B 抵不掉）。
        first, second = (arm_a, arm_b) if i % 2 == 0 else (arm_b, arm_a)
        schedule = [first, second, second, first] * (chunks // 2)
        sums = {}
        for arm in schedule:
            d = _run_arm(arm, chunk_n, a.seed, a.lineup_p, a.lineup_o,
                         a.cpu_time, a.warmup,
                         a.root_a if arm == arm_a else a.root_b,
                         a.pure_py)
            acc = sums.setdefault(arm, {"p50_ms": [], "mean_ms": [],
                                        "n": 0})
            acc["p50_ms"].append(d["p50_ms"])
            acc["mean_ms"].append(d["mean_ms"])
            acc["n"] += d["n"]
        got = {arm: {k: (statistics.fmean(v) if k != "n" else v)
                     for k, v in acc.items()}
               for arm, acc in sums.items()}
        pa, pb = got[arm_a]["p50_ms"], got[arm_b]["p50_ms"]
        ma, mb = got[arm_a]["mean_ms"], got[arm_b]["mean_ms"]
        rows_a.append(pa)
        rows_b.append(pb)
        pairs.append(round(pb / pa, 4) if pa else None)
        # ★ mean_ms 配对（M0v2）：Windows process_time 粒度 15.625ms，单场
        #   ~320ms 只有 ~20 刻度，n=40 的 p50 全落在刻度整数倍上——一个刻度
        #   就是 5%，亚刻度效应（M2 各项 0.5-5%）完全被量化淹没。均值把刻度
        #   噪声摊到 n 上（分辨率 ≈15.6ms/n ≈ 0.1%），是本机唯一可信的
        #   亚刻度口径；p50 保留作兼容对照。
        mean_pairs.append(round(mb / ma, 4) if ma else None)
        print("[ab] round %d  %s=p50 %.1f/mean %.2fms  %s=p50 %.1f/mean %.2fms"
              "  ratio_mean=%.4f"
              % (i + 1, arm_a, pa, ma, arm_b, pb, mb, mb / ma if ma else 0),
              flush=True)

    ratios = [p for p in pairs if p]
    med_ratio = _median(ratios)
    mean_ratios = [p for p in mean_pairs if p]
    med_mean_ratio = _median(mean_ratios)
    spread_a = (max(rows_a) - min(rows_a)) / _median(rows_a) * 100 if len(rows_a) > 1 else 0
    spread_b = (max(rows_b) - min(rows_b)) / _median(rows_b) * 100 if len(rows_b) > 1 else 0
    spread_r = (max(ratios) - min(ratios)) / med_ratio * 100 if len(ratios) > 1 and med_ratio else 0
    spread_m = ((max(mean_ratios) - min(mean_ratios)) / med_mean_ratio * 100
                if len(mean_ratios) > 1 and med_mean_ratio else 0)

    print()
    print("=" * 64)
    print("A(%s) p50 中位 %.1fms  单臂散布 %.1f%%" % (arm_a, _median(rows_a), spread_a))
    print("B(%s) p50 中位 %.1fms  单臂散布 %.1f%%" % (arm_b, _median(rows_b), spread_b))
    print("配对比值(mean, 主口径) B/A: 中位 %.4f   配对散布 %.2f%%"
          % (med_mean_ratio, spread_m))
    print("配对比值(p50, 对照)      B/A: 中位 %.3f   配对散布 %.1f%%"
          % (med_ratio, spread_r))
    print("=" * 64)

    out = {
        "tool": "bench_ab/v2",
        "n": a.n, "rounds": a.rounds, "seed": a.seed,
        "arm_a": arm_a, "arm_b": arm_b,
        "root_a": a.root_a or ROOT, "root_b": a.root_b or ROOT,
        "pure_py": bool(a.pure_py),
        "clock": "process_time" if a.cpu_time else "perf_counter",
        "warmup": a.warmup,
        "p50_a": rows_a, "p50_b": rows_b,
        "ratio_b_over_a": pairs,
        "median_ratio": med_ratio,
        "spread_a_pct": round(spread_a, 2),
        "spread_b_pct": round(spread_b, 2),
        "spread_ratio_pct": round(spread_r, 2),
        "ratio_mean_b_over_a": mean_pairs,
        "median_ratio_mean": med_mean_ratio,
        "spread_ratio_mean_pct": round(spread_m, 2),
        "verdict": ("ratio_ok" if spread_m <= 5.0 else "ratio_unstable"),
    }
    if a.json:
        os.makedirs(os.path.dirname(a.json), exist_ok=True)
        with io.open(a.json, "w", encoding="utf-8") as fh:
            json.dump(out, fh, ensure_ascii=False, indent=1)
        print("→", a.json)
    return 0 if spread_m <= 5.0 else 1


if __name__ == "__main__":
    sys.exit(main())