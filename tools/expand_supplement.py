#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_supplement.py — 稀有物品定向补样（第二批，异阵容）

动机（2026-11-07 主人指令）：首批 1,168 场已把物品种类（512/514）、职业配对
（49/49）打满，但稀有物品出场次数仍偏少——历史库出现 ≤60 次的 30 件物品里，
19 件在语料中只出现 0–2 次。事件类型侧已实证 8 种定义内类型在 events.json 面
不可达（源码无 logEvent 路径 / 物品调用未传 item），因此补样目标只放在
「稀有物品出场分布」上，不追求事件类型数量。

做法：
  1) 统计首批语料每件物品的出场场次（读 lineups.json，双方都算，含宝石）。
  2) 对「历史库频次 ≤ --rare-freq 且首批出场 < --min-uses」的物品各补若干场；
     Random Loadout Bag / Snowman 两件装配不落盘，自动跳过并记录。
  3) 候选回合来自 inventory.json（1.1.5–1.1.9），与首批不重复；对手也带同一
     稀有物品时优先（一次补齐两件）。
  4) 对手：同阶段、不同 run、双方物品多重集不同（延续首批硬约束）。

用法：
    python -X utf8 tools/expand_supplement.py
    python -X utf8 tools/expand_supplement.py --per-item 2 --rare-freq 60 --min-uses 3
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INV = os.path.join(ROOT, "output", "oracle", "expand", "inventory.json")
CASES = os.path.join(ROOT, "output", "oracle", "expand", "cases.json")
FIGHTS = os.path.join(ROOT, "output", "oracle", "expand", "fights")
OUT = os.path.join(ROOT, "output", "oracle", "expand", "supplement_cases.json")
REPORT = os.path.join(ROOT, "output", "oracle", "expand", "supplement_report.md")

MAIN_VERSIONS = ("1.1.5", "1.1.6", "1.1.7", "1.1.8", "1.1.9")
SEED_MASK = 0x7FFFFFFF
ROUND_STAGES = ((1, 1), (2, 3), (4, 6), (7, 9), (10, 12), (13, 15), (16, 18))
UNREACHABLE = {"Random Loadout Bag", "Snowman"}


def stage_of(round_id):
    for lo, hi in ROUND_STAGES:
        if lo <= round_id <= hi:
            return str(lo) if lo == hi else "%d-%d" % (lo, hi)
    return "19+"


def derive_seed(run_id, round_id, opp_run_id):
    return (run_id * 7919 + round_id * 104729 + opp_run_id * 1299709 + 13) & SEED_MASK


