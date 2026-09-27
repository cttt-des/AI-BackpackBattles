# -*- coding: utf-8 -*-
"""scan_item_inherit.py — 扫描 Items/*.gd 的继承链与耦合度

用途：评估「原版物品脚本能否直接挂到 gd_core 上跑」。
输出：继承形态分布 / 中间基类清单 / 继承链深度 / 各文件视觉行占比。
"""
from __future__ import annotations

import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full", "Items")

EXT_RE = re.compile(r"^\s*extends\s+([^\n#]+)", re.M)
FUNC_RE = re.compile(r"^func\s+([A-Za-z_]\w*)", re.M)

# 视觉 / 节点 / 物理 API —— 这些在无头内核里必须剥离
VISUAL = [
    r"\$", r"get_node\(", r"animation", r"particles", r"sprite", r"\.play\(",
    r"scale", r"modulate", r"z_index", r"add_child", r"queue_free",
    r"AnimationPlayer", r"Tween", r"tween", r"shader", r"visible",
    r"Global\.", r"Audio", r"sound", r"emit_signal\(\"hovered", r"position",
    r"rotation_degrees", r"linear_velocity", r"angular_velocity", r"apply_impulse",
    r"collision_layer", r"collision_mask", r"Shape", r"_physics_process",
    r"_process", r"_input", r"_draw", r"_notification",
]


def collect():
    out = {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fn in files:
            if not fn.endswith(".gd"):
                continue
            path = os.path.join(dirpath, fn)
            rel = os.path.relpath(path, SRC).replace(os.sep, "/")
            with open(path, encoding="utf-8", errors="replace") as fh:
                out[rel] = fh.read()
    return out


def visual_lines(body: str) -> int:
    n = 0
    for line in body.splitlines():
        code = line.split("#")[0]
        if any(re.search(v, code) for v in VISUAL):
            n += 1
    return n


def main() -> int:
    scr = collect()
    print("Items/ 下 .gd 脚本数：%d" % len(scr))

    exts = collections.Counter()
    children = collections.defaultdict(list)
    for rel, body in scr.items():
        m = EXT_RE.search(body)
        e = m.group(1).strip() if m else "(none)"
        exts[e] += 1
        children[e].append(rel)

    print("\n=== extends 形态 ===")
    for k, v in exts.most_common(30):
        print("  %-44s %d" % (k, v))

    # 本地可解析的父类（同名 .gd 存在于 Items/ 下）
    local_names = {rel[:-3]: rel for rel in scr}
    base = "Item"
    mid = []
    for parent, kids in children.items():
        if parent in local_names and len(kids) >= 1:
            mid.append((parent, kids))
    mid.sort(key=lambda x: -len(x[1]))
    print("\n=== 被其他物品 extends 的中间基类 ===")
    for parent, kids in mid:
        print("  %-28s ← %d 个子类" % (parent, len(kids)))

    # 继承链深度（从每个脚本上溯到 Item）
    def chain(name, depth=0, seen=None):
        seen = seen or set()
        if name in seen or depth > 8:
            return depth
        seen.add(name)
        rel = local_names.get(name)
        if rel is None:
            return depth
        m = EXT_RE.search(scr[rel])
        p = m.group(1).strip() if m else None
        if p is None or p.startswith("res://"):
            return depth
        return chain(p, depth + 1, seen)

    depths = collections.Counter()
    for rel in scr:
        if rel == "Item.gd":
            continue
        depths[chain(rel[:-3])] += 1
    print("\n=== 继承链深度（到 Item 的层数） ===")
    for d in sorted(depths):
        print("  深度 %d：%d 个脚本" % (d, depths[d]))

    # 叶节点（无子类）＝ 真实物品
    leaves = [rel for rel in scr
              if rel != "Item.gd" and rel[:-3] not in {p for p, _ in mid}]
    print("\n叶节点（真实物品）：%d" % len(leaves))

    total_lines = sum(len(b.splitlines()) for rel, b in scr.items() if rel != "Item.gd")
    total_vis = sum(visual_lines(b) for rel, b in scr.items() if rel != "Item.gd")
    print("总行数 %d，视觉行 %d（%.1f%%）" % (total_lines, total_vis,
                                          100.0 * total_vis / max(total_lines, 1)))

    # 叶节点的战斗函数统计
    battle_funcs = collections.Counter()
    for rel in leaves:
        for fn in FUNC_RE.findall(scr[rel]):
            battle_funcs[fn] += 1
    print("\n=== 叶节点定义的函数（前 25，按出现数） ===")
    for fn, n in battle_funcs.most_common(25):
        print("  %-30s %d" % (fn, n))
    return 0


if __name__ == "__main__":
    sys.exit(main())
