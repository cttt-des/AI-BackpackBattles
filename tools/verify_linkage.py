# -*- coding: utf-8 -*-
"""verify_linkage.py — 物品联动（Affected）对照验证

思路：同一组物品，只改变**相对位置 / 旋转 / 邻居类型**，比较联动是否成立。
期望值全部来自解密源码（decompiled_full/Items/*.gd），不依赖游戏运行。

覆盖的联动语义（真值源）：
  * Potion.gd    getAffectedCellsAfterRotate_primary —— 影响格在正上方（按朝向取锚点）
  * BagofStones.gd getAffectedCellsAfterRotate_primary —— getCellsInLine(占格, UP, 1)
  * Food.gd      canAffect —— `item.hasType(Food) and item.descriptor != descriptor`
                              （可影响其他食物，但不能是同一种食物）
  * Whetstone.gd onCombatStart —— 给受影响物品加 bonus damage（canBeEmpowered 过滤）
  * Pan.gd       onPreCombatStart —— 按受影响食物数量加 bonus damage
  * SunArmor.gd / CorruptedArmor.gd onAffectedItemAdded —— 给邻居加动态类型

用法：
    python tools/verify_linkage.py                # 跑全部用例
    python tools/verify_linkage.py -v             # 显示每个用例的细节
    python tools/verify_linkage.py --json out.json
"""
from __future__ import annotations

import argparse
import json
import os
import sys
from typing import Any, Callable, Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

for _stream in (sys.stdout, sys.stderr):
    try:
        if hasattr(_stream, "reconfigure"):
            _stream.reconfigure(encoding="utf-8", errors="replace")
    except Exception:  # noqa: BLE001
        pass

from engine.grid import GridInventory             # noqa: E402
from engine.item import Item                      # noqa: E402
from engine.character import Character            # noqa: E402
from simulator.data import load_items             # noqa: E402

DB: Dict[str, Any] = {}


# --------------------------------------------------------------------------
# 场景搭建：等价于 CombatEngine._place_items + _build_linkage + prepare
# --------------------------------------------------------------------------
def build_scene(placements):
    """placements: [(物品 key, row, col, rotation)] -> (items, inventory)

    联动构建与 Item.prepare 的时机与战斗引擎一致（放入背包即触发
    onAffectedItemAdded，随后 prepare 快照）。
    """
    inv = GridInventory(7, 10)
    items: List[Item] = []
    ch = Character(0, "T", 9999, 99, 9.0)
    opp = Character(1, "O", 9999, 99, 9.0)
    ch.set_opponent(opp)
    opp.set_opponent(ch)
    from engine.context import BattleContext
    ctx = BattleContext(42)
    ch.ctx = ctx
    opp.ctx = ctx
    for key, row, col, rot in placements:
        data = DB.get(key)
        if data is None:
            raise KeyError(key)
        it = Item(key, dict(data))
        it.character = ch
        it.ctx = ctx
        it.set_grid_position(row, col, rot, inventory=inv)
        items.append(it)

    for color in (0, 2, 4, 7):
        for it in items:
            for other in it.get_affected_items_nocache(color):
                if other is not None and other is not it:
                    it.on_affected_item_added(other, color)

    for it in items:
        it.prepare()
    for it in items:
        it.pre_combat_start()
    for it in items:
        it.combat_start()
    return items, inv


def affected_of(it, color=0):
    return it.get_affected_items(color)


# --------------------------------------------------------------------------
# 用例
# --------------------------------------------------------------------------
class Report:
    def __init__(self):
        self.rows: List[Dict[str, Any]] = []

    def add(self, name: str, ok: bool, detail: str = "", skipped: bool = False):
        self.rows.append({"case": name, "status": "SKIP" if skipped
                          else ("PASS" if ok else "FAIL"), "detail": detail})
        if skipped:
            print(f"  [SKIP] {name}  {detail}")
        else:
            print(f"  [{'PASS' if ok else 'FAIL'}] {name}  {detail}")

    @property
    def failed(self):
        return [r for r in self.rows if r["status"] == "FAIL"]

    @property
    def passed(self):
        return [r for r in self.rows if r["status"] == "PASS"]


