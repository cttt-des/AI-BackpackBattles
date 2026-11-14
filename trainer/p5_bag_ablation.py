# -*- coding: utf-8 -*-
"""p5_bag_ablation.py — ② 包集合动作消融（规划 v3 §7.3）

假设：换包改「容器层 + 加成域 + 自身属性」三样 ⇒ 效应量远大于单步（单步已实测 ≈ 噪声）；
但它在历史菜单里权重最低、从未被单独评估。§1.3 指出早期换包应是主力动作。

设计（配对）：同一 (回合, 血统, 对手池, 种子族) 下跑三臂，只差动作菜单：
  control    默认菜单（跨包交换 4 / 复合 4 / 其余各 1）
  swap_heavy 换包主导（act_swap_bag_H 5 ≈ 42%，其余压缩）
  drop_heavy 减物品单列（act_drop_item 5 ≈ 42%——用户明确关心的
             「少上几件换拓扑」，此前权重 1/12 从未单测）

H 注入：每血统注入 3 个持有包（_extra；排除 Singular 与已在板 id）——
注入量级是开放问题（§9.7），此处文档化为最小可判定选择。

判据（§7.3 预注册）：swap_heavy 的池 A 最终 wr 比 control 高 ≥0.02。
产出 trainer/p5_bag_ablation_report.json。
"""
from __future__ import annotations

import argparse
import json
import os
import random
import sys
import time
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import ItemIndex  # noqa: E402
from trainer.evaluator import OpponentPool, SIMS_TOTAL  # noqa: E402
from trainer.p2_search import (search_lineage, bench_pools,  # noqa: E402
                               load_history_lineups_at_round)
from trainer.actions import inject_extra_bags  # noqa: E402
import trainer.actions as A  # noqa: E402

MENUS = {
    "control": [(A.act_cross_bag_swap, 4), (A.act_composite, 4),
                (A.act_swap_items, 1), (A.act_move_bag, 1),
                (A.act_move_item, 1), (A.act_drop_item, 1),
                (A.act_rotate_item, 1)],
    "swap_heavy": [(A.act_swap_bag_H, 5), (A.act_composite, 2),
                   (A.act_cross_bag_swap, 2), (A.act_move_bag, 1),
                   (A.act_drop_item, 1), (A.act_swap_items, 1),
                   (A.act_move_item, 1), (A.act_rotate_item, 1)],
    "drop_heavy": [(A.act_drop_item, 5), (A.act_composite, 3),
                   (A.act_cross_bag_swap, 2), (A.act_swap_items, 1),
                   (A.act_rotate_item, 1)],
}


def main():
    # 控制台可能是 GBK：统一 utf-8 + replace，避免 U+2212 之类字符崩掉长实验
    try:
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
        sys.stderr.reconfigure(encoding="utf-8", errors="replace")
    except Exception:
        pass
    ap = argparse.ArgumentParser()
    ap.add_argument("--rounds", default="1,18")
    ap.add_argument("--per-round", type=int, default=3)
    ap.add_argument("--pool", type=int, default=100)
    ap.add_argument("--seeds", type=int, default=2)
    ap.add_argument("--max-iters", type=int, default=6)
    ap.add_argument("--n-cands", type=int, default=6)
    ap.add_argument("--topk", type=int, default=3)
    ap.add_argument("--accept", type=float, default=0.02)
    ap.add_argument("--confirm", type=int, default=2)
    ap.add_argument("--patience", type=int, default=6)
    ap.add_argument("--inject", type=int, default=3)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--arms", default="control,swap_heavy,drop_heavy")
    args = ap.parse_args()

    t0 = time.time()
    idx = ItemIndex()
    pool_builder = OpponentPool()
    bench_items, bench_bags = bench_pools(idx)
    log = lambda msg: print(msg, flush=True)
    arms = args.arms.split(",")

    rounds = [int(r) for r in args.rounds.split(",")]
    report = {"args": vars(args), "arms": {}, "verdict": {}}
    for r in rounds:
        opponents = pool_builder.sample_at_round(r, args.pool, seed=100 + r)
        bases = load_history_lineups_at_round("history-07.db", r, args.per_round,
                                              min_items=5)
        log(f"===== ROUND {r} ===== pool={len(opponents)} bases={len(bases)}")
        arm_results = {}
        for arm in arms:
            results = []
            for bi, base in enumerate(bases):
                base = inject_extra_bags(idx, base,
                                         random.Random(5000 + r * 100 + bi),
                                         k=args.inject)
                cfg = {"seed": 2000 + r * 10 + bi,
                       "seed_base": 30_000_000 + r * 1_000_000 + bi * 100_000,
                       "seeds": args.seeds, "max_iters": args.max_iters,
                       "n_cands": args.n_cands, "topk": args.topk,
                       "accept": args.accept, "confirm": args.confirm,
                       "patience": args.patience, "workers": args.workers,
                       "menu": MENUS[arm]}
                cur, base_mean, final_mean, steps = search_lineage(
                    idx, base, opponents, bench_items, bench_bags, cfg, log)
                actions = [s["action"] for s in steps]
                results.append({"base": base["name"],
                                "items": len(base["items"]),
                                "n_extra": len(base.get("_extra") or []),
                                "base_wr": base_mean, "final_wr": final_mean,
                                "steps": steps, "accepted_actions": actions})
                log(f"  [{arm}][R{r}] #{bi} {base['name']}: "
                    f"{base_mean:.3f} → {final_mean:.3f} | accepted: {actions}")
            gains = [x["final_wr"] - x["base_wr"] for x in results]
            arm_results[arm] = {
                "results": results,
                "mean_gain": sum(gains) / len(gains),
                "mean_final": sum(x["final_wr"] for x in results) / len(results),
                "n_accepts": sum(len(x["steps"]) for x in results),
                "action_dist": dict(Counter(a for x in results
                                            for a in x["accepted_actions"])),
            }
            log(f"[{arm}][R{r}] mean_final={arm_results[arm]['mean_final']:.3f} "
                f"mean_gain={arm_results[arm]['mean_gain']:+.4f} "
                f"accepts={arm_results[arm]['n_accepts']} "
                f"dist={arm_results[arm]['action_dist']}")
        # §7.3 判据：swap_heavy 比 control 高 ≥0.02
        if "control" in arm_results and "swap_heavy" in arm_results:
            diff = (arm_results["swap_heavy"]["mean_final"]
                    - arm_results["control"]["mean_final"])
            report["verdict"][f"R{r}"] = {
                "swap_minus_control": round(diff, 4),
                "pass": diff >= 0.02,
            }
            log(f"[R{r}] §7.3 判据 swap_heavy - control = {diff:+.4f} "
                f"-> {'PASS' if diff >= 0.02 else 'FAIL'} (阈 +0.02)")
        report["arms"].setdefault(f"R{r}", {}).update(arm_results)

    with open(os.path.join(ROOT, "trainer", "p5_bag_ablation_report.json"),
              "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1, default=str)
    print("saved -> trainer/p5_bag_ablation_report.json")
    print(f"total {time.time()-t0:.0f}s | sims {SIMS_TOTAL['count']}")


if __name__ == "__main__":
    main()
