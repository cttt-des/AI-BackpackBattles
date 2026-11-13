# -*- coding: utf-8 -*-
"""规模曲线：物品数 → 每千 tick 耗时。判断「布局/缓存优化」值不值得做的熔断依据。

用法：
    python -X utf8 tools/bench_scale.py                 # 按 20 件一档取代表夹具
    python -X utf8 tools/bench_scale.py --per-bucket 3

为什么需要它：G1（对象图 SoA / 热字段紧凑布局）的预期收益完全取决于
「每 tick 成本是否随物品数超线性增长」。
  · 线性 / 亚线性 ⇒ 瓶颈是每物品的固定算法工作，布局紧凑化收益有限
  · 超线性        ⇒ 工作集超出 L3（本机 6 MB），布局紧凑化有真实收益

⚠️ 已知局限（写清楚，防止后人误用）：
  · 本机 process_time 粒度 15.62 ms，单场 100–250 ms 时量化误差 6–15%；
  · 不同夹具的 trigger 密度差异很大（同规模档内散布可达 56%）⇒ **单点比较无效**，
    只能看整体趋势，且要把 R² 一起报出来；
  · 2026-11-14 首测：物品 7.3x → 成本 9.13x（超线性比 0.46–0.87），R²=0.55，
    **不足以定论**——这正是它被列为 G1 熔断条件而非常规判据的原因。

输出：每档 items / ticks / ms_per_ktick，以及「成本比 vs 规模比」。
"""
import argparse
import glob
import json
import os
import statistics
import sys
import time

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

FIGHTS = os.path.join(_ROOT, "output/oracle/expand/fights")


def side_to_lineup(side, keep=None):
    items = []
    src = side.get("items") or []
    if keep is not None:
        src = src[:keep]
    for it in src:
        occ = it.get("occupied") or [[0, 0]]
        items.append({"id": it.get("name") or it.get("key"),
                      "row": min(int(c[1]) for c in occ),
                      "col": min(int(c[0]) for c in occ),
                      "rotation": int(it.get("rotation", 0) or 0) % 360,
                      "gems": it.get("gems") or []})
    return {"version": 3, "character": side.get("class_name") or "Adventurer",
            "round": 1, "class_modifiers": {"health_multiplier": 100.0},
            "health_override": None,
            "backpack": {"grid": {"rows": 7, "cols": 9}, "items": items},
            "storage": []}


def main() -> int:
    ap = argparse.ArgumentParser(description="规模曲线（布局优化熔断依据）")
    ap.add_argument("--per-bucket", type=int, default=2, help="每 20 件档取几个夹具")
    ap.add_argument("--reps", type=int, default=3, help="每夹具重复次数（取中位）")
    ap.add_argument("--json", default="")
    args = ap.parse_args()

    from simulator.gd_core_engine import GDCoreEngine

    buckets = {}
    for d in sorted(glob.glob(os.path.join(FIGHTS, "run*"))):
        lp_path = os.path.join(d, "lineups.json")
        if not os.path.exists(lp_path):
            continue
        try:
            raw = json.load(open(lp_path, encoding="utf-8"))
        except Exception:  # noqa: BLE001
            continue
        n = len((raw.get("player") or {}).get("items") or []) + \
            len((raw.get("opponent") or {}).get("items") or [])
        b = (n // 20) * 20
        if len(buckets.setdefault(b, [])) >= args.per_bucket:
            continue
        buckets[b].append((n, d, raw))

    rows = []
    for b in sorted(buckets):
        for n, d, raw in buckets[b]:
            lp = side_to_lineup(raw["player"])
            lo = side_to_lineup(raw["opponent"])
            try:
                ts, tks = [], []
                for i in range(args.reps):
                    t0 = time.process_time()
                    e = GDCoreEngine(lp, lo, {}, {},
                                     seed=int(raw.get("seed") or 42) + i,
                                     max_time=180.0)
                    e.run()
                    ts.append(time.process_time() - t0)
                    tks.append(int(e._ticks))
                med, tk = statistics.median(ts), statistics.median(tks)
                per_k = med / tk * 1000 * 1000
                rows.append({"case": os.path.basename(d), "items": n, "ticks": tk,
                             "sec": round(med, 4), "ms_per_ktick": round(per_k, 2)})
                print("%-28s items=%3d ticks=%4d %.4fs %8.2f ms/千tick"
                      % (os.path.basename(d), n, tk, med, per_k), flush=True)
            except Exception as exc:  # noqa: BLE001
                print("FAIL", os.path.basename(d), repr(exc)[:100])

    print()
    if not rows:
        print("无可用夹具")
        return 1
    base = min(rows, key=lambda r: r["items"])
    print("%6s %12s %10s %12s" % ("items", "ms/千tick", "规模比", "成本比"))
    for r in sorted(rows, key=lambda x: x["items"]):
        rn = r["items"] / base["items"]
        rc = r["ms_per_ktick"] / base["ms_per_ktick"]
        print("%6d %12.2f %9.2fx %11.2fx" % (r["items"], r["ms_per_ktick"], rn, rc))
    print()
    print("判读：成本比/规模比 → >1 超线性（布局有收益）<1 亚线性（布局收益有限）")
    print("⚠️ 必须同时看散布与 R²；本机首测 R²=0.55，不足以定论。")
    if args.json:
        json.dump(rows, open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=2)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
