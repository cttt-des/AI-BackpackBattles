# -*- coding: utf-8 -*-
"""调试 scan_shadow_py 的继承链。"""
import ast, io, os, re, sys

ROOT = r"D:\文件资料\学习\自动背包AI"
RES_PATH_RE = re.compile(r"""["']res://([^"']+)["']""")

by_file = {}
for dirpath, _dirs, files in os.walk(os.path.join(ROOT, "gd_core_py")):
    for f in sorted(files):
        if not f.endswith(".py"):
            continue
        path = os.path.join(dirpath, f)
        rel = os.path.relpath(path, ROOT).replace("\\", "/")
        try:
            with io.open(path, encoding="utf-8") as fh:
                tree = ast.parse(fh.read())
        except SyntaxError:
            continue
        classes = [n for n in tree.body if isinstance(n, ast.ClassDef)]
        if classes:
            by_file[rel] = classes

print("by_file 条目数:", len(by_file))
target = "gd_core_py/gd_core_items/Exclusive/GirlPower.py"
print(target, "in by_file:", target in by_file)
cls = by_file[target][0]
print("类名:", cls.name)
for b in cls.bases:
    print("  基类表达式:", repr(ast.unparse(b)))
    m = RES_PATH_RE.search(ast.unparse(b))
    print("  正则命中:", m.group(1) if m else None)
    if m:
        gd_rel = m.group(1)
        py_rel = "gd_core_py/" + (gd_rel[:-3] + ".py" if gd_rel.endswith(".gd") else gd_rel + ".py")
        print("  映射到:", py_rel, "存在:", py_rel in by_file)

# CoreItem 里有没有 def speed
sc = by_file.get("gd_core_py/gd_core/CoreItem.py")
if sc:
    for c in sc:
        if any("_R.C(" in ast.unparse(b) for b in c.bases):
            names = [n.name for n in c.body if isinstance(n, ast.FunctionDef)]
            print("CoreItem 类方法数:", len(names), "含 speed:", "speed" in names)
            break