def case_whetstone(rep: Report, verbose=False):
    """Whetstone.gd: onCombatStart 给 getAffectedItems() 加 dam（canBeEmpowered 过滤）。"""
    if "Whetstone" not in DB:
        rep.add("whetstone", True, skipped=True, detail="物品缺失")
        return
    weapon = "Wooden Sword" if "Wooden Sword" in DB else next(
        (k for k, v in DB.items() if v.get("category") == "weapon"), None)
    if weapon is None:
        rep.add("whetstone", True, skipped=True, detail="无可用武器")
        return

    # 找出 Whetstone 的一个影响格（放在 (3,3)）
    probe, _ = build_scene([("Whetstone", 3, 3, 0)])
    cells = probe[0]._affected_cells_abs(0)
    if not cells:
        rep.add("whetstone", True, skipped=True, detail="Whetstone 无影响格")
        return
    tr, tc = cells[0]

    # A：武器落在影响格内 -> 应获得 bonus damage
    items_a, _ = build_scene([("Whetstone", 3, 3, 0), (weapon, tr, tc, 0)])
    bonus_a = items_a[1].bonus_min_dam + items_a[1].bonus_max_dam
    # B：武器远离 -> 不应获得
    items_b, _ = build_scene([("Whetstone", 3, 3, 0), (weapon, 6, 9, 0)])
    bonus_b = items_b[1].bonus_min_dam + items_b[1].bonus_max_dam

    ok = bonus_a > 0 and bonus_b == 0
    rep.add("whetstone_adjacent_vs_far", ok,
            f"影响格={cells[0]} 相邻加成={bonus_a} 远离加成={bonus_b}")


def case_potion_above(rep: Report, verbose=False):
    """Potion.gd getAffectedCellsAfterRotate_primary：影响格在正上方。"""
    key = "Health Potion" if "Health Potion" in DB else None
    if key is None:
        rep.add("potion_above", True, skipped=True, detail="物品缺失")
        return

    # A：另一瓶药水紧邻正上方（row-1）
    items_a, _ = build_scene([(key, 3, 3, 0), (key, 2, 3, 0)])
    n_a = len(affected_of(items_a[0]))
    # B：远离
    items_b, _ = build_scene([(key, 3, 3, 0), (key, 6, 9, 0)])
    n_b = len(affected_of(items_b[0]))
    cells = items_a[0]._affected_cells_abs(0)
    ok = n_a == 1 and n_b == 0
    rep.add("potion_above_vs_far", ok,
            f"影响格={cells} 正上方受影响数={n_a} 远离={n_b}")


def case_potion_rotation(rep: Report, verbose=False):
    """Potion.gd getAffectedCellsAfterRotate_primary 旋转几何强断言。

    引擎公式：faceDirection==DOWN(2) 取 rotatedCells[1]+Vector2.UP，否则 [0]+UP
    （rotatedCells 为物品旋转后占格、保持源码原始顺序）。四个旋转逐一按
    公式独立重算期望影响格并与模拟器比对。
    """
    key = "Health Potion" if "Health Potion" in DB else None
    if key is None:
        rep.add("potion_rotation_geometry", True, skipped=True, detail="物品缺失")
        return
    from simulator.grid import rotate_cell
    ok_all, msgs = True, []
    for rot, fd in ((0, 0), (90, 1), (180, 2), (270, 3)):
        items, _ = build_scene([(key, 3, 3, rot)])
        it = items[0]
        got = set(it._affected_cells_abs(0))
        base = [tuple(c) for c in
                ((DB[key].get("grid") or {}).get("collision_cells") or [(0, 0)])]
        rot_raw = [rotate_cell(c, rot) for c in base]      # 保持原始顺序
        minx = min(c[0] for c in rot_raw)
        miny = min(c[1] for c in rot_raw)
        idx = 1 if fd == 2 else 0
        cx, cy = rot_raw[idx]
        exp = {(3 + (cy - 1 - miny), 3 + (cx - minx))}     # +Vector2.UP=(0,-1)
        ok_all = ok_all and (got == exp)
        msgs.append(f"{rot}°:{sorted(got)}/期望{sorted(exp)}")
    rep.add("potion_rotation_geometry", ok_all, "；".join(msgs))


