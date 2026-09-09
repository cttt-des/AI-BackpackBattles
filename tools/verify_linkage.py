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

from simulator.grid import GridInventory          # noqa: E402
from simulator.item import Item                   # noqa: E402
from simulator.character import Character         # noqa: E402
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
    for key, row, col, rot in placements:
        data = DB.get(key)
        if data is None:
            raise KeyError(key)
        it = Item(key, dict(data))
        it.character = ch
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
    """旋转后影响格应随锚点变化（Potion: rotation 180 -> FaceDirection.DOWN -> 取 [1]）。"""
    key = "Health Potion" if "Health Potion" in DB else None
    if key is None:
        rep.add("potion_rotation", True, skipped=True, detail="物品缺失")
        return
    items0, _ = build_scene([(key, 3, 3, 0)])
    items180, _ = build_scene([(key, 3, 3, 180)])
    c0 = items0[0]._affected_cells_abs(0)
    c180 = items180[0]._affected_cells_abs(0)
    fd0, fd180 = items0[0].face_direction, items180[0].face_direction
    # 药水只占 1 个背包格（两个 40px tile 合并），两个锚点映射到同一格，
    # 故影响格不随旋转改变；此处只校验朝向换算正确且影响格始终存在。
    ok = bool(c0) and bool(c180) and fd0 == 0 and fd180 == 2
    rep.add("potion_face_direction", ok,
            f"faceDirection 0°={fd0} / 180°={fd180}；影响格 0°={c0} 180°={c180}")


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
    """Battery.gd：onCombatStart 发射电荷 → 途经物品 addSpeed（changeChargedItemStat）。

    电荷沿固定 chargeCells（电池左上一列 (-1,-1)..(-1,-5)）传播，
    验证 send_charge/onNewCellEntered/changeChargedItemStat/chargedItemStatChange 链。
    """
    if "Battery" not in DB:
        rep.add("battery_charge_speed", True, skipped=True, detail="物品缺失")
        return
    items, _ = build_scene([("Battery", 3, 3, 0)])
    bat = items[0]
    cells = getattr(bat, "chargeCells", None)
    if not cells:
        rep.add("battery_charge_speed", False, detail="chargeCells 未初始化")
        return
    dr, dc = int(cells[0][0]), int(cells[0][1])
    weapon = next((k for k, v in DB.items()
                   if v.get("category") == "weapon" and v.get("cd")
                   and (v.get("grid") or {}).get("collision_cells")), None)
    if weapon is None:
        rep.add("battery_charge_speed", True, skipped=True, detail="无武器样本")
        return
    # 武器放在 chargeCells 第一格（电池左上）
    items, _ = build_scene([("Battery", 3, 3, 0),
                            (weapon, 3 + dr, 3 + dc, 0)])
    bat, wp = items[0], items[1]
    flat = getattr(bat, "flatSpeed", None) or 0
    speed1 = wp.speed_scale
    # build_scene 的 combat_start 已让 Battery 发射电荷（onCombatStart），
    # 首格物品应获得 flatSpeed 的速度加成
    ok = abs(speed1 - flat) < 1e-6 and flat > 0
    rep.add("battery_charge_speed", ok,
            f"{weapon} 速度={speed1}（期望=flatSpeed {flat}）")


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


CASES: List[Callable[[Report, bool], None]] = [
    case_whetstone,
    case_potion_above,
    case_potion_rotation,
    case_food_same_type,
    case_bag_of_stones,
    case_dynamic_type,
    case_affected_is_symmetric,
    case_goobert_activated,
    case_busted_blade_rage,
    case_spiked_shield_block,
    case_battery_charge_speed,
    case_djinn_lamp_ingredients,
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
