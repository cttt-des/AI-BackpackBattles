# -*- coding: utf-8 -*-
"""audit_item_transcript.py — gd_core_items 移植层 vs decompiled_full 原版 逐函数语义对账

用法: python tools/audit_item_transcript.py
输出: 每个物品中，函数体 token 序列不一致的函数列表。
"""
from __future__ import annotations

import os
import re
import sys

_BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_ORIG = os.path.join(_BASE, "decompiled_full", "Items")
SRC_PORT = os.path.join(_BASE, "gd_core_items")

FUNC_RE = re.compile(r"^func\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(", re.M)
TOKEN_RE = re.compile(r"[A-Za-z_][A-Za-z0-9_]*|\d+\.\d+|\d+|[-+*/%=<>!&|(),\[\]:\.]")


def strip_noise(src: str) -> str:
    """去掉注释、字符串字面量、动画/节点路径噪声。"""
    out = []
    for line in src.splitlines():
        line = re.sub(r'".*?"', '""', line)
        line = re.sub(r'#.*', '', line)
        line = re.sub(r'\$[A-Za-z0-9_/]+', '', line)
        out.append(line)
    return "\n".join(out)


def parse_funcs(path: str) -> dict:
    try:
        src = strip_noise(open(path, encoding="utf-8").read())
    except FileNotFoundError:
        return {}
    funcs = {}
    matches = list(FUNC_RE.finditer(src))
    for i, m in enumerate(matches):
        name = m.group(1)
        start = m.start()
        end = matches[i + 1].start() if i + 1 < len(matches) else len(src)
        body = src[start:end]
        toks = TOKEN_RE.findall(body)
        # 跳过函数头 tokens: func name ( ... ) -> type :
        funcs[name] = toks
    return funcs


def norm_extend(ports: dict):
    """gd_core_items 里 extends "res://Items/X.gd" 的对应原版路径提示。"""
    return ports


def find_orig(name: str):
    cand = os.path.join(SRC_ORIG, name)
    if os.path.exists(cand):
        return cand
    sub = os.path.join(SRC_ORIG, "Exclusive", name)
    if os.path.exists(sub):
        return sub
    for root, _dirs, files in os.walk(SRC_ORIG):
        if name in files:
            return os.path.join(root, name)
    return None


def token_diff(a, b):
    import difflib
    sm = difflib.SequenceMatcher(a=a, b=b, autojunk=False)
    ops = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            ops.append((tag, a[max(0, i1 - 3):i1 + 3], b[max(0, j1 - 3):j1 + 3]))
    return ops


def main():
    only = sys.argv[1:] if len(sys.argv) > 1 else None
    items = sorted(f for f in os.listdir(SRC_PORT) if f.endswith(".gd"))
    n_diff = 0
    for f in items:
        if only and not any(o in f for o in only):
            continue
        orig_path = find_orig(f)
        port_funcs = parse_funcs(os.path.join(SRC_PORT, f))
        if orig_path is None:
            continue
        orig_funcs = parse_funcs(orig_path)
        problems = []
        for name, ptoks in port_funcs.items():
            if name == "_readyInit":
                continue  # 视觉初始化，语义等价于 onready
            otoks = orig_funcs.get(name)
            if otoks is None:
                problems.append(("MISSING_IN_ORIG", name, [], []))
                continue
            if ptoks != otoks:
                ops = token_diff(otoks, ptoks)
                if ops:
                    problems.append(("DIFF", name, ops[:4], None))
        for name in orig_funcs:
            if name not in port_funcs and name not in (
                    "_ready", "_process", "_draw", "getDescription",
                    "getTooltipStats", "_to_string"):
                problems.append(("MISSING_IN_PORT", name, [], []))
        if problems:
            n_diff += 1
            print("=== %s ===" % f)
            for kind, name, a, b in problems:
                if kind == "DIFF":
                    print("  [%s] %s" % (kind, name))
                    for tag, x, y in a:
                        print("      %s orig...%s | port...%s" % (tag, x, y))
                else:
                    print("  [%s] %s" % (kind, name))
    print("\n%d 个文件存在函数级差异" % n_diff)


if __name__ == "__main__":
    main()