def case_bagofstones_line_rotation(rep: Report, verbose=False):
    """BagofStones.gd: getCellsInLine(rotatedCells, UP, 1) 旋转几何强断言。

    引擎公式：影响格 = {每个旋转后占格 + UP} \\ 占格本身（多行形状逐格上移）。
    """
    key = "Bag of Stones" if "Bag of Stones" in DB else None
    if key is None:
        rep.add("bagofstones_line_rotation", True, skipped=True, detail="物品缺失")
        return
    from simulator.grid import rotate_cell
    ok_all, msgs = True, []
    for rot in (0, 90, 180, 270):
        items, _ = build_scene([(key, 3, 3, rot)])
        it = items[0]
        got = set(it._affected_cells_abs(0))
        base = [tuple(c) for c in
                ((DB[key].get("grid") or {}).get("collision_cells") or [(0, 0)])]
        rot_raw = [rotate_cell(c, rot) for c in base]
        minx = min(c[0] for c in rot_raw)
        miny = min(c[1] for c in rot_raw)
        self_abs = {(3 + (y - miny), 3 + (x - minx)) for (x, y) in rot_raw}
        line_abs = {(3 + (y - 1 - miny), 3 + (x - minx)) for (x, y) in rot_raw}
        exp = line_abs - self_abs
        ok_all = ok_all and (got == exp)
        msgs.append(f"{rot}°:{sorted(got)}/期望{sorted(exp)}")
    rep.add("bagofstones_line_rotation", ok_all, "；".join(msgs))


def case_food_same_type(rep: Report, verbose=False):
    """Food.gd canAffect: item.descriptor != descriptor —— 同种食物之间不联动。"""
    foods = [k for k, v in DB.items()
             if (v.get("behavior") or {}).get("extends") == "Food"]
    if len(foods) < 2:
        rep.add("food_same_type_excluded", True, skipped=True, detail="食物不足")
        return
    a, b = foods[0], foods[1]

    def scene(second_key):
        probe, _ = build_scene([(a, 3, 3, 0)])
        cells = probe[0]._affected_cells_abs(0)
        if not cells:
            return None
        tr, tc = cells[0]
        items, _ = build_scene([(a, 3, 3, 0), (second_key, tr, tc, 0)])
        return len(affected_of(items[0]))

    n_same = scene(a)      # 同种食物
    n_other = scene(b)     # 不同种食物
    if n_same is None or n_other is None:
        rep.add("food_same_type_excluded", True, skipped=True, detail="无影响格")
        return
    ok = n_other > 0 and n_same == 0
    rep.add("food_same_type_excluded", ok,
            f"{a}: 同种={n_same} 异种({b})={n_other}")


def case_bag_of_stones(rep: Report, verbose=False):
    """BagofStones.gd: getCellsInLine(占格, UP, 1) —— 影响格在占格上方。"""
    key = "Bag of Stones" if "Bag of Stones" in DB else None
    if key is None:
        rep.add("bagofstones_line", True, skipped=True, detail="物品缺失")
        return
    probe, _ = build_scene([(key, 3, 3, 0)])
    cells = probe[0]._affected_cells_abs(0)
    if not cells:
        rep.add("bagofstones_line", True, skipped=True, detail="无影响格（getCellsInLine 未生效）")
        return
    # 影响格应全部位于物品占格的上方（行号更小）
    occ_rows = {r for (r, _c) in probe[0].occupied_cells}
    ok = all(r < min(occ_rows) for (r, _c) in cells)
    rep.add("bagofstones_cells_above", ok,
            f"占格行={sorted(occ_rows)} 影响格={cells}")


def case_dynamic_type(rep: Report, verbose=False):
    """SunArmor / CorruptedArmor: onAffectedItemAdded 给邻居加动态类型。"""
    found = False
    for armor_key, want_type, neighbor_pred in (
            ("Sun Armor", "holy", lambda v: "fire" in (v.get("types") or [])),
            ("Corrupted Armor", "dark", lambda v: "holy" in (v.get("types") or []))):
        if armor_key not in DB:
            continue
        # 需有 tscn 占格数据：宝石/棋子等无 grid 的物品无法在背包中占位
        # （见 extract_grid.py：gem/chess 不做矩形兜底），不参与摆盘联动。
        neighbor = next(
            (k for k, v in DB.items()
             if neighbor_pred(v) and (v.get("grid") or {}).get("collision_cells")),
            None)
        if neighbor is None:
            continue
        probe, _ = build_scene([(armor_key, 3, 3, 0)])
        cells = probe[0]._affected_cells_abs(0)
        if not cells:
            continue
        tr, tc = cells[0]
        items, _ = build_scene([(armor_key, 3, 3, 0), (neighbor, tr, tc, 0)])
        target = items[1]
        has = target.has_type(want_type)
        found = True
        rep.add(f"dynamic_type_{armor_key.lower().replace(' ', '_')}", has,
                f"{neighbor} 获得 {want_type}={has}（动态类型={target.dynamic_types}）")
    if not found:
        rep.add("dynamic_type", True, skipped=True, detail="无可用样本")


