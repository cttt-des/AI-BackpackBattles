# -*- coding: utf-8 -*-
"""侦察：GDScript 内建类的静态成员访问（Color.white / Vector2.ZERO / OS.x …）。"""
import io, os, re
from collections import Counter
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
pat = re.compile(r"(?<![\w.\"'])(Color|Vector2|Vector3|OS|Math|Engine|PI|INF|NAN|TAU)\s*\.\s*([A-Za-z_]\w*)")
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
                    cnt[(m.group(1), m.group(2))] += 1
                    samples.setdefault((m.group(1), m.group(2)), []).append(
                        "%s:%d  %s" % (rel, i + 1, s[:90]))
for k, v in cnt.most_common():
    print("%-34s %4d   %s" % ("%s.%s" % k, v, samples[k][0][:70]))
