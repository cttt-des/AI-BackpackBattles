#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""expand_accept.py — 扩样语料验收（覆盖广度 / 异阵容 / 完整性）

对 output/oracle/expand/fights/ 下的扩样语料做四类验收，产出
output/oracle/expand/acceptance_report.md + acceptance.json：

  A 完整性   用例表每一场是否都有 events.json（event_count>0）；失败/剔除数量与清单
  B 异阵容   逐场读 lineups.json，双方物品多重集必须不同（本批硬约束）；
             同时统计双方职业、版本、件数分布
  C 覆盖广度 物品/宝石覆盖（对照 inventory 的 514 种与描述符表全部物品）、
             事件类型覆盖（Game.EventType 0..25 + 98..112）、职业配对 7x7、
             回合阶段分布、结果分布（胜负/平）
  D 质量     事件数/ticks 分布、winner 可知率、战斗时长分布

只读：不改任何语料文件。

用法：
    python -X utf8 tools/expand_accept.py
    python -X utf8 tools/expand_accept.py --root output/oracle/expand/fights
"""
from __future__ import annotations

import argparse
import json
import os
import sys
import time
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CASES = os.path.join(ROOT, "output", "oracle", "expand", "cases.json")
INV = os.path.join(ROOT, "output", "oracle", "expand", "inventory.json")
FIGHTS = os.path.join(ROOT, "output", "oracle", "expand", "fights")
REPORT = os.path.join(ROOT, "output", "oracle", "expand", "acceptance_report.md")
OUT_JSON = os.path.join(ROOT, "output", "oracle", "expand", "acceptance.json")

EVENT_NAMES = {
    0: "Activation", 1: "DealDamage", 2: "CriticalDamage", 3: "MissedAttack",
    4: "TakeDamage", 5: "LoseHealth", 6: "AttackSpeed", 7: "InvulnerableStart",
    8: "InvulnerableEnd", 9: "Stun", 10: "StunResisted", 11: "CriticalResisted",
    12: "Health", 13: "Stamina", 14: "DrainStamina", 15: "OutofStamina",
    16: "DamageBuff", 17: "DamReduction", 18: "DamIncrease",
    19: "TemporaryMaxHealth", 20: "TemporaryMaxStamina", 21: "BattleRageStart",
    22: "BattleRageEnd", 23: "Reincarnate", 24: "CooldownAdvance",
    98: "Unhealing", 99: "Fatigue", 100: "Block", 101: "Lucky",
    102: "Regeneration", 103: "Vampirism", 104: "Spikes", 105: "Mana",
    106: "Empower", 107: "Heat", 108: "Poison", 109: "Blind", 110: "Cold",
    111: "Win", 112: "Loss",
}
CLASS_NAMES = {0: "Ranger", 1: "Reaper", 2: "Berserker", 3: "Pyromancer",
               4: "Mage", 5: "Adventurer", 6: "Engineer"}


def item_names(side):
    return [it.get("name") for it in side.get("items", [])]


def main() -> None:
    ap = argparse.ArgumentParser(description="扩样语料验收")
    ap.add_argument("--root", default=FIGHTS)
    ap.add_argument("--cases", default=CASES)
    ap.add_argument("--inventory", default=INV)
    ap.add_argument("--report", default=REPORT)
    args = ap.parse_args()

    t0 = time.time()
    with open(args.cases, encoding="utf-8") as f:
        cdoc = json.load(f)
    cases = {c["case_id"]: c for c in cdoc["cases"]}
    with open(args.inventory, encoding="utf-8") as f:
        inv = json.load(f)

    done, missing, zero_event = [], [], []
    same_lineup = []
    lineup_diff = []          # 双方物品多重集的差异件数（平分差 / 2）
    ev_types = Counter()
    ev_total = 0
    item_used = Counter()
    gem_used = Counter()
    winners = Counter()
    ticks_list = []
    events_list = []
    pair = Counter()
    stage = Counter()
    pclass = Counter()
    oclass = Counter()
    hp_zero = 0
    errors = []

    for cid, c in cases.items():
        d = os.path.join(args.root, cid)
        evp = os.path.join(d, "events.json")
        lp = os.path.join(d, "lineups.json")
        if not os.path.exists(evp):
            missing.append(cid)
            continue
        try:
            with open(evp, encoding="utf-8") as f:
                ev = json.load(f)
        except Exception as e:
            errors.append("%s: events 解析失败 %s" % (cid, e))
            continue
        n = int(ev.get("event_count", 0) or 0)
        if n <= 0:
            zero_event.append(cid)
            continue
        done.append(cid)
        ev_total += n
        events_list.append(n)
        ticks_list.append(int(ev.get("ticks", 0) or 0))
        winners[str(ev.get("winner"))] += 1
        for e in ev.get("events", []):
            ev_types[int(e.get("type", -1))] += 1
        if os.path.exists(lp):
            try:
                with open(lp, encoding="utf-8") as f:
                    lu = json.load(f)
            except Exception as e:
                errors.append("%s: lineups 解析失败 %s" % (cid, e))
                lu = None
            if lu:
                pi = item_names(lu.get("player", {}))
                oi = item_names(lu.get("opponent", {}))
                if sorted(pi) == sorted(oi):
                    same_lineup.append(cid)
                lineup_diff.append(len(set(pi) ^ set(oi)))
                for name in pi + oi:
                    item_used[name] += 1
                pclass[CLASS_NAMES.get(int(lu.get("player", {}).get("class", -1)), "?")] += 1
                for it in lu.get("player", {}).get("items", []) + lu.get("opponent", {}).get("items", []):
                    for g in it.get("gems", []) or []:
                        gem_used[g] += 1

    # 用例表里声明的职业/阶段（不受 lineups 影响）
    for c in cdoc["cases"]:
        pair[(c.get("player_class"), c.get("opp_class"))] += 1
        stage[c.get("player_stage")] += 1
        oclass[c.get("opp_class")] += 1

    hist_freq = {k: int(v) for k, v in inv["item_freq"].items()}
    missing_items = sorted(k for k in hist_freq if item_used.get(k, 0) == 0)
    # 描述符表全集（含历史库从未出现的物品）
    desc_items = set()
    try:
        with open(os.path.join(ROOT, "assets", "item_index_map_live.json"), encoding="utf-8") as f:
            imap = json.load(f)
        desc_items = set(imap["index_to_name"].values())
    except Exception:
        pass
    desc_missing = sorted(desc_items - set(item_used))
    rare_uncovered = sorted(k for k, v in hist_freq.items() if v <= 40 and item_used.get(k, 0) == 0)

    pair_missing = [("%s->%s" % (a, b)) for a in CLASS_NAMES.values() for b in CLASS_NAMES.values()
                    if (a, b) not in pair]

    doc = {
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%S"),
        "root": os.path.relpath(args.root, ROOT).replace("\\", "/"),
        "cases": {
            "total": len(cases),
            "done": len(done),
            "missing": len(missing),
            "zero_event": len(zero_event),
            "errors": errors[:50],
        },
        "lineup": {
            "same_lineup_cases": len(same_lineup),
            "same_lineup_examples": same_lineup[:20],
            "lineup_diff_kinds_mean": (sum(lineup_diff) / len(lineup_diff)) if lineup_diff else 0,
            "lineup_diff_kinds_min": min(lineup_diff) if lineup_diff else 0,
            "lineup_diff_kinds_max": max(lineup_diff) if lineup_diff else 0,
            "lineup_diff_kinds_buckets": {
                "1-3": sum(1 for x in lineup_diff if 1 <= x <= 3),
                "4-6": sum(1 for x in lineup_diff if 4 <= x <= 6),
                "7-10": sum(1 for x in lineup_diff if 7 <= x <= 10),
                "11+": sum(1 for x in lineup_diff if x >= 11),
            },
        },
        "coverage": {
            "item_kinds_used": len(item_used),
            "item_kinds_in_history": len(hist_freq),
            "item_missing_in_history_kinds": len(missing_items),
            "rare_uncovered": rare_uncovered,
            "descriptor_items": len(desc_items),
            "descriptor_missing": desc_missing,
            "event_types_seen": len(ev_types),
            "event_types": {EVENT_NAMES.get(k, str(k)): v for k, v in sorted(ev_types.items())},
            "class_pairs": {"%s->%s" % k: v for k, v in sorted(pair.items())},
            "class_pairs_missing": pair_missing,
            "player_class": dict(sorted(pclass.items())),
            "opp_class": dict(sorted(oclass.items())),
            "stage": dict(sorted(stage.items(), key=lambda kv: int(kv[0].split("-")[0]))),
        },
        "quality": {
            "winners": dict(winners),
            "events_total": ev_total,
            "events_mean": (sum(events_list) / len(events_list)) if events_list else 0,
            "events_max": max(events_list) if events_list else 0,
            "ticks_mean": (sum(ticks_list) / len(ticks_list)) if ticks_list else 0,
            "ticks_max": max(ticks_list) if ticks_list else 0,
        },
        "item_freq": dict(sorted(item_used.items(), key=lambda kv: (-kv[1], kv[0]))),
        "gem_freq": dict(sorted(gem_used.items(), key=lambda kv: (-kv[1], kv[0]))),
    }
    with open(OUT_JSON, "w", encoding="utf-8", newline="\n") as f:
        json.dump(doc, f, ensure_ascii=False, indent=1)
        f.write("\n")

    ok = len(done) == len(cases) and not same_lineup and not pair_missing
    lines = []
    lines.append("# 扩样语料验收报告")
    lines.append("")
    lines.append("生成：%s｜根目录：%s｜验收器：tools/expand_accept.py"
                 % (doc["generated_at"], doc["root"]))
    lines.append("")
    lines.append("**总判定：%s**（完成 %d/%d，异阵容违例 %d，职业配对缺 %d）"
                 % ("PASS" if ok else "PARTIAL", len(done), len(cases), len(same_lineup), len(pair_missing)))
    lines.append("")
    lines.append("## A 完整性")
    lines.append("")
    lines.append("| 项 | 值 |")
    lines.append("|---|---|")
    lines.append("| 用例总数 | %d |" % len(cases))
    lines.append("| 已产出 events.json | %d |" % len(done))
    lines.append("| 缺 events.json | %d |" % len(missing))
    lines.append("| 事件数为 0 | %d |" % len(zero_event))
    lines.append("| 解析错误 | %d |" % len(errors))
    if missing:
        lines.append("")
        lines.append("缺失清单（前 30）：" + "、".join(missing[:30]))
    lines.append("")
    lines.append("## B 异阵容（本批硬约束）")
    lines.append("")
    lines.append("| 项 | 值 |")
    lines.append("|---|---|")
    lines.append("| 双方物品多重集相同的对局 | **%d** |" % len(same_lineup))
    lines.append("| 双方阵容差异（不同物品种类）均值 / 最小 / 最大 | %.1f / %d / %d |"
                 % (doc["lineup"]["lineup_diff_kinds_mean"],
                    doc["lineup"]["lineup_diff_kinds_min"],
                    doc["lineup"]["lineup_diff_kinds_max"]))
    lines.append("| 差异分档（1-3 / 4-6 / 7-10 / 11+ 件） | %s |"
                 % " / ".join(str(doc["lineup"]["lineup_diff_kinds_buckets"][k])
                               for k in ("1-3", "4-6", "7-10", "11+")))
    lines.append("| 玩家职业分布 | %s |" % "、".join("%s:%d" % kv for kv in sorted(pclass.items())))
    lines.append("| 对手职业分布 | %s |" % "、".join("%s:%d" % kv for kv in sorted(oclass.items())))
    lines.append("")
    lines.append("## C 覆盖广度")
    lines.append("")
    lines.append("| 维度 | 结果 |")
    lines.append("|---|---|")
    lines.append("| 物品 | 用上 **%d** 种 / 历史库 %d 种 / 描述符表 %d 种 |"
                 % (len(item_used), len(hist_freq), len(desc_items)))
    lines.append("| 历史库物品未出现 | %d 种%s |"
                 % (len(missing_items), ("（" + "、".join(missing_items[:10]) + "）") if missing_items else ""))
    lines.append("| 稀有物品（≤40 次）未覆盖 | %d 种 |" % len(rare_uncovered))
    lines.append("| 宝石 | %d 种 |" % len(gem_used))
    lines.append("| 事件类型 | **%d** 种 / 定义 39 种 |" % len(ev_types))
    lines.append("| 职业配对 | **%d** / 49%s |"
                 % (len(pair), ("，缺 " + "、".join(pair_missing)) if pair_missing else ""))
    lines.append("")
    lines.append("### 事件类型计数")
    lines.append("")
    lines.append("| 类型 | 名称 | 次数 |")
    lines.append("|---|---|---|")
    for k, v in sorted(ev_types.items()):
        lines.append("| %d | %s | %d |" % (k, EVENT_NAMES.get(k, "?"), v))
    lines.append("")
    lines.append("## D 质量")
    lines.append("")
    lines.append("| 项 | 值 |")
    lines.append("|---|---|")
    lines.append("| 胜负分布 | %s |" % "、".join("%s:%d" % kv for kv in sorted(winners.items())))
    lines.append("| 事件总数 | %d |" % ev_total)
    lines.append("| 单场事件均值 / 最大 | %.0f / %d |" % (doc["quality"]["events_mean"], doc["quality"]["events_max"]))
    lines.append("| 单场 tick 均值 / 最大 | %.0f / %d |"
                 % (doc["quality"]["ticks_mean"], doc["quality"]["ticks_max"]))
    lines.append("")
    lines.append("## 附录：物品使用频次（前 40）")
    lines.append("")
    lines.append("| 物品 | 次数 |")
    lines.append("|---|---|")
    for k, v in list(doc["item_freq"].items())[:40]:
        lines.append("| %s | %d |" % (k, v))
    with open(args.report, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")

    print("[accept] %s：完成 %d/%d，缺 %d，事件0 %d，异阵容违例 %d，配对 %d/49，事件类型 %d 种"
          % ("PASS" if ok else "PARTIAL", len(done), len(cases), len(missing), len(zero_event),
             len(same_lineup), len(pair), len(ev_types)))
    print("[accept] 物品 %d / 历史库 %d；宝石 %d；用时 %.1fs"
          % (len(item_used), len(hist_freq), len(gem_used), time.time() - t0))
    print("[accept] 报告：%s" % args.report)


if __name__ == "__main__":
    main()
