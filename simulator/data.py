# -*- coding: utf-8 -*-
"""data.py — 加载物品/角色 JSON 数据（对齐 docs/simulator_architecture.md §3）"""
from __future__ import annotations

import json
import os
import sys
from typing import Any, Dict, Optional

# 资源目录解析：开发态指向仓库 assets/；冻结态（PyInstaller --onefile）
# 指向临时解包目录 sys._MEIPASS 下的 assets/。
if getattr(sys, 'frozen', False):
    _BASE = getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(sys.executable)))
else:
    _BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASSETS = os.path.join(_BASE, 'assets')


def _load_json(path: str) -> Dict[str, Any]:
    with open(path, encoding='utf-8') as f:
        return json.load(f)


def load_items() -> Dict[str, Dict[str, Any]]:
    """返回 {item_key: item_data}（battle_items.json）"""
    data = _load_json(os.path.join(ASSETS, 'battle_items.json'))
    items = data.get('items', data)
    out = {}
    for k, v in items.items():
        d = dict(v)
        d.setdefault('key', k)
        out[k] = d
    return out


def load_characters() -> Dict[str, Dict[str, Any]]:
    """返回 {character_key: character_data}（characters.json）"""
    data = _load_json(os.path.join(ASSETS, 'characters.json'))
    chars = data.get('characters', data)
    out = {}
    for k, v in chars.items():
        d = dict(v)
        d.setdefault('key', k)
        out[k] = d
    return out


def get_item(key: str) -> Dict[str, Any]:
    return load_items()[key]


def get_character(key: str) -> Dict[str, Any]:
    return load_characters()[key]


def items_to_list(item_names) -> list:
    """把物品名列表转成物品数据列表（兼容旧接口）"""
    db = load_items()
    out = []
    for n in item_names:
        if n in db:
            d = dict(db[n])
            d['key'] = n
            out.append(d)
    return out
