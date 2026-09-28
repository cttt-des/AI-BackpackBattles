# -*- coding: utf-8 -*-
"""audit_stripped_funcs.py — 枚举「整函数剥离误伤行为逻辑」的函数清单。

对每件物品：找 gd_core_items 产物里的空桩函数（体只有 pass/父调用/零值返回），
回原版反编译源取同函数体，用生成器自己的 classify_statements 分类每个语句；
若「行为语句」（keep / 非视觉的 raw）数 ≥1，则该剥离是**误伤**，报告之。

★ 判定纪律：0 命中要配正对照 —— 本工具对 MagicRing.sortEffects 必须报出。
"""
from __future__ import annotations

import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, "tools"))

import build_item_scripts as B                                  # noqa: E402


def init_generator_state():
    scr = B.collect()
    all_modals = B.extract_node_modals(scr)
    B.TIMER_MODAL_NAMES = {m for m in all_modals if m.endswith("Timer")}
    B.NODE_MODALS = all_modals - B.TIMER_MODAL_NAMES
    B.CORE_MEMBERS = B.core_members(os.path.join(ROOT, "gd_core"))
    B.SHELL_MEMBERS = (B.script_names(os.path.join(B.SRC, "Item.gd"))["var"]
                       - B.script_names(os.path.join(ROOT, "gd_core", "CoreItem.gd"))["var"])
    return scr


def stub_names_out(rel: str) -> dict:
    """gd_core_items 产物里的空桩函数 -> (体行数, 是否含父调用)。"""
    path = os.path.join(ROOT, "gd_core_items", rel)
    if not os.path.exists(path):
        return {}
    with io.open(path, encoding="utf-8") as fh:
        text = fh.read()
    funcs = B.split_functions(text)[0]
    stubs = {}
    # 空桩的 return 只可能是零值字面量（见 build_item_scripts.STUB_RETURN / stub_body）
    ZERO = re.compile(r"^(return\s+(0|0\.0|false|true|\"\"|null|\[\]|\{\}|Vector2\.ZERO)\s*$|pass$)")
    for f in funcs:
        header, name, blines = f[0], f[1], f[2]
        body = [l for l in blines
                if l.strip() and not ZERO.match(l.strip())
                and not re.match(r"^\.\s*[A-Za-z_]", l.strip())]
        if not body:
            stubs[name] = (len([l for l in blines if l.strip()]), header)
    return stubs


def behavioral_lines(func_header: str, blines: list, in_file: set):
    """用生成器口径分类原版函数体，返回 (keep 行, mixed 行, pure 行数)。"""
    stmts = B.classify_statements(blines, in_file)
    keep, mixed, pure = [], [], 0
    for kind, raw, rewritten in stmts:
        if kind == "keep":
            keep.append("\n".join(raw))
        elif kind == "mixed":
            mixed.append("\n".join(raw))
        else:
            pure += len(raw)
    return keep, mixed, pure


def main() -> int:
    scr = init_generator_state()
    positive_control = {"MagicRing.gd": {"sortEffects", "randEffects"}}
    hits = []
    for rel in sorted(scr):
        if rel == "Item.gd":
            continue          # 基类适配层单独过滤，口径不同
        body = scr[rel]
        in_file = B.collect_in_file_names(body)
        stubs = stub_names_out(rel)
        if not stubs:
            continue
        funcs = B.split_functions(body)[0]
        for f in funcs:
            header, name, blines = f[0], f[1], f[2]
            if name not in stubs:
                continue
            keep, mixed, pure = behavioral_lines(header, blines, in_file)
            if keep or mixed:
                hits.append((rel, name, len(keep), len(mixed), keep[:3] or mixed[:3]))

    print("误伤函数共 %d 个（跨 %d 个文件）"
          % (len(hits), len({h[0] for h in hits})))
    for rel, name, nk, nm, sample in hits:
        print("  %-40s %-26s keep=%d mixed=%d" % (rel, name, nk, nm))
        for s in sample:
            for ln in s.splitlines()[:2]:
                print("        | " + ln.strip()[:100])

    # ── 正对照：MagicRing 的两个函数必须在场（按 basename 对） ──
    got = {(os.path.basename(r), n) for r, n, *_ in hits}
    missing = [(f, n) for f, ns in positive_control.items() for n in ns
               if (f, n) not in got]
    if missing:
        print("\n正对照失败（扫描器坏了）：未报出 %s" % missing)
        return 1
    print("\n正对照：MagicRing sortEffects/randEffects 均已报出 ✓")
    return 0


if __name__ == "__main__":
    sys.exit(main())
