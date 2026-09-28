# -*- coding: utf-8 -*-
"""扫描 GDScript 里「合法但 Python 非法」的标识符用法，为转写器定规则。

关注：
  A. Python 关键字被当作 var 名 / 参数名 / for 变量 / 函数名
  B. export / onready / setget 等声明修饰符的形态分布
  C. 缩进非单调（= 有未识别的语法块，例如 match）
  D. 其它未覆盖的 GDScript 语法糖
"""
import io
import os
import re
import sys
from collections import Counter, defaultdict

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

STR_RE = re.compile(r'"(?:[^"\\]|\\.)*"')
CMT_RE = re.compile(r"#.*$")

# Python 3 关键字
PY_KW = set("""False None True and as assert async await break class continue def
del elif else except finally for from global if import in is lambda nonlocal not
or pass raise return try while with yield""".split())

# GDScript 3.x 关键字（不可作标识符）
GD_KW = set("""if elif else for while break continue pass return match case func
static class class_name extends const enum var onready export setget signal tool
breakpoint preload yield assert void true false null self and or not in is as
remote master puppet sync""".split())

CAND = PY_KW - GD_KW          # 可作为 GDScript 标识符、但是 Python 关键字


def sc(s):
    return CMT_RE.sub("", STR_RE.sub('""', s))


files = []
for d in ("gd_core", "gd_core_items"):
    for root, _s, names in os.walk(d):
        for n in sorted(names):
            if n.endswith(".gd"):
                p = os.path.join(root, n)
                files.append(p)

print("候选关键字（GDScript 合法 / Python 关键字）: %s\n" % sorted(CAND))

hits = defaultdict(list)
decl_hits = defaultdict(list)
export_forms = Counter()
other = Counter()

VAR_RE = re.compile(r"^(\s*)(?:(onready|export(?:\s*\([^)]*\))?)\s+)*(var|const)\s+([A-Za-z_]\w*)")
ARG_RE = re.compile(r"func\s+\w+\s*\(([^)]*)\)")
FOR_RE = re.compile(r"^\s*for\s+([A-Za-z_]\w*)\s+in\b")

for p in files:
    lines = io.open(p, encoding="utf-8", errors="replace").read().split("\n")
    for i, raw in enumerate(lines, 1):
        s = sc(raw)
        if not s.strip():
            continue
        m = VAR_RE.match(s)
        if m:
            nm = m.group(4)
            mods = re.findall(r"onready|export(?:\s*\([^)]*\))?", s[:m.start(3)])
            for mod in mods:
                export_forms[mod.split("(")[0].strip() +
                             ("(...)" if "(" in mod else "")] += 1
            if nm in CAND:
                decl_hits["var:" + nm].append("%s:%d %s" % (p, i, s.strip()[:70]))
        m = ARG_RE.search(s)
        if m:
            for a in m.group(1).split(","):
                nm = a.split(":")[0].split("=")[0].strip()
                if nm in CAND:
                    decl_hits["arg:" + nm].append("%s:%d %s" % (p, i, s.strip()[:70]))
        m = FOR_RE.match(s)
        if m and m.group(1) in CAND:
            decl_hits["for:" + m.group(1)].append("%s:%d %s" % (p, i, s.strip()[:70]))
        for nm in CAND:
            if re.search(r"(?<![\w.])%s(?![\w])" % nm, s):
                hits[nm].append("%s:%d %s" % (p, i, s.strip()[:70]))
        for kw in ("setget", "export_group", "export_category", "tool",
                   "remote ", "master ", "puppet ", "sync ",
                   "yield", "preload", "assert("):
            if kw in s:
                other[kw] += 1

print("══ A1. 作为声明名（var / 参数 / for 变量）出现 ══")
if not decl_hits:
    print("   无")
for k in sorted(decl_hits):
    v = decl_hits[k]
    print("  %-16s %3d 处   e.g. %s" % (k, len(v), v[0]))

print("\n══ A2. 作为裸标识符整体出现（含上面那些的使用点）══")
for nm in sorted(hits):
    v = hits[nm]
    print("  %-12s %4d 处" % (nm, len(v)))
    for x in v[:3]:
        print("        " + x)

print("\n══ B. 声明修饰符形态 ══")
for k, v in export_forms.most_common():
    print("  %-20s %4d" % (k, v))

print("\n══ D. 其它语法糖 ══")
for k, v in other.most_common():
    print("  %-20s %4d" % (k, v))

print("\n══ C. 检查 `_` 与 `_` 已有后缀名撞车 ══")
for nm in sorted(CAND):
    n2 = nm + "_"
    cnt = 0
    for p in files:
        for raw in io.open(p, encoding="utf-8", errors="replace"):
            if re.search(r"(?<![\w.])%s(?![\w])" % n2, sc(raw)):
                cnt += 1
    if cnt:
        print("  %-12s → %-12s 已存在 %d 处" % (nm, n2, cnt))
