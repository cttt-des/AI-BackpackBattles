# -*- coding: utf-8 -*-
"""survey_truth.py — 盘点 11 组真值（5 文件/组）"""
import glob
import json
import os

ROOT = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    "dist", "output", "combat_logs")

for grp in sorted(glob.glob(os.path.join(ROOT, "*"))):
    if not os.path.isdir(grp):
        continue
    base = os.path.join(grp, os.path.basename(grp))
    try:
        lu = json.load(open(base + ".Player.json", encoding="utf-8"))
        lo = json.load(open(base + ".Opponent.json", encoding="utf-8"))
        lg = json.load(open(base + ".json", encoding="utf-8"))
        evs = lg.get("events", [])
        tend = max((e.get("t", 0) for e in evs), default=0)
        win = any(e.get("type_name") == "Win" for e in evs)
        loss = any(e.get("type_name") == "Loss" for e in evs)
        print("%-44s P:%2d O:%2d 事件:%4d 时长:%5.1fs %s" % (
            os.path.basename(grp), len(lu["items"]), len(lo["items"]),
            len(evs), tend, "Win" if win else ("Loss" if loss else "?")))
    except Exception as e:
        print(os.path.basename(grp), "ERR", e)
