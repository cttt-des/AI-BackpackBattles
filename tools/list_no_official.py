# -*- coding: utf-8 -*-
"""list_no_official.py — 列出 events.py TEMPLATES 中无 Interface.csv 官方译文的项。"""
import re
import csv

src = open('simulator/events.py', encoding='utf-8').read()
m0 = re.search(r'TEMPLATES = \{', src)
m1 = re.search(r'\n\}\n', src[m0.end():])
block = src[m0.end():m0.end()+m1.start()+1]
pat = re.compile(r'("[A-Za-z_0-9]+")\s*:\s*\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*\)')
ms = pat.findall(block)

with open('extracted/Sheets/CSV/Interface.csv', encoding='utf-8-sig') as f:
    rows = list(csv.reader(f))
hdr = rows[0]
i_en, i_zh = hdr.index('en'), hdr.index('zh_Hans_CN')
pairs = {}
for r in rows[1:]:
    if len(r) > i_zh and r[i_en] and r[i_zh]:
        pairs[r[i_en].strip()] = r[i_zh].strip()

no_official = [(k.strip('"'), en) for k, en, _ in ms if en not in pairs]
print(f"无官方译文 {len(no_official)} 项 / 共 {len(ms)} 项:")
for k, en in no_official:
    print(f"  {k}: {en}")
