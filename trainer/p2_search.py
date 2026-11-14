# -*- coding: utf-8 -*-
"""p2_search.py — P2 纯搜索基线（规划 §7 P2，初步训练主循环）

结构（§7 P2 三层交替的初步实现）：
  外层（本脚本主循环）：接受/拒绝候选 → 换动作类型再提
  中层（evaluator）：候选 vs 池 A 的 CRN 配对实测（排序权威）
  内层（actions）：合法性复核 + 解析分预筛（§5.4 一级，免费）

冷启动：history 三库高评分终盘摆盘（用户指定的高质量数据集）。
判据（§7 P2）：搜索最佳摆盘在池 A 上击败人类终盘阵容的中位水平。

评估协议（P1 实测定谳）：每候选 = 池 A × 2 seeds 的 CRN 配对胜差，
100 对手分辨力 ≈ 0.01–0.02（p1_crn_report.json）。
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

from trainer.layout_rules import ItemIndex, check_layout, analytic_score, COLS, ROWS  # noqa: E402
from trainer.evaluator import OpponentPool, _run_jobs  # noqa: E402
from trainer.p1_crn_test import load_history_lineups  # noqa: E402
import trainer.actions as A  # noqa: E402


def paired_mean_delta(cand: dict, base_wr: dict, pool, seed_base: int, seeds: int,
                      workers: int) -> float:
    """候选 vs 基准的 CRN 配对 Δ̂（基准胜率已缓存）。"""
    jobs = [(cand, opp, seed_base + oi * 10000 + k)
            for oi, opp in enumerate(pool) for k in range(seeds)]
    res = _run_jobs(jobs, workers)
    ds = []
    for oi, opp in enumerate(pool):
        wins = res[oi * seeds:(oi + 1) * seeds]
        valid = [w for w in wins if w >= 0]
        wr = sum(valid) / max(len(valid), 1)
        ds.append(wr - base_wr[oi])
    return sum(ds) / len(ds)


def evaluate_player_wr(lu: dict, pool, seed_base: int, seeds: int,
                       workers: int) -> dict:
    """绝对胜率（per-opponent）+ 聚合（多指标 §5.1）。"""
    jobs = [(lu, opp, seed_base + oi * 10000 + k)
            for oi, opp in enumerate(pool) for k in range(seeds)]
    res = _run_jobs(jobs, workers)
    per = []
    for oi, opp in enumerate(pool):
        wins = res[oi * seeds:(oi + 1) * seeds]
        valid = [w for w in wins if w >= 0]
        per.append(sum(valid) / max(len(valid), 1))
    n = len(per)
    mean = sum(per) / n
    return {"mean": mean,
            "std": (sum((x - mean) ** 2 for x in per) / n) ** 0.5,
            "worst": min(per), "per": per}


def propose_candidates(index, cur: dict, rng, bench_items, bench_bags, n: int = 6,
                       menu=None):
    """动作菜单提案（§7.2 动作空间）。单步与复合（LNS-lite）混采：
    复合动作改多处覆盖关系，效应量更大（P2 实测单步效应≈噪声）。
    候选 lineup 附 `_action` 标签（回合分层实验的接受动作分布用）。
    menu=None → 默认菜单；消融实验（p5）传自定义 [(act, weight), ...]。"""
    if menu is None:
        menu = [(A.act_cross_bag_swap, 4), (A.act_composite, 4),
                (A.act_swap_items, 1), (A.act_move_bag, 1),
                (A.act_move_item, 1), (A.act_drop_item, 1),
                (A.act_rotate_item, 1)]
    weights = [w for _a, w in menu]
    cands = []
    seen = set()
    for _ in range(n * 5):
        if len(cands) >= n:
            break
        act = rng.choices([a for a, _w in menu], weights=weights)[0]
        if act is A.act_composite:
            lu = act(index, cur, rng, n_moves=rng.randint(2, 4))
        else:
            lu = act(index, cur, rng)
        if lu is None:
            continue
        key = json.dumps([(it["id"], it["at"], it.get("r")) for it in lu["items"]],
                         sort_keys=True)
        if key in seen:
            continue
        lu["_action"] = act.__name__
        seen.add(key)
        cands.append(lu)
        seen.add(key)
        cands.append(lu)
    return cands


def analytic_prefilter(index, cur: dict, cands, topk: int = 3):
    """§5.4 一级：解析分（A+B）预筛，免模拟排序。"""
    s0 = analytic_score(index, A._entries_of(cur))
    scored = []
    for c in cands:
        s1 = analytic_score(index, A._entries_of(c))
        scored.append((s1["A"] + s1["B"] - s0["A"] - s0["B"], c))
    scored.sort(key=lambda x: -x[0])
    return [c for _d, c in scored[:topk]]


def search_lineage(index, base: dict, pool, bench_items, bench_bags, cfg, log):
    rng = random.Random(cfg["seed"])
    cur = base
    # 三缓存基准：report + trial + trial2（accept 双种子族确认，压假阳性）
    cur_wr = evaluate_player_wr(cur, pool, cfg["seed_base"], cfg["seeds"], cfg["workers"])
    trial_seed_base = cfg["seed_base"] + 1_000_000
    trial2_seed_base = cfg["seed_base"] + 2_000_000
    cur_trial = [x for x in evaluate_player_wr(
        cur, pool, trial_seed_base, cfg["seeds"], cfg["workers"])["per"]]
    cur_trial2 = [x for x in evaluate_player_wr(
        cur, pool, trial2_seed_base, cfg["seeds"], cfg["workers"])["per"]]
    sc0 = analytic_score(index, A._entries_of(cur))
    base_mean = cur_wr["mean"]
    log(f"  base wr={base_mean:.3f} (A+B={sc0['A'] + sc0['B']:.1f})")
    no_improve = 0
    steps = []
    n_confirm = cfg.get("confirm", 1)
    for it in range(cfg["max_iters"]):
        cands = propose_candidates(index, cur, rng, bench_items, bench_bags,
                                   n=cfg["n_cands"], menu=cfg.get("menu"))
        prefilter = cfg.get("prefilter") or analytic_prefilter
        cands = prefilter(index, cur, cands, cfg["topk"])
        improved = None
        for c in cands:
            d1 = paired_mean_delta(c, cur_trial, pool,
                                   trial_seed_base, cfg["seeds"], cfg["workers"])
            if d1 <= cfg["accept"]:
                continue
            if n_confirm >= 2:
                d2 = paired_mean_delta(c, cur_trial2, pool,
                                       trial2_seed_base, cfg["seeds"], cfg["workers"])
                if d2 <= cfg["accept"]:
                    log(f"  iter {it}: cand Δ1={d1:+.3f} but Δ2={d2:+.3f} → reject (noise)")
                    continue
                d = (d1 + d2) / 2
            else:
                d = d1
            improved = (c, d)
            break
        if improved:
            c, d = improved
            cur = c
            cur_wr = evaluate_player_wr(cur, pool, cfg["seed_base"],
                                        cfg["seeds"], cfg["workers"])
            cur_trial = [x for x in evaluate_player_wr(
                cur, pool, trial_seed_base, cfg["seeds"], cfg["workers"])["per"]]
            cur_trial2 = [x for x in evaluate_player_wr(
                cur, pool, trial2_seed_base, cfg["seeds"], cfg["workers"])["per"]]
            sc = analytic_score(index, A._entries_of(cur))
            log(f"  iter {it}: accept Δ={d:+.3f} → wr={cur_wr['mean']:.3f} "
                f"(A+B={sc['A'] + sc['B']:.1f}, B_edges={sc['B_edges']})")
            steps.append({"iter": it, "delta": d, "wr": cur_wr["mean"],
                          "action": c.get("_action")})
            no_improve = 0
        else:
            no_improve += 1
            if no_improve >= cfg["patience"]:
                log(f"  iter {it}: patience {cfg['patience']} reached, stop")
                break
    return cur, base_mean, cur_wr["mean"], steps


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--target", type=float, default=450.0)
    ap.add_argument("--pool", type=int, default=100)
    ap.add_argument("--seeds", type=int, default=2)
    ap.add_argument("--max-iters", type=int, default=25)
    ap.add_argument("--n-cands", type=int, default=6)
    ap.add_argument("--topk", type=int, default=3)
    ap.add_argument("--accept", type=float, default=0.02)
    ap.add_argument("--confirm", type=int, default=1)
    ap.add_argument("--patience", type=int, default=6)
    ap.add_argument("--bases", type=int, default=3)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--out", default="trainer/p2_search_report.json")
    args = ap.parse_args()

    t0 = time.time()
    idx = ItemIndex()
    pool_builder = OpponentPool()
    poolA = pool_builder.sample((args.target, args.target + 200), args.pool, seed=42)
    log = lambda msg: print(msg, flush=True)
    log(f"pool A [{args.target},{args.target+200}]: {len(poolA)} lineups, "
        f"rating {min(o['_rating'] for o in poolA):.0f}-{max(o['_rating'] for o in poolA):.0f}")

    # 冷启动：history 高评分终盘（按 runData.rank 排序的高质量摆盘）
    bases = load_history_lineups_ranked("history-07.db", 120)
    bases = [b for b in bases if b["round"] >= 14]
    log(f"history cold-start candidates: {len(bases)}")

    # 人类中位数参照（P2 判据）：抽 20 个同段位人类阵容作为"玩家"打池 A
    ref_lineups = [o for o in poolA[:20]]
    ref_wrs = []
    for i, lu in enumerate(ref_lineups):
        r = evaluate_player_wr(lu, poolA, 909_000 + i * 77, 1, args.workers)
        ref_wrs.append(r["mean"])
    ref_wrs.sort()
    median_human = ref_wrs[len(ref_wrs) // 2]
    log(f"human reference (n=20, vs pool A): median={median_human:.3f} "
        f"p25={ref_wrs[len(ref_wrs)//4]:.3f} p75={ref_wrs[3*len(ref_wrs)//4]:.3f}")

    bench_items, bench_bags = bench_pools(idx)
    poolB = pool_builder.sample((max(args.target - 200, 0), args.target),
                                min(args.pool, 50), seed=43)
    poolC = pool_builder.sample(None, min(args.pool, 50), seed=44)
    log(f"validation pools: B={len(poolB)} C={len(poolC)}")
    results = []
    for bi, base in enumerate(bases[:args.bases]):
        log(f"lineage {bi}: {base['name']} items={len(base['items'])} round={base['round']} rank={base.get('_rank')}")
        cfg = {"seed": 1000 + bi, "seed_base": 3_000_000 + bi * 100_000,
               "seeds": args.seeds, "max_iters": args.max_iters,
               "n_cands": args.n_cands, "topk": args.topk,
               "accept": args.accept, "confirm": args.confirm, "patience": args.patience,
               "workers": args.workers}
        cur, base_mean, final_mean, steps = search_lineage(
            idx, base, poolA, bench_items, bench_bags, cfg, log)
        # 泛化验证（§5.2：验收用 B/C，防对池 A 过拟合）
        valB_base = evaluate_player_wr(base, poolB, 7_000_000 + bi * 100_000,
                                       args.seeds, args.workers)["mean"]
        valB_final = evaluate_player_wr(cur, poolB, 7_000_000 + bi * 100_000,
                                        args.seeds, args.workers)["mean"]
        valC_base = evaluate_player_wr(base, poolC, 8_000_000 + bi * 100_000,
                                       args.seeds, args.workers)["mean"]
        valC_final = evaluate_player_wr(cur, poolC, 8_000_000 + bi * 100_000,
                                        args.seeds, args.workers)["mean"]
        results.append({"base": base["name"], "rank": base.get("_rank"),
                        "base_wr": base_mean, "final_wr": final_mean,
                        "valB_base": valB_base, "valB_final": valB_final,
                        "valC_base": valC_base, "valC_final": valC_final,
                        "final_items": len(cur["items"]), "steps": steps,
                        "final_lineup": cur})
        log(f"  lineage result: A {base_mean:.3f} → {final_mean:.3f} | "
            f"B {valB_base:.3f} → {valB_final:.3f} | C {valC_base:.3f} → {valC_final:.3f}")
    results.sort(key=lambda r: -r["final_wr"])
    best = results[0]
    verdict = ("PASS" if best["final_wr"] > median_human else "FAIL")
    log(f"\nP2 判据: 搜索最佳 {best['final_wr']:.3f} vs 人类中位 {median_human:.3f} → {verdict}")
    with open(os.path.join(ROOT, args.out), "w", encoding="utf-8") as f:
        json.dump({"args": vars(args), "median_human": median_human,
                   "ref_wrs": ref_wrs, "results": results, "verdict": verdict},
                  f, ensure_ascii=False, indent=1, default=str)
    print("saved ->", args.out)
    print(f"total {time.time()-t0:.0f}s")


def bench_pools(idx: ItemIndex):
    """闲置池：搜索可加入的物品/包（R3 已核实的可得性口径不做限制——
    对手池即天梯真实分布，搜出的阵容用于同池对战）。"""
    items = list(idx.items.keys())
    bags = sorted(idx.bag_set())
    return items, bags


def load_history_lineups_ranked(db: str, limit: int):
    """按 rank（rating）降序取合法终盘阵容（冷启动质量优先）。

    ★ roundID 是 **1 基**（R1..R18，2026-11-12 修正，此前 round=roundID+1
    错位成 'R19'）。★ roundData.health 是已含回合成长的当回合基础最大血量
    ⇒ 用 health_override 直通，class_modifiers 只放 stamina（否则
    character_stats 按 round 再叠成长 = 双重计数，R18 双侧虚高 ~355 血）。
    """
    return load_history_lineups_at_round(db, None, limit, min_items=20)


def load_history_lineups_at_round(db: str, round_no, limit: int,
                                  min_items: int = 5, ranked: bool = True):
    """取 history 里指定回合的合法棋盘。round_no=None → 各 run 的最末回合。

    round_no 为 1 基回合号（roundID 即回合号，R1..R18）。
    """
    import sqlite3
    from core.build_history import decode_build_info, _find_map
    hmap = _find_map()
    idx = ItemIndex()
    con = sqlite3.connect(os.path.join(ROOT, "history", db))
    cur = con.cursor()
    if round_no is None:
        rows = cur.execute(
            "SELECT r.runID, r.rank, MAX(q.roundID) FROM runData r "
            "JOIN roundData q ON q.runID = r.runID "
            "GROUP BY r.runID ORDER BY r.rank DESC LIMIT ?", (limit * 3,)).fetchall()
        pairs = [(run_id, rank, last) for run_id, rank, last in rows]
    else:
        rows = cur.execute(
            "SELECT r.runID, r.rank FROM runData r "
            "JOIN roundData q ON q.runID = r.runID "
            "WHERE q.roundID = ? ORDER BY r.rank DESC LIMIT ?",
            (round_no, limit * 6)).fetchall()
        pairs = [(run_id, rank, round_no) for run_id, rank in rows]
    out = []
    for run_id, rank, rnd in pairs:
        row = cur.execute(
            "SELECT buildInfo FROM roundData WHERE runID=? AND roundID=?",
            (run_id, rnd)).fetchone()
        if not row or not row[0]:
            continue
        try:
            dec = decode_build_info(row[0], hmap)
        except Exception:
            continue
        if not dec:
            continue
        ents = [{"id": it["id"], "rot": it["r"], "row": it["at"][0], "col": it["at"][1]}
                for it in dec["items"] if it["at"][0] < ROWS and it["at"][1] < COLS]
        if not check_layout(idx, ents)[0] or len(ents) < min_items:
            continue
        run_row = cur.execute(
            "SELECT class FROM runData WHERE runID=?", (run_id,)).fetchone()
        # 1.1.9 Classes_Full 七职业（gd_core/CoreConst.gd:343-351）；旧 4 职业表
        # 会把 Mage/Adventurer/Engineer(4/5/6) 全错落成 Adventurer
        cls = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}.get(
            run_row[0] if run_row else None, "Adventurer")
        lineup = {"version": 4, "name": f"{db}:run{run_id}:R{rnd}",
                  "character": cls,
                  "round": rnd, "grid": [ROWS, COLS],
                  "items": [{"id": e["id"], "at": [e["row"], e["col"]], "r": e["rot"]}
                            for e in ents],
                  "storage": [],
                  "health_override": dec["health"],
                  "class_modifiers": {"stamina": dec["stamina"]},
                  "_rank": rank}
        out.append(lineup)
        if len(out) >= limit:
            break
    con.close()
    return out


if __name__ == "__main__":
    main()
