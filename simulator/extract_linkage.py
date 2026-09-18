# -*- coding: utf-8 -*-
"""extract_linkage.py — 物品联动（Affected）专项提取器

真值源：decompiled_full/Items/**.gd（GDEC 解密后的 GDScript）。

原版联动机制（对齐 Items/Item.gd）：
  * 影响格分四色：Affected.Primary=0 / Secondary=2 / Tertiary=4 / Lightning=7
  * 影响格来源 = tscn 的 Affected tile（已入 grid.affected_*）
                + 脚本覆写 getAffectedCellsAfterRotate_primary/_secondary
  * 过滤：canAffect / canAffect_secondary / canAffect_tertiary / canAffect_lightning
          （按颜色分发，见 canAffect_color）；canAffect_global 为无视位置的全局联动
  * 回调：onAffectedItemAdded / onAffectedItemRemoved（放置/移除/类型变化时触发）
  * 标志：affectsEmpty / isAffectingDistinct
  * 行列：getRelatedItemColumns（同类目按列联动，如护符/Badge 系）

继承：GDScript 用 extends 继承，基类脚本也定义联动方法（如 Potion.gd 定义
canAffect + getAffectedCellsAfterRotate_primary，Food.gd 定义 canAffect，
Bag.gd 定义袋内联动）。因此提取时必须沿 extends 链向上解析：自身覆写优先，
否则继承最近祖先的实现。链在 Item 处停止（Item.gd 即引擎的 Item 类本身，
其方法已由 simulator/item.py 原生实现，不作为行为脚本入库）。

本脚本职责：
  1. 扫描物品脚本（含继承链），识别联动方法及其来源
  2. 与已入库的 tscn 影响格（grid.affected_*）合并，生成 linkage 元数据
  3. 以**增量**方式把联动方法写回 battle_items.json 的 behavior（不动其余方法），
     并写入 linkage 元数据；写库前自动备份

用法：
  python -m simulator.extract_linkage --report    # 只统计，不写库
  python -m simulator.extract_linkage --apply     # 增量写库（自动 .bak 备份）
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import sys
from datetime import datetime
from typing import Dict, List, Optional, Set, Tuple

from . import extract_items as E

DB_PATH = E.DB_PATH

# ---------------- 联动方法分类（真值源：Items/Item.gd） ----------------
# 按颜色分发的判定方法
JUDGE_METHODS = ("canAffect", "canAffect_secondary",
                 "canAffect_tertiary", "canAffect_lightning")
# 无视位置的全局判定
GLOBAL_METHODS = ("canAffect_global",)
# 放置/移除时的联动回调
CALLBACK_METHODS = ("onAffectedItemAdded", "onAffectedItemRemoved",
                    "onAffectedItemInsideAdded", "onAffectedItemInsideRemoved")
# 脚本补充的影响格（旋转后计算）
CELLS_METHODS = ("getAffectedCellsAfterRotate_primary",
                 "getAffectedCellsAfterRotate_secondary")
# 影响格语义标志
FLAG_METHODS = ("affectsEmpty", "isAffectingDistinct")
# 行列联动
RELATED_METHODS = ("getRelatedItemColumns", "getRelatedItemRows")

LINKAGE_METHODS = (JUDGE_METHODS + GLOBAL_METHODS + CALLBACK_METHODS +
                   CELLS_METHODS + FLAG_METHODS + RELATED_METHODS)

# 颜色 -> (判定方法, grid 字段名, 元数据名)
COLOR_SPEC = {
    0: ("canAffect", "affected_cells", "primary"),
    2: ("canAffect_secondary", "affected_secondary", "secondary"),
    4: ("canAffect_tertiary", "affected_tertiary", "tertiary"),
    7: ("canAffect_lightning", "affected_lightning", "lightning"),
}

# 继承链最大深度（防 extends 成环）
MAX_CHAIN_DEPTH = 8

_BEH_CACHE: Dict[str, Optional[dict]] = {}
_ANCESTORS: Dict[str, dict] = {}
_PARSE_CACHE: Dict[str, dict] = {}


def behavior_of(path: str) -> Optional[dict]:
    """带缓存地转译一个脚本（build_behavior 对同一基类会被多个物品复用）。"""
    if path not in _BEH_CACHE:
        try:
            _BEH_CACHE[path] = E.build_behavior(path, ancestor_entries=_ANCESTORS)
        except Exception as e:  # noqa: BLE001
            print(f"  [PARSE ERR] {os.path.basename(path)}: {e}")
            _BEH_CACHE[path] = None
    return _BEH_CACHE[path]


def resolve_script(key: str, item: dict, idx: Dict[str, str]) -> Optional[str]:
    """定位物品对应的 .gd 脚本（与 regen_behaviors.py 相同的匹配策略）。"""
    scr = item.get("script")
    sp = None
    if scr:
        norm = (scr[:-3].lower().replace(" ", "") if scr.endswith(".gd")
                else scr.lower().replace(" ", ""))
        sp = idx.get(norm)
    if sp is None:
        sp = E.match_script_key(key, idx)
    return sp


def script_chain(sp: str, idx: Dict[str, str]) -> List[Tuple[str, dict]]:
    """沿 extends 链收集 [(脚本路径, 该脚本的方法字典), ...]，自身在前、祖先在后。

    到 Item 为止：Item.gd 的方法由 simulator/item.py 原生实现，不入库。
    """
    chain: List[Tuple[str, dict]] = []
    cur = sp
    seen: Set[str] = set()
    for _ in range(MAX_CHAIN_DEPTH):
        if not cur or cur in seen:
            break
        seen.add(cur)
        if cur in _PARSE_CACHE:
            ext, methods = _PARSE_CACHE[cur]
        else:
            try:
                ext, _iv, _or, _td, methods = E.parse_script(cur)
            except Exception:  # noqa: BLE001
                ext, methods = None, {}
            _PARSE_CACHE[cur] = (ext, methods)
        chain.append((cur, methods))
        if not ext or ext == "Item":
            break
        cur = idx.get(str(ext).lower())
    return chain


def collect_linkage(sp: str, idx: Dict[str, str]) -> Dict[str, dict]:
    """汇总物品可用的联动方法（自身覆写优先，否则继承最近祖先）。

    返回 {方法名: {"src": python源码 或 "raw": 原文, "owner": 来源脚本名,
                   "own": 是否自身覆写}}
    """
    chain = script_chain(sp, idx)
    out: Dict[str, dict] = {}
    # 从最远祖先向自身遍历：近的覆盖远的
    for path, methods in reversed(chain):
        beh = behavior_of(path)
        if not beh:
            continue
        base = os.path.basename(path)
        for m in LINKAGE_METHODS:
            if m not in methods:
                continue
            if m in beh["methods"]:
                out[m] = {"src": beh["methods"][m], "owner": base,
                          "own": path == sp}
            elif m in beh["methods_raw"]:
                out[m] = {"raw": beh["methods_raw"][m], "owner": base,
                          "own": path == sp}
    return out


def build_linkage_meta(item: dict, methods: Dict[str, dict]) -> dict:
    """生成 linkage 元数据：脚本继承链 + tscn 影响格的合并视图。"""
    grid = item.get("grid") or {}
    colors = {}
    for color, (judge_method, grid_key, name) in COLOR_SPEC.items():
        has_tile = bool(grid.get(grid_key))
        has_judge = judge_method in methods
        colors[name] = bool(has_tile or has_judge)

    overrides = sorted(m for m, info in methods.items() if info.get("own"))
    inherited = sorted(f"{m}<-{info['owner']}"
                       for m, info in methods.items() if not info.get("own"))

    return {
        "overrides": overrides,
        "inherited": inherited,
        "colors": colors,
        "script_affected": any(m in methods for m in CELLS_METHODS),
        "global": any(m in methods for m in GLOBAL_METHODS),
        "related_columns": any(m in methods for m in RELATED_METHODS),
        "callbacks": sorted(m for m in methods if m in CALLBACK_METHODS),
    }


def scan(idx: Dict[str, str], items: Dict[str, dict], verbose: bool = False):
    """扫描全部物品，返回 (统计, {物品: (脚本路径, 联动方法字典)})。"""
    stats = {m: [] for m in LINKAGE_METHODS}
    own_stats = {m: [] for m in LINKAGE_METHODS}
    per_item: Dict[str, Tuple[str, Dict[str, dict]]] = {}
    no_script: List[str] = []

    for key, item in items.items():
        sp = resolve_script(key, item, idx)
        if sp is None:
            no_script.append(key)
            continue
        methods = collect_linkage(sp, idx)
        per_item[key] = (sp, methods)
        for m, info in methods.items():
            stats[m].append(key)
            if info.get("own"):
                own_stats[m].append(key)

    if verbose:
        print(f"无脚本物品: {len(no_script)}（示例 {no_script[:8]}）")
    return stats, own_stats, per_item, no_script


def report(stats, own_stats, per_item, items):
    print("=" * 70)
    print("联动方法统计（真值源 decompiled_full/Items/**.gd，含 extends 继承）")
    print("=" * 70)
    print(f"  {'方法':<40}{'自身':>6}{'可用':>6}   示例")
    for m in LINKAGE_METHODS:
        own_n, all_n = len(own_stats[m]), len(stats[m])
        if not all_n:
            print(f"  {m:<40}{own_n:>6}{all_n:>6}")
            continue
        print(f"  {m:<40}{own_n:>6}{all_n:>6}   {', '.join(stats[m][:5])}")
    print("-" * 70)
    with_own = sum(1 for _sp, ms in per_item.values()
                   if any(i.get("own") for i in ms.values()))
    with_inh = sum(1 for _sp, ms in per_item.values()
                   if any(not i.get("own") for i in ms.values()))
    with_tile = sum(1 for v in items.values()
                    if any(k.startswith("affected") for k in (v.get("grid") or {})))
    with_any = sum(1 for k, (_s, ms) in per_item.items()
                   if ms or any(x.startswith("affected")
                                for x in (items[k].get("grid") or {})))
    print(f"  自身覆写联动方法的物品: {with_own}")
    print(f"  仅继承联动方法的物品:   {with_inh}")
    print(f"  tscn 带影响格的物品:    {with_tile}")
    print(f"  参与联动的物品合计:     {with_any}")
    print("=" * 70)


def apply(items: Dict[str, dict], per_item) -> dict:
    """增量写入：只更新联动相关方法与 linkage 元数据，保留其余字段。"""
    changed_methods = 0
    changed_meta = 0
    raw_fallback: List[str] = []

    for key, (sp, methods) in per_item.items():
        item = items[key]
        bm = item.setdefault("behavior", {})
        ms = bm.setdefault("methods", {})
        raw = bm.setdefault("methods_raw", {})

        for m in LINKAGE_METHODS:
            info = methods.get(m)
            if info is None:
                if m in ms:
                    ms.pop(m)
                    changed_methods += 1
                if m in raw:
                    raw.pop(m)
                continue
            if "src" in info:
                if ms.get(m) != info["src"]:
                    changed_methods += 1
                ms[m] = info["src"]
                raw.pop(m, None)
            else:
                # 转译失败：保留原文供审计，且不残留可执行的旧版本
                raw[m] = info["raw"]
                if m in ms:
                    ms.pop(m)
                    changed_methods += 1
                raw_fallback.append(f"{key}.{m}")

        meta = build_linkage_meta(item, methods)
        if item.get("linkage") != meta:
            changed_meta += 1
        item["linkage"] = meta

    print(f"  联动方法变更: {changed_methods}   元数据变更: {changed_meta}")
    if raw_fallback:
        print(f"  转译失败(存 methods_raw): {len(raw_fallback)} -> {raw_fallback[:10]}")
    return {"methods_changed": changed_methods, "meta_changed": changed_meta,
            "raw": raw_fallback}


def main(argv=None):
    ap = argparse.ArgumentParser(description="物品联动（Affected）专项提取器")
    ap.add_argument("--report", action="store_true", help="只统计，不写库")
    ap.add_argument("--apply", action="store_true", help="增量写库（自动备份）")
    ap.add_argument("--no-backup", action="store_true", help="写库时不备份")
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args(argv)

    if not args.report and not args.apply:
        args.report = True

    print(f"数据库: {DB_PATH}")
    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    idx = E.scan_scripts()
    print(f"脚本索引: {len(idx)}   物品: {len(items)}")

    stats, own_stats, per_item, no_script = scan(idx, items, verbose=args.verbose)

    if args.report:
        report(stats, own_stats, per_item, items)
        return 0

    if not args.no_backup:
        stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        bak = f"{DB_PATH}.bak_{stamp}"
        shutil.copy2(DB_PATH, bak)
        print(f"已备份: {bak}")

    print("写入中...")
    res = apply(items, per_item)

    json.dump(db, open(DB_PATH, "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)
    print(f"已写出 {DB_PATH}")
    print(f"完成: {res['methods_changed']} 个方法变更, "
          f"{res['meta_changed']} 个元数据变更")
    return 0


if __name__ == "__main__":
    sys.exit(main())
