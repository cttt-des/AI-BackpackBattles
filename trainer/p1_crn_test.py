# -*- coding: utf-8 -*-
"""p1_crn_test.py — P1 验收：CRN 配对比较能否在个位数场次内分辨 0.02–0.03 级差异。

实验设计（对规划 §7 P1 判据的实现口径修正，理由见 trainer/训练报告）：
  规划原文「20 阵容 × 10 扰动 × 100 对手，扰动间 Δ 的 std < 0.03」。
  不同扰动的 Δ 含真实效应差异，其 std 是信号不是噪声；决策需要的是
  「同一对候选的 Δ 估计量换种子后变不变」= 复现性噪声。
  → 每个中强度基准 × 8 扰动 × 100 对手 × 2 个独立种子集：
      noise_paired   = mean_i |Δ̂_i^s0 − Δ̂_i^s1|   （CRN 配对）
      noise_unpaired = 同口径但候选与基准种子错开   （独立流，对照组）
  判据：noise_paired < 0.03 通过；同时 CRN 增益 = noise_unpaired / noise_paired。

基准筛选：先对 10 对手样本实测胜率，取 [0.15, 0.85] 的中强度阵容
（全胜/全败会让任何方差判据退化为无信息通过）。
"""
from __future__ import annotations

import argparse
import json
import os
import sqlite3
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from trainer.layout_rules import ItemIndex, check_layout, COLS, ROWS  # noqa: E402
from trainer.evaluator import OpponentPool, crn_reproducibility_probe, _run_jobs  # noqa: E402
from trainer.actions import random_perturb, coverage_perturb  # noqa: E402


def load_history_lineups(db: str, limit: int, min_items: int = 12):
    from core.build_history import decode_build_info, _find_map
    hmap = _find_map()
    idx = ItemIndex()
    con = sqlite3.connect(os.path.join(ROOT, "history", db))
    cur = con.cursor()
    out = []
    for run_id, last in cur.execute(
            "SELECT runID, MAX(roundID) FROM roundData GROUP BY runID").fetchall():
        row = cur.execute(
            "SELECT buildInfo FROM roundData WHERE runID=? AND roundID=?",
            (run_id, last)).fetchone()
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
        cls = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}.get(
            run_row[0] if run_row else None, "Adventurer")
        lineup = {"version": 4, "name": f"{db}:run{run_id}", "character": cls,
                  "round": last, "grid": [ROWS, COLS],
                  "items": [{"id": e["id"], "at": [e["row"], e["col"]], "r": e["rot"]}
                            for e in ents],
                  "storage": [],
                  "health_override": dec["health"],
                  "class_modifiers": {"stamina": dec["stamina"]}}
        out.append(lineup)
        if len(out) >= limit:
            break
    con.close()
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--target", type=float, default=450.0)
    ap.add_argument("--opp", type=int, default=100)
    ap.add_argument("--perturbs", type=int, default=8)
    ap.add_argument("--bases", type=int, default=5)
    ap.add_argument("--workers", type=int, default=8)
    args = ap.parse_args()

    t0 = time.time()
    pool = OpponentPool()
    opponents = pool.sample((args.target, args.target + 200), args.opp, seed=42)
    print(f"opponent pool [{args.target}, {args.target+200}]: {len(opponents)} legal lineups "
          f"({time.time()-t0:.1f}s)", flush=True)

    all_bases = load_history_lineups("history-07.db", 300)
    idx = ItemIndex()
    screened = []
    for b in all_bases:
        if len(screened) >= args.bases:
            break
        jobs = [(b, o, 555 + k) for k, o in enumerate(opponents[:10])]
        res = _run_jobs(jobs, args.workers)
        wr = sum(max(r, 0) for r in res) / max(len(jobs), 1)
        if 0.15 <= wr <= 0.85:
            screened.append(b)
            print(f"  screen: {b['name']} items={len(b['items'])} wr={wr:.2f} [OK]", flush=True)
    print(f"bases screened: {len(screened)}", flush=True)

    results = []
    for bi, base in enumerate(screened):
        t1 = time.time()
        probe = crn_reproducibility_probe(
            base, opponents, lambda lu, i: coverage_perturb(idx, lu, i),
            n_perturb=args.perturbs, n_seedsets=2,
            base_seed=2026_11_12 + bi * 7919, workers=args.workers)
        n_sims = (probe["n_valid_perturb"] * 2 + 2) * len(opponents) * 2
        dt = time.time() - t1
        print(f"base {bi} ({base['name']}, items={len(base['items'])}, round={base['round']}): "
              f"~{n_sims} sims in {dt:.0f}s | base_wr={probe['base_wr_mean']:.2f} | "
              f"noise_paired={probe['noise_paired_mean']:.4f} "
              f"(max {probe['noise_paired_max']:.3f}) | "
              f"noise_unpaired={probe['noise_unpaired_mean']:.4f}", flush=True)
        gain = (probe["noise_unpaired_mean"] / probe["noise_paired_mean"]
                if probe["noise_paired_mean"] and probe["noise_paired_mean"] > 0 else None)
        verdict = ("PASS" if probe["noise_paired_mean"] is not None
                   and probe["noise_paired_mean"] < 0.03 else "FAIL")
        print(f"         → 判据 (noise_paired < 0.03): {verdict}"
              + (f" | CRN 增益 {gain:.1f}x" if gain else ""), flush=True)
        results.append({"base": base["name"], "items": len(base["items"]),
                        "round": base["round"], "probe": probe, "verdict": verdict,
                        "crn_gain": gain})

    passes = sum(1 for r in results if r["verdict"] == "PASS")
    print(f"\nTOTAL: {passes}/{len(results)} bases PASS (noise_paired < 0.03)")
    out = os.path.join(ROOT, "trainer", "p1_crn_report.json")
    with open(out, "w", encoding="utf-8") as f:
        json.dump({"args": vars(args), "results": results,
                   "pass_count": passes}, f, ensure_ascii=False, indent=1, default=str)
    print("saved ->", out)


if __name__ == "__main__":
    main()
