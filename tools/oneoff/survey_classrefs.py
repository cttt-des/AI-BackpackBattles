# -*- coding: utf-8 -*-
"""侦察：转写产物里会有哪些「裸类名」引用（Python 里会 NameError 的地方）。

分类：
  A. `<类名>.new(`            —— 脚本实例化（含内建类型 / 跨文件 class_name / 同文件嵌套类）
  B. `<类名>.<非new方法>(`     —— 静态方法调用（CoreUtil.truth / CoreConst.Rarity 等）
  C. `is <类名>`              —— isinstance 目标
  D. 其他裸类名出现           —— 不在 A/B/C、不在 extends/class_name/声明左侧

对每个类名标注：内建映射 / 跨文件 class_name / 同文件顶层类名 / 同文件嵌套类名 / 未知
"""
import io
import os
import re
import sys
from collections import Counter, defaultdict

sys.stdout.reconfigure(encoding="utf-8")

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIRS = ("gd_core", "gd_core_items")

TYPE_MAP = {
    "void": "None", "String": "str", "Array": "list", "Dictionary": "dict",
    "Vector2": "Vector2", "Reference": "GodotObject", "Object": "GodotObject",
    "Resource": "GodotObject", "Node2D": "GodotObject", "Node": "GodotObject",
    "bool": "bool", "int": "int", "float": "float", "FuncRef": "FuncRef",
    "Color": "Color", "PoolStringArray": "list", "PoolIntArray": "list",
}

# GD 内建「类」（可 .new()，但不是项目类）
GD_BUILTIN_NEW = {
    "Vector2", "Vector3", "Rect2", "Color", "RandomNumberGenerator", "FuncRef",
    "Array", "Dictionary", "StringArray", "PoolStringArray", "PoolByteArray",
    "PoolIntArray", "PoolRealArray", "Node", "Reference", "Node2D", "Timer",
    "Image", "Shader", "Curve", "Gradient", "Object", "Resource",
}

STR_RE = re.compile(r'"(?:[^"\\]|\\.)*"')
COMMENT_RE = re.compile(r"#.*$")


def strip_str_comment(s):
    s = STR_RE.sub('""', s)
    return COMMENT_RE.sub("", s)


files = []
for d in SRC_DIRS:
    base = os.path.join(ROOT, d)
    for root, _subs, names in os.walk(base):
        for n in names:
            if n.endswith(".gd"):
                p = os.path.join(root, n)
                rel = os.path.relpath(p, ROOT).replace(os.sep, "/")
                files.append((rel, p))
files.sort()

by_name = {}       # class_name -> rel
by_stem = defaultdict(list)   # 文件名 stem -> [rel]
file_text = {}
for rel, p in files:
    txt = io.open(p, encoding="utf-8", errors="replace").read()
    file_text[rel] = txt
    stem = os.path.splitext(os.path.basename(rel))[0]
    by_stem[stem].append(rel)
    m = re.search(r"^class_name\s+([A-Za-z_]\w*)", txt, re.M)
    if m:
        by_name[m.group(1)] = rel

all_names = set(by_name) | set(by_stem)


def nest_of(name):
    """判断 name 是哪个文件的类（顶层类名 / 嵌套类名）。"""
    if name in by_name:
        return ("跨文件class_name", by_name[name])
    if name in by_stem:
        return ("同文件顶层(按文件名)", by_stem[name][0])
    return (None, None)


NEW_RE = re.compile(r"(?<![\w.\[\]\"'])([A-Za-z_]\w*)\s*\.\s*new\s*\(")
STATIC_RE = re.compile(r"(?<![\w.\[\]\"'])([A-Za-z_]\w*)\s*\.\s*([A-Za-z_]\w*)\s*\(")
IS_RE = re.compile(r"\bis\s+([A-Za-z_]\w*)")

A = Counter()          # new 目标
A_kind = defaultdict(Counter)
B = Counter()          # 静态调用目标
B_kind = defaultdict(Counter)
C = Counter()
D = Counter()
nest_hits = defaultdict(list)   # 嵌套类名 -> 出现处

