# -*- coding: utf-8 -*-
"""lineup.py — 阵容 JSON 加载与校验（对齐 docs/simulator_architecture.md §2）

阵容格式 v4（简洁版，推荐）：
{
  "version": 4,
  "name": "...",
  "character": "Ranger",
  "round": 5,
  "grid": [7, 10],
  "items": [
    {"id": "Leather Bag", "at": [3, 3], "r": 0},
    {"id": "Bow and Arrow", "at": [3, 3], "r": 0, "in": 0, "gems": ["Chipped Ruby"]}
  ],
  "class_modifiers": {"health": 25, "stamina": 5, "stamina_regen": 1.0, "gold": 13},
  "health_override": null,
  "storage": []
}
  * `in` = 承载袋在 items 数组中的下标（省略 = 袋外松放）——物品与背包的
    承载关系显式化，模拟器据此建立袋内联动（Bag.gd getItemsInside 语义）
  * `at` = [row, col]（旋转后占格左上角，对齐游戏 topLeftCell 存档语义）
  * `r` = 旋转角度（0/90/180/270，默认 0）；`gems` = 宝石 id 字符串数组
  * meta 拍平为 `name`；class_modifiers/health_override/storage 可选

load 时 v4 规范化为内部表示（v3 形状：backpack.items + 嵌套 contents），
v1/v2/v3 原样通过 —— 引擎与工具链只面对内部形状。

阵容文件 v3 格式（仍完全兼容）：
{
  "version": 3,
  "meta": {"name": "...", "source": "gui_export|manual"},
  "character": "Ranger",
  "round": 5,
  "class_modifiers": {"health": 25, "stamina": 5, "stamina_regen": 1.0, "gold": 13},
  "health_override": null,
  "backpack": {"grid": {"rows": 7, "cols": 10}, "items": [...]},
  "storage": []
}
"""
from __future__ import annotations

import json
import os
from typing import Any, Dict, List, Optional


class LineupError(Exception):
    pass


