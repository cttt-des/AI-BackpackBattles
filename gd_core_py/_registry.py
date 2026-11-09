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
    import os as _os
    if _os.environ.get("GD_DEBUG_PLACEHOLDER") == "1":
        import sys as _sys
        import traceback as _tb
        print("WARN[placeholder] %s" % str(name), file=_sys.stderr)
        _tb.print_stack(file=_sys.stderr)
    ph = _PH.get(name)
    if ph is None:
        ph = type(str(name).rsplit("/", 1)[-1].rsplit(".", 1)[0] or "Placeholder",
                  (_PH_BASE,), {"__placeholder_for__": name})
        _PH[name] = ph
        _MISSING[name] = 0
    _MISSING[name] += 1
    return ph


def _is_behavior_tree(cls) -> bool:
    """实例链真身判定：夹具脚本路径恒为 res://gd_core_items/**，引擎据此从
    gd_core_py.gd_core_items.** 装配物品——行为脚本的基类链（Item_2/Bag/…）
    全在行为树模块里。"""
    return getattr(cls, "__module__", "").startswith("gd_core_py.gd_core_items.")


def reg(name, cls):
    """登记一个类（幂等；同名重复登记以先到者为准之外的后者覆盖）。

    ★ np24-P3-7 仲裁（2026-10-27）：裸类名可能被**两棵平行树**登记——
      gd_core/Item.gd（build_item_scripts 生成的适配层，class_name Item）与
      gd_core_items/Item.gd（行为基类，同名 class_name）转写后都注册 "Item"，
      后到者胜。而引擎实例**固定**经 gd_core_items 树装配（夹具 script 路径），
      若裸名被适配层占据，行为脚本里所有 `x is Item`（→
      `isinstance(x, _R.C("Item"))`）恒 False——CorruptedCrystal 的
      giveBlock 闸因此全废（gd 9710 条 gem Block vs py 1531，run845 因此
      链式分叉并在 CoreBuff.onTimeout 崩溃）。故仲裁：行为树已持有的裸名，
      拒绝内核/适配树的后写覆盖；反向（行为树后写）仍按后者覆盖。
    """
    name = str(name)
    prev = _REG.get(name)
    if prev is not None and _is_behavior_tree(prev) and not _is_behavior_tree(cls):
        return cls
    _REG[name] = cls
    return cls


_LAZY_IMPORTING = set()


def _lazy_import(name):
    """未登记名 → 按资源路径/class_name 惰性导入对应生成模块后重查。

    ★ 2026-10-08：转写器会把「成员初始化器里的字典字面量」提升到类体
      （如 CoreCharacter 的 classResources 以 `_R.C("CoreConst").Classes.Ranger`
      为键）——这类引用在**导入期**求值，先于 extends 拓扑序里排在后面的
      CoreConst 注册，导致 AttributeError 级联。与其维护脆弱的排序，不如
      在 C() 未命中时按名找模块导入一次（幂等、防递归）。

    ★ 2026-11-09（B2 分层导入回归修复）：`gd_core/` 树直猜之外，回落
      `_bootstrap._STEM2MOD`（生成器发射的 stem→全模块路径全量表）——
      items 树的**非祖先跨类引用**（如 ChessBoard 运行时 isinstance
      `_R.C("ChessPiece")`，ChessPiece 非 ChessBoard 祖先、不在 load_for
      闭包）此前落占位类：isinstance 恒 False=沉默语义死，属性访问炸=
      py 腿缺产物（60 场精选集 14 红的根因，docs/性能优化执行路径.md）。"""
    stem = str(name).rsplit("/", 1)[-1]
    if stem.endswith(".gd"):
        stem = stem[:-3]
    for modname in _lazy_modnames(stem):
        if modname in _LAZY_IMPORTING:
            continue
        _LAZY_IMPORTING.add(modname)
        try:
            import importlib
            importlib.import_module(modname)
            hit = _REG.get(name)
            if hit is not None:
                return hit
        except Exception:  # noqa: BLE001 —— 找不到模块/循环导入时回落占位类
            pass
        finally:
            _LAZY_IMPORTING.discard(modname)
    return None


def _lazy_modnames(stem):
    """候选模块路径：gd_core/ 树直猜 + _bootstrap._STEM2MOD 全量映射兜底。"""
    names = ["gd_core_py.gd_core." + stem]
    try:
        from . import _bootstrap as _b
        m = getattr(_b, "_STEM2MOD", {}).get(stem)
        if m and m not in names:
            names.append(m)
    except Exception:  # noqa: BLE001 —— bootstrap 未导入时仅直猜
        pass
    return names


def C(name):
    """按 res_path / class_name / stem 取类对象。

    极简实现：这是生成代码里最高频的调用之一（1140 处引用点），
    每条都是 dict 查找 + 一次函数调用。
    """
    cls = _REG.get(name)
    if cls is not None:
        return cls
    cls = _lazy_import(name)
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
