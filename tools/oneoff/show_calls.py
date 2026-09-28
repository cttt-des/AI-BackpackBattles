# -*- coding: utf-8 -*-
"""按名字打印 gd 源里的调用点（带接收者上下文）。"""
import io
import os
import re
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAMES = sys.argv[1].split(",")

for n in NAMES:
    print("── %s ──" % n)
    pat = re.compile(r"([\w.\)\]]+)\.%s\s*\(" % re.escape(n))
    found = 0
    for base in ("gd_core", "gd_core_items"):
        for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
            for f in fn:
                if not f.endswith(".gd"):
                    continue
                p = os.path.join(dp, f)
                rel = os.path.relpath(p, ROOT).replace("\\", "/")
                for i, l in enumerate(io.open(p, encoding="utf-8").read().split("\n")):
                    code = l.split("#")[0]
                    if f".{n}(" not in code:
                        continue
                    m = pat.search(code)
                    if not m:
                        continue
                    print("   %-58s %-40s :: %s" % (rel + ":" + str(i + 1), m.group(1), code.strip()[:80]))
                    found += 1
                    if found >= 8:
                        break
                if found >= 8:
                    break
            if found >= 8:
                break
