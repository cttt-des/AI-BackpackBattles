# -*- coding: utf-8 -*-
"""侦察 `/` 与 `%` 的实际用法：判断是否必须做 GDScript 整除语义。

GDScript 3：int/int → 截断整除；int%int → 取余（符号随被除数）。
Python：/ → 真除；% → 取余（符号随除数）；// → 地板除。
故若两处都有 int/int，必须转成运行时助手，否则静默偏值。
"""
import os
import re
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def strip_str_cmt(s):
    s = re.sub(r'"[^"\n]*"', '""', s)
    s = re.sub(r"'[^'\n]*'", "''", s)
    s = re.sub(r"#[^\n]*", "", s)
    return s


for d in ("gd_core", "gd_core_items"):
    base = os.path.join(ROOT, d)
    div_lines, mod_lines, fmt_lines = [], [], []
    for root, _, files in os.walk(base):
        for f in sorted(files):
            if not f.endswith(".gd"):
                continue
            p = os.path.join(root, f)
            rel = os.path.relpath(p, ROOT).replace(os.sep, "/")
            for i, ln in enumerate(open(p, encoding="utf-8", errors="replace"), 1):
                code = strip_str_cmt(ln)
                # 找算术 `/`：排除注释后仍存在的、且不在 http/res 路径里
                if re.search(r"[\w\)\]]\s*/\s*[\w\(]", code):
                    div_lines.append((rel, i, ln.rstrip()))
                if re.search(r"[\w\)\]]\s*%\s*[\w\(]", code):
                    mod_lines.append((rel, i, ln.rstrip()))
                if re.search(r'%', ln) and re.search(r'"[^"]*%"', ln):
                    fmt_lines.append((rel, i, ln.rstrip()))
    print("════════ %s ════════" % d)
    print("含算术 / 的行: %d   含算术 %% 的行: %d   含字符串格式化的行: %d"
          % (len(div_lines), len(mod_lines), len(fmt_lines)))
    print("\n── 算术 / 样例（最多 40）──")
    for rel, i, ln in div_lines[:40]:
        print("  %-40s %5d  %s" % (rel, i, ln.strip()[:96]))
    print("\n── 算术 %% 样例（最多 30）──")
    for rel, i, ln in mod_lines[:30]:
        print("  %-40s %5d  %s" % (rel, i, ln.strip()[:96]))
    print("\n── 字符串格式化样例（最多 15）──")
    for rel, i, ln in fmt_lines[:15]:
        print("  %-40s %5d  %s" % (rel, i, ln.strip()[:96]))
    print()
