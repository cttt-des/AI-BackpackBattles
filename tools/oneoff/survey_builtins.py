# -*- coding: utf-8 -*-
"""侦察：gd_core / gd_core_items 里用到的 GDScript 内建类型构造器调用。"""
import io, os, re, sys
from collections import Counter
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# GDScript 3.x 内建类型 + 常用构造
NAMES = """Array Dictionary String PoolStringArray PoolByteArray PoolIntArray
PoolRealArray PoolVector2Array PoolColorArray Vector2 Vector3 Vector2Array Color
Color8 Rect2 Rect3 AABB Plane Quat Basis Transform Transform2D NodePath
Object Reference Node Node2D Resource FuncRef WeakRef RID RandomNumberGenerator
Dictionary String bool int float str""".split()

pat = re.compile(r"(?<![\w.\"'$])(%s)\s*\(" % "|".join(sorted(set(NAMES), key=len, reverse=True)))
cnt = Counter()
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
                for m in pat.finditer(l):
                    cnt[m.group(1)] += 1
                    samples.setdefault(m.group(1), []).append("%s:%d  %s" % (rel, i + 1, s[:90]))
for k, v in cnt.most_common():
    print("%-22s %4d" % (k, v))
    for s in samples[k][:4]:
        print("        " + s)
