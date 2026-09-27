# -*- coding: utf-8 -*-
"""list_clean_items.py — 列出外部依赖最少的物品脚本（转译首批候选）"""
from __future__ import annotations

import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")

sys.path.insert(0, os.path.join(ROOT, "tools"))
from scan_item_deps import CALL_RE, ENGINE, IDENT_RE, IGNORE, collect, strip_comments_and_strings


def external_symbols(body, local_cls, known):
    code = strip_comments_and_strings(body)
    code = re.sub(r"^\s*extends[^\n]*", "", code, flags=re.M)
    names = set()
    for m in CALL_RE.finditer(code):
        n = m.group(1)
        if n not in ENGINE and n not in local_cls:
            names.add(n)
    for m in IDENT_RE.finditer(code):
        n = m.group(1)
        if n not in known and n not in IGNORE:
            names.add(n)
    return names


def main() -> int:
    want = sys.argv[1] if len(sys.argv) > 1 else "clean"
    scr = collect()
    local_cls = set()
    for rel, body in scr.items():
        for m in re.finditer(r"^class_name\s+([A-Za-z_]\w*)", body, re.M):
            local_cls.add(m.group(1))
    local_cls.add("Item")

    known = set(local_cls) | ENGINE
    rows = []
    for rel, body in scr.items():
        if rel == "Item.gd":
            continue
        ext = re.search(r"^\s*extends\s+([^\n#]+)", body, re.M)
        names = external_symbols(body, local_cls, known | set(re.findall(
            r"(?<![\w.])([A-Z][A-Za-z0-9_]*)\s*\.", strip_comments_and_strings(body))))
        nfunc = len(re.findall(r"^func\s", body, re.M))
        rows.append((len(names), rel, ext.group(1).strip() if ext else "?", nfunc,
                     len(body.splitlines()), sorted(names)))

    if want == "clean":
        sel = [r for r in rows if r[0] == 0]
        sel.sort(key=lambda r: -r[3])
        print("=== 0 种外部依赖的脚本（%d 个），按函数数降序 ===" % len(sel))
        for n, rel, ext, nf, nl, _ in sel[:60]:
            print("  %-42s extends=%-24s funcs=%-3d lines=%d" % (rel, ext, nf, nl))
    else:
        name = os.path.basename(want)
        for n, rel, ext, nf, nl, names in rows:
            if name.lower() in rel.lower():
                print("%s\n  extends=%s funcs=%d lines=%d\n  externals=%s"
                      % (rel, ext, nf, nl, names))
    return 0


if __name__ == "__main__":
    sys.exit(main())