def main():
    ap = argparse.ArgumentParser(description="稀有物品定向补样（第二批）")
    ap.add_argument("--inventory", default=INV)
    ap.add_argument("--cases", default=CASES)
    ap.add_argument("--fights", default=FIGHTS)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--report", default=REPORT)
    ap.add_argument("--rare-freq", type=int, default=60)
    ap.add_argument("--min-uses", type=int, default=3)
    ap.add_argument("--per-item", type=int, default=2)
    args = ap.parse_args()

    t0 = time.time()
    with open(args.inventory, encoding="utf-8") as f:
        inv = json.load(f)
    with open(args.cases, encoding="utf-8") as f:
        cdoc = json.load(f)
    base_cases = cdoc["cases"]
    used = {(c["run_id"], c["round_id"]) for c in base_cases}
    used |= {(c["opp_run_id"], c["opp_round_id"]) for c in base_cases}

    uses = Counter()
    for c in base_cases:
        lp = os.path.join(args.fights, c["case_id"], "lineups.json")
        if not os.path.exists(lp):
            continue
        with open(lp, encoding="utf-8") as f:
            lu = json.load(f)
        seen = set()
        for side in ("player", "opponent"):
            for it in lu[side]["items"]:
                seen.add(it["name"])
                for g in it.get("gems") or []:
                    seen.add(g)
        for n in seen:
            uses[n] += 1

    hist = inv["item_freq"]
    targets, skipped = [], []
    for name, f in sorted(hist.items(), key=lambda kv: (kv[1], kv[0])):
        if f > args.rare_freq:
            continue
        if name in UNREACHABLE:
            skipped.append((name, uses.get(name, 0), "装配不落盘（原版语义），语料无法覆盖"))
            continue
        if uses.get(name, 0) < args.min_uses:
            targets.append((name, f, uses.get(name, 0)))
    print("[supp] 目标稀有物品 %d 件；跳过 %d 件" % (len(targets), len(skipped)))

    rounds = [r for r in inv["rounds"] if r["version"] in MAIN_VERSIONS and r["item_count"] >= 1]
    by_item = defaultdict(list)
    for r in rounds:
        if (r["run_id"], r["round_id"]) in used:
            continue
        for name in set(r["items"]) | set(r["gems"]):
            by_item[name].append(r)

    def multiset(r):
        return tuple(sorted(r["items"]))

    opp_by_stage = defaultdict(list)
    for r in rounds:
        opp_by_stage[stage_of(r["round_id"])].append(r)
    for st in opp_by_stage:
        opp_by_stage[st].sort(key=lambda r: (r["run_id"], r["round_id"]))

    chosen_keys = set(used)
    out_cases = []
    opp_used = Counter()
    filled = Counter()

    for name, f, cur in targets:
        need = args.min_uses - cur
        cands = by_item.get(name, [])
        cands.sort(key=lambda r: (abs(r["round_id"] - 10), r["run_id"], r["round_id"]))
        got = 0
        for r in cands:
            if got >= max(need, args.per_item):
                break
            key = (r["run_id"], r["round_id"])
            if key in chosen_keys:
                continue
            st = stage_of(r["round_id"])
            ocands = opp_by_stage.get(st) or opp_by_stage[sorted(opp_by_stage)[0]]
            best = None
            ms_r = multiset(r)
            for o in ocands:
                if o["run_id"] == r["run_id"]:
                    continue
                if (o["run_id"], o["round_id"]) in chosen_keys:
                    continue
                if multiset(o) == ms_r:
                    continue
                bonus = 3.0 if name in o["items"] else 0.0
                score = bonus + (1.0 if o["round_id"] == r["round_id"] else 0.0)
                score -= 0.02 * opp_used[(o["run_id"], o["round_id"])]
                if best is None or score > best[0]:
                    best = (score, o)
            if best is None:
                continue
            o = best[1]
            chosen_keys.add(key)
            chosen_keys.add((o["run_id"], o["round_id"]))
            opp_used[(o["run_id"], o["round_id"])] += 1
            filled[name] += 1
            if name in o["items"]:
                filled[name] += 1
            out_cases.append({
                "case_id": "run%d_r%d_o%d_r%d" % (r["run_id"], r["round_id"], o["run_id"], o["round_id"]),
                "seed": derive_seed(r["run_id"], r["round_id"], o["run_id"]),
                "run_id": r["run_id"], "round_id": r["round_id"],
                "opp_run_id": o["run_id"], "opp_round_id": o["round_id"],
                "player_class": r["class"], "player_class_id": r["class_id"],
                "opp_class": o["class"], "opp_class_id": o["class_id"],
                "player_version": r["version"], "opp_version": o["version"],
                "player_stage": st,
                "player_items": r["item_count"], "opp_items": o["item_count"],
                "select_reason": "supplement:%s" % name,
            })
            got += 1

    ids = [c["case_id"] for c in out_cases]
    assert len(ids) == len(set(ids)), "补样 case_id 重复"
    mirrored = [c for c in out_cases if c["run_id"] == c["opp_run_id"]]
    doc = {
        "format": "oracle-fight-cases/1",
        "generated_by": "tools/expand_supplement.py",
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "note": "第二批：稀有物品定向补样（与首批 cases.json 互不重复，全部异阵容）",
        "seed_rule": cdoc.get("seed_rule", ""),
        "case_id_rule": cdoc.get("case_id_rule", ""),
        "selection": {
            "rare_freq": args.rare_freq,
            "min_uses": args.min_uses,
            "per_item": args.per_item,
            "targets": [{"item": n, "hist": f, "before": u} for n, f, u in targets],
            "skipped_unreachable": [{"item": n, "before": u, "why": w} for n, u, w in skipped],
            "supplement_cases": len(out_cases),
            "mirrored_cases": len(mirrored),
            "filled": dict(sorted(filled.items())),
        },
        "cases": out_cases,
    }
    with open(args.out, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, ensure_ascii=False, indent=1)
        f.write("\n")

    lines = ["# 稀有物品补样报告（第二批）", ""]
    lines.append("生成：%s｜补样器：tools/expand_supplement.py｜补样 **%d 场**"
                 % (doc["generated_at"], len(out_cases)))
    lines.append("")
    lines.append("## 一、目标与缺口")
    lines.append("")
    lines.append("| 物品 | 历史库频次 | 补样前出场 | 本批补入 |")
    lines.append("|---|---|---|---|")
    for n, f, u in targets:
        lines.append("| %s | %d | %d | %d |" % (n, f, u, filled.get(n, 0)))
    if skipped:
        lines.append("")
        lines.append("### 无法覆盖（如实记录）")
        lines.append("")
        for n, u, w in skipped:
            lines.append("- %s（补样前 %d 次）：%s" % (n, u, w))
    lines.append("")
    lines.append("## 二、硬约束")
    lines.append("")
    lines.append("| 项 | 值 |")
    lines.append("|---|---|")
    lines.append("| 与首批重复 | 0（候选池已排除首批用过的回合） |")
    lines.append("| 镜像对局 | %d |" % len(mirrored))
    lines.append("| 补样场次 | %d |" % len(out_cases))
    lines.append("")
    lines.append("## 三、执行")
    lines.append("")
    lines.append("    python -X utf8 tools/expand_run_oracle.py --cases output/oracle/expand/supplement_cases.json")
    with open(args.report, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")

    print("[supp] 补样场次 %d；镜像 %d；目标物品 %d 件；用时 %.1fs"
          % (len(out_cases), len(mirrored), len(targets), time.time() - t0))
    print("[supp] 已写出 %s 与 %s" % (args.out, args.report))


if __name__ == "__main__":
    main()