def load_lineup(path: str) -> Dict[str, Any]:
    """加载并校验阵容 JSON；v4 规范化为内部（v3 形状）表示"""
    if not os.path.exists(path):
        raise LineupError(f"阵容文件不存在: {path}")
    try:
        with open(path, encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        raise LineupError(f"阵容文件 JSON 解析失败: {path}: {e}")

    if isinstance(data, dict) and int(data.get('version') or 0) >= 4:
        data = _normalize_v4(data, path)
    _validate(data, path)
    return data


def _normalize_v4(data: Dict[str, Any], path: str) -> Dict[str, Any]:
    """v4 平铺格式 -> 内部 v3 形状（backpack.items + 嵌套 contents）"""
    if not isinstance(data.get('items'), list):
        raise LineupError(f"{path}: v4 阵容缺少 items 数组")
    raw = data['items']
    grid = data.get('grid') or [7, 10]

    entries: List[Dict[str, Any]] = []
    for i, it in enumerate(raw):
        if not isinstance(it, dict) or not it.get('id'):
            raise LineupError(f"{path}: items[{i}] 缺少 id")
        at = it.get('at') or [0, 0]
        entries.append({
            'id': it['id'],
            'row': int(at[0]),
            'col': int(at[1]),
            'rotation': int(it.get('r', 0) or 0) % 360,
            'quantity': 1,
            'container': False,
            'contents': [],
            'gems': [{'id': g} for g in (it.get('gems') or [])],
        })
    # 承载关系：in 指向袋子的数组下标（仅一层检查，深层由袋子自身的 in 链表达）
    for i, it in enumerate(raw):
        parent = it.get('in')
        if parent is None:
            continue
        if not isinstance(parent, int) or parent == i or parent < 0 or parent >= len(raw):
            raise LineupError(f"{path}: items[{i}].in={parent!r} 非法（须为其他物品的下标）")
        entries[parent]['contents'].append(entries[i])
        entries[parent]['container'] = True
    roots = [e for i, e in enumerate(entries) if raw[i].get('in') is None]

    meta = data.get('meta') or {'name': data.get('name') or
                                os.path.splitext(os.path.basename(path))[0],
                                'source': 'v4'}
    return {
        'version': 3,
        'meta': meta,
        'character': data.get('character'),
        'round': data.get('round') if data.get('round') is not None else 1,
        'class_modifiers': data.get('class_modifiers') or {},
        'health_override': data.get('health_override'),
        'backpack': {
            'grid': {'rows': int(grid[0]), 'cols': int(grid[1])},
            'items': roots,
        },
        'storage': data.get('storage') or [],
    }


def to_v4(data: Dict[str, Any]) -> Dict[str, Any]:
    """内部（v3 形状）表示 -> v4 平铺格式（导出/写回用）"""
    flat: List[Dict[str, Any]] = []

    def walk(entries: List[Dict], bag_index: Optional[int]):
        for e in entries:
            item: Dict[str, Any] = {
                'id': e.get('id'),
                'at': [int(e.get('row', 0)), int(e.get('col', 0))],
                'r': int(e.get('rotation', 0) or 0),
            }
            if bag_index is not None:
                item['in'] = bag_index
            if e.get('gems'):
                item['gems'] = [g.get('id') if isinstance(g, dict) else g
                                for g in e['gems']]
            flat.append(item)
            walk(e.get('contents') or [], len(flat) - 1)

    bp = data.get('backpack') or {}
    grid = bp.get('grid') or {'rows': 7, 'cols': 10}
    walk(bp.get('items') or [], None)
    out: Dict[str, Any] = {
        'version': 4,
        'name': (data.get('meta') or {}).get('name')
                or os.path.splitext(os.path.basename(str(data.get('_path', ''))))[0]
                or 'lineup',
        'character': data.get('character'),
    }
    if data.get('round') is not None:
        out['round'] = data['round']
    out['grid'] = [int(grid.get('rows', 7)), int(grid.get('cols', 10))]
    out['items'] = flat
    for k in ('class_modifiers', 'health_override', 'storage'):
        if data.get(k) is not None:
            out[k] = data[k]
    return out


def _validate(data: Dict[str, Any], path: str):
    if not isinstance(data, dict):
        raise LineupError(f"{path}: 阵容必须是 JSON 对象")
    version = data.get('version')
    if version is None:
        # 兼容 v2（GUI 早期导出，无 version 字段）
        pass
    elif int(version) < 2:
        raise LineupError(f"{path}: 不支持的版本 v{version}（需要 v2+）")

    if not data.get('character'):
        raise LineupError(f"{path}: 缺少 character 字段")
    if 'backpack' not in data or not isinstance(data.get('backpack'), dict):
        raise LineupError(f"{path}: 缺少 backpack 字段")
    items = data['backpack'].get('items', [])
    if not isinstance(items, list):
        raise LineupError(f"{path}: backpack.items 必须是数组")

    for i, it in enumerate(items):
        if not it.get('id'):
            raise LineupError(f"{path}: backpack.items[{i}] 缺少 id")
        if 'row' not in it or 'col' not in it:
            raise LineupError(f"{path}: backpack.items[{i}] 缺少 row/col")


def resolve_items(lineup: Dict[str, Any], item_db: Dict[str, Dict]):
    """解析阵容中的物品 key 列表（含容器递归），返回 (found, unknown)"""
    found = []
    unknown = []

    def walk(items: List[Dict]):
        for it in items:
            key = it.get('id')
            if key in item_db:
                found.append(key)
            else:
                unknown.append(key)
            for sub in (it.get('contents') or []):
                walk([sub])

    walk(lineup.get('backpack', {}).get('items', []))
    return found, unknown


def make_lineup(character: str = "Adventurer", items: Optional[List[Dict]] = None,
                round_: int = 1, name: str = "", source: str = "manual",
                class_modifiers: Optional[Dict] = None,
                health_override: Optional[float] = None) -> Dict[str, Any]:
    """构造一个阵容字典（便于测试与示例生成）"""
    return {
        "version": 3,
        "meta": {"name": name, "source": source},
        "character": character,
        "round": round_,
        "class_modifiers": class_modifiers or {},
        "health_override": health_override,
        "backpack": {
            "grid": {"rows": 7, "cols": 10},
            "items": items or [],
        },
        "storage": [],
    }
