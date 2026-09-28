# -*- coding: utf-8 -*-
"""逐件对比：run_gd_py 装配 vs GDCoreEngine 装配（同阵容、同种子）。"""
import os
import sys

ROOT = r"D:\文件资料\学习\自动背包AI"
sys.path.insert(0, ROOT)

from simulator import gd_core_engine as GE                # noqa: E402
from simulator.lineup import load_lineup                  # noqa: E402
from tools.gen_lineup_fixture import build as build_fixture  # noqa: E402
from tools import run_gd_py as GP                         # noqa: E402

FIX_ITEMS, FIX_LINEUPS = build_fixture()

A, B = "lineup_cursed_reaper", "lineup_armor_wall"
SEED = 20260923 + 101 * 1 + 0

# ── 参考路径（run_gd_py / LineupBattle.gd 口径） ──
w = GP.new_battle(SEED, A, B)
ref = {}
for it in w["p_items"]:
    ref[it.getName() + "#%d" % id(it)] = it


def dump(it, tag):
    d = it.descriptor
    return {
        "cls": type(it).__name__,
        "name": it.getName(),
        "occupied": sorted((int(c.x), int(c.y)) for c in it.occupiedCells),
        "collision": [(int(c.x), int(c.y)) for c in it.collisionCells],
        "affected": {k: sorted((int(c.x), int(c.y)) for c in v)
                     for k, v in it.affectedTileCells.items()},
        "ownerType": int(it.ownerType),
        "gems": len(it.gems),
        "placed": bool(it.placed),
        "descr": {
            "id": d.identifier, "minDam": d.minDam, "maxDam": d.maxDam,
            "cd": d.cd, "extraCds": list(d.extraCds), "accuracy": d.accuracy,
            "staminaCost": d.staminaCost, "block": d.block, "price": d.price,
            "rarity": int(d.rarity), "classes": int(d.classes),
            "canActivate": bool(d.canActivate), "chance": d.chance,
            "chance2": d.chance2, "types": list(d.types), "tags": int(d.tags),
            "params": list(d.params),
            "namedParams": dict(d.namedParams),
        },
    }


print("=== 参考：run_gd_py.new_battle(%d, %s, %s) ===" % (SEED, A, B))
print("  P items:", [it.getName() for it in w["p_items"]])
print("  O items:", [it.getName() for it in w["o_items"]])
print("  P char: class=%s hp=%s maxhp=%s sta=%s regen=%s"
      % (w["p"].characterClass, w["p"].curHealth, w["p"].maxHealth,
         w["p"].maxStamina, w["p"].staminaRegen))
print("  cur_round=%s  max_time=%s" % (w["ctx"].cur_round, w["combat"].max_time))

lu = {A: load_lineup(os.path.join(ROOT, "lineups", A + ".json")),
      B: load_lineup(os.path.join(ROOT, "lineups", B + ".json"))}
eng = GE.GDCoreEngine(lu[A], lu[B], {}, {}, seed=SEED, max_time=180.0)
print("=== 被测：GDCoreEngine(%s, %s, seed=%d) ===" % (A, B, SEED))
print("  P items:", [i.key for i in eng.player_items])
print("  O items:", [i.key for i in eng.opponent_items])
print("  P char: class=%s hp=%s maxhp=%s sta=%s regen=%s"
      % (eng._p.characterClass, eng._p.curHealth, eng._p.maxHealth,
         eng._p.maxStamina, eng._p.staminaRegen))
print("  cur_round=%s  max_time=%s" % (eng.ctx.cur_round, eng.combat.max_time))

print()
print("=== 逐件对比（玩家侧） ===")
for i in range(max(len(w["p_items"]), len(eng._p_items))):
    a = w["p_items"][i] if i < len(w["p_items"]) else None
    b = eng._p_items[i] if i < len(eng._p_items) else None
    if a is None or b is None:
        print("  第 %d 件：一侧缺失 ref=%s cur=%s"
              % (i, a and a.getName(), b and b.getName()))
        continue
    da, db = dump(a, "ref"), dump(b, "cur")
    diffs = [k for k in da if da[k] != db[k]]
    print("  [%d] %-16s %s" % (i, da["name"], "OK" if not diffs else "DIFF " + str(diffs)))
    for k in diffs:
        print("        ref %s = %s" % (k, da[k]))
        print("        cur %s = %s" % (k, db[k]))
