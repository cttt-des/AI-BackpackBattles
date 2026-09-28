# -*- coding: utf-8 -*-
"""边界确认：嵌套类上下文 / OS 用法 / TriggerType / 成员名撞类名。"""
import io
import os
import re
import sys
from collections import Counter, defaultdict

sys.stdout.reconfigure(encoding="utf-8")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIRS = ("gd_core", "gd_core_items")
STR_RE = re.compile(r'"(?:[^"\\]|\\.)*"')
COMMENT_RE = re.compile(r"#.*$")


def sc(s):
    return COMMENT_RE.sub("", STR_RE.sub('""', s))


files = []
for d in SRC_DIRS:
    for root, _s, names in os.walk(os.path.join(ROOT, d)):
        for n in names:
            if n.endswith(".gd"):
                p = os.path.join(root, n)
                files.append((os.path.relpath(p, ROOT).replace(os.sep, "/"), p))
files.sort()
text = {r: io.open(p, encoding="utf-8", errors="replace").read() for r, p in files}

by_name, by_stem = {}, defaultdict(list)
for rel, _p in files:
    stem = os.path.splitext(os.path.basename(rel))[0]
    by_stem[stem].append(rel)
    m = re.search(r"^class_name\s+([A-Za-z_]\w*)", text[rel], re.M)
    if m:
        by_name[m.group(1)] = rel
all_names = set(by_name) | set(by_stem)

print("══ 1. 嵌套类定义位置 ══")
for rel, _p in files:
    for m in re.finditer(r"^(\t*)class\s+([A-Za-z_]\w*)\s*(?:extends\s+([^\s:]+))?\s*:",
                         text[rel], re.M):
        ind = len(m.group(1))
        # 找外层类名
        outer = "?"
        for mm in re.finditer(r"^(class\s+([A-Za-z_]\w*)\s+extends[^\n]*|class_name\s+([A-Za-z_]\w*))",
                              text[rel][:m.start()], re.M):
            outer = mm.group(2) or mm.group(3) or outer
        ln = text[rel][:m.start()].count("\n") + 1
        print("  %-34s :%-5d depth=%d  outer=%s  nested=%s  extends=%s"
              % (rel, ln, ind, outer, m.group(2), m.group(3)))

print("\n══ 2. 嵌套类被引用的上下文 ══")
targets = {"TemporaryStacks", "CoreItemSort", "CoreSignalConnection", "DictSorter"}
for rel, _p in files:
    lines = text[rel].split("\n")
    for i, raw in enumerate(lines):
        s = sc(raw)
        for t in targets:
            if re.search(r"(?<![\w.])%s\s*\.\s*new\s*\(" % t, s):
                # 往上找最近 func
                owner = "?"
                depth_static = False
                for j in range(i, -1, -1):
                    m = re.match(r"^(\s*)(static\s+)?func\s+([A-Za-z_]\w*)", lines[j])
                    if m:
                        owner = ("static " if m.group(2) else "") + m.group(3)
                        break
                print("  %-30s :%-5d  %s.new(   所在=%s" % (rel, i + 1, t, owner))

print("\n══ 3. OS.* / Engine.* / 其他全局对象用法 ══")
g = Counter()
for rel, _p in files:
    for raw in text[rel].split("\n"):
        s = sc(raw)
        for m in re.finditer(r"(?<![\w.])(OS|Engine|Input|ProjectSettings|Globals|"
                             r"TranslationServer|JSON|VisualServer|AudioServer|"
                             r"Performance|ResourceLoader|Time|Math)\s*\.\s*([A-Za-z_]\w*)", s):
            g["%s.%s" % (m.group(1), m.group(2))] += 1
for k, v in g.most_common(40):
    print("  %-40s %5d" % (k, v))

print("\n══ 4. TriggerType / 其他未登记标识符 ══")
t = Counter()
for rel, _p in files:
    for raw in text[rel].split("\n"):
        s = sc(raw)
        for m in re.finditer(r"(?<![\w.])(TriggerType|ItemType|BuffType|StackType)\b", s):
            t[m.group(1)] += 1
print("  ", dict(t))

print("\n══ 5. 成员名撞 class_names（会被 _members 误跳过 → NameError 风险）══")
DECL_RE = re.compile(r"^(\s*)(?:onready\s+)?(?:var|const)\s+([A-Za-z_]\w*)\s*(?::[^=]+)?(?:=|$)")
risk = []
for rel, _p in files:
    lines = text[rel].split("\n")
    # 收集所有成员声明名
    for i, raw in enumerate(lines):
        code = sc(raw)
        m = DECL_RE.match(code)
        if not m:
            continue
        nm = m.group(2)
        if nm in all_names and not nm.startswith("_"):
            risk.append((rel, i + 1, nm, m.group(1).count("\t")))
seen = defaultdict(list)
for rel, ln, nm, ind in risk:
    seen[nm].append((rel, ln, ind))
for nm in sorted(seen):
    print("  %-34s %d 处  如 %s" % (nm, len(seen[nm]), seen[nm][:3]))
if not seen:
    print("  无（安全）")

print("\n══ 6. class_name 与文件名 stem 不一致的脚本（影响 reg 别名）══")
mismatch = [(n, r) for n, r in sorted(by_name.items())
            if os.path.splitext(os.path.basename(r))[0] != n]
print("  共 %d 个" % len(mismatch))
for n, r in mismatch[:25]:
    print("  %-30s %s" % (n, r))

print("\n══ 7. 同名 stem 冲突（py_class 需去重）══")
dup = {k: v for k, v in by_stem.items() if len(v) > 1}
print("  共 %d 组" % len(dup))
for k, v in sorted(dup.items())[:25]:
    print("  %-30s %s" % (k, v))
