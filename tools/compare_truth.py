# -*- coding: utf-8 -*-
"""compare_truth.py — 真值战斗日志 ↔ 模拟器对照基准

对 dist/output/combat_logs/ 下每组真值（3 日志 + 2 阵容）：
  1. 用真值双方阵容喂模拟器（engine 内核）跑 N 个种子
  2. 汇总：胜负命中率、战斗时长中位数 vs 真值、事件类型分布比
输出控制台报告 + output/truth_compare.json
"""
from __future__ import annotations

import glob
import json
import os
import statistics
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

TRUTH_DIR = os.path.join(ROOT, "dist", "output", "combat_logs")
OUT_PATH = os.path.join(ROOT, "output", "truth_compare.json")
SEEDS = list(range(42, 47))          # 5 个种子取分布
# 参与对比的事件类型（模拟器 type → 真值 type_name 对齐名）
TYPES = ["Activation", "DealDamage", "CriticalDamage", "MissedAttack",
         "Health", "Block", "Lucky", "Mana", "Empower", "Heat", "Poison",
         "Spikes", "Regeneration", "Vampirism", "Stamina", "DrainStamina",
         "Stun", "Fatigue", "TemporaryMaxHealth"]


def truth_groups():
    out = []
    for grp in sorted(glob.glob(os.path.join(TRUTH_DIR, "*"))):
        if not os.path.isdir(grp):
            continue
        base = os.path.join(grp, os.path.basename(grp))
        if not os.path.exists(base + ".Player.json"):
            continue
        out.append({
            "name": os.path.basename(grp),
            "player": base + ".Player.json",
            "opponent": base + ".Opponent.json",
            "log": json.load(open(base + ".json", encoding="utf-8")),
        })
    return out


def sim_event_counts(events, type_names):
    """模拟器事件按真值 type_name 分类计数。"""
    # 模拟器 type 字符串 → 真值 type_name
    m = {
        "item_activate": "Activation", "attack": "DealDamage", "missed": "MissedAttack",
        "heal": "Health", "stack_gain": None, "stack_lose": None,
        "stack_timeout": None, "stun": "Stun", "stun_resisted": None,
        "invulnerable_start": None, "invulnerable_end": None,
        "stamina_gain": "Stamina", "stamina_drain": "DrainStamina",
        "out_of_stamina": None, "lose_health": None, "spike_damage": None,
        "unhealing": None, "fatigue_damage": "Fatigue", "fatigue_start": None,
        "crit_resisted": None, "combat_start": None, "combat_end": None,
        "death": None,
    }
    # stack_gain/lose 按参数 buff 名细分类（engine params['buff'] 为
    # BuffType.INV 名：block/regen/vampirism/...）
    buff_map = {"block": "Block", "lucky": "Lucky", "mana": "Mana",
                "empower": "Empower", "heat": "Heat", "poison": "Poison",
                "spikes": "Spikes", "regen": "Regeneration",
                "vampirism": "Vampirism", "blind": None, "cold": None}
    counts = Counter()
    for ev in events:
        name = m.get(ev["type"], "?")
        if name is None and ev["type"] in ("stack_gain", "stack_lose",
                                           "stack_timeout"):
            name = buff_map.get((ev.get("params", {}).get("buff") or "").lower())
        if name:
            counts[name] += 1
        if ev["type"] == "temporary_max_health":
            counts["TemporaryMaxHealth"] += 1
        if ev["type"] == "attack" and (ev.get("params", {}).get("crit")):
            counts["CriticalDamage"] += 1
    return counts


def truth_counts(events):
    return Counter(e.get("type_name", "?") for e in events
                   if e.get("type_name") in TYPES)


def main():
    from engine.combat import CombatEngine
    from engine.data import load_items, load_characters
    from simulator.lineup import load_lineup

    item_db = load_items()
    char_db = load_characters()
    groups = truth_groups()
    print(f"真值组: {len(groups)}  每组 {len(SEEDS)} 种子\n")

    report = []
    for g in groups:
        tev = g["log"]["events"]
        tc = truth_counts(tev)
        t_end = max((e.get("t", 0) for e in tev), default=0)
        t_win = any(e.get("type_name") == "Win" for e in tev)

        wins = 0
        ends = []
        dists = []
        for seed in SEEDS:
            try:
                la = load_lineup(g["player"])
                lb = load_lineup(g["opponent"])
                eng = CombatEngine(la, lb, item_db, char_db, seed=seed)
                eng.run()
            except Exception as e:  # noqa: BLE001
                print(f"  {g['name']} seed{seed} 模拟失败: {e}")
                continue
            s = eng.summary()
            if eng.player_wins():
                wins += 1
            ends.append(s["time"])
            dists.append(sim_event_counts(eng.log.to_dict(), TYPES))

        if not ends:
            continue
        win_rate = wins / len(ends)
        med_end = statistics.median(ends)
        # 事件分布比：模拟中位数 / 真值（逐类型）
        dist_ratio = {}
        for t in TYPES:
            tv = tc.get(t, 0)
            if tv == 0:
                continue
            sims = sorted(d.get(t, 0) for d in dists)
            med = sims[len(sims) // 2]
            dist_ratio[t] = {"truth": tv, "sim_med": med,
                             "ratio": round(med / tv, 2) if tv else None}

        # 大偏差类型（ratio < 0.6 或 > 1.6）
        deviant = {t: v for t, v in dist_ratio.items()
                   if v["ratio"] is not None and (v["ratio"] < 0.6 or v["ratio"] > 1.6)}
        print("%-44s 胜率 %.0f%% (真值%s) 时长 med %.1fs vs %.1fs" % (
            g["name"], win_rate * 100, "Win" if t_win else "Loss",
            med_end, t_end))
        print("   大偏差类型: %s" % json.dumps(deviant, ensure_ascii=False))
        report.append({
            "name": g["name"], "win_rate": win_rate, "truth_win": t_win,
            "sim_time_median": med_end, "truth_time": t_end,
            "dist": dist_ratio, "deviant": deviant,
        })

    with open(OUT_PATH, "w", encoding="utf-8") as f:
        json.dump(report, f, ensure_ascii=False, indent=1)
    print(f"\n报告: {OUT_PATH}")


if __name__ == "__main__":
    main()
