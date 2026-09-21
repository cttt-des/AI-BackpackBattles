# -*- coding: utf-8 -*-
"""audit_item_effects.py — 物品效果三层静态对账（不需要运行游戏）

以解密源码 decompiled_full/Items/**.gd 为唯一权威，逐物品比对：

  1. 源码层   ：脚本里定义了哪些方法
  2. 转译层   ：哪些方法进了 battle_items.json 的 behavior.methods，
                哪些转译失败落在 methods_raw，哪些完全没入库（被跳过名单过滤）
  3. 运行时层 ：真正执行一遍生命周期（prepare → preCombatStart → combatStart →
                doCooldownEffect → combatEnd），收集被静默吞掉的异常
                （开启 simulator.behavior.STRICT）

另外静态扫描转译后代码调用了哪些引擎 API，列出**模拟器尚未实现**的 API，
按「视觉类 / 可疑战斗类」分类，作为补齐优先级的依据。

输出：output/audit/effects_report.json（+ 控制台摘要）
用法：
    python tools/audit_item_effects.py
    python tools/audit_item_effects.py --no-runtime     # 只做静态层（更快）
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
from collections import Counter
from datetime import datetime
from typing import Any, Dict, List

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

for _stream in (sys.stdout, sys.stderr):
    try:
        if hasattr(_stream, "reconfigure"):
            _stream.reconfigure(encoding="utf-8", errors="replace")
    except Exception:  # noqa: BLE001
        pass

import engine.behavior as B                        # noqa: E402
from simulator import extract_items as E           # noqa: E402（源码索引/方法池同源）
from engine.character import Character             # noqa: E402
from engine.data import load_items                 # noqa: E402
from engine.grid import GridInventory              # noqa: E402
from engine.item import Item                       # noqa: E402

OUT_DIR = os.path.join(ROOT, "output", "audit")

# 视觉/表现层 API：缺失通常不影响战斗数值，优先级低
VISUAL_HINTS = {
    "preload", "Color", "setTexture", "sprite", "animation", "particles",
    "Particle", "connector", "tween", "z_index", "modulate", "ObjectPool",
    "Sound", "tooltip", "shader", "label", "icon", "visual", "position",
    "rotation", "scale", "texture", "node", "queue", "updateConnector",
    "updatePaws", "updateScale", "createBondVisual", "updateBondVisuals",
    "playAffectedPlacedAnimation", "popIn", "tr", "Dictionary", "Vector2",
    "Vector2i", "ceil", "floor", "get_parent", "setFaceDirection",
}


def is_visual(name: str) -> bool:
    low = name.lower()
    return (name in VISUAL_HINTS
            or any(h.lower() in low for h in
                   ("particle", "sprite", "texture", "animation", "visual",
                    "sound", "tooltip", "shader", "tween", "label", "icon")))


# --------------------------------------------------------------------------
# 第 1+2 层：源码方法 vs 入库方法
# --------------------------------------------------------------------------
def source_vs_db(items: Dict[str, dict], idx: Dict[str, str]):
    missing: Dict[str, List[str]] = {}
    raw: Dict[str, List[str]] = {}
    for key, item in items.items():
        sp = None
        scr = item.get("script")
        if scr:
            norm = (scr[:-3].lower().replace(" ", "") if scr.endswith(".gd")
                    else scr.lower().replace(" ", ""))
            sp = idx.get(norm)
        if sp is None:
            sp = E.match_script_key(key, idx)
        if sp is None:
            continue
        try:
            _ext, _iv, _or, _td, methods = E.parse_script(sp)
        except Exception:  # noqa: BLE001
            continue
        beh = item.get("behavior") or {}
        in_db = set(beh.get("methods") or {}) | set(beh.get("methods_raw") or {})
        gap = [m for m in methods if m not in in_db]
        if gap:
            missing[key] = gap
        if beh.get("methods_raw"):
            raw[key] = list(beh["methods_raw"])

    # 基类方法池：与各自源码对账（键 "<-Class.gd>" 前缀区分）
    class_methods = _load_class_methods()
    for cls, entry in sorted(class_methods.items()):
        sp = idx.get(cls.lower().replace(" ", ""))
        if sp is None:
            continue
        try:
            _ext, _iv, _or, _td, methods = E.parse_script(sp)
        except Exception:  # noqa: BLE001
            continue
        in_db = set(entry.get("methods") or {}) | set(entry.get("methods_raw") or {})
        gap = [m for m in methods
               if m not in in_db and m not in E.ENGINE_LIFECYCLE]
        if gap:
            missing[f"<class:{cls}>"] = gap
        if entry.get("methods_raw"):
            raw[f"<class:{cls}>"] = list(entry["methods_raw"])
    return missing, raw


def _load_class_methods() -> Dict[str, dict]:
    """读取 battle_items.json 顶层的 class_methods（键=脚本类名）"""
    import json as _json
    path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                        "assets", "battle_items.json")
    try:
        with open(path, encoding="utf-8") as f:
            return _json.load(f).get("class_methods") or {}
    except Exception:  # noqa: BLE001
        return {}


# --------------------------------------------------------------------------
# 第 3 层：运行时执行（开启严格模式，暴露静默失败）
# --------------------------------------------------------------------------
def runtime_probe(key: str, data: dict) -> Dict[str, str]:
    """执行一遍物品生命周期，返回 {方法名: 错误信息}。"""
    try:
        from engine.context import BattleContext
        it = Item(key, dict(data))
        ch = Character(0, "P", 9999, 99.0, 9.0)
        opp = Character(1, "O", 9999, 99.0, 9.0)
        ch.set_opponent(opp)
        opp.set_opponent(ch)
        # ctx 必须先于 set_grid_position（入背包 ready 依赖 ctx.game/combatLog）
        ctx = BattleContext(0)
        it.ctx = ctx
        ch.ctx = ctx
        opp.ctx = ctx
        ctx.game.PLAYER = ch
        ctx.game.OPPONENT = opp
        it.character = ch
        # 引擎战斗中角色必持有全部物品（Game.prepareItems 前已摆盘）——
        # inventory.getItems() 类联动（Time Dilator 等）依赖这一点
        ch.set_items([it])
        it.set_grid_position(0, 0, 0, inventory=GridInventory(7, 10))
        it.prepare()
        it.pre_combat_start()
        it.combat_start()
        it.post_combat_start()
        if it.has_cooldown():
            it.do_cooldown_effect(0.0)
        it.combat_end()
    except Exception as e:  # noqa: BLE001
        return {"<lifecycle>": f"{type(e).__name__}: {e}"}

    ex = getattr(it, "_behavior_executor", None)
    if ex is None:
        return {}
    # failures 键为 (cls, name) 元组（继承链感知）——拍平成字符串便于 JSON 序列化
    out = {}
    for k, v in ex.failures.items():
        kk = k if isinstance(k, str) else ":".join(str(x) for x in k if x)
        out[kk or k[1]] = v
    return out


# --------------------------------------------------------------------------
# 缺失 API 扫描
# --------------------------------------------------------------------------
def missing_api_scan(items: Dict[str, dict]):
    miss_self: Counter = Counter()      # _item.xxx() —— 自身 API
    miss_other: Counter = Counter()     # item.xxx()  —— 其他物品 API（联动判定用）
    class_methods = _load_class_methods()
    for key, data in items.items():
        beh = data.get("behavior") or {}
        methods = beh.get("methods") or {}
        # 继承链上会被本物品实际执行到的基类方法源码也纳入扫描
        chain = beh.get("extends_chain") or []
        for cls in chain:
            methods = {**(class_methods.get(cls, {}).get("methods") or {}), **methods}
        if not methods:
            continue
        src = "\n".join(methods.values())
        try:
            probe = Item(key, dict(data))
        except Exception:  # noqa: BLE001
            continue
        for name in set(re.findall(r'_item\.(\w+)\s*\(', src)):
            # 新内核：命名空间常量以 _const_* 模块级形式注入，不会出现在
            # _item.xxx() 调用面上；无需旧 BEHAVIOR_GLOBALS 豁免清单
            if not hasattr(probe, name):
                miss_self[name] += 1
        for name in set(re.findall(r'(?<![\w._])item\.(\w+)\s*\(', src)):
            if not hasattr(probe, name):
                miss_other[name] += 1
    return miss_self, miss_other


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="物品效果三层静态对账")
    ap.add_argument("--no-runtime", action="store_true", help="跳过运行时探测")
    ap.add_argument("--json", default=os.path.join(OUT_DIR, "effects_report.json"))
    args = ap.parse_args(argv)

    # 新内核行为执行 fail-fast + failures 记录（无需旧 STRICT 开关）
    items = load_items()
    idx = E.scan_scripts()
    print(f"物品: {len(items)}   脚本索引: {len(idx)}")

    print("[1/4] 源码方法 vs 入库方法 ...")
    missing, raw = source_vs_db(items, idx)
    print(f"      未入库方法: {sum(len(v) for v in missing.values())} "
          f"（涉及 {len(missing)} 个物品）")
    print(f"      转译失败(methods_raw): {sum(len(v) for v in raw.values())} "
          f"（涉及 {len(raw)} 个物品）")

    print("[2/4] 缺失 API 静态扫描 ...")
    miss_self, miss_other = missing_api_scan(items)
    combat_self = {k: v for k, v in miss_self.items() if not is_visual(k)}
    combat_other = {k: v for k, v in miss_other.items() if not is_visual(k)}
    print(f"      自身 API 缺失: {len(miss_self)} 种（其中非视觉 {len(combat_self)}）")
    print(f"      其他物品 API 缺失: {len(miss_other)} 种（其中非视觉 {len(combat_other)}）")

    runtime: Dict[str, Dict[str, str]] = {}
    if args.no_runtime:
        print("[3/4] 运行时探测：已跳过")
    else:
        print("[3/4] 运行时探测（每物品一次生命周期）...")
        for i, (key, data) in enumerate(items.items(), 1):
            f = runtime_probe(key, data)
            if f:
                runtime[key] = f
            if i % 100 == 0:
                print(f"      {i}/{len(items)} ...", flush=True)
        print(f"      运行时报错物品: {len(runtime)}")

    print("[4/4] 写出报告 ...")
    os.makedirs(os.path.dirname(os.path.abspath(args.json)), exist_ok=True)
    report = {
        "generated_at": datetime.now().isoformat(timespec="seconds"),
        "summary": {
            "items": len(items),
            "items_untranslated": len(missing),
            "methods_untranslated": sum(len(v) for v in missing.values()),
            "items_raw": len(raw),
            "methods_raw": sum(len(v) for v in raw.values()),
            "items_runtime_error": len(runtime),
            "missing_api_self": len(miss_self),
            "missing_api_self_combat": len(combat_self),
            "missing_api_other": len(miss_other),
            "missing_api_other_combat": len(combat_other),
        },
        "untranslated_methods": missing,
        "raw_methods": raw,
        "runtime_failures": runtime,
        "missing_api_self": dict(miss_self.most_common()),
        "missing_api_self_combat": dict(
            sorted(combat_self.items(), key=lambda kv: -kv[1])),
        "missing_api_other": dict(miss_other.most_common()),
        "missing_api_other_combat": dict(
            sorted(combat_other.items(), key=lambda kv: -kv[1])),
    }
    json.dump(report, open(args.json, "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)

    print("=" * 70)
    print("摘要")
    print(f"  未入库方法（源码有、behavior 无）: {report['summary']['methods_untranslated']}")
    print(f"  转译失败 methods_raw            : {report['summary']['methods_raw']}")
    print(f"  运行时报错物品                  : {len(runtime)}")
    print(f"  缺失自身 API（非视觉，前 15）   :")
    for k, v in list(report["missing_api_self_combat"].items())[:15]:
        print(f"      {k:<38} x{v}")
    print(f"  缺失其他物品 API（前 15）       :")
    for k, v in list(report["missing_api_other"].items())[:15]:
        print(f"      {k:<38} x{v}")
    print(f"报告: {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
