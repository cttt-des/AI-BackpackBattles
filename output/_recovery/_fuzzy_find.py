# -*- coding: utf-8 -*-
"""模糊搜 artifacts 中的 Amulet / battle_items 路径事件。"""
import json
import os
import glob
import collections

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
m = collections.defaultdict(list)

for d in sorted(os.listdir(ROOT)):
    dp = os.path.join(ROOT, d)
    if not os.path.isdir(dp):
        continue
    for f in glob.glob(os.path.join(dp, "*.json")):
        try:
            j = json.load(open(f, encoding="utf-8"))
        except Exception:
            continue
        for fe in j.get("files", []) or []:
            p = (fe.get("path") or "").replace("\\", "/").lower()
            if "amulet" in p or "battle_items" in p:
                m[p].append((j.get("createdAt"), d[:30], j.get("toolName")))

for p, evs in sorted(m.items()):
    evs.sort()
    print(p, "| 事件数", len(evs), "| 最早", evs[0][0][:16], "| 最晚", evs[-1][0][:16], evs[-1][2])
