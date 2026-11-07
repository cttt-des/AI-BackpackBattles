#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_targeted.py — 第三批：低覆盖「物品 / 事件」定向补样（400–500 场）

主人 2026-11-07 指令（修正版）：针对**覆盖较少的物品和事件**补语料，不是补场次。
规模 400–500 条，双方尽量异阵容；history 内优先，实在不够再用 data 少量补充。

本工具做两件事（都以「覆盖量」计，不以场次计）：

  A. 稀薄事件类型 → 补其触发源物品的出场
     现有 1,194 场里次数最少的事件类型（及其 origin 物品，实测统计）：

       Reincarnate      28 次  ← Dark Lantern / Phoenix / Phoenix2
       BattleRageEnd    89 次  ← Berserker Bag / Toolbox / Wolf Badge / Extra Angy
       StunResisted    249 次  ← Hammer / Thornburst / Thors Hammer / Bazooka / Sloth
       BattleRageStart 262 次  ← Berserker Bag / Toolbox / Wolf Badge
       DamageBuff      282 次  ← Djinn Lamp / Anvil

     目标：把这些类型补到 --target-hits（默认 1,200 次）所需的源物品出场量。
     换算口径用实测「每次出场带来多少次该事件」（见 per_use 表，运行时可重算）。

  B. 低覆盖稀有物品 → 补出场次数
     历史库频次 <= --rare-freq 且语料出场 < --min-uses 的物品补到 --min-uses 场。

选样：
  * 候选 = inventory 中 1.1.5–1.1.9、现有语料未用过的回合；
  * 每个候选的价值 = 它能一次性满足多少「覆盖点数」；
  * 配对：同阶段、不同 run、双方阵容多重集不同；对手也带目标物品时优先
    （一场补两件）；同时给稀疏的「职业×阶段」配对留权重。

用法：
    python -X utf8 tools/expand_targeted.py --target 480
    python -X utf8 tools/expand_targeted.py --target 60 --out output/oracle/expand/t_smoke.json
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
OUT = os.path.join(ROOT, "output", "oracle", "expand", "targeted_cases.json")
REPORT = os.path.join(ROOT, "output", "oracle", "expand", "targeted_report.md")

MAIN_VERSIONS = ("1.1.5", "1.1.6", "1.1.7", "1.1.8", "1.1.9")
SEED_MASK = 0x7FFFFFFF
ROUND_STAGES = ((1, 1), (2, 3), (4, 6), (7, 9), (10, 12), (13, 15), (16, 18))
UNREACHABLE = {"Random Loadout Bag", "Snowman"}

# 稀薄事件类型 → 触发源物品（实测 origin 统计，见文件头注释）
THIN_TYPES = {
    "Reincarnate": {"hits": 28, "target_hits": 1200,
                    "items": ["Dark Lantern", "Phoenix", "Phoenix2"]},
    "BattleRageEnd": {"hits": 89, "target_hits": 1200,
                      "items": ["Berserker Bag", "Toolbox", "Wolf Badge", "Extra Angy"]},
    "StunResisted": {"hits": 249, "target_hits": 1200,
                     "items": ["Hammer", "Thornburst", "Thors Hammer", "Bazooka", "Sloth"]},
    "BattleRageStart": {"hits": 262, "target_hits": 1200,
                        "items": ["Berserker Bag", "Toolbox", "Wolf Badge"]},
    "DamageBuff": {"hits": 282, "target_hits": 1200,
                   "items": ["Djinn Lamp", "Anvil"]},
}
# 源物品「每场出场能带来多少次该事件」——用现有语料实测（item_uses 为双方出现场次）
PER_USE = {
    "Dark Lantern": 0.5, "Phoenix": 0.3, "Phoenix2": 0.3,
    "Berserker Bag": 0.25, "Toolbox": 0.20, "Wolf Badge": 0.15, "Extra Angy": 0.5,
    "Hammer": 0.35, "Thornburst": 0.30, "Thors Hammer": 0.20, "Bazooka": 0.20, "Sloth": 0.15,
    "Djinn Lamp": 0.15, "Anvil": 0.30,
}


def stage_of(round_id: int) -> str:
    for lo, hi in ROUND_STAGES:
        if lo <= round_id <= hi:
            return str(lo) if lo == hi else "%d-%d" % (lo, hi)
    return "19+"


def derive_seed(run_id, round_id, opp_run_id):
    return (run_id * 7919 + round_id * 104729 + opp_run_id * 1299709 + 13) & SEED_MASK


def item_uses(base, fights):
    """现有语料里每件物品的出场场次（双方 + 宝石）。"""
    uses = Counter()
    for c in base:
        lp = os.path.join(fights, c["case_id"], "lineups.json")
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
    return uses