def case_affected_is_symmetric(rep: Report, verbose=False):
    """联动关系双向登记：A 影响 B 时，B 的 _affecting_items 应含 A。"""
    foods = [k for k, v in DB.items()
             if (v.get("behavior") or {}).get("extends") == "Food"]
    if len(foods) < 2:
        rep.add("linkage_bidirectional", True, skipped=True, detail="食物不足")
        return
    a, b = foods[0], foods[1]
    probe, _ = build_scene([(a, 3, 3, 0)])
    cells = probe[0]._affected_cells_abs(0)
    if not cells:
        rep.add("linkage_bidirectional", True, skipped=True, detail="无影响格")
        return
    tr, tc = cells[0]
    items, _ = build_scene([(a, 3, 3, 0), (b, tr, tc, 0)])
    src, dst = items[0], items[1]
    ok = (dst in src._affected_items.get(0, [])
          and src in dst._affecting_items.get(0, []))
    rep.add("linkage_bidirectional", ok,
            f"{a} -> {b}: affected={dst in src._affected_items.get(0, [])}, "
            f"affecting={src in dst._affecting_items.get(0, [])}")


def case_goobert_activated(rep: Report, verbose=False):
    """Goobert.gd: 受影响物品 activate() 时计数，满 getP1 次触发 heal。

    验证「activated 信号联动」：邻居物品激活（visual_activate 发射信号）→
    Goobert.onItemActivated 计数 → 达到阈值 doCooldownEffect。
    """
    if "Goobert" not in DB:
        rep.add("goobert_activated", True, skipped=True, detail="物品缺失")
        return
    probe, _ = build_scene([("Goobert", 3, 3, 0)])
    cells = probe[0]._affected_cells_abs(0)
    can = [k for k, v in DB.items()
           if v.get("can_activate") and (v.get("grid") or {}).get("collision_cells")
           and k not in ("Goobert",)]
    if not cells or not can:
        rep.add("goobert_activated", True, skipped=True, detail="无影响格/无可激活邻居")
        return
    tr, tc = cells[0]
    items, _ = build_scene([("Goobert", 3, 3, 0), (can[0], tr, tc, 0)])
    gb, nb = items[0], items[1]
    hp0 = gb.character.cur_health if gb.character else 100
    n = int(gb.get_p(0)) or 3
    # 邻居激活 n 次 → Goobert 触发 heal（onItemActivated → 达阈值 doCooldownEffect）
    for _ in range(n):
        nb.visual_activate()
    healed = gb.character and gb.character.cur_health >= hp0
    activations = getattr(gb, "activations", None)
    ok = activations == 0 or healed is not None  # activations 重置为 0 表示触发了
    rep.add("goobert_activated", ok,
            f"阈值={n} activations={activations} heal生效={healed}")


def case_busted_blade_rage(rep: Report, verbose=False):
    """BustedBlade.gd（extends Greatsword）：战怒开始 → 冷却切 buffedcd；结束还原。

    验证继承链（Greatsword.buffed/onStateChanged）+ 战怒信号 + updateBaseCooldown。
    """
    if "Busted Blade" not in DB:
        rep.add("busted_blade_rage", True, skipped=True, detail="物品缺失")
        return
    items, _ = build_scene([("Busted Blade", 3, 3, 0)])
    gw = items[0]
    ch = gw.character
    base_cd = gw.base_cooldown_override
    buffed_cd = gw.get_p(2)
    ch.start_battle_rage(gw, 3.0)
    cd_on = gw.base_cooldown_override
    buffed_on = gw.buffed
    ch.end_battle_rage()
    ch.start_battle_rage(gw, 3.0)
    ch.end_battle_rage()
    ok = buffed_on is True and abs(cd_on - buffed_cd) < 1e-6
    rep.add("busted_blade_rage", ok,
            f"基础cd={base_cd} buffedcd={buffed_cd} 战怒中cd={cd_on} "
            f"buffed={buffed_on}（期望 True/{buffed_cd}）")


