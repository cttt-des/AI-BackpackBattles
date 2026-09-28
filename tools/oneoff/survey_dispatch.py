# -*- coding: utf-8 -*-
"""统计信号/派发/杂项内建用法，为 _rt.py 定 API。"""
import io
import os
import re
import sys

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

STR_RE = re.compile(r'"(?:[^"\\]|\\.)*"')
CMT_RE = re.compile(r"#.*$")


def sc(s):
    return CMT_RE.sub("", STR_RE.sub('""', s))


PATS = [
    ("signal 声明", r"^\s*signal\s+\w+"),
    ("connect(", r"(?<![\w.])(connect|connectEvent)\s*\("),
    (".connect(", r"\.(connect|connectEvent)\s*\("),
    ("emit_signal(", r"emit_signal\s*\("),
    (".emit(", r"\.emit\s*\("),
    ("FuncRef", r"FuncRef|funcref"),
    ("has_method(", r"has_method\s*\("),
    ("call( / callv(", r"(?<![\w.])(call|callv)\s*\("),
    ("call_func*", r"call_func\w*"),
    ("is_connected", r"is_connected"),
    ("disconnect", r"disconnect"),
    ("get_instance_id", r"get_instance_id"),
    ("hash(", r"(?<![\w.])hash\s*\("),
    ("get_slice", r"get_slice"),
    ("join(", r"\.join\s*\("),
    ("sort_custom", r"sort_custom"),
    ("randomize(", r"(?<![\w.])randomize\s*\("),
    ("to_json/parse_json", r"to_json|parse_json|JSON"),
    ("instance/ClassDB", r"instance\s*\(|ClassDB|\.instantiate"),
    ("setget", r"setget"),
    ("yield", r"(?<![\w.])yield\b"),
    ("get_node/$", r"get_node|\$[A-Za-z_]"),
    ("print(", r"(?<![\w.])print\s*\("),
    ("assert(", r"(?<![\w.])assert\s*\("),
    ("push_error/warning", r"push_error|push_warning"),
    ("is_instance_valid", r"is_instance_valid"),
    ("weakref", r"weakref"),
]

results = {}
for label, pat in PATS:
    hits = []
    for d in ("gd_core", "gd_core_items"):
        for root, _s, names in os.walk(d):
            for n in sorted(names):
                if not n.endswith(".gd"):
                    continue
                p = os.path.join(root, n)
                for i, ln in enumerate(io.open(p, encoding="utf-8",
                                               errors="replace"), 1):
                    if re.search(pat, sc(ln)):
                        hits.append("%s:%d %s" % (p, i, sc(ln).strip()[:80]))
    results[label] = hits

for label, _p in PATS:
    h = results[label]
    print("=== %s  (%d) ===" % (label, len(h)))
    for x in h[:10]:
        print("   ", x)
