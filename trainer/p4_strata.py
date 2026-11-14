# -*- coding: utf-8 -*-
"""p4_strata.py — ① 回合分层实验（规划 v3 §7.2，最便宜的信息）

问题：R1 只有 14 格容器，R18 有 63 格——搜索行为（接受的动作类型）是否完全不同？

做法：同一套搜索（p2_search.search_lineage，双种子族确认），只换基线阵容的
回合与对手池（回合匹配）：
  回合 {1, 5, 12, 18} × 每回合 3 血统（corpus 高分 run 的该回合棋盘）× 6 迭代
判据（§7.2）：早期与后期的接受动作类型分布差异 >50% ⇒ 必须分档策略。
产出：trainer/p2_search_report_round{r}.json + 动作接受率汇总表。
"""
from __future__ import annotations

import argparse
import json
import os
import sqlite3
import sys
import time
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import ItemIndex, check_layout, COLS, ROWS  # noqa: E402
from trainer.evaluator import OpponentPool  # noqa: E402
from trainer.p2_search import (search_lineage, bench_pools,  # noqa: E402
                               load_history_lineups_at_round)

FACE_TO_ROT = {0: 0, 1: 90, 2: 180, 3: 270}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rounds", default="1,5,12,18")
    ap.add_argument("--per-round", type=int, default=3)
    ap.add_argument("--pool", type=int, default=100)
    ap.add_argument("--seeds", type=int, default=2)
    ap.add_argument("--max-iters", type=int, default=6)
    ap.add_argument("--n-cands", type=int, default=6)
    ap.add_argument("--topk", type=int, default=3)
    ap.add_argument("--accept", type=float, default=0.02)
    ap.add_argument("--confirm", type=int, default=2)
    ap.add_argument("--patience", type=int, default=6)
    ap.add_argument("--workers", type=int, default=8)
    args = ap.parse_args()

    t0 = time.time()
    idx = ItemIndex()
    pool_builder = OpponentPool()
    bench_items, bench_bags = bench_pools(idx)
    log = lambda msg: print(msg, flush=True)

    rounds = [int(r) for r in args.rounds.split(",")]
    aggregate = {}
    for r in rounds:
        opponents = pool_builder.sample_at_round(r, args.pool, seed=100 + r)
        # 基线 = history 高分 run 的该回合棋盘（用户指定的高质量摆盘数据集；
        # roundID 1 基，R1..R18 全有记录——2026-11-12 修正索引后 R1 也可用）
        bases = load_history_lineups_at_round("history-07.db", r, args.per_round,
                                              min_items=5)
        log(f"===== ROUND {r} ===== pool={len(opponents)} bases={len(bases)} "
            f"(items {['%d' % len(b['items']) for b in bases]})")
        results = []
        for bi, base in enumerate(bases):
            cfg = {"seed": 2000 + r * 10 + bi,
                   "seed_base": 20_000_000 + r * 1_000_000 + bi * 100_000,
                   "seeds": args.seeds, "max_iters": args.max_iters,
                   "n_cands": args.n_cands, "topk": args.topk,
                   "accept": args.accept, "confirm": args.confirm,
                   "patience": args.patience, "workers": args.workers}
            cur, base_mean, final_mean, steps = search_lineage(
                idx, base, opponents, bench_items, bench_bags, cfg, log)
            actions = [s["action"] for s in steps]
            results.append({"base": base["name"], "rating": base.get("_rating"),
                            "items": len(base["items"]),
                            "base_wr": base_mean, "final_wr": final_mean,
                            "steps": steps, "accepted_actions": actions,
                            "final_lineup": cur})
            log(f"  [R{r}] #{bi} items={len(base['items'])}: "
                f"{base_mean:.3f} → {final_mean:.3f} | accepted: {actions}")
        gains = [r_["final_wr"] - r_["base_wr"] for r_ in results]
        act_counter = Counter(a for r_ in results for a in r_["accepted_actions"])
        aggregate[r] = {"results": results,
                        "mean_gain": sum(gains) / len(gains),
                        "n_accepts": sum(len(r_["steps"]) for r_ in results),
                        "action_dist": dict(act_counter)}
        log(f"[R{r}] mean gain {aggregate[r]['mean_gain']:+.4f}, "
            f"accepts={aggregate[r]['n_accepts']}, dist={dict(act_counter)}")
        with open(os.path.join(ROOT, f"trainer/p2_search_report_round{r}.json"),
                  "w", encoding="utf-8") as f:
            json.dump({"args": vars(args), "round": r, **aggregate[r]},
                      f, ensure_ascii=False, indent=1, default=str)

    # ── 跨回合汇总（§7.2 判据表）──
    log("\n===== 动作接受率汇总 =====")
    all_actions = sorted({a for r in rounds
                          for a in aggregate[r]["action_dist"]})
    total_accepts = {r: aggregate[r]["n_accepts"] for r in rounds}
    header = "action".ljust(24) + "".join(f"R{r}".rjust(8) for r in rounds)
    log(header)
    for a in all_actions:
        row = a.replace("act_", "").ljust(24)
        for r in rounds:
            n = aggregate[r]["action_dist"].get(a, 0)
            tot = max(total_accepts[r], 1)
            row += f"{n / tot:8.0%}"
        log(row)
    log("accepts".ljust(24) + "".join(f"{total_accepts[r]:8d}" for r in rounds))
    log("mean_gain".ljust(24) + "".join(f"{aggregate[r]['mean_gain']:+8.3f}"
                                        for r in rounds))
    out = os.path.join(ROOT, "trainer", "p4_strata_summary.json")
    with open(out, "w", encoding="utf-8") as f:
        json.dump({"args": vars(args), "aggregate": aggregate},
                  f, ensure_ascii=False, indent=1, default=str)
    print("saved ->", out)
    print(f"total {time.time()-t0:.0f}s")


if __name__ == "__main__":
    main()
