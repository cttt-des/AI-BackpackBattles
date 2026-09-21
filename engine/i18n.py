# -*- coding: utf-8 -*-
"""i18n.py — 物品名国际化（游戏官方中文翻译）

中文名来源：battle_items.json 的 zh 字段（extracted 的 PHashTranslation
zh_Hans_CN 经提取确认，见 tools/update_zh_names.py）。日志渲染用。
"""
from __future__ import annotations
import json
import os

_ZH_MAP = None
_LOADED = False

# 非物品 origin 标签的中文（伤害来源）
_ORIGIN_ZH = {
    "spikes": "反伤", "Spikes": "反伤", "poison": "中毒", "Poison": "中毒",
    "fatigue": "疲劳", "Fatigue": "疲劳", "unhealing": "不治", "Unhealing": "不治",
    "Vampirism": "吸血", "Regeneration": "再生", "Block": "格挡",
    "poison_tick": "中毒", "spike": "反伤",
}


def _load():
    global _ZH_MAP, _LOADED
    if _LOADED:
        return
    _LOADED = True
    _ZH_MAP = {}
    path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                        "assets", "battle_items.json")
    try:
        with open(path, encoding="utf-8") as f:
            db = json.load(f)
        items = db.get("items", db)
        for k, v in items.items():
            zh = v.get("zh")
            if zh and zh != k:
                _ZH_MAP[k] = zh
    except Exception:
        pass


def zh_name(key: str) -> str:
    """物品/来源中文名；无翻译时返回英文"""
    _load()
    if not key:
        return key
    if key in _ZH_MAP:
        return _ZH_MAP[key]
    return _ORIGIN_ZH.get(key, key)
