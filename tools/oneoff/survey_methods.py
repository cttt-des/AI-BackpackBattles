# -*- coding: utf-8 -*-
"""侦察：gd 源里所有 `.方法(` 调用中，既不是 Python 内建方法、也不是本项目
自定义 func 的那些 —— 即运行时会 AttributeError 的缺口。"""
import io
import os
import re
import sys
from collections import Counter

sys.stdout.reconfigure(encoding="utf-8")
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CALL_RE = re.compile(r"\.\s*([A-Za-z_]\w*)\s*\(")
FUNC_RE = re.compile(r"^\s*(?:static\s+)?func\s+([A-Za-z_]\w*)\s*\(")

# ① 本项目自定义的方法名（gd_core + gd_core_items 里的 func）
own = set()
for base in ("gd_core", "gd_core_items"):
    for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
        for f in fn:
            if f.endswith(".gd"):
                for l in io.open(os.path.join(dp, f), encoding="utf-8").read().split("\n"):
                    m = FUNC_RE.match(l)
                    if m:
                        own.add(m.group(1))

# ② Python 内建 str / list / dict / set 的方法
PY = set(dir(str)) | set(dir(list)) | set(dir(dict)) | set(dir(set)) | set(dir(tuple)) | set(dir(float)) | set(dir(int))
# ③ 生成器已经改写掉的（见 tools/gd_to_py.py 规则表）+ _rt 垫片
ALREADY = {
    "size", "push_back", "empty", "erase", "shuffle", "append_array", "duplicate",
    "keys", "values", "remove", "pop_front", "sort_custom", "find", "resize",
    "begins_with", "length", "pop_back", "get_slice", "has", "new",
}

# gd 源里 `.new(` 是构造器；`has(` 是 Object.has_method 之类，非容器
cnt = Counter()
samples = {}
for base in ("gd_core", "gd_core_items"):
    for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
        for f in fn:
            if not f.endswith(".gd"):
                continue
            p = os.path.join(dp, f)
            rel = os.path.relpath(p, ROOT).replace("\\", "/")
            for i, l in enumerate(io.open(p, encoding="utf-8").read().split("\n")):
                s = l.strip()
                if s.startswith("#"):
                    continue
                code = s.split("#")[0]
                for m in CALL_RE.finditer(code):
                    n = m.group(1)
                    if n in own or n in PY or n in ALREADY:
                        continue
                    cnt[n] += 1
                    samples.setdefault(n, []).append("%s:%d  %s" % (rel, i + 1, code[:95]))

print("本项目自定义方法 %d 个；Python 内建方法 %d 个" % (len(own), len(PY)))
print("疑似缺口 %d 个名字：\n" % len(cnt))
for k, v in cnt.most_common():
    print("%-26s %4d" % (k, v))
    for s in samples[k][:3]:
        print("        " + s)
