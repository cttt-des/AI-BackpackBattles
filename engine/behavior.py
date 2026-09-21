# -*- coding: utf-8 -*-
"""engine/behavior.py — 行为执行器（新架构）

与旧架构的区别：
* 方法函数来自**编译期生成的模块**（engine/gen/behaviors.py 的 FUNCS 注册表），
  import 常驻、跨场复用——不再运行时 exec 字符串。
* 未知名字在代码生成期即报错（fail-fast）；无 _SafeDict/_Noop 兜底。
* 运行期异常不再静默：全部计入 failures（非致命，战斗继续），可在战报观测。
"""
from __future__ import annotations

from typing import Any, Dict, Optional


def _load_gen():
    """惰性加载生成模块（首次生成前 FUNCS 为空）"""
    from .gen import behaviors as _gen
    return _gen


class _FuncTable:
    """FUNCS/METAS 的惰性代理（生成模块存在后透明转发）"""

    def __init__(self, attr: str):
        self._attr = attr

    def __getitem__(self, key):
        return getattr(_load_gen(), self._attr)[key]

    def get(self, key, default=None):
        return getattr(_load_gen(), self._attr).get(key, default)

    def __contains__(self, key):
        return key in getattr(_load_gen(), self._attr)

    def __iter__(self):
        return iter(getattr(_load_gen(), self._attr))

    def items(self):
        return getattr(_load_gen(), self._attr).items()


FUNCS = _FuncTable("FUNCS")
METAS = _FuncTable("METAS")


class _ClassMethodsView:
    """CLASS_METHODS 兼容视图：{cls: {'instance_vars': [...], 'methods': {}}}。

    新架构下方法源码不再运行时消费（编译期固化进 FUNCS），
    内核只读 instance_vars（onready 注入）。
    """

    def get(self, cls, default=None):
        meta = METAS.get(cls)
        if meta is None:
            return default if default is not None else {"instance_vars": [], "methods": {}}
        return {"instance_vars": meta.get("instance_vars", []), "methods": {}}

    def __contains__(self, cls):
        return METAS.get(cls) is not None

    def __getitem__(self, cls):
        return self.get(cls)


CLASS_METHODS = _ClassMethodsView()


def set_class_methods(class_methods):
    """兼容入口：class_methods 池已在代码生成期固化为 FUNCS（无操作）"""


_RARITY_TABLE: Dict[str, int] = {}


def set_rarity_table(table):
    """物品 key → Rarity 数值（ItemBook 描述符/宠物归类用）"""
    _RARITY_TABLE.clear()
    _RARITY_TABLE.update(table or {})


def rarity_table():
    return _RARITY_TABLE


class BehaviorRunner:
    """BehaviorExecutor 兼容面（item/character 内核无感切换）"""

    def __init__(self, item_key: str, data_behavior: dict):
        self.item_key = item_key
        self.spec: Dict[str, Any] = data_behavior or {}
        self.extends_chain: list = list(self.spec.get("extends_chain", []) or [])
        self.timer_connections: Dict[str, str] = dict(self.spec.get("timer_connections", {}) or {})
        self.failures: Dict[Any, str] = {}
        self._warned: set = set()

    # ---- 解析：自身(物品 key) → 沿 extends_chain 的基类池 ----
    def _owners(self):
        yield self.item_key
        for cls in self.extends_chain:
            yield cls

    def resolve_fn(self, name: str):
        for owner in self._owners():
            fn = FUNCS.get((owner, name))
            if fn is not None:
                return owner, fn
        return None, None

    def has_behavior(self, name: str) -> bool:
        owner, fn = self.resolve_fn(name)
        return fn is not None

    def has(self, name: str) -> bool:
        """兼容面（内核 has_behavior 调用 behavior.has）"""
        return self.has_behavior(name)

    def resolve(self, name: str):
        """兼容面：返回 (owner, fn)（旧内核以 [1] 判存在）"""
        return self.resolve_fn(name)

    # ---- 调用 ----
    def call(self, item, name: str, *args):
        owner, fn = self.resolve_fn(name)
        if fn is None:
            return None
        try:
            return fn(item, *args)
        except Exception as e:  # noqa: BLE001
            self._record_failure(item, name, e, "执行异常", owner)
            return None

    def execute(self, item, name: str, *args):
        """兼容面（旧内核 call_behavior → behavior.execute）"""
        return self.call(item, name, *args)

    def execute_class(self, item, cls: str, name: str, *args):
        fn = FUNCS.get((cls, name))
        if fn is None:
            return None
        try:
            return fn(item, *args)
        except Exception as e:  # noqa: BLE001
            self._record_failure(item, name, e, "执行异常", cls)
            return None

    def super_execute(self, item, name: str, from_cls, *args):
        chain = self.extends_chain
        try:
            idx = chain.index(from_cls)
        except ValueError:
            idx = -1
        for cls in chain[idx + 1:]:
            fn = FUNCS.get((cls, name))
            if fn is not None:
                return self.execute_class(item, cls, name, *args)
        return None

    def instance_vars(self, cls: Optional[str] = None):
        if cls is None:
            return list(self.spec.get("instance_vars", []) or [])
        return list(METAS.get(cls, {}).get("instance_vars", []) or [])

    def timer_connections(self):
        return self.timer_connections

    def _record_failure(self, item, name, exc: BaseException, phase: str, cls=None):
        key = (cls, name, phase)
        if key not in self._warned:
            self._warned.add(key)
            self.failures[(cls, name)] = f"{phase}: {type(exc).__name__}: {exc}"
            log = getattr(item, "log", None)
            if log is not None and hasattr(log, "warn"):
                log.warn(f"[{getattr(item, 'key', '?')}] behavior {name} {phase}: {exc!r}")


class _Noop:
    """仅存兼容：旧引擎代码里少量 `_Noop()` 引用点（engine 内已无静默兜底语义）"""

    def __getattr__(self, name):
        raise AttributeError(f"engine 不再提供 _Noop 兜底（访问了 {name}）；"
                             f"请改用 engine/stubs.py 登记桩")
