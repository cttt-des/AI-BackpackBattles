# -*- coding: utf-8 -*-
"""compare_gd_truth.py — 真值战斗日志 ↔ **gd_core 内核**（GDCoreEngine）对照基准

为什么存在
==========
tools/compare_truth.py 是仓库里唯一的真值对照工具，但它在 main() 里驱动的是
**旧引擎** `engine.combat.CombatEngine`（tools/compare_truth.py:90），完全不
import gd_core_py——它测不到 gd_core 内核。gd_core 内核成为唯一内核（旧内核
已下线）且经历 2026-10-03 同 seed 复现性修复（行为不保持，见
ai/kernel_fix_behavior_change.md）之后，**修复后的 gd_core 内核没有任何真值
对齐数**。本工具补上这一块：协议与 tools/compare_truth.py 同款（同真值组、
同 seeds 42..46、同事件类型映射），只把被测引擎换成 GDCoreEngine。

对每组真值（dist/output/combat_logs 下 3 日志 + 2 阵容）：
  1. 装配闸：构造一次 GDCoreEngine——抛 _MissingItem 的组（实录混有
     GoldCounter 等不可装配件）整组跳过（与 ai/eval.py 口径一致）；
  2. 用真值双方阵容跑 seeds 42..46（每局前 reset_kernel_state()，与
     eval.py / dump_gd_outcomes.py 口径一致）；
  3. 汇总：逐组方向命中（5 seed 多数胜负 vs 真值 Win/Loss）、逐 (组,seed)
     胜负命中、时长中位数 vs 真值、事件类型分布比（sim 中位 / 真值）。

输出：控制台报告 + ai/gd_truth_compare.json

直接运行：  python ai/compare_gd_truth.py [--seeds 42,43,44,45,46]
"""
from __future__ import annotations

import glob
import json
import os
import statistics
import sys
from collections import Counter

_HERE = os.path.dirname(os.path.abspath(__file__))
_ROOT = os.path.dirname(_HERE)
if _ROOT not in sys.path:
    sys.path.insert(0, _ROOT)

from simulator.gd_core_engine import GDCoreEngine, _MissingItem   # noqa: E402
from simulator.lineup import load_lineup                          # noqa: E402

_LOG_DIR = os.path.join(_ROOT, "dist", "output", "combat_logs")
_OUT_PATH = os.path.join(_HERE, "gd_truth_compare.json")
SEEDS = list(range(42, 47))          # 与 tools/compare_truth.py 同款
# 参与对比的事件类型（同 tools/compare_truth.py::TYPES）
TYPES = ["Activation", "DealDamage", "CriticalDamage", "MissedAttack",
         "Health", "Block", "Lucky", "Mana", "Empower", "Heat", "Poison",
         "Spikes", "Regeneration", "Vampirism", "Stamina", "DrainStamina",
         "Stun", "Fatigue", "TemporaryMaxHealth"]

