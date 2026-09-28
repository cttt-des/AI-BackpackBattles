# -*- coding: utf-8 -*-
"""gd_core_py 类注册表（手写文件，不被 tools/gd_to_py.py 覆盖）。

GDScript 的 `class_name` 是一个**全局命名空间**：跨文件写 `CoreItem.new()`、
`CoreConst.getBuffs(...)`、`x is CoreItem` 都靠它解析。Python 模块之间没有
共享全局名，因此转写器把所有跨文件类引用改写成 `_R.C("名字")`（见
tools/gd_to_py.py 的 Rewriter._classrefs），由本模块统一解析。

登记策略：每个生成模块在**末尾**按三个别名登记自己的类 ——
    res_path（"res://gd_core_items/Bag.gd"）、class_name（"Bag"）、文件名 stem（"Bag"）
前两者用于 `extends "res://..."` 与 `_load("res://...")`，第三者是兜底
（实测本项目 class_name 与 stem 完全一一对应、无重名，故三者等价）。

★ 为什么 `import` 顺序由生成器排成 extends 拓扑序：`class X(_R.C("基类"))`
  是**在导入时**求值的，基类必须已经 reg。若顺序错了，C() 会回落到占位类，
  于是 X 继承了一个空类 —— 判定会静默走空实现，且不报错。故 C() 记录
  miss 清单，供 `missing()` 暴露给闸门。
"""

from __future__ import annotations

from ._rt import GodotObject

__all__ = ["reg", "C", "get", "missing", "is_registered", "all_names", "stats"]

_REG = {}
_PH = {}
_MISSING = {}
_PH_BASE = GodotObject


def _placeholder(name):
    """未登记名的占位类（只可能是导入顺序问题，正常流程不会走到）。"""
    ph = _PH.get(name)
    if ph is None:
        ph = type(str(name).rsplit("/", 1)[-1].rsplit(".", 1)[0] or "Placeholder",
                  (_PH_BASE,), {"__placeholder_for__": name})
        _PH[name] = ph
        _MISSING[name] = 0
    _MISSING[name] += 1
    return ph


def reg(name, cls):
    """登记一个类（幂等；同名重复登记以先到者为准之外的后者覆盖）。"""
    _REG[str(name)] = cls
    return cls


def C(name):
    """按 res_path / class_name / stem 取类对象。

    极简实现：这是生成代码里最高频的调用之一（1140 处引用点），
    每条都是 dict 查找 + 一次函数调用。
    """
    cls = _REG.get(name)
    if cls is not None:
        return cls
    return _placeholder(name)


def get(name, default=None):
    return _REG.get(name, default)


def is_registered(name):
    return name in _REG


def missing():
    """返回 {名字: 尝试次数} —— 非空说明有类的导入顺序不对（闸门应判失败）。"""
    return dict(_MISSING)


def all_names():
    return sorted(_REG)


def stats():
    return {"registered": len(_REG), "placeholders": len(_PH),
            "missing": dict(_MISSING)}
