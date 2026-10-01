# -*- coding: utf-8 -*-
"""per_item_diff.py — 逐物品激活/伤害/事件量对照（单组真值 vs 模拟中位数）"""
from __future__ import annotations

import json
import os
import statistics
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

SEEDS = (42, 43, 44)


def side_of_origin(log_events):
    """真值 origin 物品 → 'P'/'O'。DealDamage/CriticalDamage 的 origin 在
    target 对面（攻击者）；其余事件 origin 与 side 同侧。"""
    vote = {}
    for e in log_events:
        o = e.get("origin")
        if not (o and o.get("name")):
            continue
        name = o["name"]
        t = e.get("type_name", "")
        tgt = e.get("target")
        side = e.get("side")
        if t in ("DealDamage", "CriticalDamage") and tgt in (0, 1):
            side = "O" if tgt == 0 else "P"
        if side in ("P", "O"):
            vote.setdefault(name, {}).setdefault(side, 0)
            vote[name][side] += 1
    return {name: max(v, key=v.get) for name, v in vote.items()}


def analyze(events, side_of, origin_key, side_key, side_map=None):
    """按 (side, item) 统计激活次数与伤害总量。

    origin_key(events[i]) → 物品名；side_key(events[i]) → 'P'/'O' 或
    需经 side_map 映射（模拟器 actor 名 → P/O）。
    """
    act = Counter()
    dmg = Counter()
    for e in events:
        name = origin_key(e)
        if not name:
            continue
        side = side_key(e)
        if side_map and side not in ("P", "O"):
            side = side_map.get(side)
        if side not in ("P", "O"):
            continue
        key = (side, name)
        t = e.get("type_name") or e.get("type")
        if t == "Activation" or t == "item_activate":
            act[key] += 1
        if t in ("DealDamage", "CriticalDamage") or t == "attack":
            dmg[key] += (e.get("params", {}) or {}).get("damage", 0)
    return act, dmg


def main(grp_path):
    from engine.combat import CombatEngine
    from engine.data import load_items, load_characters
    from simulator.lineup import load_lineup

    base = os.path.join(grp_path, os.path.basename(grp_path.rstrip("\\/")))
    log = json.load(open(base + ".json", encoding="utf-8"))
    tev = log["events"]
    side_map = side_of_origin(tev)

    t_act, t_dmg = analyze(
        tev, side_map,
        lambda e: (e.get("origin") or {}).get("name"),
        lambda e: e.get("side"))

    item_db = load_items()
    char_db = load_characters()
    la = load_lineup(base + ".Player.json")
    lb = load_lineup(base + ".Opponent.json")

    sim_acts = []
    sim_dmgs = []
    for seed in SEEDS:
        eng = CombatEngine(la, lb, item_db, char_db, seed=seed)
        eng.run()
        p_name = eng.player.name()
        o_name = eng.opponent.name()
        smap = {p_name: "P", o_name: "O"}
        act, dmg = analyze(
            eng.log.to_dict(), None,
            lambda e: e.get("origin"),
            lambda e: smap.get(e.get("actor")))
        sim_acts.append(act)
        sim_dmgs.append(dmg)

    def med(counter_list, key):
        vals = [c.get(key, 0) for c in counter_list]
        return statistics.median(vals)

    keys = sorted(set(t_act) | set(t_dmg) |
                  set().union(*[set(c) for c in sim_acts + sim_dmgs]))
    rows = []
    for k in keys:
        ta, td = t_act.get(k, 0), t_dmg.get(k, 0)
        ma = med(sim_acts, k)
        md = med(sim_dmgs, k)
        if ta == 0 and td == 0 and ma == 0 and md == 0:
            continue
        rows.append({
            "side": k[0], "item": k[1],
            "act_truth": ta, "act_sim_med": ma,
            "act_ratio": round(ma / ta, 2) if ta else None,
            "dmg_truth": td, "dmg_sim_med": md,
            "dmg_ratio": round(md / td, 2) if td else None,
        })
    rows.sort(key=lambda r: -max(r["act_truth"], r["dmg_truth"],
                                 r["act_sim_med"], r["dmg_sim_med"]))
    print("%-2s %-22s %8s %8s %6s | %8s %8s %6s" % (
        "侧", "物品", "激活真值", "激活模拟", "比", "伤害真值", "伤害模拟", "比"))
    for r in rows:
        print("%-2s %-22s %8d %8.0f %6s | %8d %8.0f %6s" % (
            r["side"], r["item"], r["act_truth"], r["act_sim_med"],
            r["act_ratio"] if r["act_ratio"] is not None else "-",
            r["dmg_truth"], r["dmg_sim_med"],
            r["dmg_ratio"] if r["dmg_ratio"] is not None else "-"))
    return rows


if __name__ == "__main__":
    grp = sys.argv[1] if len(sys.argv) > 1 else os.path.join(
        ROOT, "dist", "output", "combat_logs",
        "CombatLog_20261001_221407_R19_Win")
    main(grp)
