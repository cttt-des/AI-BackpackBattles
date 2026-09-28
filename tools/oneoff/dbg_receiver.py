# -*- coding: utf-8 -*-
"""定位 receiver_start 对 `a[color].keys()` 的解析。"""
import sys
import os

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)

import tools.gd_to_py as G

line = "\tcachedAffectedItems[color] = currentAffectedItems[color].keys()"
m = G.PY  # noqa
import re
m = re.compile(r"\.([A-Za-z_]\w*)\s*\(").search(line, 0)
print("第一个匹配:", m.group(1), "at", m.start(), "end", m.end())
rs = G.receiver_start(line, m.start())
print("receiver_start ->", rs, repr(line[rs:m.start()]))
print("chain_start 试算:")
print("  last =", m.start() - 1, "->", G.chain_start(line, m.start() - 1))
print("字面:", repr(line))

# 逐字符回溯
s = line
i = m.start() - 1
print("起点字符:", repr(s[i]))
j = G.find_matching_back(s, i, "]", "[")
print("find_matching_back ->", j, repr(s[j] if j >= 0 else None))
i2 = j - 1
print("j-1 =", i2, repr(s[i2]))
