# -*- coding: utf-8 -*-
"""侦察：gd 源里 str( / String( / Dictionary( 的用法（含参数个数）。"""
import io, os, re
from collections import Counter
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def split_top(s):
    depth = 0; cur = []; out = []
    inq = None
    for ch in s:
        if inq:
            cur.append(ch)
            if ch == inq:
                inq = None
            continue
        if ch in "\"'":
            inq = ch; cur.append(ch); continue
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur)); cur = []
        else:
            cur.append(ch)
    out.append("".join(cur))
    return [x for x in out if x.strip()]

pats = {
    "str": re.compile(r"(?<![\w.\"'])str\s*\("),
    "String": re.compile(r"(?<![\w.\"'])String\s*\("),
    "Dictionary": re.compile(r"(?<![\w.\"'])Dictionary\s*\("),
    "Array": re.compile(r"(?<![\w.\"'])Array\s*\("),
    "PoolStringArray": re.compile(r"(?<![\w.\"'])PoolStringArray\s*\("),
}
stats = {k: Counter() for k in pats}
samples = {}
for base in ("gd_core", "gd_core_items"):
    for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
        for f in fn:
            if not f.endswith(".gd"):
                continue
            p = os.path.join(dp, f)
            rel = os.path.relpath(p, ROOT).replace("\\", "/")
            for i, l in enumerate(io.open(p, encoding="utf-8").read().split("\n")):
                s = l.strip()
                if s.startswith("#"):
                    continue
                for k, pat in pats.items():
                    for m in pat.finditer(l):
                        # 括号配对取参数
                        j = l.index("(", m.end() - 1)
                        depth = 0; k2 = j
                        while k2 < len(l):
                            if l[k2] == "(":
                                depth += 1
                            elif l[k2] == ")":
                                depth -= 1
                                if depth == 0:
                                    break
                            k2 += 1
                        args = split_top(l[j + 1:k2])
                        stats[k][len(args)] += 1
                        if k in ("str", "String") and (len(args) != 1 or k == "String"):
                            samples.setdefault(k, []).append(
                                "%s:%d  argc=%d  %s" % (rel, i + 1, len(args), s[:100]))
for k in pats:
    print("%-18s %s" % (k, dict(stats[k])))
print()
for k, v in samples.items():
    print("── %s 非单参样例 ──" % k)
    for s in v[:25]:
        print("   " + s)
