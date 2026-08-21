# -*- coding: utf-8 -*-
"""lineup.py — 阵容 JSON 加载与校验（对齐 docs/simulator_architecture.md §2）

阵容文件 v3 格式：
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
    """加载并校验阵容 JSON"""
    if not os.path.exists(path):
        raise LineupError(f"阵容文件不存在: {path}")
    try:
        with open(path, encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        raise LineupError(f"阵容文件 JSON 解析失败: {path}: {e}")

    _validate(data, path)
    return data


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
