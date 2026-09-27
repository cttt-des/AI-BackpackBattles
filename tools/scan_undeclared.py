#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""scan_undeclared.py — 一次性列出「未声明的标识符」

背景：Godot 3 每个脚本只报**首个**解析错误，改一个跑一次太慢（尤其 Item.gd
一失败就连锁带崩 469 个子类）。本工具用静态分析把「用了但没声明」的标识符
**全部**列出来，按出现次数排序，供转译器批量补规则。

用法：
    python tools/scan_undeclared.py                      # 扫适配层 Item.gd
    python tools/scan_undeclared.py --all                # 扫全部物品脚本
    python tools/scan_undeclared.py --file gd_core_items/Bag.gd
"""
from __future__ import annotations

import collections
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# GDScript 关键字 / 内建函数 / 内建类型 / 内建常量（解析期本就可见）
BUILTIN = set("""
and or not if else elif for while in return pass break continue
var const enum func class class_name extends signal static onready export
setget tool remote master puppet sync yield assert breakpoint
self true false null void
preload load range str int float bool abs min max len print printraw
pow sqrt sin cos tan asin acos atan atan2 randf randi rand_range randi_range
randf_range round floor ceil sign clamp lerp lerp_angle deg2rad rad2deg
inverse_lerp move_toward linear2db db2linear exp log log10
is_instance_valid type_of typeof weakref funcref ord char
Color Vector2 Vector3 Rect2 Transform2D Basis Quat AABB Plane Dictionary
Array String NodePath RID PoolStringArray PoolByteArray PoolIntArray
PoolRealArray PoolVector2Array PoolColorArray
PI TAU INF NAN Math
match stepify
RigidBody2D Node2D Area2D CanvasItem Sprite Label Control ColorRect
SceneTreeTween Tween Physics2DDirectBodyState InputEvent
""".split())

# `ctx.<attr>` 的合法属性名（CoreContext 的字段）
CTX_ATTRS = {"rng", "util", "bus", "hooks", "player", "opponent", "combat",
             "log", "grid", "owner", "event", "self"}

IDENT_RE = re.compile(r"(?<![\w.\"'])([A-Za-z_]\w*)")


def read(path: str) -> str:
    with io.open(path, encoding="utf-8", errors="replace") as fh:
        return fh.read()


def strip_code(line: str) -> str:
    """去掉注释与字符串内容，避免把文案里的词当标识符。"""
    line = re.sub(r"#[^\n]*", "", line)
    line = re.sub(r'"(?:[^"\\]|\\.)*"', '""', line)
    line = re.sub(r"'(?:[^'\\]|\\.)*'", "''", line)
    return line


def declarations(body: str) -> set:
    """本文件所有会「引入一个名字」的声明。"""
    out = set()
    pats = [
        r"^\s*(?:onready\s+)?var\s+([A-Za-z_]\w*)",
        r"^\s*const\s+([A-Za-z_]\w*)",
        r"^\s*enum\s+([A-Za-z_]\w*)",
        r"^\s*signal\s+([A-Za-z_]\w*)",
        r"^\s*class_name\s+([A-Za-z_]\w*)",
        r"^\s*(?:static\s+)?func\s+([A-Za-z_]\w*)",
        r"^\s*class\s+([A-Za-z_]\w*)",
    ]
    for p in pats:
        for m in re.finditer(p, body, re.M):
            out.add(m.group(1))
    # 函数参数（含默认值里的名字不算，故先切掉 `=` 右侧）
    for m in re.finditer(r"^\s*(?:static\s+)?func\s+[A-Za-z_]\w*\s*\((.*?)\)",
                         body, re.M | re.S):
        for p in m.group(1).split(","):
            p = p.split("=")[0].strip()
            p = p.split(":")[0].strip()
            if re.match(r"^[A-Za-z_]\w*$", p):
                out.add(p)
    # 局部变量（含 for 循环变量）
    for m in re.finditer(r"(?:^|\s)var\s+([A-Za-z_]\w*)", body):
        out.add(m.group(1))
    for m in re.finditer(r"\bfor\s+([A-Za-z_]\w*)\s+in\b", body):
        out.add(m.group(1))
    return out


def core_names(core_dir: str, chain=("CoreItem.gd",)) -> set:
    """内核继承链上可见的名字（含 CoreConst 常量表 —— 转译后以 CoreConst.X 引用）。"""
    out = set()
    for fn in os.listdir(core_dir):
        if fn.endswith(".gd"):
            # CoreConst / CoreUtil 等是 `CoreXxx.` 前缀引用，属性名不必入表；
            # 但 `CoreConst.X` 的 X 需要可见，故把常量表整个并入。
            out |= declarations(read(os.path.join(core_dir, fn)))
    for m in re.finditer(r"CoreConst\.([A-Za-z_]\w*)",
                         "".join(read(os.path.join(core_dir, f))
                                 for f in os.listdir(core_dir)
                                 if f.endswith(".gd"))):
        out.add(m.group(1))
    # 类型名 Core* 本身
    out |= {f[:-3] for f in os.listdir(core_dir) if f.endswith(".gd")}
    return out


def strip_blocks(body: str) -> str:
    """把 `enum X{ ... }` 的**体**清空（枚举成员不是表达式，会被误报为未声明）。"""
    lines = body.splitlines()
    out = []
    i = 0
    in_enum = 0
    while i < len(lines):
        line = lines[i]
        if in_enum == 0 and re.match(r"^\s*enum\s+[A-Za-z_]\w*\s*\{", line):
            in_enum = 1
            out.append(line)
            i += 1
            continue
        if in_enum:
            in_enum += line.count("{") - line.count("}")
            out.append("")
            i += 1
            continue
        out.append(line)
        i += 1
    return "\n".join(out)


def scan(path: str, known: set) -> collections.Counter:
    body = strip_blocks(read(path))
    decls = declarations(read(path)) | known | BUILTIN
    bad = collections.Counter()
    for line in body.splitlines():
        code = strip_code(line)
        if not code.strip():
            continue
        # 字典字面量的键（`Foo: 1`）在解析期不是表达式，跳过
        for m in IDENT_RE.finditer(code):
            name = m.group(1)
            if name in decls or name in CTX_ATTRS:
                continue
            end = m.end()
            rest = code[end:]
            # 函数调用（`has_method(...)` / `set_process(...)`）：Godot 报的是
            # 「The method X isn't declared」而不是 identifier，且 Object 内建方法
            # 本就可见，故跳过。
            if rest.lstrip().startswith("("):
                continue
            # 属性访问：`.name`
            if m.start() and code[m.start() - 1] == ".":
                continue
            # 后面紧跟 `:` 且前面是 `{`/`,`/行首 → 字典键，跳过
            if rest.lstrip().startswith(":") and not rest.lstrip().startswith(":="):
                continue
            bad[name] += 1
    return bad


def main() -> int:
    core = core_names(os.path.join(ROOT, "gd_core"))
    if "--all" in sys.argv:
        targets = []
        for dirpath, _d, files in os.walk(os.path.join(ROOT, "gd_core_items")):
            for f in files:
                if f.endswith(".gd"):
                    targets.append(os.path.join(dirpath, f))
    elif "--file" in sys.argv:
        p = sys.argv[sys.argv.index("--file") + 1]
        targets = [p if os.path.isabs(p) else os.path.join(ROOT, p)]
    else:
        targets = [os.path.join(ROOT, "gd_core_items", "Item.gd")]

    total = collections.Counter()
    per_file = {}
    for t in targets:
        c = scan(t, core)
        per_file[os.path.relpath(t, ROOT)] = c
        total.update(c)

    print("=" * 72)
    print("未声明标识符静态扫描（%d 个文件）" % len(targets))
    print("=" * 72)
    if len(targets) == 1:
        rel = list(per_file)[0]
        print("文件：%s" % rel)
        print("未声明标识符 %d 种，共 %d 处" % (len(total), sum(total.values())))
        print()
        for name, n in total.most_common():
            print("%4d  %s" % (n, name))
    else:
        print("未声明标识符 %d 种，共 %d 处" % (len(total), sum(total.values())))
        print()
        for name, n in total.most_common(60):
            files = sum(1 for c in per_file.values() if name in c)
            print("%5d 处 / %3d 文件  %s" % (n, files, name))
    return 0


if __name__ == "__main__":
    sys.exit(main())
