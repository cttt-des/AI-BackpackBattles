# -*- coding: utf-8 -*-
"""侦察：gd 源里「类体成员名 / 方法名」与 NEVER_SELF 冲突的有哪些。"""
import io
import os
import re
import sys
from collections import Counter

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
import tools.gd_to_py as G

DECL = G.DECL_RE
FUNC = G.FUNC_RE
NEVER = {n for n in G.NEVER_SELF if n.isidentifier()}

members = Counter()
methods = Counter()
for base in ("gd_core", "gd_core_items"):
    for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
        for f in fn:
            if not f.endswith(".gd"):
                continue
            p = os.path.join(dp, f)
            rel = os.path.relpath(p, ROOT).replace("\\", "/")
            for l in io.open(p, encoding="utf-8").read().split("\n"):
                code = l.split("#")[0]
                m = DECL.match(code)
                if m and m.group(3) in NEVER:
                    members[(m.group(3), rel)] += 1
                m = FUNC.match(code)
                if m and m.group(2) in NEVER:
                    methods[(m.group(2), rel)] += 1

print("== 成员名撞 NEVER_SELF ==")
for (n, rel), c in sorted(members.items()):
    print("   %-14s %s" % (n, rel))
print("== 方法名撞 NEVER_SELF ==")
for (n, rel), c in sorted(methods.items()):
    print("   %-14s %s" % (n, rel))
print("合计 成员 %d / 方法 %d" % (len(members), len(methods)))
