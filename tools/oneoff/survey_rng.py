# -*- coding: utf-8 -*-
"""统计 RNG 使用面，为 Python 垫片定 API。"""
import io
import os
import re
import sys
from collections import Counter

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

STR_RE = re.compile(r'"(?:[^"\\]|\\.)*"')
CMT_RE = re.compile(r"#.*$")


def sc(s):
    return CMT_RE.sub("", STR_RE.sub('""', s))


RNGVARS = ("rng", "_rng", "accuracyRng", "critRng", "critResistanceRng",
           "stunResistanceRng", "damageRangeRng", "chanceRng", "BalancedRng",
           "BalancedRange", "combatRng")
pat = Counter()
ctx = {}
for d in ("gd_core", "gd_core_items"):
    for root, _s, names in os.walk(d):
        for n in names:
            if not n.endswith(".gd"):
                continue
            p = os.path.join(root, n)
            for i, ln in enumerate(io.open(p, encoding="utf-8",
                                           errors="replace"), 1):
                s = sc(ln)
                for m in re.finditer(r"\b(?:%s)\.([A-Za-z_]\w*)" % "|".join(RNGVARS), s):
                    pat[m.group(1)] += 1
                    ctx.setdefault(m.group(1), []).append(
                        "%s:%d %s" % (p, i, s.strip()[:70]))
print("=== RNG 对象上的方法/属性调用 ===")
for k, v in pat.most_common(40):
    print("  %-24s %5d   e.g. %s" % (k, v, ctx[k][0][:80]))

print("\n=== 全局 RNG 内建（randf/randi/randf_range/randi_range/seed/randomize） ===")
g = Counter()
for d in ("gd_core", "gd_core_items"):
    for root, _s, names in os.walk(d):
        for n in names:
            if not n.endswith(".gd"):
                continue
            for ln in io.open(os.path.join(root, n), encoding="utf-8",
                              errors="replace"):
                s = sc(ln)
                for m in re.finditer(r"(?<![\w.])(randf|randi|randf_range|"
                                     r"randi_range|randomize|randfn|seed|"
                                     r"is_instance_valid)\s*\(", s):
                    g[m.group(1)] += 1
print("  ", dict(g))

print("\n=== .shuffle( 的接收者 ===")
sh = Counter()
for d in ("gd_core", "gd_core_items"):
    for root, _s, names in os.walk(d):
        for n in names:
            if not n.endswith(".gd"):
                continue
            p = os.path.join(root, n)
            for i, ln in enumerate(io.open(p, encoding="utf-8",
                                           errors="replace"), 1):
                s = sc(ln)
                for m in re.finditer(r"([A-Za-z_][\w\.\[\]]*)\.shuffle\s*\(", s):
                    sh[m.group(1)] += 1
                    print("  %-46s %s:%d" % (m.group(1), p, i))
for k, v in sh.most_common():
    print("  %-46s %d" % (k, v))
