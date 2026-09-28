# -*- coding: utf-8 -*-
"""产物语法体检：逐文件 ast.parse，按错误类型归类。

用途：转写器每次改动后，一眼看出还剩几类问题、各在哪些文件。
比 bootstrap 导入好在：能一次报出**所有**文件的语法错误（导入遇错即停）。
比 Godot 好在：不依赖引擎。

用法: python tools/check_gd_py.py [--show N]
退出码 0 = 全部通过。
"""
from __future__ import annotations

import ast
import io
import os
import re
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PKG = os.path.join(ROOT, "gd_core_py")
# 手写文件（非转写产物）。★ 它们**仍要过语法体检** —— 只是不计入「产物」口径。
#   早先这里被当成「跳过体检」的名单用，等于让唯一由人手写的几个文件免检；
#   而手写文件恰恰是最需要体检的（生成器由闸门守着，人手写的没有）。
HANDWRITTEN = {"_rt.py", "_registry.py", "_bootstrap.py", "_colors.py", "__init__.py"}
SHOW = 3
for i, a in enumerate(sys.argv):
    if a == "--show" and i + 1 < len(sys.argv):
        SHOW = int(sys.argv[i + 1])


def read(path):
    return io.open(path, encoding="utf-8", errors="replace").read()


def main():
    generated, handwritten = [], []
    for root, _s, names in os.walk(PKG):
        for n in sorted(names):
            if not n.endswith(".py"):
                continue
            p = os.path.join(root, n)
            (handwritten if n in HANDWRITTEN else generated).append(p)
    # ★ 两类都体检
    files = sorted(generated + handwritten)

    kinds = defaultdict(list)
    ok = 0
    for p in files:
        text = read(p)
        try:
            ast.parse(text)
            ok += 1
        except SyntaxError as exc:
            kinds[exc.__class__.__name__ +
                  ("/" + re.sub(r"[^A-Za-z ]", "", exc.msg or "")[:40]).strip()
                  ].append((p, exc.lineno or 0, exc))

    print("产物文件 %d 个（手写 %d 个）：语法通过 %d，失败 %d\n"
          % (len(generated), len(handwritten), ok, len(files) - ok))
    if not kinds:
        print("CHECK_GD_PY: 全部通过。")
        return 0

    for kind, items in sorted(kinds.items(), key=lambda kv: -len(kv[1])):
        print("══ %s  共 %d 个文件 ══" % (kind, len(items)))
        for p, ln, exc in items[:SHOW]:
            rel = os.path.relpath(p, ROOT)
            lines = read(p).split("\n")
            print("   %s:%d" % (rel, ln))
            print("      msg : %s" % exc.msg)
            if 0 < ln <= len(lines):
                src = lines[ln - 1]
                print("      prod: %r" % src[:100])
                # 顺带把对应 gd 源码行也带出来，便于判断是转写器的问题
                gd = _gd_line_for(rel, ln)
                print("      gd  : %r" % (gd or "<未定位>"))
        if len(items) > SHOW:
            print("   ... 其余 %d 个" % (len(items) - SHOW))
        print()
    return 1


_GD_CACHE = {}


def _gd_line_for(py_rel, py_line):
    """粗略地把产物行号映射回 gd 行号（产物保留了注释行，多数情况下同号或接近）。"""
    rel = py_rel.replace("\\", "/")
    if not rel.endswith(".py"):
        return None
    gd_rel = rel[:-3] + ".gd"
    gd_path = os.path.join(ROOT, *gd_rel.split("/"))
    if not os.path.exists(gd_path):
        return None
    if gd_path not in _GD_CACHE:
        _GD_CACHE[gd_path] = read(gd_path).split("\n")
    lines = _GD_CACHE[gd_path]
    best, best_d = None, 99
    for d in range(0, 60):
        for cand in (py_line - d, py_line + d):
            if 1 <= cand <= len(lines):
                s = lines[cand - 1].strip()
                if s:
                    best, best_d = (cand, lines[cand - 1]), d
                    break
        if best is not None and d >= 3:
            break
    return ("%d: %s" % best) if best else None


if __name__ == "__main__":
    raise SystemExit(main())