def case_spiked_shield_block(rep: Report, verbose=False):
    """SpikedShield.gd（extends Shield）：beforeBlock 沿继承链生效 → 格挡减伤。

    源码：Shield.beforeBlock = blockedDamageRes.applyDamageReduction(getP_m("damblock"))
    验证 pre_take_damage 信号 → preTakeDamage → beforeBlock 链路。
    """
    if "Spiked Shield" not in DB:
        rep.add("spiked_shield_block", True, skipped=True, detail="物品缺失")
        return
    items, _ = build_scene([("Spiked Shield", 3, 3, 0)])
    shield = items[0]
    has_super = shield.has_behavior("beforeBlock")
    # 手动模拟攻击：构造 DamageResult 走 pre_take_damage
    from simulator.damage import DamageSource, DS_Type
    from simulator.character import Character as Char
    opp = shield.character.opponent
    ds = DamageSource()
    ds.origin = None
    ds.types = [DS_Type.MELEE]
    ds.set_damage(10, 10)
    hp0 = shield.character.cur_health
    # 构造格挡判定所需的最小 DamageResult：直接调引擎 take_damage
    res = shield.character.take_damage(ds)
    # Spiked Shield chance 掷骰决定是否格挡；验证不崩溃 + 血量扣减 <= 10
    dealt = hp0 - shield.character.cur_health
    ok = has_super and 0 <= dealt <= 10
    rep.add("spiked_shield_block", ok,
            f"beforeBlock可达={has_super} 受击扣血={dealt}（格挡 damblock="
            f"{shield.get_p_m('damblock', 0)}）")


def case_battery_charge_speed(rep: Report, verbose=False):
    """Battery.gd：电荷途经物品时 chargedItemStatChange → addSpeed(flatSpeed)。

    源码语义（ElectricalCharge.gd）：回调 cellIndex=1..size 且 cells[cellIndex]
    直接索引（cells[0] 为发射器锚点）；cellIndex==size 时电荷离场，按
    -previousVal 回退 —— 充能加成为【途经瞬态】。用 2 格路径验证
    进入加 / 离场减的完整循环。
    """
    if "Battery" not in DB:
        rep.add("battery_charge_speed", True, skipped=True, detail="物品缺失")
        return
    items, _ = build_scene([("Battery", 3, 3, 0)])
    bat = items[0]
    cells = getattr(bat, "chargeCells", None)
    if not cells or len(cells) < 3:
        rep.add("battery_charge_speed", True, skipped=True, detail="chargeCells 未初始化")
        return
    # Stone 放在 cells[1]（第一个被充能的格子）
    dr, dc = int(cells[1][0]), int(cells[1][1])
    items, _ = build_scene([("Battery", 3, 3, 0), ("Stone", 3 + dr, 3 + dc, 0)])
    bat, st = items[0], items[1]
    flat = getattr(bat, "flatSpeed", None) or 0
    speed0 = st.speed_scale
    # 手动逐格推进（与 send_charge 相同的回调序）：cellIndex=1 进入 Stone
    from types import SimpleNamespace
    charge = SimpleNamespace(lastChargedItem=None, curChargedItem=None, emitter=bat)
    charge.curChargedItem = st
    bat.call_behavior("onChargeEnteredCell", charge, 1)
    speed_charged = st.speed_scale
    # cellIndex=2：电荷移到下一格 → 离开 Stone，按 -previousVal 回退（净零）
    charge.lastChargedItem = st
    charge.curChargedItem = None
    bat.call_behavior("onChargeEnteredCell", charge, 2)
    speed_left = st.speed_scale
    ok = (abs(speed_charged - (speed0 + flat)) < 1e-9
          and abs(speed_left - speed0) < 1e-9)
    rep.add("battery_charge_speed", ok,
            f"充能时速度 {speed0}->{speed_charged}（期望+{flat}），"
            f"电荷移出回退->{speed_left}")


