# -*- coding: utf-8 -*-
"""check_templates.py — 对比 events.py TEMPLATES 区块的键与正则匹配覆盖率。"""
import re

src = open('simulator/events.py', encoding='utf-8').read()
m0 = re.search(r'TEMPLATES = \{', src)
m1 = re.search(r'\n\}\n', src[m0.end():])
block = src[m0.end():m0.end()+m1.start()+1]

pat = re.compile(r'("[A-Za-z_0-9]+")\s*:\s*\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"\s*\)')
matches = pat.findall(block)
keys_in_block = re.findall(r'"([A-Za-z_0-9]+)"\s*:', block)
matched_keys = {k.strip('"') for k, _, _ in matches}
print("keys in block:", len(keys_in_block), "| matched:", len(matches))
unmatched = [k for k in keys_in_block if k not in matched_keys]
print("unmatched:", unmatched)
# 打印未匹配项原文
for k in unmatched:
    i = block.find(f'"{k}"')
    print("---", k, "---")
    print(block[i:i+150])
