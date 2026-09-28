# -*- coding: utf-8 -*-
"""临时侦察：只跑装配，快速暴露运行期错误。"""
import sys, os, traceback
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

from tools.run_gd_py import (new_battle, run_battle, outcome, live_lineups,
                             FIXTURE_ITEMS, FIXTURE_LINEUPS, BASE_SEED, _SCRIPT_FAIL)

names = live_lineups()
print("阵容:", names)

w = new_battle(BASE_SEED, names[0], names[1])
print("装配 OK: p=%d o=%d" % (len(w["p_items"]), len(w["o_items"])))
for it in w["p_items"]:
    print("   ", it.getName(), "placed=", it.placed, "owner=", it.ownerType,
          "cells=", len(it.occupiedCells), "gems=", len(it.gems),
          "descr-id=", id(it.descriptor))

run_battle(w["ctx"], w["combat"])
print("战斗 OK:", outcome(w))
print("脚本未转译:", _SCRIPT_FAIL)