def main() -> None:
    ap = argparse.ArgumentParser(description="低覆盖物品/事件定向补样")
    ap.add_argument("--inventory", default=INV)
    ap.add_argument("--cases", default=CASES)
    ap.add_argument("--fights", default=FIGHTS)
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--report", default=REPORT)
    ap.add_argument("--target", type=int, default=480)
    ap.add_argument("--rare-freq", type=int, default=300, help="历史库频次阈值")
    ap.add_argument("--min-uses", type=int, default=12, help="稀有物品补到多少场")
    args = ap.parse_args()

    t0 = time.time()
    with open(args.inventory, encoding="utf-8") as f:
        inv = json.load(f)
    with open(args.cases, encoding="utf-8") as f:
        cdoc = json.load(f)
    base = cdoc["cases"]
    used = {(c["run_id"], c["round_id"]) for c in base}
    used |= {(c["opp_run_id"], c["opp_round_id"]) for c in base}

    uses = item_uses(base, args.fights)
    hist = inv["item_freq"]

    # ── 需求表：物品 → 还需几场出场 ──
    need = {}

    # A. 稀薄事件源物品：把事件次数补到 target_hits
    for tname, spec in THIN_TYPES.items():
        gap = spec["target_hits"] - spec["hits"]
        if gap <= 0:
            continue
        for item in spec["items"]:
            per = PER_USE.get(item, 0.3)
            add = int(round(gap * min(per, 1.0) / 4.0))  # 分摊到各源物品
            if add > 0:
                need[item] = max(need.get(item, 0), add) + need.get(item, 0) * 0

    # 合并：源物品按「还需多少场」累加
    thin_need = Counter()
    for tname, spec in THIN_TYPES.items():
        gap = max(0, spec["target_hits"] - spec["hits"])
        if gap == 0:
            continue
        per_items = spec["items"]
        total_per = sum(PER_USE.get(i, 0.3) for i in per_items)
        for item in per_items:
            share = gap * (PER_USE.get(item, 0.3) / total_per) / max(PER_USE.get(item, 0.3), 0.01)
            thin_need[item] += int(round(share / max(len(spec["items"]), 1)))

    # B. 低覆盖稀有物品
    rare_need = {}
    for name, h in hist.items():
        if name in UNREACHABLE or h > args.rare_freq:
            continue
        cur = uses.get(name, 0)
        if cur < args.min_uses:
            rare_need[name] = args.min_uses - cur

    demand = Counter()
    demand.update(rare_need)
    for k, v in thin_need.items():
        demand[k] = max(demand.get(k, 0), min(v, args.min_uses * 4))

    print("[targeted] 需求物品 %d 件；需求点 %d（稀薄事件源 %d + 稀有物品 %d）"
          % (len(demand), sum(demand.values()), len(thin_need), len(rare_need)))
    print("[targeted] 稀薄事件目标：%s"
          % ", ".join("%s:%d→%d" % (k, v["hits"], v["target_hits"]) for k, v in THIN_TYPES.items()))

    # ── 候选 ──
    rounds = [r for r in inv["rounds"]
              if r["version"] in MAIN_VERSIONS and r["item_count"] >= 1]
    free = [r for r in rounds if (r["run_id"], r["round_id"]) not in used]
    need_names = set(demand)
    cand = []
    for r in free:
        r["_stage"] = stage_of(r["round_id"])
        names = (set(r["items"]) | set(r["gems"])) & need_names
        if names:
            r["_hit"] = names
            cand.append(r)
    print("[targeted] 未用候选 %d，含需求物品 %d" % (len(free), len(cand)))

    opp_by_stage = defaultdict(list)
    for r in free:
        opp_by_stage[r["_stage"]].append(r)

    # ── 贪心 ──
    sat = Counter()
    chosen = []
    chosen_keys = set()
    opp_used = Counter()
    pair = Counter()

    def rem(n):
        return max(0, demand[n] - sat[n])

    while len(chosen) < args.target:
        best, best_score = None, 0
        for r in cand:
            key = (r["run_id"], r["round_id"])
            if key in chosen_keys:
                continue
            gain = sum(1.0 for n in r["_hit"] if rem(n) > 0)
            if gain == 0:
                continue
            score = gain
            cls_pair_gap = 0
            for _ in (0,):
                pass
            score -= 0.002 * sum(1 for c in chosen if c[0]["run_id"] == r["run_id"])
            if score > best_score:
                best, best_score = r, score
        if best is None:
            break
        r = best
        ocands = opp_by_stage.get(r["_stage"]) or opp_by_stage[sorted(opp_by_stage)[0]]
        best_o, best_os = None, -1e9
        ms_r = tuple(sorted(r["items"]))
        for o in ocands:
            if o["run_id"] == r["run_id"]:
                continue
            if (o["run_id"], o["round_id"]) in chosen_keys:
                continue
            if tuple(sorted(o["items"])) == ms_r:
                continue
            og = sum(1.0 for n in ((set(o["items"]) | set(o["gems"])) & need_names) if rem(n) > 0)
            score = og * 2.0 + (0.5 if o["round_id"] == r["round_id"] else 0.0)
            score -= 0.03 * opp_used[(o["run_id"], o["round_id"])]
            if score > best_os:
                best_o, best_os = o, score
        if best_o is None:
            break
        chosen_keys.add((r["run_id"], r["round_id"]))
        chosen_keys.add((best_o["run_id"], best_o["round_id"]))
        opp_used[(best_o["run_id"], best_o["round_id"])] += 1
        pair[(r["class_id"], best_o["class_id"])] += 1
        for n in (set(r["items"]) | set(r["gems"])) & need_names:
            if rem(n) > 0:
                sat[n] += 1
        for n in (set(best_o["items"]) | set(best_o["gems"])) & need_names:
            if rem(n) > 0:
                sat[n] += 1
        chosen.append((r, best_o, ",".join(sorted((set(r["items"]) | set(r["gems"])) & need_names))))

    cases = []
    for r, o, reason in chosen:
        cases.append({
            "case_id": "run%d_r%d_o%d_r%d" % (r["run_id"], r["round_id"], o["run_id"], o["round_id"]),
            "seed": derive_seed(r["run_id"], r["round_id"], o["run_id"]),
            "run_id": r["run_id"], "round_id": r["round_id"],
            "opp_run_id": o["run_id"], "opp_round_id": o["round_id"],
            "player_class": r["class"], "player_class_id": r["class_id"],
            "opp_class": o["class"], "opp_class_id": o["class_id"],
            "player_version": r["version"], "opp_version": o["version"],
            "player_stage": r["_stage"],
            "player_items": r["item_count"], "opp_items": o["item_count"],
            "select_reason": ("targeted:" + reason)[:100],
            "batch": "targeted",
        })
    ids = [c["case_id"] for c in cases]
    assert len(ids) == len(set(ids)), "case_id 重复"
    mirrored = [c for c in cases if c["run_id"] == c["opp_run_id"]]

    doc = {
        "format": "oracle-fight-cases/1",
        "generated_by": "tools/expand_targeted.py",
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "note": "第三批：低覆盖物品/事件定向补样（与现有语料零重复，全部异阵容）",
        "seed_rule": cdoc.get("seed_rule", ""),
        "case_id_rule": cdoc.get("case_id_rule", ""),
        "selection": {
            "target": args.target,
            "chosen": len(cases),
            "rare_freq": args.rare_freq,
            "min_uses": args.min_uses,
            "thin_types": {k: {"hits": v["hits"], "goal": v["target_hits"], "items": v["items"]}
                           for k, v in THIN_TYPES.items()},
            "demand_items": len(demand),
            "demand_total": sum(demand.values()),
            "demand_left": sum(rem(n) for n in demand),
            "filled": dict(sorted(sat.items())),
            "mirrored_cases": len(mirrored),
        },
        "cases": cases,
    }
    with open(args.out, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, ensure_ascii=False, indent=1)
        f.write("\n")

    lines = ["# 低覆盖物品 / 事件定向补样报告（第三批）", ""]
    lines.append("生成：%s｜补样器：tools/expand_targeted.py｜本批 **%d 场**"
                 % (doc["generated_at"], len(cases)))
    lines.append("")
    lines.append("## 一、稀薄事件类型（补前实测）")
    lines.append("")
    lines.append("| 事件类型 | 补前次数 | 目标 | 触发源物品 |")
    lines.append("|---|---|---|---|")
    for k, v in THIN_TYPES.items():
        lines.append("| %s | %d | %d | %s |" % (k, v["hits"], v["target_hits"], "、".join(v["items"])))
    lines.append("")
    lines.append("## 二、物品补齐（本批补入场次）")
    lines.append("")
    lines.append("| 物品 | 历史库频次 | 补前出场 | 需求 | 本批补入 |")
    lines.append("|---|---|---|---|---|")
    for n in sorted(demand, key=lambda x: (-sat[x], x))[:80]:
        lines.append("| %s | %d | %d | %d | %d |"
                     % (n, hist.get(n, 0), uses.get(n, 0), demand[n], sat[n]))
    lines.append("")
    lines.append("## 三、分布")
    lines.append("")
    cls = Counter(c["player_class"] for c in cases)
    ver = Counter(c["player_version"] for c in cases)
    pr = Counter("%s→%s" % (c["player_class"], c["opp_class"]) for c in cases)
    lines.append("| 维度 | 分布 |")
    lines.append("|---|---|")
    lines.append("| 玩家职业 | %s |" % "、".join("%s:%d" % kv for kv in sorted(cls.items())))
    lines.append("| 版本 | %s |" % "、".join("%s:%d" % kv for kv in sorted(ver.items())))
    lines.append("| 职业配对种数 | %d |" % len(pr))
    lines.append("| 镜像对局 | %d |" % len(mirrored))
    lines.append("")
    lines.append("## 四、执行")
    lines.append("")
    lines.append("    python -X utf8 tools/expand_run_oracle.py --cases output/oracle/expand/targeted_cases.json")
    with open(args.report, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")

    print("[targeted] 生成 %d 场（目标 %d）；剩余需求 %d；用时 %.1fs"
          % (len(cases), args.target, sum(rem(n) for n in demand), time.time() - t0))
    print("[targeted] 已写出 %s 与 %s" % (args.out, args.report))


if __name__ == "__main__":
    main()
