# -*- coding: utf-8 -*-
"""一次性探针：核查 battle_items.json 里 effects / on_start 的**烘焙数值**
是否因早先 params 紧凑存储而错位。

做法：对每件物品重新跑一遍 build_data 的 `_parse_effects` / `_parse_on_combat_start`
+ `_resolve_params`（这次用**列对齐**的 params），与库里现存值比对。
只有「引用过 p:N」的条目才可能受影响，故先筛出这类条目再比。
"""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, "tools"))

import item_sheet
import simulator.build_data as bd

rows = item_sheet.load_rows()
db = json.loads(open(os.path.join(ROOT, "assets", "battle_items.json"),
                     encoding="utf-8").read())["items"]


def refs(effects) -> bool:
    for e in effects or []:
        for v in e.values():
            if isinstance(v, str) and v.startswith("p:"):
                return True
    return False


bad_eff, bad_os, checked = [], [], 0
for key, entry in db.items():
    row = rows.get(key)
    if row is None:
        continue
    sp = bd._find_script(key)
    if not sp:
        continue
    with open(sp, encoding="utf-8", errors="replace") as fh:
        text = fh.read()

    params = item_sheet.aligned_params(row)
    named = item_sheet.named_params(row)

    eff_raw = bd._parse_effects(text)
    os_raw = bd._parse_on_combat_start(text)
    if not refs(eff_raw) and not refs(os_raw):
        continue
    checked += 1
    eff_new = bd._resolve_params({"params": params, "named_params": named}, eff_raw)
    os_new = bd._resolve_params({"params": params, "named_params": named}, os_raw)
    if eff_new != (entry.get("effects") or []):
        bad_eff.append((key, entry.get("effects"), eff_new))
    if (os_new or None) != entry.get("on_start"):
        bad_os.append((key, entry.get("on_start"), os_new or None))

print(f"引用过 p:N 的物品：{checked} 件")
print(f"  effects 与列对齐后重算不一致：{len(bad_eff)}")
for k, a, b in bad_eff[:12]:
    print(f"    {k:22s} 库 {a}\n{'':26s} 算 {b}")
print(f"  on_start 不一致：{len(bad_os)}")
for k, a, b in bad_os[:12]:
    print(f"    {k:22s} 库 {a}\n{'':26s} 算 {b}")
