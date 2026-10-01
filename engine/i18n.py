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
# ★ spikes 的游戏内显示名为「尖刺」（CombatLog_*.zh.txt 实测），非「反伤」。
_ORIGIN_ZH = {
    "spikes": "尖刺", "Spikes": "尖刺", "poison": "中毒", "Poison": "中毒",
    "fatigue": "疲劳", "Fatigue": "疲劳", "unhealing": "不治", "Unhealing": "不治",
    "Vampirism": "吸血", "Regeneration": "再生", "Block": "格挡",
    "poison_tick": "中毒", "spike": "尖刺",
}

# 物品运行时显示名覆盖：battle_items.json 的 zh 提取自翻译资源，个别条目与
# 游戏实际显示名（getTranslatedName，经内存导出战报实测）不一致。以下键值
# 逐一对过游戏导出日志（dist/output/combat_logs/CombatLog_*.json 的 origin.zh）。
_RUNTIME_ZH_OVERRIDE = {
    "Crown": "辉耀王冠",
    "Evil Cap": "腐败头盔",
    "Amulet of Agility": "能量护符",
    "Joker": "小丑牌",
    "Berserker Bag": "旅行包",
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
    if key in _RUNTIME_ZH_OVERRIDE:
        return _RUNTIME_ZH_OVERRIDE[key]
    if key in _ZH_MAP:
        return _ZH_MAP[key]
    return _ORIGIN_ZH.get(key, key)
