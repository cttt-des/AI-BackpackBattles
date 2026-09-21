# -*- coding: utf-8 -*-
"""engine/codegen.py — 转译产物 → 编译期 Python 模块（fail-fast 代码生成）

输入：assets/battle_items.json 的 behavior.methods / class_methods（旧转译管线的
产物，行为逻辑已由 GDScript 转出）。
输出：engine/gen/behaviors.py —— 全部方法的**真实 Python 模块**（import 常驻，
跨场复用），以及 FUNCS/METAS 注册表与校验报告 gen_report.json。

fail-fast 校验（生成期，未通过则清单报告）：
  * 裸名字必须在 CTX_NAMES / 常量表 / STUB 常量表 / 内建 中
  * `_item.X` 属性/调用必须命中：engine Item API、登记桩、行为方法、实例变量
运行期：命中登记桩 → 计数可见；无任何静默兜底。
"""
from __future__ import annotations

import ast
import builtins
import json
import os
import re
from collections import Counter
from typing import Dict, List, Set

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
GEN_PATH = os.path.join(ROOT, "engine", "gen", "behaviors.py")
REPORT_PATH = os.path.join(ROOT, "engine", "gen", "gen_report.json")

# 战斗上下文对象（转译代码经 _item.ctx 访问，codegen 替换裸名）
CTX_NAMES = {
    "Game": "_item.ctx.game",
    "EventBus": "_item.ctx.event_bus",
    "Util": "_item.ctx.util",
    "ItemBook": "_item.ctx.item_book",
    "descriptor": "_item.descriptor",
    "placed": "_item.placed",
    "me": "_item",
    "data": "_item.data",
    "sprite": "_item.sprite_stub",
    "fluid": "_item.sprite_stub",
    "connector": "_item.sprite_stub",
    "dragParticles": "_item.sprite_stub",
    "animation": "_item.sprite_stub",
    "ActivationAni": "_item.ctx.const.ActivationAni",
}

BUILTINS = set(dir(builtins))


def _sanitize(s: str) -> str:
    return re.sub(r"\W+", "_", s)


class _Transform(ast.NodeTransformer):
    """裸名字 → ctx/常量/桩 的 AST 替换"""

    def __init__(self, const_names: Set[str], stub_names: Set[str], errors: List[str],
                 owner: str, method: str, assigned: Set[str]):
        self.const_names = const_names
        self.stub_names = stub_names
        self.errors = errors
        self.owner = owner
        self.method = method
        self.assigned = assigned        # 参数 + 局部变量（原样保留）

    def visit_Name(self, node: ast.Name) -> ast.AST:
        if isinstance(node.ctx, ast.Store) or node.id in self.assigned:
            return node
        if node.id in CTX_NAMES:
            return ast.parse(CTX_NAMES[node.id], mode="eval").body
        if node.id in self.const_names:
            return ast.parse(f"_const_{_sanitize(node.id)}", mode="eval").body
        if node.id in self.stub_names:
            return ast.parse(f"_stub_{_sanitize(node.id)}", mode="eval").body
        if node.id not in BUILTINS:
            self.errors.append(
                f"[{self.owner}.{self.method}] 未解析裸名 {node.id!r}")
            return ast.parse(f"_unknown({node.id!r})", mode="eval").body
        return node


def _collect_item_attrs(tree: ast.AST) -> Set[str]:
    attrs = set()
    for node in ast.walk(tree):
        if isinstance(node, ast.Attribute) and isinstance(node.value, ast.Name) \
                and node.value.id == "_item":
            attrs.add(node.attr)
    return attrs


