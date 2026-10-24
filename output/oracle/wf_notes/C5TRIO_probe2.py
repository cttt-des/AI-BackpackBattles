# -*- coding: utf-8 -*-
"""C5TRIO 取证：GP 影响格全量对撞——布局真值 vs 引擎缓存值（只读）。"""
import io, json, sys

ROOT = r"D:/文件资料/学习/自动背包AI"
sys.path.insert(0, ROOT)
from simulator.data import load_items, load_characters
from simulator.lineup import load_lineup
from simulator.gd_core_engine import GDCoreEngine

item_db = load_items()
character_db = load_characters()

CASE = sys.argv[1] if len(sys.argv) > 1 else "run608_r18"
seed = json.load(io.open(ROOT + "/output/oracle/fights/%s/lineups.json" % CASE, encoding="utf-8"))["seed"]
player = load_lineup(ROOT + "/output/oracle/align/lineups/oracle_%s_player.json" % CASE)
opponent = load_lineup(ROOT + "/output/oracle/align/lineups/oracle_%s_opponent.json" % CASE)
eng = GDCoreEngine(player, opponent, item_db, character_db, seed=seed, max_time=90.0,
                    below_master=True, probe_bases=(), reseed_after_player_character=True,
                    post_seed_draws=0, rng_state=None, label_rng_enabled=True)

items_by_key = item_db  # simulator.data load_items 返回
gj = items_by_key["items"]["Girl Power"]["grid"] if isinstance(items_by_key, dict) and "items" in items_by_key else None

for label, lst, lu_key in (("player", eng._p_items, player), ("opponent", eng._o_items, opponent)):
    gp = next(it for it in lst if str(it.name) == "Girl Power")
    idx_gp = lst.index(gp)
    # 引擎口中的影响格（inventory 坐标）
    acells = gp.getAffectedCellsInInventory()
    acs = set((int(c.x), int(c.y)) for c in acells)
    print("=" * 90)
    print(case_label := CASE, label, "GP idx=%d" % idx_gp, "affected_cells(%d):" % len(acs), sorted(acs))
    # 布局真值：每件物品的 occupiedCells ∩ 影响格
    print("  [布局真值] 与影响格相交的物品：")
    for i, it in enumerate(lst):
        occ = set((int(c.x), int(c.y)) for c in it.occupiedCells)
        inter = occ & acs
        if inter:
            cls = it.descriptor.classes
            print("    idx=%-3d %-26s classes=%-4s occ∩aff=%d %s" %
                  (i, str(it.name), cls, len(inter), "CLASS" if cls not in (0,) else ""))
    # 引擎的 getAffectedItems 答案
    got = [(lst.index(x), str(x.name)) for x in gp.getAffectedItems()]
    print("  [引擎 getAffectedItems]:", got)