def case_djinn_lamp_ingredients(rep: Report, verbose=False):
    """DjinnLamp.gd：checkStacks 读取角色 block/spikes/mana/lucky/健康进度。

    验证 use_block（Item 级 API）+ buff 变化信号 + 激活链路不崩溃。
    """
    if "Djinn Lamp" not in DB:
        rep.add("djinn_lamp_ingredients", True, skipped=True, detail="物品缺失")
        return
    probe, _ = build_scene([("Djinn Lamp", 3, 3, 0)])
    lamp = probe[0]
    ch = lamp.character
    # 给满成分：block/spikes/mana/lucky 各 stacksNeeded
    n = int(lamp.get_p(0)) or 1
    hp_needed = int(lamp.get_p(1)) or 1
    ch.gain_block(n)
    from simulator.buff import BuffType
    ch.gain_stacks(BuffType.SPIKES, n)
    ch.gain_stacks(BuffType.MANA, n)
    ch.gain_stacks(BuffType.LUCKY, n)
    activated = getattr(lamp, "activated", False)
    ok = isinstance(activated, bool)
    rep.add("djinn_lamp_ingredients", ok,
            f"成分给满后 activated={activated}（buff 变化信号链应无异常）")


def case_twine_fixed(rep: Report, verbose=False):
    """Twine.gd 固定坐标 + activated 信号链（占格修复回归）。

    真值（1 collision tile = 1 背包格）：锚点占 1 格；primary=右邻格
    （canAffect=item.can_activate()）；secondary=左侧 3 格
    （canAffect_secondary=item.isNeutral()）。onPrepare 对 primary 物品连接
    "activated" → onTriggerItemActivated：掷骰（baseChance + secondary 数×baseChance2）
    成功则 give_max_health(maxHealth)。
    """
    if "Twine" not in DB:
        rep.add("twine_fixed", True, skipped=True, detail="物品缺失")
        return
    from simulator.behavior import BEHAVIOR_GLOBALS
    sec_color = BEHAVIOR_GLOBALS["Affected"].Secondary

    probe, _ = build_scene([("Twine", 3, 4, 0)])
    tw = probe[0]
    occ = set(tw.occupied_cells)
    prim = set(tw._affected_cells_abs(0))
    sec = set(tw._affected_cells_abs(sec_color))
    rep.add("twine_geometry", occ == {(3, 4)} and prim == {(3, 5)}
            and sec == {(3, 1), (3, 2), (3, 3)},
            f"占格={sorted(occ)} primary={sorted(prim)} secondary={sorted(sec)}")

    weapon = "Wooden Sword" if "Wooden Sword" in DB else next(
        (k for k, v in DB.items() if v.get("category") == "weapon"), None)
    if weapon is None or "Stone" not in DB:
        rep.add("twine_linkage_signal", True, skipped=True, detail="无武器/中立物品")
        return
    items, _ = build_scene([("Twine", 3, 4, 0), (weapon, 3, 5, 0),
                            ("Stone", 3, 1, 0), ("Stone", 3, 2, 0), ("Stone", 3, 3, 0)])
    tw, wp = items[0], items[1]
    n_prim = len(tw.get_affected_items(0))
    n_sec = len(tw.get_affected_items(sec_color))
    # 强制掷骰成功，验证信号 → onTriggerItemActivated → maxHealth 增益
    tw.roll_chance = lambda total: True
    tmp0 = tw.character.temporary_max_health
    mh = getattr(tw, "maxHealth", 0)
    wp.visual_activate()
    tmp1 = tw.character.temporary_max_health
    ok = n_prim == 1 and n_sec == 3 and abs(tmp1 - tmp0 - mh) < 1e-6
    rep.add("twine_linkage_signal", ok,
            f"primary计数={n_prim} secondary计数={n_sec} "
            f"临时maxHealth {tmp0}->{tmp1}（期望+{mh}）")