for rel, _p in files:
    nested_names = set(re.findall(r"^\s+class\s+([A-Za-z_]\w*)", file_text[rel], re.M))
    text = file_text[rel]
    for i, raw in enumerate(text.split("\n"), 1):
        s = strip_str_comment(raw)
        if not s.strip():
            continue
        s_nostr = s
        for m in NEW_RE.finditer(s_nostr):
            nm = m.group(1)
            A[nm] += 1
            if nm in GD_BUILTIN_NEW:
                A_kind[nm]["GD内建"] += 1
            elif nm in nested_names:
                A_kind[nm]["★同文件嵌套类(需 self. 或外部类名)"] += 1
                nest_hits[nm].append((rel, i))
            else:
                kind, src = nest_of(nm)
                A_kind[nm][kind or "未知"] += 1
                if kind is None:
                    nest_hits[nm].append((rel, i))
        for m in STATIC_RE.finditer(s_nostr):
            nm = m.group(1)
            if nm in GD_BUILTIN_NEW:
                continue
            B[(nm, m.group(2))] += 1
            if nm in nested_names:
                B_kind[nm]["★同文件嵌套类"] += 1
            else:
                kind, src = nest_of(nm)
                B_kind[nm][kind or "未知"] += 1
        for m in IS_RE.finditer(s_nostr):
            C[m.group(1)] += 1
        for m in re.finditer(r"(?<![\w.\[\]\"'])([A-Za-z_]\w*)(?![\w.\[])", s_nostr):
            nm = m.group(1)
            if nm in GD_BUILTIN_NEW or nm in TYPE_MAP:
                continue
            if nm not in all_names:
                continue
            if re.match(r"^\s*(class_name|extends)\b", s_nostr):
                continue
            if re.match(r"^\s*(static\s+)?func\b", s_nostr):
                continue
            if re.search(r"^\s*(var|const)\s+%s\b" % re.escape(nm), s_nostr):
                continue
            D[nm] += 1

print("扫描 %d 个 .gd 文件\n" % len(files))

print("══ A. X.new( 目标（按出现次数）══")
for nm, cnt in A.most_common(40):
    kinds = ", ".join("%s=%d" % kv for kv in A_kind[nm].most_common())
    print("  %-32s %5d   %s" % (nm, cnt, kinds))

print("\n══ B. X.method( 静态/类限定调用（Top 40）══")
for (nm, meth), cnt in B.most_common(40):
    kinds = ", ".join("%s=%d" % kv for kv in B_kind[nm].most_common())
    print("  %-28s .%-24s %5d  %s" % (nm, meth, cnt, kinds))

print("\n══ C. `is <类名>` 目标 ══")
for nm, cnt in C.most_common(40):
    kind, src = nest_of(nm)
    print("  %-32s %5d   %s" % (nm, cnt, kind or "未知"))

print("\n══ D. 其他裸类名出现（非 A/B/C，Top 40）══")
for nm, cnt in D.most_common(40):
    kind, src = nest_of(nm)
    print("  %-32s %5d   %s" % (nm, cnt, kind or "未知"))

print("\n══ 汇总 ══")
print("  A 唯一目标 %d 个 / 共 %d 处" % (len(A), sum(A.values())))
print("  B 唯一(类,方法) %d 组 / 共 %d 处" % (len(B), sum(B.values())))
print("  C 唯一类型 %d 个 / 共 %d 处" % (len(C), sum(C.values())))
print("  D 唯一标识符 %d 个 / 共 %d 处" % (len(D), sum(D.values())))

bad = [nm for nm in A if nm not in GD_BUILTIN_NEW and nm not in all_names]
if bad:
    print("\n★ A 里未知类名：", bad)
badB = [nm for nm, _m in B if nm not in all_names and nm not in GD_BUILTIN_NEW]
if badB:
    print("★ B 里未知类名：", sorted(set(badB))[:30])

# 嵌套类引用详细
print("\n★ 同文件嵌套类被裸引用（必须特殊处理）：")
if nest_hits:
    for nm, hits in sorted(nest_hits.items()):
        print("  %-28s %d 处  如 %s" % (nm, len(hits), hits[:3]))
else:
    print("  无")
