# -*- coding: utf-8 -*-
"""恢复审计：扫 cli/artifacts 全部 Edit/Write 工件，统计仓库内事件覆盖度。"""
import json
import os
import glob
import collections

ROOT = r"C:/Users/Windows/.zcode/cli/artifacts"
REPO = "D:\\文件资料\\学习\\自动背包AI"

sess_stats = collections.Counter()
tmin = {}
path_latest = {}

for d in sorted(os.listdir(ROOT)):
    dp = os.path.join(ROOT, d)
    if not os.path.isdir(dp):
        continue
    cnt = 0
    tminx = None
    for f in glob.glob(os.path.join(dp, "*.json")):
        try:
            j = json.load(open(f, encoding="utf-8"))
        except Exception:
            continue
        for fe in j.get("files", []) or []:
            p = fe.get("path", "")
            if p.startswith(REPO):
                cnt += 1
                t = j.get("createdAt")
                tminx = t if tminx is None else min(tminx, t)
                key = p[len(REPO) + 1:].replace("\\", "/")
                if key not in path_latest or t > path_latest[key][0]:
                    path_latest[key] = (t, d, j.get("toolName"))
    if cnt:
        sess_stats[d] = cnt
        tmin[d] = tminx

print("=== 各会话仓库内事件数（前14）===")
for s, c in sess_stats.most_common(14):
    ts = tmin[s] or "?"
    print("%5d  %s  %s" % (c, ts[:10], s[:44]))
print("总独立文件数:", len(path_latest))
print("=== np时代已知文件抽查 ===")
checks = [
    "gd_core_test/OracleAlignBattle.gd",
    "gd_core/CoreBuff.gd",
    "gd_core/CoreItem.gd",
    "gd_core/CoreRng.gd",
    "gd_core/CoreEventBus.gd",
    "gd_core_items/RubyChonk.gd",
    "gd_core_items/Exclusive/AmuletOfAgility.gd",
    "assets/battle_items.json",
    "tools/verify_oracle.py",
    "simulator/gd_core_engine.py",
    "output/alignment_fix_log.md",
    "output/oracle/wf_notes/np8_bl.md",
]
for k in checks:
    v = path_latest.get(k)
    if v:
        print("OK  ", k, "->", v[0][:16], v[2])
    else:
        print("MISS", k)
