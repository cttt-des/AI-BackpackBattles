# -*- coding: utf-8 -*-
"""侦察：列出 gd_core / gd_core_items 里的同文件内嵌类，及其与外层的引用方向。"""
import io, os, re, sys
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

NESTED_RE = re.compile(r"^class\s+([A-Za-z_]\w*)\s*(?:extends\s+([\w\.\"/]+))?\s*:")

def scan(path):
    lines = io.open(path, encoding="utf-8").read().split("\n")
    out = []
    for i, l in enumerate(lines):
        if NESTED_RE.match(l):
            out.append((i + 1, l.strip()))
    return lines, out

total = 0
for base in ("gd_core", "gd_core_items"):
    for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
        for f in fn:
            if not f.endswith(".gd"):
                continue
            p = os.path.join(dp, f)
            lines, found = scan(p)
            if not found:
                continue
            rel = os.path.relpath(p, ROOT).replace("\\", "/")
            for lineno, txt in found:
                total += 1
                # 类体长度
                end = lineno
                j = lineno
                while j < len(lines) and (not lines[j].strip() or lines[j].startswith("\t")):
                    j += 1
                print("%s:%d  %s   [体 %d 行]" % (rel, lineno, txt, j - lineno))
                # 引用方向探查
                body = "\n".join(lines[lineno:j])
                m = NESTED_RE.match(txt)
                nm = m.group(1)
                for other in lines[:lineno] + lines[j:]:
                    if re.search(r"\b%s\b" % re.escape(nm), other) and not other.strip().startswith("#"):
                        print("      外层引用内嵌类: %s" % other.strip()[:100])
                        break
print("内嵌类总数:", total)
