# -*- coding: utf-8 -*-
"""一次性探针：找 Inventory（原版 Core/Inventory.gd）里被物品脚本用到、
但内核 CoreGrid 未提供的 API —— 成类缺口，避免逐个报错逐个补。"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

FUNC_RE = re.compile(r"^func\s+([A-Za-z_]\w*)", re.M)

def funcs(path):
    with open(path, encoding="utf-8", errors="replace") as fh:
        return set(FUNC_RE.findall(fh.read()))

inv = funcs(os.path.join(ROOT, "decompiled_full", "Core", "Inventory.gd"))
grid = funcs(os.path.join(ROOT, "gd_core", "CoreGrid.gd"))
missing = sorted(inv - grid)
print(f"Inventory 方法 {len(inv)}，CoreGrid {len(grid)}，缺失 {len(missing)}")

# 物品脚本 / 内核里对 inventory 的调用点
calls = set()
for base in ("decompiled_full/Items", "gd_core_items"):
    for dirpath, _, names in os.walk(os.path.join(ROOT, base)):
        for n in names:
            if not n.endswith(".gd"):
                continue
            p = os.path.join(dirpath, n)
            with open(p, encoding="utf-8", errors="replace") as fh:
                for m in re.finditer(r"\binventory\.([A-Za-z_]\w*)", fh.read()):
                    calls.add(m.group(1))

print(f"\n物品/内核里出现过的 inventory.<X> 调用：{len(calls)} 个名字")
hit = sorted(c for c in calls if c in missing)
print(f"其中属于『Inventory 有、CoreGrid 无』的：{len(hit)}")
for c in hit:
    print("   ", c)
other = sorted(c for c in calls if c not in missing and c not in grid)
print(f"\n两边都没有的（需人工判断是否引擎基类方法）：{len(other)}")
for c in other:
    print("   ", c)