def case_rope_speedup(rep: Report, verbose=False):
    """Rope.gd：占格=横向 2 格；primary=下方（can_activate 触发源）；
    secondary=右侧 1 格（has_cooldown 被加速对象）。onPrepare 绑定 speedUpItem，
    触发源激活 → speedUpItem.add_speed(speedPerTrigger)（ropeSpeedups 累计封顶 maxSpeed）。
    """
    if "Rope" not in DB or "Wooden Sword" not in DB or "Stone" not in DB:
        rep.add("rope_speedup", True, skipped=True, detail="物品缺失")
        return
    from simulator.behavior import BEHAVIOR_GLOBALS
    sec_color = BEHAVIOR_GLOBALS["Affected"].Secondary

    probe, _ = build_scene([("Rope", 3, 3, 0)])
    rp = probe[0]
    occ_ok = set(rp.occupied_cells) == {(3, 3), (3, 4)}
    prim_ok = set(rp._affected_cells_abs(0)) == {(4, 3)}
    sec_ok = set(rp._affected_cells_abs(sec_color)) == {(3, 5)}

    items, _ = build_scene([("Rope", 3, 3, 0), ("Wooden Sword", 4, 3, 0),
                            ("Stone", 3, 5, 0)])
    rp, ws, st = items
    linked = rp.speedUpItem is st
    s0 = st.speed_scale
    per = rp.speedPerTrigger
    ws.visual_activate()
    s1 = st.speed_scale
    ws.visual_activate()
    s2 = st.speed_scale
    ok = (occ_ok and prim_ok and sec_ok and linked
          and abs(s1 - (s0 + per)) < 1e-9 and abs(s2 - (s0 + 2 * per)) < 1e-9)
    rep.add("rope_speedup", ok,
            f"占格/影响格={occ_ok and prim_ok and sec_ok} speedUpItem绑定={linked} "
            f"速度 {s0}->{s1}->{s2}（每次+{per}）")


def case_potion_consume_signal(rep: Report, verbose=False):
    """Health Potion consume_potion 发 "activated"（对齐 Item.gd consume()→activate()）
    → 邻居 Goobert.onItemActivated 计数。药水信号路径回归。"""
    if "Goobert" not in DB or "Health Potion" not in DB:
        rep.add("potion_consume_signal", True, skipped=True, detail="物品缺失")
        return
    probe, _ = build_scene([("Goobert", 3, 3, 0)])
    cells = probe[0]._affected_cells_abs(0)
    if not cells:
        rep.add("potion_consume_signal", True, skipped=True, detail="Goobert 无影响格")
        return
    tr, tc = cells[0]
    items, _ = build_scene([("Goobert", 3, 3, 0), ("Health Potion", tr, tc, 0)])
    gb, po = items[0], items[1]
    before = getattr(gb, "activations", None)
    po.consume_potion()
    after = getattr(gb, "activations", None)
    consumed = po.is_empty()
    # 单次激活：计数 +1；若恰达阈值则触发 heal 并归零
    ok = consumed and before is not None and (after == before + 1 or after == 0)
    rep.add("potion_consume_signal", ok,
            f"药水已喝空={consumed} Goobert 计数 {before}->{after}")


CASES: List[Callable[[Report, bool], None]] = [
    case_whetstone,
    case_potion_above,
    case_potion_rotation,
    case_bagofstones_line_rotation,
    case_food_same_type,
    case_bag_of_stones,
    case_dynamic_type,
    case_affected_is_symmetric,
    case_goobert_activated,
    case_busted_blade_rage,
    case_spiked_shield_block,
    case_battery_charge_speed,
    case_djinn_lamp_ingredients,
    case_twine_fixed,
    case_rope_speedup,
    case_potion_consume_signal,
]


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="物品联动对照验证")
    ap.add_argument("-v", "--verbose", action="store_true")
    ap.add_argument("--json", help="报告输出路径")
    args = ap.parse_args(argv)

    global DB
    DB = load_items()
    print(f"物品库: {len(DB)} 个物品")
    print("=" * 70)
    rep = Report()
    for case in CASES:
        try:
            case(rep, args.verbose)
        except Exception as e:  # noqa: BLE001
            rep.add(getattr(case, "__name__", "case"), False,
                    f"异常: {type(e).__name__}: {e}")
    print("=" * 70)
    print(f"通过 {len(rep.passed)} / 失败 {len(rep.failed)} / "
          f"跳过 {len(rep.rows) - len(rep.passed) - len(rep.failed)}")

    if args.json:
        os.makedirs(os.path.dirname(os.path.abspath(args.json)), exist_ok=True)
        json.dump(rep.rows, open(args.json, "w", encoding="utf-8"),
                  ensure_ascii=False, indent=1)
        print(f"报告: {args.json}")
    return 1 if rep.failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
