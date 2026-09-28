# -*- coding: utf-8 -*-
"""扫描 match 语句的全部形态，为转写规则定依据。

GDScript match 的 case 可以写成：
    常量:            ItemStat.MaxDamage:
    多值:            A, B:
    default:         _:
    类型:            int:
    绑定:            var x:
    数组模式:        [1, 2, var rest]:
    字典模式:        {"k": var v}:
规则不同 → 必须逐类看清再下手，不能只按「A:」一种写。
"""
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


def count_tabs(s):
    return len(s) - len(s.lstrip("\t"))


files = []
for d in ("gd_core", "gd_core_items"):
    for root, _s, names in os.walk(d):
        for n in sorted(names):
            if n.endswith(".gd"):
                files.append(os.path.join(root, n))

tot = 0
shapes = Counter()
samples = {}
for p in files:
    lines = io.open(p, encoding="utf-8", errors="replace").read().split("\n")
    i = 0
    while i < len(lines):
        code = sc(lines[i])
        m = re.match(r"^(\t*)match\s+(.+?)\s*:\s*$", code)
        if not m:
            i += 1
            continue
        tot += 1
        ind = len(m.group(1))
        subj = m.group(2)
        print("── %s:%d  match %s" % (p, i + 1, subj[:60]))
        j = i + 1
        while j < len(lines):
            c = sc(lines[j])
            if c.strip() and count_tabs(c) <= ind:
                break
            t = count_tabs(c)
            if c.strip() and t == ind + 1:
                # 这是一条 case 行
                body_ind = ind + 2
                kind = "常量"
                if c.strip() == "_:" or c.strip().startswith("_:"):
                    kind = "default(_)"
                elif re.match(r"^\s*var\s+\w+\s*:", c):
                    kind = "绑定(var)"
                elif re.match(r"^\s*(int|float|String|bool|Array|Dictionary)\s*:", c):
                    kind = "类型"
                elif "," in c:
                    kind = "多值"
                elif c.strip().startswith("["):
                    kind = "数组模式"
                elif c.strip().startswith("{"):
                    kind = "字典模式"
                elif ":" in c and not re.search(r"[=<>!]=|[<>+*/%-]", c):
                    kind = "表达式"
                shapes[kind] += 1
                samples.setdefault(kind, []).append(
                    "%s:%d %s" % (p, j + 1, c.strip()[:70]))
            j += 1
        i = j

print("\n══ match 总数 %d ══" % tot)
for k, v in shapes.most_common():
    print("  %-10s %3d   e.g. %s" % (k, v, samples[k][0] if samples.get(k) else ""))
