# -*- coding: utf-8 -*-
"""一次性冒烟：用 GDCoreEngine 跑一局并打印摘要。"""
import io
import os
import sys
import traceback

ROOT = r"D:\文件资料\学习\自动背包AI"
sys.path.insert(0, ROOT)

from simulator.lineup import load_lineup                      # noqa: E402
from simulator.gd_core_engine import GDCoreEngine             # noqa: E402

a = load_lineup(os.path.join(ROOT, "lineups", "lineup_armor_wall.json"))
b = load_lineup(os.path.join(ROOT, "lineups", "lineup_dagger_swarm.json"))

try:
    eng = GDCoreEngine(a, b, {}, {}, seed=20260923 + 101, max_time=180.0)
    print("assemble ok: player %d 件 / opponent %d 件"
          % (len(eng.player_items), len(eng.opponent_items)))
    print("  player items:", [i.key for i in eng.player_items])
    print("  opponent items:", [i.key for i in eng.opponent_items])
    eng.run()
    s = eng.summary()
    print("winner=%s reason=%s time=%.2f fatigue=%d"
          % (s["winner"], s["reason"], s["time"], s["fatigue_counter"]))
    print("  P hp=%s/%s  buffs=%s" % (s["player"]["hp"], s["player"]["max_hp"], s["player"]["buffs"]))
    print("  O hp=%s/%s  buffs=%s" % (s["opponent"]["hp"], s["opponent"]["max_hp"], s["opponent"]["buffs"]))
    print("  P stats:", s["player"]["stats"])
    print("  O stats:", s["opponent"]["stats"])
    print("  totals:", eng.totals())
    print("  events:", len(eng.log.events))
    txt = eng.log.to_text("zh")
    lines = txt.split("\n")
    print("--- 日志前 12 行 / 共 %d 行 ---" % len(lines))
    for ln in lines[:12]:
        print("   ", ln)
    print("--- 日志后 4 行 ---")
    for ln in lines[-4:]:
        print("   ", ln)
    import json
    print("  result_json ok:", json.dumps(eng.result_json(), ensure_ascii=False)[:160])
    print("SMOKE: PASS")
except Exception:
    traceback.print_exc()
    print("SMOKE: FAIL")
    sys.exit(1)
