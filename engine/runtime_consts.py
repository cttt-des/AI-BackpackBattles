# -*- coding: utf-8 -*-
"""engine/runtime_consts.py — 行为代码可见常量的运行时单一真源

codegen 与生成模块共同引用；合并旧全局表的真值枚举/类（纯数据/函数）
与新命名空间表。过渡期复用 simulator.behavior.BEHAVIOR_GLOBALS 的实现，
后续逐项内联。
"""
from __future__ import annotations

from .namespaces import make_constant_table

_CACHE = None


def build_constants() -> dict:
    global _CACHE
    if _CACHE is not None:
        return _CACHE
    from simulator.behavior import BEHAVIOR_GLOBALS as _OLD
    table = dict(_OLD)
    table.update(make_constant_table({}))
    for k in ("Game", "EventBus", "Util", "ItemBook", "descriptor", "placed",
              "me", "sprite", "data"):
        table.pop(k, None)          # 战斗上下文面（经 _item.ctx 访问）
    _CACHE = table
    return table
