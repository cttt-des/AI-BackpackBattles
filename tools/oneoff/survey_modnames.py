# -*- coding: utf-8 -*-
"""找出文件名/路径里对 Python 模块名非法的字符，并检查 sanitize 后是否撞名。"""
import os
import re
import sys
from collections import defaultdict

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

rows = []
for d in ("gd_core", "gd_core_items"):
    for root, _s, names in os.walk(os.path.join(ROOT, d)):
        for n in names:
            if not n.endswith(".gd"):
                continue
            rel = os.path.relpath(os.path.join(root, n), ROOT).replace(os.sep, "/")
            rows.append(rel)

ILL = re.compile(r"[^A-Za-z0-9_]")


def sanitize(rel):
    parts = rel[:-3].split("/")
    return ".".join(ILL.sub("_", p) for p in parts)


bad = [(r, sanitize(r)) for r in rows if ILL.search(r[:-3])]
print("含非法字符的路径：%d / %d" % (len(bad), len(rows)))
for r, s in bad[:40]:
    print("  %-52s -> %s" % (r, s))

seen = defaultdict(list)
for r in rows:
    seen[sanitize(r)].append(r)
dup = {k: v for k, v in seen.items() if len(v) > 1}
print("\nsanitize 后撞名：%d 组" % len(dup))
for k, v in list(dup.items())[:20]:
    print("  %s <- %s" % (k, v))

# 非法字符种类
chars = defaultdict(int)
for r in rows:
    for m in ILL.finditer(r[:-3]):
        chars[m.group(0)] += 1
print("\n非法字符种类:", dict(chars))
