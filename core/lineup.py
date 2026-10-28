# -*- coding: utf-8 -*-
"""lineup.py — ItemInfo 列表 → 模拟器 v4 平铺阵容的唯一实现

此前这段逻辑有两份副本（combatlog_exporter._v4_lineup 与
gui/app._on_export_lineup），语料记录器又需要第三份；统一到这里，避免
三处几何/旋转口径漂移。

v4 格式（见 README「阵容格式」）::

    {"version": 4, "name": ..., "character": "Ranger", "round": 12,
     "grid": [7, 9], "items": [
        {"id": "Leather Bag", "at": [3, 3], "r": 0},
        {"id": "Bow and Arrow", "at": [3, 3], "r": 0, "in": 0,
         "gems": ["Chipped Ruby"]}]}

约定
----
* `at` = 旋转后占格左上角 `(row, col)`；无 cells 时退回 ItemInfo 的
  `row/col`（袋内物品 compute_grid=False，恒为 None → 落 (0,0)，由 `in`
  表达归属）。
* `r` = 度 0/90/180/270（ItemInfo.rotation 弧度 → 90 度取整）。
* `in` = 承载袋在 `items` 数组里的下标（袋内物品显式化）。
* `gems` = 宝石 id 列表，无宝石则省略该键（与真值实录一致）。
* 编码层（ai/encoding.py）只装配无 `in` 的根物品；此处不改变这一语义。

对外函数
--------
* `rotation_deg(it)`      —— ItemInfo → 0/90/180/270
* `anchor_cell(it)`       —— ItemInfo → (row, col)
* `gems_of(it)`           —— ItemInfo → [gem id, ...]
* `to_v4(items, ...)`     —— ItemInfo 列表 → v4 dict（含袋内递归）
* `item_signature(it)`    —— 差分用规范键 (id, row, col, r, gems, in)
* `flatten_v4(lineup)`    —— v4 → [(id, row, col, r, tuple(gems), parent_idx)]
* `lineup_key(lineup)`    —— v4 的多重集规范串（去重/比对用）
"""
from __future__ import annotations

import math
from typing import Any, Dict, Iterable, List, Optional, Tuple

DEFAULT_GRID = (7, 9)


def rotation_deg(it: dict) -> int:
    """ItemInfo.rotation（弧度）→ 度，归一化到 0/90/180/270。

    非 90 度倍数（拖动中的中间角度、读取抖动）按最近的 90 度取整，
    与既有导出实现逐字一致。
    """
    try:
        rot = float(it.get("rotation", 0.0) or 0.0)
    except (TypeError, ValueError):
        return 0
    if not math.isfinite(rot):
        return 0
    deg = int(round(rot * 180.0 / math.pi / 90.0) * 90) % 360
    return deg


def anchor_cell(it: dict) -> Tuple[int, int]:
    """物品锚点格 (row, col)：优先用占格并集的左上角，否则退回 row/col。"""
    cells = it.get("cells") or []
    if cells:
        try:
            return (int(min(r for r, _ in cells)), int(min(c for _, c in cells)))
        except (TypeError, ValueError):
            pass
    try:
        return (int(it.get("row") or 0), int(it.get("col") or 0))
    except (TypeError, ValueError):
        return (0, 0)


def gems_of(it: dict) -> List[str]:
    return [g.get("id") for g in (it.get("gems") or []) if g and g.get("id")]


def _entry(it: dict, bag_index: Optional[int] = None) -> dict:
    row, col = anchor_cell(it)
    e: Dict[str, Any] = {
        "id": it.get("name", ""),
        "at": [row, col],
        "r": rotation_deg(it),
    }
    if bag_index is not None:
        e["in"] = bag_index
    gems = gems_of(it)
    if gems:
        e["gems"] = gems
    return e


def to_v4(items: Optional[Iterable[dict]], character: str = "Adventurer",
          round_num: Optional[int] = None, name: str = "",
          grid: Tuple[int, int] = DEFAULT_GRID) -> dict:
    """ItemInfo 列表 → v4 阵容。袋内物品递归展开并用 `in` 指向承载袋下标。"""
    out: List[dict] = []

    def walk(it: dict, bag_index: Optional[int] = None) -> None:
        out.append(_entry(it, bag_index))
        sub = len(out) - 1
        for child in (it.get("contents") or []):
            walk(child, bag_index=sub)

    for it in (items or []):
        if isinstance(it, dict):
            walk(it)

    return {
        "version": 4,
        "name": name or "对局实录",
        "character": character or "Adventurer",
        "round": int(round_num) if round_num is not None else 1,
        "grid": [int(grid[0]), int(grid[1])],
        "items": out,
    }


def item_signature(it: dict, parent_idx: Optional[int] = None) -> Tuple:
    """差分用的规范键：同一物品在不同帧里键相同即可判定"还是那一件"。

    实例身份刻意不含节点地址：背包格子互斥使 (id, at, r, gems, in) 在实践中
    足够唯一，而节点地址会随重建/复用漂移且无法落盘（见 docs/recorder_design.md §5）。
    """
    row, col = anchor_cell(it)
    return (
        str(it.get("name", "")),
        int(row), int(col), int(rotation_deg(it)),
        tuple(sorted(gems_of(it))),
        -1 if parent_idx is None else int(parent_idx),
    )


def flatten_v4(lineup: dict) -> List[Tuple[str, int, int, int, Tuple[str, ...], int]]:
    """v4 阵容 → 规范元组列表（供多重集比对/折叠）。

    返回 [(id, row, col, r, gems, in), ...]，`in` 缺省为 -1。
    """
    out: List[Tuple[str, int, int, int, Tuple[str, ...], int]] = []
    for e in (lineup.get("items") or []):
        if not isinstance(e, dict):
            continue
        at = e.get("at") or [0, 0]
        try:
            row, col = int(at[0]), int(at[1])
        except (TypeError, ValueError, IndexError):
            row, col = 0, 0
        try:
            rot = int(e.get("r", 0) or 0) % 360
        except (TypeError, ValueError):
            rot = 0
        gems = tuple(sorted(e.get("gems") or []))
        parent = e.get("in")
        out.append((str(e.get("id", "")), row, col, rot, gems,
                    -1 if parent is None else int(parent)))
    return out


def lineup_key(lineup: dict) -> str:
    """v4 的多重集规范串：排序后拼接，用于"阵容是否变化"的快速判等。"""
    flat = flatten_v4(lineup)
    flat.sort()
    return "|".join("%s@%d,%d/r%d/g%s/%s" % (i, r, c, rot, ",".join(g), p)
                    for (i, r, c, rot, g, p) in flat)


def lineup_from_flat(flat: List[Tuple], character: str = "Adventurer",
                     round_num: Optional[int] = None,
                     grid: Tuple[int, int] = DEFAULT_GRID) -> dict:
    """规范元组列表 → v4（折叠层/测试用，与 flatten_v4 互逆）。"""
    items: List[dict] = []
    for (i, row, col, rot, gems, parent) in flat:
        e: Dict[str, Any] = {"id": i, "at": [int(row), int(col)], "r": int(rot) % 360}
        if parent is not None and int(parent) >= 0:
            e["in"] = int(parent)
        if gems:
            e["gems"] = list(gems)
        items.append(e)
    return {
        "version": 4,
        "name": "折叠阵容",
        "character": character or "Adventurer",
        "round": int(round_num) if round_num is not None else 1,
        "grid": [int(grid[0]), int(grid[1])],
        "items": items,
    }
