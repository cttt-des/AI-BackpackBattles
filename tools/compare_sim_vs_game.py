# -*- coding: utf-8 -*-
"""compare_sim_vs_game.py — 模拟器战报 vs 游戏导出战报 的结构化对比工具

用法:
    python tools/compare_sim_vs_game.py <玩家阵容.json> <对手阵容.json> \
        <游戏日志.json> [--seed 1]

游戏日志 JSON = combatlog_exporter 导出的 {meta, events}（CoreConst.EventType 口径）。
模拟器事件 = gd_core 内核事件桥（同口径，经 _LogMixin 转成 engine/log_text 视图）。

对比维度（RNG 不同时精确序列不可比，因此聚焦确定性/聚合维度）：
  1. t=0 开场事件多重集（无 RNG 参与）
  2. 每件物品首次触发时间
  3. 按 (side, origin, kind) 聚合的 触发次数 / 数值合计
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
from collections import defaultdict

_BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, _BASE)

from simulator.gd_core_engine import GDCoreEngine  # noqa: E402
from simulator.data import load_items, load_characters  # noqa: E402
from simulator.lineup import load_lineup  # noqa: E402

STACK_ZH = {100: "护盾", 101: "幸运", 102: "恢复", 103: "吸血", 104: "尖刺",
            105: "魔法", 106: "充能", 107: "狂热", 108: "中毒", 109: "致盲",
            110: "冰冷"}


_KIND_NORM = {
    "InvulnerableStart": "invulnerable_start",
    "InvulnerableEnd": "invulnerable_end",
    "OutofStamina": "out_of_stamina",
    "BattleRageStart": "battle_rage_start",
    "BattleRageEnd": "battle_rage_end",
}


def norm_kind(e) -> str:
    """把两边的 kind 归一成一个短标签。"""
    return _KIND_NORM.get(e["kind"], e["kind"])


def load_game_events(path: str):
    d = json.load(open(path, encoding="utf-8"))
    out = []
    for ev in d["events"]:
        tn = ev.get("type_name", "")
        side = ev.get("side", "")
        origin = (ev.get("origin") or {}).get("name") or (ev.get("origin") or {}).get("zh")
        params = ev.get("params") or {}
        t = float(ev.get("t", 0.0))
        if tn == "Activation":
            continue  # 两边 txt 都不渲染
        if 100 <= int(ev.get("type", -1)) <= 110:
            amt = int(params.get("amount", 0) or 0)
            kind = ("stack_lose" if amt < 0 else "stack_gain") + "|" + STACK_ZH[int(ev["type"])]
            amt = abs(amt)
        elif tn in ("DealDamage",):
            kind, amt = "dmg", float(params.get("damage", 0) or 0)
        elif tn == "CriticalDamage":
            kind, amt = "crit", float(params.get("damage", 0) or 0)
        elif tn == "Health":
            kind, amt = "heal", float(params.get("amount", 0) or 0)
        elif tn == "TemporaryMaxHealth":
            kind, amt = "tempmaxhp", float(params.get("amount", 0) or 0)
        elif tn == "DamageBuff":
            kind, amt = "dmgbuff", float(params.get("damage", params.get("amount", 0)) or 0)
        elif tn in ("LoseHealth",):
            kind, amt = "losehp", float(params.get("amount", 0) or 0)
        else:
            kind, amt = tn, None
        out.append({"t": t, "side": "P" if side == "P" else "O",
                    "kind": _KIND_NORM.get(kind, kind), "origin": _norm_origin(origin), "amount": amt})
    return out


def load_sim_events(player_path, opponent_path, seed):
    item_db, char_db = load_items(), load_characters()
    p = load_lineup(player_path)
    o = load_lineup(opponent_path)
    eng = GDCoreEngine(p, o, item_db, char_db, seed=seed, max_time=90.0)
    eng.run()
    out = []
    for e in eng.log.events:
        etype = e.type
        origin_zh = e.origin.key if e.origin is not None else None
        t = float(e.t)
        if etype.startswith("stack_"):
            zh = STACK_ZH.get(e.buff_type, str(e.buff_type))
            kind = etype + "|" + zh
            amt = abs(float(e.params.get("amount", 0) or 0))
        elif etype == "attack":
            kind, amt = "dmg", float(e.params.get("damage", 0) or 0)
        elif etype == "critical":
            kind, amt = "crit", float(e.params.get("damage", 0) or 0)
        elif etype == "heal":
            kind, amt = "heal", float(e.params.get("amount", 0) or 0)
        elif etype == "temporary_max_health":
            kind, amt = "tempmaxhp", float(e.params.get("amount", 0) or 0)
        elif etype == "damage_buff":
            kind, amt = "dmgbuff", float(e.params.get("damage", 0) or 0)
        elif etype == "lose_health":
            kind, amt = "losehp", float(e.params.get("amount", 0) or 0)
        elif etype in ("item_activate",):
            continue
        else:
            kind, amt = etype, None
        out.append({"t": t, "side": "P" if e.actor == "player" else "O",
                    "kind": _KIND_NORM.get(kind, kind), "origin": _norm_origin(origin_zh), "amount": amt})
    return out, eng


def _zh_name(key):
    if key is None:
        return None
    from engine.i18n import zh_name
    return zh_name(key)


# 两侧叫法归一（渲染口径差异，非行为差异）：非物品伤害来源
_ALIAS = {
    "spikes": "Spikes", "bl": "Block", "regen": "Regeneration",
    "vampirism": "Vampirism", "poison": "Poison", "poison_tick": "Poison",
}


def _norm_origin(name):
    if name is None:
        return None
    return _ALIAS.get(name, name)


def agg(events):
    """按 (side, origin, kind) 聚合 -> {key: [count, sum_amount]}"""
    m = defaultdict(lambda: [0, 0.0])
    for e in events:
        k = (e["side"], e["origin"] or "?", e["kind"])
        m[k][0] += 1
        if e["amount"] is not None:
            m[k][1] += e["amount"]
    return m


def opening(events, t_max=0.05):
    return [(e["side"], e["kind"], e["origin"], e["amount"]) for e in events
            if e["t"] <= t_max and e["kind"] != "combat_end"]


def first_triggers(events):
    m = {}
    for e in sorted(events, key=lambda x: x["t"]):
        k = (e["side"], e["origin"] or "?", e["kind"])
        if k not in m:
            m[k] = e["t"]
    return m


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("player")
    ap.add_argument("opponent")
    ap.add_argument("gamelog")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--tmax", type=float, default=None, help="截断时间窗")
    args = ap.parse_args()

    game = load_game_events(args.gamelog)
    sim, eng = load_sim_events(args.player, args.opponent, args.seed)
    if args.tmax:
        game = [e for e in game if e["t"] <= args.tmax]
        sim = [e for e in sim if e["t"] <= args.tmax]

    print("=== 总览 ===")
    print("游戏: %d 事件, 战斗时长 %.2fs" % (len(game), max(e["t"] for e in game)))
    print("模拟: %d 事件, 战斗时长 %.2fs" % (len(sim), max(e["t"] for e in sim)))
    r = eng.result_json()
    print("模拟结果:", json.dumps({k: r[k] for k in r if k in ("winner", "reason", "player_health", "opponent_health")}, ensure_ascii=False))

    print("\n=== t=0 开场（确定性）===")
    go, so = opening(game), opening(sim)
    from collections import Counter
    cg, cs = Counter(go), Counter(so)
    for k in sorted(set(cg) | set(cs)):
        a, b = cg.get(k, 0), cs.get(k, 0)
        mark = "  " if a == b else "❌"
        if a != b or True:
            print("%s G%2d S%2d  %s %s %s %s" % (mark, a, b, k[0], k[1], k[2], k[3]))

    print("\n=== 首次触发时间差异（同物品同 kind）===")
    ftg, fts = first_triggers(game), first_triggers(sim)
    rows = []
    for k in set(ftg) & set(fts):
        rows.append((abs(ftg[k] - fts[k]), k, ftg[k], fts[k]))
    rows.sort(reverse=True)
    for d, k, gt, st in rows[:40]:
        print("%.2fs vs %.2fs (Δ%.2f)  %s %s %s" % (gt, st, d, k[0], k[1], k[2]))

    print("\n=== 聚合差异（触发次数/数值合计, 只列有出入项）===")
    ag, as_ = agg(game), agg(sim)
    keys = sorted(set(ag) | set(as_), key=lambda k: (k[0], k[1], k[2]))
    for k in keys:
        gc, gs = ag.get(k, [0, 0.0]), as_.get(k, [0, 0.0])
        if gc[0] == gs[0] and abs(gc[1] - gs[1]) < 1e-6:
            continue
        print("❌ %-2s %-14s %-14s  游戏n=%3d sum=%8.1f | 模拟n=%3d sum=%8.1f"
              % (k[0], k[1] or "-", k[2], gc[0], gc[1], gs[0], gs[1]))


if __name__ == "__main__":
    main()
