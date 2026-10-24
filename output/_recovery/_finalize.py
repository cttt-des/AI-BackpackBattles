# -*- coding: utf-8 -*-
"""终批：清错位、验桩、classes 不动点自实现、镜像再生。"""
import json
import os
import shutil
import subprocess

REPO = r"D:\文件资料\学习\自动背包AI"
os.chdir(REPO)

# 1) 错位件清理（output/oracle/* 被误映射到 oracle/ 下的重复件）
for junk in ("oracle/wf_notes", "oracle/probe", "oracle/offpeak_handoff.md"):
    if os.path.exists(junk):
        shutil.rmtree(junk, ignore_errors=True) if os.path.isdir(junk) else os.remove(junk)
        print("清错位:", junk)

# 2) 桩残留验证
of = open("oracle/oracle_fight.gd", encoding="utf-8", errors="replace").read()
print("oracle_fight: ORACLE_NOLIMIT=", "ORACLE_NOLIMIT" in of,
      "| TSNAP=", "ORACLE_TIMER_SNAP" in of,
      "| determinism(events_first)=", "events_first" in of,
      "| 事件闸25000=", "25000" in of)
buf = open("oracle/Core/Buff.gd", encoding="utf-8", errors="replace").read()
print("Buff.gd: np20钩子标记=", "np20" in buf or "BATCHD" in buf)

# 3) classes 不动点（ItemBook.calcClassAvailability 语义自实现）
CSV = None
for cand in ("decompiled_full/Core/ItemBook.csv",):
    pass
import csv as _csv
import glob as _glob
# gate 映射来自解包 CSV（enrich_classes.py 原逻辑：ItemData 主表）
gate = {}
for path in _glob.glob("decompiled_full/**/*.csv", recursive=True):
    try:
        with open(path, encoding="utf-8-sig") as f:
            for r in _csv.DictReader(f):
                g = (r.get("gateItem") or "").strip()
                if g:
                    gate[r["name"]] = g
    except Exception:
        continue
print("gate 映射件数:", len(gate))

bj = "assets/battle_items.json"
d = json.load(open(bj, encoding="utf-8"))
items = d["items"]
changed = True
rounds = 0
while changed and rounds < 16:
    changed = False
    rounds += 1
    for k, v in items.items():
        cur = int(v.get("classes") or 0)
        new = cur
        g = gate.get(k)
        if cur == 0 and g and g in items:
            new = int(items[g].get("classes") or 0)
        for rec in v.get("originating_recipes") or []:
            rc = 127
            for ing in ([rec["b"]] + list(rec["i"])):
                if ing in items:
                    rc &= int(items[ing].get("classes") or 0)
            new |= rc
        if new != cur:
            v["classes"] = new
            changed = True
sd = items.get("Spectral Dagger", {})
if not int(sd.get("classes") or 0):
    sd["classes"] = 127
json.dump(d, open(bj, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
nonzero = sum(1 for v in items.values() if int(v.get("classes") or 0))
print("classes 不动点完成：非零件数 =", nonzero, "| 轮数 =", rounds)

# 4) 镜像再生
for cmd in (["python", "-X", "utf8", "tools/gd_to_py.py"],
            ["python", "-X", "utf8", "tools/gen_gd_core_data.py"]):
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO)
    tail = (r.stdout or r.stderr).strip().splitlines()[-1:] 
    print(cmd[-1], "rc=", r.returncode, tail)
