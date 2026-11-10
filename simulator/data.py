# -*- coding: utf-8 -*-
"""data.py — 加载物品/角色 JSON 数据（对齐 docs/simulator_architecture.md §3）"""
from __future__ import annotations

import json
import os
import sys
from typing import Any, Dict, Optional

# 资源目录解析（三种形态都要能找到 assets/）：
#   ① frozen（PyInstaller --onefile）→ sys._MEIPASS/assets
#   ② 开发态（仓库根）→ <repo>/assets
#   ③ pip 安装（wheel）→ 依次尝试 <site-packages>/assets、<sys.prefix>/assets
#   ④ 显式覆盖：BACKPACK_ASSETS 环境变量（训练脚本可自定义数据目录）
def _resolve_assets() -> str:
    cands = []
    env = os.environ.get("BACKPACK_ASSETS")
    if env:
        cands.append(env)
    if getattr(sys, 'frozen', False):
        cands.append(os.path.join(
            getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(sys.executable))),
            'assets'))
    _here = os.path.dirname(os.path.abspath(__file__))
    cands.append(os.path.join(os.path.dirname(_here), 'assets'))      # 开发态
    cands.append(os.path.join(_here, 'assets'))                       # 包内 assets
    cands.append(os.path.join(sys.prefix, 'assets'))                  # wheel data-files
    cands.append(os.path.join(sys.base_prefix, 'assets'))
    for c in cands:
        if c and os.path.isdir(c):
            return c
    return cands[0] if cands else os.path.join(_here, 'assets')


_BASE = os.path.dirname(_resolve_assets())
ASSETS = _resolve_assets()


def _load_json(path: str) -> Dict[str, Any]:
    with open(path, encoding='utf-8') as f:
        return json.load(f)


def load_items() -> Dict[str, Dict[str, Any]]:
    """返回 {item_key: item_data}（battle_items.json）"""
    data = _load_json(os.path.join(ASSETS, 'battle_items.json'))
    items = data.get('items', data)
    # 基类行为池（GDScript 继承链）：注入 behavior 执行器，供 extends_chain 解析
    from . import behavior as _behavior
    _behavior.set_class_methods(data.get('class_methods'))
    # 物品名 → Rarity 枚举数值（Item.gd 148：Common=0…Unique=5），
    # 供 ItemBook.getDescriptor().getRarity 等行为侧查询
    _behavior.set_rarity_table({
        k: _RARITY_ENUM.get(v.get('rarity'), 0) for k, v in items.items()
    })
    out = {}
    for k, v in items.items():
        d = dict(v)
        d.setdefault('key', k)
        out[k] = d
    return out


_RARITY_ENUM = {
    'Common': 0, 'Rare': 1, 'Epic': 2, 'Legendary': 3, 'Godly': 4, 'Unique': 5,
}


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


def is_bag_data(item_data: Optional[Dict[str, Any]]) -> bool:
    """物品数据是否为背包/袋子类（占 bags 底层，物品可叠其上）。

    判定 = category=='bag'（与 types 含 'bag' 等价，已核验两集合相同）。
    依据反编译源码：decompiled_full/Items 下 extends Bag 的 24 个物品脚本
    + 直接用 Bag.gd 基类的 Leather Bag + FannyPack/PotionBelt（字符串路径
    继承，grep 'extends Bag' 搜不到）= 27 个，与 category=='bag' 名单完全一致。
    """
    if not item_data:
        return False
    return item_data.get('category') == 'bag' or 'bag' in (item_data.get('types') or [])


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