# 模拟器 type 字符串 → 真值 type_name（逐字复制 tools/compare_truth.py 的映射，
# GDCoreEngine 的事件视图与旧引擎 `engine/events.py::Event` 字段一致，
# 见 simulator/gd_core_engine.py::_EventOut / _LogMixin.to_dict）。
_ET_MAP = {
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
_BUFF_MAP = {"block": "Block", "lucky": "Lucky", "mana": "Mana",
             "empower": "Empower", "heat": "Heat", "poison": "Poison",
             "spikes": "Spikes", "regen": "Regeneration",
             "vampirism": "Vampirism", "blind": None, "cold": None}


# 栈事件 buff 类型：gd_core 引擎的栈事件（stack_gain/lose/timeout）把类型放在
# 事件视图的 `buff_type`（CoreConst.EventType 100..110，见
# simulator/gd_core_engine.py::_LogMixin.logEvent），而不是旧引擎的
# params['buff'] 字符串——故这里按 int 映射（CoreConst.EventType 实测序）。
_STACK_MAP = {100: "Block", 101: "Lucky", 102: "Regeneration",
              103: "Vampirism", 104: "Spikes", 105: "Mana", 106: "Empower",
              107: "Heat", 108: "Poison", 109: None, 110: None}


def sim_event_counts(events):
    """模拟器事件按真值 type_name 分类计数（同 tools/compare_truth.py）。"""
    counts = Counter()
    for ev in events:
        name = _ET_MAP.get(ev["type"], "?")
        if name is None and ev["type"] in ("stack_gain", "stack_lose",
                                           "stack_timeout"):
            bt = ev.get("buff_type")
            if bt is not None:
                name = _STACK_MAP.get(bt if isinstance(bt, int) else int(bt))
            else:
                name = _BUFF_MAP.get((ev.get("params", {}).get("buff") or "").lower())
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


def main(argv):
    seeds = SEEDS
    if "--seeds" in argv:
        seeds = [int(s) for s in argv[argv.index("--seeds") + 1].split(",")]
    from ai.kernel_reset import reset_kernel_state

    groups = []
    for grp in sorted(glob.glob(os.path.join(_LOG_DIR, "*"))):
        base = os.path.join(grp, os.path.basename(grp))
        if os.path.isfile(base + ".Player.json"):
            groups.append((os.path.basename(grp), base))
    print("真值组: %d  每组 %d 种子（内核: GDCoreEngine）\n" % (len(groups), len(seeds)))

    report = []
    n_row_hit = n_row = 0
    n_dir_hit = n_dir = 0
    for name, base in groups:
        truth_log = json.load(open(base + ".json", encoding="utf-8"))
        tev = truth_log["events"]
        tc = truth_counts(tev)
        t_end = max((e.get("t", 0) for e in tev), default=0)
        t_win = any(e.get("type_name") == "Win" for e in tev)

        try:
            la = load_lineup(base + ".Player.json")
            lb = load_lineup(base + ".Opponent.json")
        except Exception as e:  # noqa: BLE001
            report.append({"name": name, "skip": "load: %r" % (e,)})
            print("%-44s SKIP(load): %r" % (name, e))
            continue

        # 装配闸：_MissingItem 的组整组跳过（同 ai/eval.py 口径）
        reset_kernel_state()
        try:
            probe = GDCoreEngine(la, lb, {}, {}, seed=seeds[0])
        except _MissingItem as e:
            report.append({"name": name, "skip": "missing_item: %s" % (e,)})
            print("%-44s SKIP(missing_item)" % name)
            continue
        del probe

        wins = 0
        ends = []
        dists = []
        row_hits = []
        rows = []
        for seed in seeds:
            reset_kernel_state()
            try:
                eng = GDCoreEngine(la, lb, {}, {}, seed=seed)
                eng.run()
            except Exception as e:  # noqa: BLE001
                print("  %s seed%d 模拟失败: %r" % (name, seed, e))
                row_hits.append(None)
                rows.append({"seed": seed, "error": repr(e)})
                continue
            w = int(eng.player_wins())
            wins += w
            hit = (w == int(t_win))
            row_hits.append(hit)
            rows.append({"seed": seed, "winner": w, "truth_winner": int(t_win),
                         "time": round(eng.summary()["time"], 3)})
            ends.append(eng.summary()["time"])
            # 注意：不能走 eng.log.to_dict()——它不携带 buff_type，栈事件
            # （Block/Lucky/Mana…）会全部数成 0。直接用事件视图对象。
            dists.append(sim_event_counts(
                [{"type": e.type, "params": e.params, "buff_type": e.buff_type}
                 for e in eng.log.events]))

        ok = [h for h in row_hits if h is not None]
        n_row += len(ok)
        n_row_hit += sum(ok)
        dir_hit = (wins >= (len(seeds) + 1) // 2) == t_win if ok else None
        if dir_hit is not None:
            n_dir += 1
            n_dir_hit += int(dir_hit)

        med_end = statistics.median(ends) if ends else None
        dist_ratio = {}
        for t in TYPES:
            tv = tc.get(t, 0)
            if tv == 0:
                continue
            sims = sorted(d.get(t, 0) for d in dists)
            med = sims[len(sims) // 2]
            dist_ratio[t] = {"truth": tv, "sim_med": med,
                             "ratio": round(med / tv, 2) if tv else None}
        deviant = {t: v for t, v in dist_ratio.items()
                   if v["ratio"] is not None and (v["ratio"] < 0.6 or v["ratio"] > 1.6)}

        print("%-44s 逐seed命中 %d/%d  胜率 %d/%d (真值%s) 时长 med %.1fs vs %.1fs" % (
            name, sum(ok), len(ok), wins, len(ends),
            "Win" if t_win else "Loss", med_end or 0, t_end))
        print("   大偏差类型: %s" % json.dumps(deviant, ensure_ascii=False))
        report.append({
            "name": name, "truth_win": t_win, "truth_time": t_end,
            "wins": wins, "n_seeds": len(ends), "direction_hit": dir_hit,
            "row_hits": "%d/%d" % (sum(ok), len(ok)) if ok else None,
            "sim_time_median": med_end, "rows": rows,
            "dist": dist_ratio, "deviant": deviant,
        })

    print("\n────── 汇总 ──────")
    print("逐组方向命中（5 seed 多数 vs 真值）: %d/%d" % (n_dir_hit, n_dir))
    print("逐 (组,seed) 胜负命中: %d/%d" % (n_row_hit, n_row))
    summary = {"direction_hits": n_dir_hit, "direction_total": n_dir,
               "row_hits": n_row_hit, "row_total": n_row, "seeds": seeds,
               "engine": "simulator.gd_core_engine.GDCoreEngine"}
    with open(_OUT_PATH, "w", encoding="utf-8") as f:
        json.dump({"summary": summary, "groups": report}, f,
                  ensure_ascii=False, indent=1)
    print("报告: %s" % _OUT_PATH)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
