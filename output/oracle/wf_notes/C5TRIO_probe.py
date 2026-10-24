# -*- coding: utf-8 -*-
"""C5TRIO 取证：装配 py 引擎（不 eng.run()），直读 GirlPower 实例计数（只读对拍）。"""
import io, json, sys

ROOT = r"D:/文件资料/学习/自动背包AI"
sys.path.insert(0, ROOT)

from simulator.data import load_items, load_characters
from simulator.lineup import load_lineup
from simulator.gd_core_engine import GDCoreEngine

item_db = load_items()
character_db = load_characters()

CASE = sys.argv[1] if len(sys.argv) > 1 else "run608_r18"
player = load_lineup(ROOT + "/output/oracle/align/lineups/oracle_%s_player.json" % CASE)
opponent = load_lineup(ROOT + "/output/oracle/align/lineups/oracle_%s_opponent.json" % CASE)

eng = GDCoreEngine(player, opponent, item_db, character_db,
                   seed=json.load(io.open(ROOT + "/output/oracle/fights/%s/lineups.json" % CASE, encoding="utf-8"))["seed"],
                   max_time=90.0,
                   below_master=True,
                   probe_bases=(),
                   reseed_after_player_character=True,
                   post_seed_draws=0,
                   rng_state=None,
                   label_rng_enabled=True)

k = eng._K
ctx = eng.ctx
print("ctx ok:", type(ctx).__name__)

for label, lst in (("player", eng._p_items), ("opponent", eng._o_items)):
    print("--- side:", label, "n=%d" % len(lst))
    found = 0
    for it in lst:
        nm = str(it.name)
        if nm == "Girl Power":
            found += 1
            n_aff = it.getNumAffectedItems()
            n_dis = it.getNumDistinctAffectedItems()
            names = sorted(set(str(x.name) for x in it.getAffectedItems()))
            print("  GP #%d: getNumAffectedItems=%d getNumDistinctAffectedItems=%d speedScale=%s" %
                  (found, n_aff, n_dis, it.speed()))
            print("    affected keys(%d): %s" % (len(names), names))
            cls_info = [(str(x.name), x.descriptor.classes) for x in it.getAffectedItems()]
            print("    classes:", cls_info)
    if not found:
        print("  (no Girl Power on this side)")