def generate(apply: bool = True, item_api: Set[str] = None) -> dict:
    from engine.namespaces import make_constant_table
    from engine import item as engine_item
    # 过渡期：真值枚举/类（Type/Owner/Vector2/DamageSource/Character/_range_or_value…）
    # 直接复用旧全局表的实现（纯数据/函数，无战斗状态）；后续逐项内联
    from simulator.behavior import BEHAVIOR_GLOBALS as _OLD

    stub_memo: dict = {}
    const_table = dict(_OLD)
    const_table.update(make_constant_table(stub_memo))
    const_table.pop("EventBus", None)     # ctx 面
    const_table.pop("Game", None)
    const_table.pop("Util", None)
    const_table.pop("ItemBook", None)
    const_table.pop("descriptor", None)
    const_table.pop("placed", None)
    const_table.pop("me", None)
    const_table.pop("sprite", None)
    const_table.pop("data", None)
    stub_names: Set[str] = set()
    for name in ("Game", "EventBus", "Util", "ItemBook", "descriptor", "placed",
                 "me", "data", "sprite", "fluid", "connector", "dragParticles",
                 "animation", "ActivationAni"):
        const_names_discard = None
    stub_names = {
        # Godot 节点属性/全局（视觉或引擎内部；物品战斗语义不依赖）
        "global_position", "global_rotation", "rotation", "scale", "visible",
        "mass", "mode", "physics_material_override", "NOTIFICATION_PREDELETE",
        "TYPE_VECTOR2", "stepify", "sqrt", "clamp",
        "collarDescriptors", "activeFront", "whelpName", "shadowOffset_dropped",
        "ObjectPool", "Sound", "ItemPool", "AnimationPlayer", "Settings",
        "CustomRules", "InputBlocker", "TileMap", "RigidBody2D", "AtlasTexture",
        "ConvexPolygonShape2D", "Physics2DShapeQueryParameters", "Particles2D",
        "CollisionShape2D", "SignalConnection", "BitStream", "CircleLight",
        "GoobertAnimation", "RingEffect", "Distortion", "BuffParticles",
        "ColdParticles", "LifestealParticles", "LifestealLight", "SkillLight",
        "SaleParticles", "ManaOrbGlow", "ManathirstInner", "ManathirstInnerGlow",
        "BottleOfBooze", "fluidGradientTex", "Zap", "Light", "Light1", "Light2",
        "Particles1", "Particles2", "ActiveParticles", "ActivationParticles1",
        "ActivationParticles2", "RingEffect2", "Frame", "Nonoxidated", "Arm",
        "Fluid", "filling", "leftCounter", "rightCounter", "Active1", "Active2",
        "StatModified", "Sockets", "self", "Color", "String", "Physics",
    }

    with open(DB_PATH, encoding="utf-8") as f:
        db = json.load(f)
    items = db.get("items", db)
    pools = db.get("class_methods", {})

    item_api = item_api or {n for n in dir(engine_item.Item)
                            if not n.startswith("__")}
    # 引擎 Item 的已知属性别名（camelCase 重定向目标）
    known_report: Counter = Counter()
    gen_errors: List[str] = []
    funcs_out: List[str] = []
    registry_lines: List[str] = []
    metas_lines: List[str] = []

    def emit_func(owner: str, method: str, src: str):
        owner_s = _sanitize(owner)
        fn_name = f"f_{owner_s}__{_sanitize(method)}"
        try:
            tree = ast.parse(src)
        except SyntaxError as e:
            gen_errors.append(f"[{owner}.{method}] 语法错误: {e}")
            return None
        fd = tree.body[0]
        if not isinstance(fd, ast.FunctionDef):
            gen_errors.append(f"[{owner}.{method}] 顶层非函数")
            return None
        fd.name = fn_name
        # 参数 + 局部变量收集（须在 transform 前完成，避免 `_item` 等参数被误判裸名）
        local_assigned = {a.arg for a in fd.args.args}
        if fd.args.vararg:
            local_assigned.add(fd.args.vararg.arg)
        if fd.args.kwarg:
            local_assigned.add(fd.args.kwarg.arg)
        for node in ast.walk(fd):
            if isinstance(node, ast.Name) and isinstance(node.ctx, ast.Store):
                local_assigned.add(node.id)
            if isinstance(node, (ast.For,)) and isinstance(node.target, ast.Name):
                local_assigned.add(node.target.id)
        tr = _Transform(set(const_table), stub_names, gen_errors, owner, method,
                        local_assigned)
        fd = tr.visit(fd)
        ast.fix_missing_locations(fd)

        # `_item.X` 校验（ctx 为框架通道，恒合法）
        used_attrs = _collect_item_attrs(fd)
        unknown_attrs = sorted(a for a in used_attrs if a not in item_api
                               and a != "ctx")
        for a in unknown_attrs:
            known_report[f"{owner}.{method}::_item.{a}"] += 1

        body_src = ast.unparse(ast.Module(body=[fd], type_ignores=[]))
        funcs_out.append(body_src)
        registry_lines.append(f"FUNCS[{owner!r}, {method!r}] = {fn_name}")
        return fn_name

    # 物品方法
    for key, v in items.items():
        beh = v.get("behavior") or {}
        for method, src in (beh.get("methods") or {}).items():
            emit_func(key, method, src)
    # 基类池
    for cls, entry in pools.items():
        for method, src in (entry.get("methods") or {}).items():
            emit_func(cls, method, src)

    # METAS
    meta_srcs = []
    for key, v in items.items():
        beh = v.get("behavior") or {}
        metas_lines.append(
            f"METAS[{key!r}] = {{'extends_chain': {beh.get('extends_chain') or []!r}, "
            f"'instance_vars': {beh.get('instance_vars') or []!r}, "
            f"'timer_connections': {beh.get('timer_connections') or {}!r}}}")
    for cls, entry in pools.items():
        metas_lines.append(
            f"METAS[{cls!r}] = {{'extends_chain': {entry.get('extends_chain') or []!r}, "
            f"'instance_vars': {entry.get('instance_vars') or []!r}, "
            f"'timer_connections': {entry.get('timer_connections') or {}!r}}}")

    const_imports = [f"_const_{_sanitize(k)} = _make_const({k!r})"
                     for k in sorted(const_table)]
    stub_imports = [f"_stub_{_sanitize(n)} = _make_stub({n!r})" for n in sorted(stub_names)]

    header = '''# -*- coding: utf-8 -*-
# 自动生成：engine/codegen.py（勿手改）。行为方法 = 旧转译管线的编译期产物。
from ..namespaces import stub_enum
from ..runtime_consts import build_constants

_CONSTS = build_constants()
_stub_memo: dict = {}

def _make_const(name):
    return _CONSTS[name]

def _make_stub(name):
    return stub_enum(name, _stub_memo)   # 命名空间桩：属性自洽并登记

def _unknown(name):
    raise NameError(f"engine codegen: 未解析名字 {name!r}（应生成期拦截）")

FUNCS = {}
METAS = {}
'''
    module_src = "\n".join(
        [header] + const_imports + stub_imports + [""] + funcs_out + [""] + registry_lines + metas_lines + ["\n"])

    report = {
        "gen_errors": gen_errors,
        "unknown_item_attrs": {k: v for k, v in known_report.items()},
        "functions": len(funcs_out),
    }
    if apply:
        os.makedirs(os.path.dirname(GEN_PATH), exist_ok=True)
        with open(GEN_PATH, "w", encoding="utf-8", newline="\n") as f:
            f.write(module_src + "\n")
        with open(REPORT_PATH, "w", encoding="utf-8") as f:
            json.dump(report, f, ensure_ascii=False, indent=1)
    return report


if __name__ == "__main__":
    rep = generate()
    print(f"生成函数: {rep['functions']} | gen_errors: {len(rep['gen_errors'])} "
          f"| unknown_item_attrs: {len(rep['unknown_item_attrs'])}")
    for e in rep["gen_errors"][:10]:
        print("  ERR", e)
    for k in list(rep["unknown_item_attrs"])[:20]:
        print("  ATTR", k)
