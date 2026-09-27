#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""gap_audit.py — 判定路径缺口的**可达性定裁**（替代按名字猜关键词）。

问题：gd_core_coverage.py 用关键词启发式判「这个方法像不像战斗方法」，会把
Items/Item.gd 里的拖拽/预览代码也算成判定路径（因为文件名在判定路径里），
既不精确也无法回答「到底谁在调它」。

本脚本改做**调用闭包**：
  1. 解析 decompiled_full/**/*.gd，按顶层 func 归属建立调用图
     (文件, 函数) → {被调函数名}
  2. 种子 = gd_core 已收录的方法在对应源文件里的同名函数（MAP 见 coverage 工具）
  3. 从种子做闭包（函数名级，跨文件同名取并集 = 保守上界）
  4. 闭包内出现、但 gd_core 未收录的方法名 = **真缺口**（必须补）
     闭包外的方法 = 从任何判定入口都走不到 → 合法剥离

因为第 3 步是上界，闭包可能偏大；偏大只会「要求多补」，不会漏判，方向安全。

用法：
    python tools/gap_audit.py                # 闭包定裁 + 真缺口清单
    python tools/gap_audit.py --detail <名>  # 看某方法的调用点明细
"""
import os
import re
import sys
from collections import deque

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "decompiled_full")
CORE = os.path.join(ROOT, "gd_core")

# gd_core 文件 → 解包源码文件（与 tools/gd_core_coverage.py 的 MAP 保持一致）
MAP = {
    "CoreItem.gd":         "Items/Item.gd",
    "CoreCharacter.gd":    "Core/Character.gd",
    "CoreBuff.gd":         "Core/Buff.gd",
    "CoreCombatLog.gd":    "Core/CombatLog.gd",
    "CoreDamageSource.gd": "Utility/DamageSource.gd",
    "CoreDamageResult.gd": "Utility/DamageResult.gd",
    "CoreEvent.gd":        "Core/CombatEvent.gd",
}

FUNC_RE = re.compile(r"^func\s+([A-Za-z_]\w*)", re.M)
CALL_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
LINE_COMMENT = re.compile(r"#.*$")

# GDScript / Godot 内置名：不是待补方法，闭包遇到就当叶子
BUILTINS = {
    "if", "for", "while", "return", "match", "and", "or", "not", "in", "is",
    "assert", "print", "printerr", "printt", "push_error", "push_warning",
    "range", "str", "int", "float", "len", "abs", "min", "max", "round",
    "floor", "ceil", "sign", "pow", "sqrt", "sin", "cos", "tan", "atan2",
    "randf", "randi", "rand_range", "randf_range", "randi_range", "randomize",
    "seed", "typeof", "type_exists", "is_instance_valid", "weakref",
    "load", "preload", "yield", "funcref", "call", "funcref", "Vector2",
    "Vector3", "Color", "Rect2", "Array", "Dictionary", "PoolStringArray",
    "PoolIntArray", "PoolByteArray", "PoolVector2Array", "PoolRealArray",
    "PoolColorArray", "String", "Node", "Node2D", "Object", "Reference",
    "Resource", "scene", "self", "null", "true", "false",
}


def parse_calls():
    """→ {(文件相对路径, 顶层函数名): set(被调名)}, {函数名: [(文件, 行, 原文)]}"""
    graph = {}
    index = {}
    for dirpath, _dirs, files in os.walk(SRC):
        for fname in files:
            if not fname.endswith(".gd"):
                continue
            path = os.path.join(dirpath, fname)
            name = os.path.relpath(path, SRC).replace("\\", "/")
            try:
                with open(path, encoding="utf-8") as fh:
                    lines = fh.read().splitlines()
            except (OSError, UnicodeDecodeError):
                continue
            cur = None
            for i, line in enumerate(lines, 1):
                code = LINE_COMMENT.sub("", line)
                m = FUNC_RE.match(code)
                if m:
                    cur = m.group(1)
                    graph.setdefault((name, cur), set())
                    index.setdefault(cur, []).append((name, i, line.strip(), True))
                    continue
                if cur is None:
                    continue
                for m in CALL_RE.finditer(code):
                    callee = m.group(1)
                    graph[(name, cur)].add(callee)
                    if callee not in BUILTINS:
                        index.setdefault(callee, []).append((name, i, line.strip(), False))
    return graph, index


def funcs_of(path):
    try:
        with open(path, encoding="utf-8") as fh:
            return set(FUNC_RE.findall(fh.read()))
    except OSError:
        return set()


def coverage_sets():
    """→ (已收录名, 原版名, 缺口名)——按 MAP 逐对统计。"""
    covered, original = set(), set()
    for core_f, src_f in MAP.items():
        covered |= funcs_of(os.path.join(CORE, core_f))
        src_path = os.path.join(SRC, src_f.replace("/", os.sep))
        original |= funcs_of(src_path)
    return covered, original


def closure(graph, seeds, resolve_files, cap=200000):
    """受限可达闭包：被调名**只解析到 resolve_files 内的定义**。

    纯函数名级闭包太松——`_ready` / `_physics_process` 会经同名的 UI 函数把
    拖拽/粒子/tooltip 整棵子树拉成「可达」。本函数只认判定路径文件
    （Items/Item.gd、Core/Character.gd、Core/Buff.gd、Core/CombatLog.gd、
    Utility/Damage*.gd、Core/CombatEvent.gd）里的定义，
    于是「谁能调到这个方法」这个问题被限制在判定路径内部，UI 文件彻底不参与。
    """
    by_name = {}
    for (f, fn), callees in graph.items():
        by_name.setdefault(fn, []).append((f, fn, callees))

    def resolve(callee):
        return [n for n in by_name.get(callee, []) if n[0] in resolve_files]

    seen_names = set()
    seen_nodes = set()
    todo = deque()
    # 种子节点只**展开自身**，其名字不记为「被调用」——
    # 否则 Items/X.gd 里对 Item.gd 方法的**覆写**会被反向解析成「有人调了 Item.gd 的它」，
    # 把大批 UI/拖拽方法误判成可达。
    for f, fn in seeds:
        for node in by_name.get(fn, []):
            if node[0] != f:
                continue
            if node[:2] not in seen_nodes:
                seen_nodes.add(node[:2])
                todo.append(node)

    steps = 0
    while todo and steps < cap:
        _f, _fn, callees = todo.popleft()
        for callee in callees:
            if callee in seen_names:
                continue
            seen_names.add(callee)
            for node in resolve(callee):
                if node[:2] not in seen_nodes:
                    seen_nodes.add(node[:2])
                    todo.append(node)
            steps += 1
    return seen_names, steps


def _roots(graph):
    """种子分两类：
      A) gd_core 已收录方法 → 内核自己会走的路径
      B) 战斗驱动与物品行为（Core/Combat.gd + Items/**.gd，但 Items/Item.gd 除外）
         —— 它们调用的 Item/Character 方法就是内核**必须暴露**的 API 面
    """
    seeds = []
    for core_f, src_f in MAP.items():
        for fn in funcs_of(os.path.join(CORE, core_f)):
            seeds.append((src_f, fn))

    root_only = []
    for dirpath, _dirs, files in os.walk(os.path.join(SRC, "Items")):
        for fname in files:
            if fname.endswith(".gd"):
                rel_f = os.path.relpath(os.path.join(dirpath, fname), SRC).replace("\\", "/")
                if rel_f == "Items/Item.gd":
                    continue  # 它的非收录函数属 UI/拖拽，不能当根
                root_only.append(rel_f)
    root_only.append("Core/Combat.gd")

    for rel_f in root_only:
        path = os.path.join(SRC, rel_f.replace("/", os.sep))
        try:
            with open(path, encoding="utf-8") as fh:
                body = fh.read()
        except (OSError, UnicodeDecodeError):
            continue
        for fn in FUNC_RE.findall(body):
            seeds.append((rel_f, fn))
    return seeds


def main():
    args = sys.argv[1:]
    if args and args[0] == "--detail":
        _graph, index = parse_calls()
        for n in args[1:]:
            print("\n%s" % n)
            for c in index.get(n, [])[:14]:
                tag = "DEF " if c[3] else "    "
                print("  %s%s:%d  %s" % (tag, c[0], c[1], c[2][:100]))
        return 0

    if args and args[0] == "--reach":
        # 只回答「给定的一批名字是否落在判定路径闭包内」
        names = [s.strip() for a in args[1:] for s in a.split(",") if s.strip()]
        if not names:
            names = [s.strip() for s in sys.stdin.read().replace("\n", ",").split(",") if s.strip()]
        graph, _index = parse_calls()
        resolve_files = set(MAP.values())
        seeds = _roots(graph)
        reachable, _steps = closure(graph, seeds, resolve_files)
        inside = [n for n in names if n in reachable]
        outside = [n for n in names if n not in reachable]
        print("可达性定裁（%d 个待判名）" % len(names))
        print("=" * 78)
        print("\n[必须补] 落在判定路径闭包内：%d 项" % len(inside))
        for n in inside:
            print("  %s" % n)
        print("\n[合法剥离] 闭包不可达：%d 项" % len(outside))
        for n in outside:
            print("  %s" % n)
        return 0

    graph, _index = parse_calls()
    covered, original = coverage_sets()
    gaps = sorted(n for n in original - covered if not n.startswith("_"))
    missing_from_all = sorted(n for n in covered if n not in original)

    # 判定路径文件：被调名只会解析到这些文件里的定义（见 closure 的说明）
    resolve_files = set(MAP.values())
    seeds = _roots(graph)
    reachable, steps = closure(graph, seeds, resolve_files)

    reach_gaps = [n for n in gaps if n in reachable]
    stripped_gaps = [n for n in gaps if n not in reachable]
    # 关键词启发式漏判的真缺口：闭包内、原版有、连 MAP 之外的脚本（如 Items/*.gd、
    # Combat.gd）也算上，看闭包引入但 gd_core 全无的名字
    all_core_names = set()
    for f in os.listdir(CORE):
        if f.endswith(".gd"):
            all_core_names |= funcs_of(os.path.join(CORE, f))

    print("判定路径缺口的可达性定裁")
    print("=" * 78)
    print("种子 %d 个（gd_core 已收录方法在其源文件里的同名函数）" % len(seeds))
    print("闭包内函数名 %d 个，展开 %d 步" % (len(reachable), steps))
    print("MAP 覆盖的原版方法 %d 个，其中 gd_core 收录 %d 个，缺口 %d 个"
          % (len(original), len(original) - len(gaps), len(gaps)))
    print("（另有 %d 个方法 gd_core 里有、源文件里没有 —— 多为内核自有辅助，属正常）"
          % len(missing_from_all))

    print("\n[必须补] 缺口且可达：%d 项" % len(reach_gaps))
    for n in reach_gaps:
        print("  " + n)

    print("\n[合法剥离] 缺口但闭包不可达：%d 项" % len(stripped_gaps))
    for n in stripped_gaps:
        print("  " + n)

    # 闭包从 Items/**、Combat.gd 等引入、被判定路径真实调用、但 gd_core 完全没实现的名字
    extra = sorted(n for n in reachable
                   if n not in all_core_names and n not in BUILTINS
                   and not n.startswith("_") and len(n) > 2)
    print("\n[闭包引入、gd_core 全无的引用名] %d 个（含引擎/插件/内嵌类方法，需人工筛）"
          % len(extra))
    for n in extra[:80]:
        print("  " + n)
    if len(extra) > 80:
        print("  ... 另 %d 个（用 --detail <名> 逐个看）" % (len(extra) - 80))
    return 0


if __name__ == "__main__":
    sys.exit(main())
