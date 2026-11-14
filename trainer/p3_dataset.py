# -*- coding: utf-8 -*-
"""p3_dataset.py — P3 学习加速·数据采集（规划 §7 P3-1：学差分偏好）

数据 = (基准摆盘, 候选摆盘) → (差分特征, Δ̂ 实测标签)：
  候选由动作菜单生成（单步+复合 LNS 混采），对同一对手池、同一种子做
  CRN 配对：Δ̂ = mean over 对手 [wr_cand(o,s) − wr_base(o,s)]。
  特征 = 完整布局的解析量（规划 §7 P3-2：输入必须是完整布局），
  含差分（cand − base）与绝对两套，模型用差分套。

输出 trainer/p3_dataset.jsonl，一行一个 (base, cand) 样本。
"""
from __future__ import annotations

import argparse
import json
import os
import random
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import (ItemIndex, check_layout, analytic_score,  # noqa: E402
                                  assign_bonuses, occ_of, COLS, ROWS)
from trainer.evaluator import OpponentPool, _run_jobs  # noqa: E402
from trainer.p2_search import load_history_lineups_ranked  # noqa: E402
import trainer.actions as A  # noqa: E402

EFFECT_KEYS = sorted({e.get("effect") for e in
                      __import__("trainer.layout_rules", fromlist=["BAG_SPECS"])
                      .BAG_SPECS.values() if e.get("effect")})


def layout_features(index: ItemIndex, entries) -> dict:
    """完整布局 → 解析特征（绝对量）。规划 §7 P3-3 的三个可学对象的载体：
    覆盖边权（effect×count）、包边际（size 桶×覆盖统计）、物品边际（类型聚合）。"""
    sc = analytic_score(index, [dict(e) for e in entries])
    assign = assign_bonuses(index, [dict(e) for e in entries])
    edges = {}
    for _ii, es in assign.items():
        for _bi, _bag, eff in es:
            edges[eff] = edges.get(eff, 0) + 1
    bags = [e for e in entries if index.is_bag(e["id"])]
    items = [e for e in entries if not index.is_bag(e["id"])]
    bag_cells = sum(index.num_cells(b["id"], b["rot"]) for b in bags)
    item_cells = sum(index.num_cells(i["id"], i["rot"]) for i in items)
    # 包的 size 桶与覆盖统计
    size_hist = {1: 0, 2: 0, 3: 0, 4: 0, 6: 0, 8: 0, 9: 0}
    bag_occupied_hit = 0
    bag_affected_hit = 0
    bag_affected_total = 0
    item_cell_set = {}
    for i in items:
        for c in occ_of(index, i):
            item_cell_set[c] = True
    for b in bags:
        size_hist[index.num_cells(b["id"], b["rot"])] = \
            size_hist.get(index.num_cells(b["id"], b["rot"]), 0) + 1
        occ = occ_of(index, b)
        aff = index.affected_cells(b["id"], b["rot"])
        bag_occupied_hit += sum(1 for c in occ if c in item_cell_set)
        bag_affected_hit += sum(1 for c in aff if c in item_cell_set)
        bag_affected_total += len(aff)
    # 物品类型聚合（CoreConst.Type 主类型）
    type_names = {0: "bag", 1: "consumable", 2: "food", 3: "pet", 4: "weapon",
                  5: "shield", 6: "armor", 10: "accessory", 11: "potion"}
    type_counts = {}
    dam_sum = heal_sum = cd_count = sock_sum = 0
    for i in items:
        d = index.descr(i["id"])
        ts = d["types"]
        key = next((type_names[t] for t in ts if t in type_names), "other")
        type_counts[key] = type_counts.get(key, 0) + 1
        dam_sum += (d["minDam"] + d["maxDam"]) / 2.0
        if d["cd"]:
            cd_count += 1
        sock_sum += d["sockets"]
        heal_sum += d["namedParams"].get("heal", 0) + d["namedParams"].get("regen", 0)
    a_detail = sc["A_detail"]
    feats = {
        "n_items": len(items), "n_bags": len(bags),
        "item_cells": item_cells, "bag_cells": bag_cells,
        "fill_ratio": item_cells / bag_cells if bag_cells else 0.0,
        "bag_occupied_hit": bag_occupied_hit,
        "bag_affected_hit": bag_affected_hit,
        "bag_affected_total": bag_affected_total,
        "A": sc["A"], "B": sc["B"],
        "dam_sum": round(dam_sum, 2), "heal_sum": round(heal_sum, 2),
        "cd_count": cd_count, "sock_sum": sock_sum,
    }
    feats.update({f"sz{k}": v for k, v in size_hist.items()})
    for k, v in type_counts.items():
        feats[f"t_{k}"] = v
    for k in sorted(a_detail):
        feats[f"a_{k}"] = round(a_detail[k], 2)
    for k in EFFECT_KEYS:
        feats[f"e_{k}"] = edges.get(k, 0)
    return feats


