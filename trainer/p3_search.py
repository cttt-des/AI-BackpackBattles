# -*- coding: utf-8 -*-
"""p3_search.py — P3 判据对照实验（规划 §7 P3 继续判据）：

  「学习初筛 + 精评的组合，在相同模拟预算下优于纯搜索。」

双臂（除预筛器外逐位同配置，引擎对局账面由 evaluator.SIMS_TOTAL 记账）：
  analytic 臂：解析分（A+B）排序取 top-K        —— = Pass 4 的纯搜索
  learned  臂：Ridge 差分偏好模型预测 Δ 排序取 top-K —— = P3 学习加速

协议与 Pass 4 完全一致（同血统、同提案种子、同评估种子族、同 accept/confirm/
patience、同 topk），预算 = 每迭代 topk 次候选实测，双臂构造性相等。
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import ItemIndex, analytic_score  # noqa: E402
from trainer.evaluator import OpponentPool, SIMS_TOTAL  # noqa: E402
from trainer.p2_search import (load_history_lineups_ranked, evaluate_player_wr,  # noqa: E402
                               search_lineage, bench_pools, propose_candidates)
from trainer.p3_dataset import layout_features, diff_features  # noqa: E402


def make_learned_prefilter(model: dict, index: ItemIndex):
    keys = model["keys"]
    w = model["w"]
    b = model["b"]
    mu = model["mu"]
    sd = model["sd"]

    def predict(f_base, f_c):
        d = diff_features(f_base, f_c)
        x = [d.get(k, 0.0) for k in keys]
        z = [(x[i] - mu[i]) / sd[i] if sd[i] > 1e-9 else 0.0 for i in range(len(x))]
        return sum(z[i] * w[i] for i in range(len(x))) + b

    def prefilter(index_, cur, cands, topk):
        f_base = layout_features(index_, cur_entries(cur))
        scored = []
        for c in cands:
            f_c = layout_features(index_, cur_entries(c))
            scored.append((predict(f_base, f_c), c))
        scored.sort(key=lambda t: -t[0])
        return [c for _s, c in scored[:topk]]

    return prefilter


def cur_entries(lineup: dict):
    import trainer.actions as A
    return A._entries_of(lineup)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--model", default="trainer/p3_model.json")
    ap.add_argument("--target", type=float, default=450.0)
    ap.add_argument("--pool", type=int, default=100)
    ap.add_argument("--seeds", type=int, default=2)
    ap.add_argument("--max-iters", type=int, default=25)
    ap.add_argument("--n-cands", type=int, default=6)
    ap.add_argument("--topk", type=int, default=3)
    ap.add_argument("--accept", type=float, default=0.02)
    ap.add_argument("--confirm", type=int, default=2)
    ap.add_argument("--patience", type=int, default=8)
    ap.add_argument("--bases", type=int, default=3)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--out", default="trainer/p3_compare_report.json")
    args = ap.parse_args()

    t0 = time.time()
    idx = ItemIndex()
    pool_builder = OpponentPool()
    poolA = pool_builder.sample((args.target, args.target + 200), args.pool,
                                seed=42)
    bases = [b for b in load_history_lineups_ranked("history-07.db", 120)
             if b["round"] >= 14][:args.bases]
    log = lambda msg: print(msg, flush=True)
    log(f"pool A: {len(poolA)} | lineages: {[b['name'] for b in bases]}")
    with open(os.path.join(ROOT, args.model), encoding="utf-8") as f:
        model = json.load(f)
    log(f"model: {model['n']} samples, LOBO spearman "
        f"{model.get('lobo_spearman_mean', float('nan')):+.3f}")

    bench_items, bench_bags = bench_pools(idx)
    learned_prefilter = make_learned_prefilter(model, idx)

    arms = {
        "analytic": None,
        "learned": learned_prefilter,
    }
    report = {"args": vars(args), "model_lobo": model.get("lobo_spearman_mean"),
              "arms": {}}
    for arm, prefilter in arms.items():
        log(f"===== ARM {arm} =====")
        arm_sims0 = SIMS_TOTAL["count"]
        results = []
        for bi, base in enumerate(bases):
            cfg = {"seed": 1000 + bi, "seed_base": 3_000_000 + bi * 100_000,
                   "seeds": args.seeds, "max_iters": args.max_iters,
                   "n_cands": args.n_cands, "topk": args.topk,
                   "accept": args.accept, "confirm": args.confirm,
                   "patience": args.patience, "workers": args.workers,
                   "prefilter": prefilter}
            cur, base_mean, final_mean, steps = search_lineage(
                idx, base, poolA, bench_items, bench_bags, cfg, log)
            results.append({"base": base["name"], "base_wr": base_mean,
                            "final_wr": final_mean, "steps": len(steps),
                            "step_log": steps, "final_lineup": cur})
            log(f"  [{arm}] {base['name']}: {base_mean:.3f} → {final_mean:.3f} "
                f"({len(steps)} steps)")
        arm_sims = SIMS_TOTAL["count"] - arm_sims0
        report["arms"][arm] = {"results": results, "sims": arm_sims}
        log(f"[{arm}] total sims: {arm_sims}")
    # 对照判定（P3 继续判据）
    fa = {r["base"]: r["final_wr"] for r in report["arms"]["analytic"]["results"]}
    fl = {r["base"]: r["final_wr"] for r in report["arms"]["learned"]["results"]}
    wins = sum(1 for k in fa if fl[k] > fa[k])
    ties = sum(1 for k in fa if fl[k] == fa[k])
    mean_a = sum(fa.values()) / len(fa)
    mean_l = sum(fl.values()) / len(fl)
    report["verdict"] = {
        "mean_analytic": mean_a, "mean_learned": mean_l,
        "learned_wins": wins, "ties": ties, "n_lineages": len(fa),
        "sims_analytic": report["arms"]["analytic"]["sims"],
        "sims_learned": report["arms"]["learned"]["sims"],
        "pass": mean_l > mean_a and report["arms"]["learned"]["sims"] <= report["arms"]["analytic"]["sims"] + 1,
    }
    log(f"\nP3 判据: 学习臂 mean={mean_l:.3f} vs 解析臂 mean={mean_a:.3f} "
        f"(wins {wins}/{len(fa)}, sims {report['arms']['learned']['sims']} vs "
        f"{report['arms']['analytic']['sims']}) → "
        f"{'PASS' if report['verdict']['pass'] else 'FAIL'}")
    with open(os.path.join(ROOT, args.out), "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1, default=str)
    print("saved ->", args.out)
    print(f"total {time.time()-t0:.0f}s")


if __name__ == "__main__":
    main()