def diff_features(f_base: dict, f_cand: dict) -> dict:
    keys = set(f_base) | set(f_cand)
    return {k: round(f_cand.get(k, 0) - f_base.get(k, 0), 4) for k in keys}


def paired_delta_label(cand: dict, base_wr, pool, seed_base: int,
                       workers: int) -> float:
    jobs = [(cand, opp, seed_base + oi * 10000)
            for oi, opp in enumerate(pool)]
    res = _run_jobs(jobs, workers)
    ds = []
    for oi in range(len(pool)):
        w = max(res[oi], 0)
        ds.append(w - base_wr[oi])
    return sum(ds) / len(ds)


def gen_candidates(index, base: dict, rng, n: int):
    menu = [(A.act_cross_bag_swap, 3), (A.act_composite, 4),
            (A.act_swap_items, 1), (A.act_move_bag, 1),
            (A.act_move_item, 1), (A.act_drop_item, 1),
            (A.act_rotate_item, 1)]
    weights = [w for _a, w in menu]
    cands, seen = [], set()
    for _ in range(n * 5):
        if len(cands) >= n:
            break
        act = rng.choices([a for a, _w in menu], weights=weights)[0]
        if act is A.act_composite:
            lu = act(index, base, rng, n_moves=rng.randint(2, 4))
        else:
            lu = act(index, base, rng)
        if lu is None:
            continue
        key = json.dumps([(it["id"], it["at"], it.get("r")) for it in lu["items"]],
                         sort_keys=True)
        if key in seen:
            continue
        seen.add(key)
        cands.append(lu)
    return cands


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--target", type=float, default=450.0)
    ap.add_argument("--pool", type=int, default=100)
    ap.add_argument("--cands-per-base", type=int, default=60)
    ap.add_argument("--bases", type=int, default=6)
    ap.add_argument("--seed", type=int, default=3300)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--out", default="trainer/p3_dataset.jsonl")
    args = ap.parse_args()

    t0 = time.time()
    idx = ItemIndex()
    pool_builder = OpponentPool()
    poolA = pool_builder.sample((args.target, args.target + 200), args.pool,
                                seed=42)
    print(f"pool A: {len(poolA)} | building dataset "
          f"({args.bases} bases x {args.cands_per_base} cands)", flush=True)

    bases = load_history_lineups_ranked("history-07.db", 200)
    # 覆盖各强度段：按 wr 采样需先测——用启发式（items 数与 round 分层）
    rng0 = random.Random(99)
    rng0.shuffle(bases)
    picked = []
    for b in bases:
        if len(picked) >= args.bases:
            break
        if 25 <= len(b["items"]) <= 60:
            picked.append(b)
    seed_base = 9_000_000
    out_path = os.path.join(ROOT, args.out)
    n_sims = 0
    with open(out_path, "w", encoding="utf-8") as out:
        for bi, base in enumerate(picked):
            base_entries = A._entries_of(base)
            f_base = layout_features(idx, base_entries)
            jobs = [(base, opp, seed_base + bi * 1_000_000 + oi * 10000)
                    for oi, opp in enumerate(poolA)]
            res = _run_jobs(jobs, args.workers)
            n_sims += len(jobs)
            base_wr = [max(r, 0) for r in res]
            base_label = sum(base_wr) / len(base_wr)
            print(f"base {bi} ({base['name']}, items={len(base['items'])}) "
                  f"wr={base_label:.3f} | {time.time()-t0:.0f}s", flush=True)
            cands = gen_candidates(idx, base, random.Random(args.seed + bi * 77),
                                   args.cands_per_base)
            for ci, cand in enumerate(cands):
                f_c = layout_features(idx, A._entries_of(cand))
                d = paired_delta_label(cand, base_wr, poolA,
                                       seed_base + bi * 1_000_000, args.workers)
                n_sims += len(poolA)
                row = {
                    "base": base["name"], "bi": bi,
                    "base_wr": base_label,
                    "delta": round(d, 4),
                    "diff": diff_features(f_base, f_c),
                    "abs": f_c,
                }
                out.write(json.dumps(row, ensure_ascii=False) + "\n")
                if (ci + 1) % 10 == 0:
                    out.flush()
                    print(f"  cand {ci+1}/{len(cands)} last Δ={d:+.3f} "
                          f"| {time.time()-t0:.0f}s", flush=True)
    print(f"dataset -> {out_path} | {n_sims} sims | {time.time()-t0:.0f}s total")


if __name__ == "__main__":
    main()
