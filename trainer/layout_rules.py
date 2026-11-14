# -*- coding: utf-8 -*-
"""layout_rules.py — P0 形式化基座：双层合法性判定 + 加成指派提取 + 失败诊断

规则真值来源（全部已核实，见 docs/训练路径规划.md §2 与 trainer/p0_verify_report.json）：
  * 战斗网格 = 9 列 × 7 行 = 63 格（oracle/Core/Inventory.gd:38 inventorySize=(9,7)，
    无禁区——isInventoryCell 是纯矩形判定 :88-91）。
  * 层 0（包层）：只能放包；包登记 **extension 格**（Inventory.gd:595-606
    addItemByTopLeft 对 isBag 用 getExtensionPoints）；包与包不重叠。
    运行时资产 rot[deg].collision 对包 = extension 格（extract_grid.py 把 Tile 2/3
    并入 collision_cells；p0_verify R1 证实 27 包 extension==collision，无混合）。
  * 层 1（物品层）：物品登记 collision 格（非包物品）；物品与物品不重叠；
    物品每个占格必须落在 ⋃bagCells 内，否则浮空（Inventory.gd:393-399）。
  * 物品可跨包：getItemsInCells 按格查 filledCells（CoreGrid.py:192-202）。
  * 加成两类覆盖域（逐包源码核实，见 BAG_SPECS 注释）：
      - occupied 域：getItemsInside()（占格与包重叠的物品）
      - affected 域：getAffectedItemsInside()（物品占格命中包的 affected 格）
  * 坐标系：lineup v4 `at=[row, col]`；内核 occupied=(col+dx, row+dy)。
    本模块对内统一用 (x=col, y=row)，对外接口接受 row/col 形式。

本模块是训练侧的纯 Python 复核器——**不替代引擎**，只负责：
  1) 搜索/训练产出的摆盘能否真摆出来（含失败原因）
  2) 给定布局下 A/B 类解析目标（§5.4 一级，免费）
"""
from __future__ import annotations

import json
import os
import re
from typing import Dict, List, Optional, Sequence, Tuple

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# ── 战斗网格（已核实：Inventory.gd:37-38）──
COLS = 9   # x ∈ [0, 9)
ROWS = 7   # y ∈ [0, 7)
NUM_CELLS = COLS * ROWS  # 63

Stack = {
    "Block": 1, "Lucky": 2, "Regeneration": 4, "Vampirism": 8, "Spikes": 16,
    "Mana": 32, "Empower": 64, "Heat": 128, "Poison": 256, "Blind": 512,
    "Cold": 1024,
}
STACK_BUFF = 2 | 4 | 8 | 16 | 32 | 64 | 128      # CoreConst Stack.Buff = 254
STACK_DEBUFF = 256 | 512 | 1024                   # Stack.Debuff = 1792
TAG_LIFESTEAL = 1

# EngineerBox.canApplyEffect: toItem.has_method("emitCharge")（源码枚举）
EMIT_CHARGE_ITEMS = {"Battery", "Charge Splitter", "Cog Badge", "Con Trap Tron",
                     "Generator", "Lightning Staff", "Mana Crystal"}

_ITEM_KIND_SINGULAR = 0


# ═════════════════════════ 物品索引 ═════════════════════════

class ItemIndex:
    """运行时资产只读索引：几何（rot.collision / rot.affected）+ 谓词所需字段。"""

    def __init__(self, runtime_path: Optional[str] = None):
        path = runtime_path or os.path.join(ROOT, "assets", "gd_core_runtime.json")
        with open(path, encoding="utf-8") as f:
            self.runtime = json.load(f)
        self.items: Dict[str, dict] = self.runtime["items"]
        self._bags: Optional[frozenset] = None

    # ── 包判定：继承链闭包（与 p0_verify 同口径，结果=27 包）──
    def bag_set(self) -> frozenset:
        if self._bags is None:
            extends_map = {}
            for root, _dirs, files in os.walk(os.path.join(ROOT, "gd_core_items")):
                for fn in files:
                    if fn.endswith(".gd"):
                        with open(os.path.join(root, fn), encoding="utf-8") as f:
                            for line in f:
                                m = re.match(r"extends\s+(\w+)", line)
                                if m:
                                    extends_map[fn[:-3]] = m.group(1)
            bags = {"Bag"}
            changed = True
            while changed:
                changed = False
                for mod, ext in extends_map.items():
                    if ext in bags and mod not in bags:
                        bags.add(mod)
                        changed = True
            names = set()
            for name, v in self.items.items():
                if os.path.basename(v["script"])[:-3] in bags:
                    names.add(name)
            self._bags = frozenset(names)
        return self._bags

    def is_bag(self, name: str) -> bool:
        return name in self.bag_set()

    def descr(self, name: str) -> dict:
        return self.items[name]["descr"]

    def has(self, name: str) -> bool:
        return name in self.items

    # ── 几何：锚点系（包围盒左上 = (0,0)，对齐 serializeRound getTopLeftCell）──
    def collision_cells(self, name: str, rot: int) -> Tuple[Tuple[int, int], ...]:
        r = self.items[name]["rot"][str(int(rot) % 360)]
        return tuple((c[0], c[1]) for c in r["collision"])

    def affected_cells(self, name: str, rot: int) -> Tuple[Tuple[int, int], ...]:
        r = self.items[name]["rot"][str(int(rot) % 360)]
        out = []
        for _color, cells in r["affected"].items():
            out.extend((c[0], c[1]) for c in cells)
        return tuple(out)

    def num_cells(self, name: str, rot: int = 0) -> int:
        return len(self.collision_cells(name, rot))

    # ── 谓词字段（翻译自 gd_core_py/gd_core/CoreItem.py，见文件头来源）──
    def has_cooldown(self, name): return self.descr(name)["cd"] != 0
    def can_damage(self, name):
        d = self.descr(name)
        return d["minDam"] > 0 or (d["tags"] & TAG_LIFESTEAL) != 0
    def can_activate(self, name): return bool(self.descr(name)["canActivate"])
    def has_type(self, name, t): return int(t) in self.descr(name)["types"]
    def is_weapon(self, name):
        # CoreItemData.isWeapon: types 含 Type.Weapon=4（CoreConst.Type 枚举）
        return 4 in self.descr(name)["types"]
    def is_neutral(self, name):
        # CoreItemData.isNeutral: classes == StuffedClasses.Neutral(127)
        return self.descr(name)["classes"] == 127
    def is_class_item(self, name):
        # CoreItemData.isClassItem: classes != Neutral(127) and classes != None(0)
        c = self.descr(name)["classes"]
        return c != 127 and c != 0
    def can_be_empowered(self, name):
        return self.is_weapon(name) and self.can_damage(name)
    def gains_stack(self, name, s): return (self.descr(name)["gainedStacks"] & s) != 0
    def gains_buffs(self, name): return (self.descr(name)["gainedStacks"] & STACK_BUFF) != 0
    def uses_buffs(self, name): return (self.descr(name)["usedStacks"] & STACK_BUFF) != 0
    def inflicts_debuffs(self, name): return (self.descr(name)["gainedStacks"] & STACK_DEBUFF) != 0
    def can_heal_or_lifesteal(self, name):
        return "heal" in self.descr(name)["namedParams"] or "lifesteal" in self.descr(name)["namedParams"]
    def has_inventory_duration(self, name):
        # CoreItem.py:1357 descrInventoryDuration —— params 含 dur>0 的口径由调用方
        # （PuzzlebagJ.modifyParam("dur")）反推：namedParams 有 dur
        return "dur" in self.descr(name)["namedParams"]
    def is_crafted(self, name):
        # CoreItem.py:1369 —— 由武器+宝石组合而来；静态口径：sockets>0 且 is_weapon
        return self.descr(name)["sockets"] > 0 and self.is_weapon(name)
    def rarity(self, name): return int(self.descr(name)["rarity"])
    def emit_charge(self, name): return name in EMIT_CHARGE_ITEMS


# ═════════════════════════ 布局表示 ═════════════════════════
# 条目 = {"id": 物品名, "rot": 0/90/180/270, "row": y, "col": x}
# 与 lineup v4 JSON 的 items[] 同构（at=[row, col] → row=at[0], col=at[1]）。


def occ_of(index: ItemIndex, e: dict) -> List[Tuple[int, int]]:
    """占格（绝对坐标 (x=col, y=row)）。"""
    return [(c[0] + int(e["col"]), c[1] + int(e["row"]))
            for c in index.collision_cells(e["id"], e.get("rot", 0))]


def affected_of(index: ItemIndex, e: dict) -> List[Tuple[int, int]]:
    return [(c[0] + int(e["col"]), c[1] + int(e["row"]))
            for c in index.affected_cells(e["id"], e.get("rot", 0))]


def in_bounds(cells: Sequence[Tuple[int, int]]) -> bool:
    return all(0 <= x < COLS and 0 <= y < ROWS for x, y in cells)


# ── 诊断码（规划 §7 P0-3）──
D_OUT_OF_BOUNDS = "OUT_OF_BOUNDS"   # 占格出 9×7
D_BAG_OVERLAP = "BAG_OVERLAP"       # 包与包重叠
D_ITEM_OVERLAP = "ITEM_OVERLAP"     # 物品与物品重叠
D_NO_CONTAINER = "NO_CONTAINER"     # 物品某格没有包垫（浮空）
D_BAD_ITEM = "BAD_ITEM"             # 物品名不在运行时资产
D_BAD_ROT = "BAD_ROT"               # 朝向非法


def check_layout(index: ItemIndex, entries: Sequence[dict]) -> Tuple[bool, List[dict]]:
    """双层合法性判定（规划 §7 P0-1）。返回 (ok, diagnostics)。

    判定顺序即失败诊断顺序：先几何存在性，再两层各自的重叠，最后浮空。
    """
    diags: List[dict] = []
    bags, items = [], []
    for e in entries:
        if not index.has(e["id"]):
            diags.append({"code": D_BAD_ITEM, "item": e["id"]})
            continue
        rot = int(e.get("rot", 0)) % 360
        if str(rot) not in index.items[e["id"]]["rot"]:
            diags.append({"code": D_BAD_ROT, "item": e["id"], "rot": rot})
            continue
        entry = dict(e, rot=rot)
        occ = occ_of(index, entry)
        if not in_bounds(occ):
            diags.append({"code": D_OUT_OF_BOUNDS, "item": e["id"],
                          "cells": [c for c in occ if not (0 <= c[0] < COLS and 0 <= c[1] < ROWS)]})
            continue
        (bags if index.is_bag(e["id"]) else items).append((entry, occ))

    # 层 0：包包不重叠
    for i in range(len(bags)):
        for j in range(i + 1, len(bags)):
            hit = set(bags[i][1]) & set(bags[j][1])
            if hit:
                diags.append({"code": D_BAG_OVERLAP, "a": bags[i][0]["id"],
                              "b": bags[j][0]["id"], "cells": sorted(hit)})
    # 层 1：物物品不重叠
    for i in range(len(items)):
        for j in range(i + 1, len(items)):
            hit = set(items[i][1]) & set(items[j][1])
            if hit:
                diags.append({"code": D_ITEM_OVERLAP, "a": items[i][0]["id"],
                              "b": items[j][0]["id"], "cells": sorted(hit)})
    # 层 1 ⊆ 层 0：浮空
    bag_union = set()
    for _e, occ in bags:
        bag_union |= set(occ)
    for e, occ in items:
        floating = [c for c in occ if c not in bag_union]
        if floating:
            diags.append({"code": D_NO_CONTAINER, "item": e["id"],
                          "cells": sorted(floating)})
    return (not diags), diags


def diagnose_fit(index: ItemIndex, entries: Sequence[dict],
                 candidate: dict) -> List[str]:
    """SHAPE_FIT 细诊：容器层有空位但形状塞不进时，返回可放/受阻原因。
    candidate = {"id", "rot", "row", "col"}——对单件候选物品做预检（不改 entries）。"""
    reasons = []
    if not index.has(candidate["id"]):
        return [D_BAD_ITEM]
    occ = occ_of(index, candidate)
    if not in_bounds(occ):
        reasons.append(D_OUT_OF_BOUNDS)
        return reasons
    bag_union, filled = set(), {}
    for e in entries:
        o = occ_of(index, e)
        if index.is_bag(e["id"]):
            bag_union |= set(o)
        else:
            for c in o:
                filled.setdefault(c, e["id"])
    if any(c not in bag_union for c in occ):
        reasons.append(D_NO_CONTAINER)
    clash = {c: filled[c] for c in occ if c in filled}
    if clash:
        reasons.append(D_ITEM_OVERLAP + ":" + ",".join(
            sorted(set(clash.values()))))
    return reasons or ["OK"]


# ═════════════════════════ 加成指派提取 ═════════════════════════
# 逐包规格（源码出处 = gd_core_py/gd_core_items[/Exclusive]/<Mod>.py）：
#   coverage: "items"    → getItemsInside()：物品占格 ∩ 包占格（ occupied 域）
#             "affected" → getAffectedItemsInside()：物品占格 ∩ 包 affected 格
#   cond:     canApplyEffect 谓词（翻译成 descr 谓词），None=无谓词（全部计入）
#   effect:   加成效果标签（解析目标的 B 类权重键，量级=【推断】待校准）
#
# 未列出效果的包（Bagtacular/EngineerBag2/RandomLoadoutBag/RelicCase 主体、
# ExtraBags 空位加速）对指派不产生 per-item 边，只进 A 类或全局协同。
BAG_SPECS: Dict[str, dict] = {
    "Fanny Pack":     {"coverage": "items", "cond": "cooldown_nonbag", "effect": "speed",
                       "global": [("fanny_x_bagtacular", "Bagtacular")]},
    "Ranger Bag":     {"coverage": "items", "cond": "can_damage", "effect": "crit"},
    "Potion Belt":    {"coverage": "items", "cond": "hasType_potion", "effect": "potion_amp"},
    "Storage Coffin": {"coverage": "items", "cond": "activate_nonbag", "effect": "charge_amp"},
    "Toolbox":        {"coverage": "items", "cond": "can_be_empowered", "effect": "toolbox"},
    "Holdall":        {"coverage": "affected", "cond": "is_neutral", "effect": "block"},
    "Box of Prosperity": {"coverage": "affected", "cond": "rarity_ge_1", "effect": "gold"},
    "Engineer Box":   {"coverage": "affected", "cond": "emit_charge", "effect": "charge_relay"},
    "Bag of Giving":  {"coverage": "affected", "cond": "class_item", "effect": "giving"},
    "Puzzlebag J":    {"coverage": "affected", "cond": "inv_duration", "effect": "dur"},
    "Puzzlebag L":    {"coverage": "affected", "cond": "heal_or_lifesteal", "effect": "healamp"},
    "Puzzlebag S":    {"coverage": "affected", "cond": "gains_buffs", "effect": "buff_amp"},
    "Puzzlebag T":    {"coverage": "affected", "cond": "uses_buffs", "effect": "buff_use"},
    "Puzzlebag Z":    {"coverage": "affected", "cond": "inflicts_debuffs", "effect": "debuff_amp"},
    "Puzzlebox":      {"coverage": "affected", "cond": "has_cooldown", "effect": "slow"},
    "Scholar Bag":    {"coverage": "affected", "cond": "gains_stack_lucky", "effect": "mana"},
    "Sewing Case":    {"coverage": "affected", "cond": "crafted_cd_or_buff", "effect": "sewing"},
    "Relic Case":     {"coverage": "affected", "cond": "is_weapon", "effect": "relic"},
    "Fire Pit":       {"coverage": "affected", "cond": "hasType_food", "effect": "firepit"},
    "Vineweave Basket": {"coverage": "affected", "cond": None, "effect": "healamp_char"},
    "Berserker Bag":  {"coverage": "items", "cond": "has_cooldown", "effect": "rage"},
    "Protective Purse": {"coverage": None, "cond": None, "effect": "block_char",
                         "global": [("purse_x_bagtacular", "Bagtacular")]},
    "Stamina Sack":   {"coverage": None, "cond": None, "effect": "stamina_reg",
                       "global": [("sack_x_bagtacular", "Bagtacular")]},
    "Portable Altar": {"coverage": None, "cond": None, "effect": "empower_char"},
    "Sandbag":        {"coverage": None, "cond": None, "effect": "blind_char"},
    "Bagtacular":     {"coverage": None, "cond": None, "effect": "bagtacular"},
    "Engineer Bag 2": {"coverage": None, "cond": None, "effect": "engineer2"},
    "Random Loadout Bag": {"coverage": None, "cond": None, "effect": "random_loadout"},
    "Extra Bags":     {"coverage": None, "cond": None, "effect": "free_slot_speed"},
    "Leather Bag":    {"coverage": None, "cond": None, "effect": None},
}

# 全局协同（规划 §2.6「位置无关」已核实：FannyPack.py:105-108）
# FannyPack.onCombatStart: isTypeInInventory(Bagtacular) → speed += Bagtacular.getP("speed")/100
# ProtectivePurse/StaminaSack 同型：Bagtacular 在背包即加 block/stamina reg。


def _cond_fn(index: ItemIndex, cond: Optional[str]):
    """canApplyEffect 谓词的静态翻译（每条注明源码出处）。"""
    if cond is None:
        return lambda name: True
    if cond == "cooldown_nonbag":   # FannyPack.py:122-123
        return lambda n: index.has_cooldown(n) and not index.is_bag(n)
    if cond == "has_cooldown":      # BerserkerBag.py / Puzzlebox.py
        return lambda n: index.has_cooldown(n)
    if cond == "can_damage":        # RangerBag.py:121-122
        return lambda n: index.can_damage(n)
    if cond == "can_be_empowered":  # Toolbox.py
        return lambda n: index.can_be_empowered(n)
    if cond == "activate_nonbag":   # StorageCoffin.py
        return lambda n: index.can_activate(n) and not index.is_bag(n)
    if cond == "is_neutral":        # Holdall.py
        return lambda n: index.is_neutral(n)
    if cond == "rarity_ge_1":       # BoxofProsperity.py
        return lambda n: index.rarity(n) >= 1
    if cond == "emit_charge":       # EngineerBox.py
        return lambda n: index.emit_charge(n)
    if cond == "class_item":        # BagofGiving.py
        return lambda n: index.is_class_item(n)
    if cond == "inv_duration":      # PuzzlebagJ.py
        return lambda n: index.has_inventory_duration(n)
    if cond == "heal_or_lifesteal":  # PuzzlebagL.py
        return lambda n: index.can_heal_or_lifesteal(n)
    if cond == "gains_buffs":       # PuzzlebagS.py
        return lambda n: index.gains_buffs(n)
    if cond == "uses_buffs":        # PuzzlebagT.py
        return lambda n: index.uses_buffs(n)
    if cond == "inflicts_debuffs":  # PuzzlebagZ.py
        return lambda n: index.inflicts_debuffs(n)
    if cond == "gains_stack_lucky":  # ScholarBag.py gainsStack(Stack.Lucky=2)
        return lambda n: index.gains_stack(n, Stack["Lucky"])
    if cond == "crafted_cd_or_buff":  # SewingCase.py: isCrafted and (hasCooldown or gainsBuffs)
        return lambda n: (index.is_crafted(n)
                          and (index.has_cooldown(n) or index.gains_buffs(n)))
    if cond == "is_weapon":         # RelicCase.py
        return lambda n: index.is_weapon(n)
    if cond == "hasType_potion":    # PotionBelt.py（Type.Potion）
        return lambda n: index.has_type(n, 11)  # CoreConst.Type: Bag0 Consumable1 Food2 Pet3
        # Weapon4 Shield5 Armor6 Gloves7 Shoes8 Helmet9 Accessory10 Potion11
    if cond == "hasType_food":      # FirePit.py（Type.Food）
        return lambda n: index.has_type(n, 2)   # Type.Food=2
    return lambda n: True


def assign_bonuses(index: ItemIndex, entries: Sequence[dict]) -> Dict[int, list]:
    """加成指派提取器（规划 §7 P0-2）。返回 {物品条目下标: [(包条目下标, 包名, 效果)]}。

    处理：跨包（一物品多包覆盖各计一条）+ 全局协同（不占格、无 coverage）。
    前提：entries 已通过 check_layout（本函数不做合法性复核）。
    """
    bags, items = [], []
    for i, e in enumerate(entries):
        if index.is_bag(e["id"]):
            bags.append((i, e))
        else:
            items.append((i, e))

    bag_union: Dict[Tuple[int, int], Tuple[int, str]] = {}   # cell → (bag_idx, bag_name)
    affected_union: Dict[Tuple[int, int], Tuple[int, str]] = {}
    for i, e in bags:
        for c in occ_of(index, e):
            bag_union.setdefault(c, (i, e["id"]))
        for c in affected_of(index, e):
            affected_union.setdefault(c, (i, e["id"]))

    present_names = {e["id"] for e in entries}
    out: Dict[int, list] = {}

    def add(ii, bi, bag_name, effect):
        out.setdefault(ii, []).append((bi, bag_name, effect))

    for ii, e in items:
        occ = set(occ_of(index, e))
        for spec_name, spec in BAG_SPECS.items():
            if spec["coverage"] is None:
                continue
            domain = bag_union if spec["coverage"] == "items" else affected_union
            # 同名多包：逐包独立判定（每包各自的域）
            for bi, be in bags:
                if be["id"] != spec_name:
                    continue
                cov = spec["coverage"]
                be_occ = set(occ_of(index, be))
                be_aff = set(affected_of(index, be))
                hit_cells = (occ & be_occ) if cov == "items" else (occ & be_aff)
                if not hit_cells:
                    continue
                cond = _cond_fn(index, spec["cond"])
                if spec["cond"] is None or cond(e["id"]):
                    add(ii, bi, be["id"], spec["effect"])

    # 全局协同：包名在场上即生效，与位置无关
    for bi, be in bags:
        for syn_name, partner in [(s[0], s[1]) for s in BAG_SPECS.get(be["id"], {}).get("global", [])]:
            if partner in present_names:
                add(bi, bi, partner, syn_name)
    return out


# ═════════════════════════ 解析目标函数（A/B 类） ═════════════════════════
# §5.4 一级（免费）。C 类（涌现协同）必须引擎实测——本函数刻意不算。
# 权重 = 【推断】初值，仅用于搜索初筛排序；终评一律引擎实测。

WEIGHTS = {
    "dmg": 1.0,        # 期望单次伤害（(min+max)/2 × cd 频率在 C 类体现，A 类只记面板）
    "block": 1.0,
    "heal": 1.0,
    "mana": 0.5,
    "luck": 0.3,
    "spikes": 0.5,
    "regen": 1.0,
    "vampirism": 0.6,
    "speed": 8.0,       # speed 百分点
    "crit": 0.4,        # crit 百分点
    "empower": 1.0,
    "stamina_reg": 2.0,
    "healamp": 0.8,     # 百分点
    "buff_amp": 0.5,
    "debuff_amp": 0.5,
    "dur": 0.5,
    "slow": 2.0,
    "gold": 0.0,        # 战斗内无效
    "potion_amp": 0.5,
    "charge_amp": 0.5,
    "charge_relay": 0.5,
    "rage": 0.5,
    "toolbox": 0.5,
    "sewing": 0.5,
    "relic": 0.5,
    "firepit": 0.5,
    "giving": 0.5,
    "buff_use": 0.3,
    "block_char": 1.0,
    "stamina_reg_char": 1.0,
    "empower_char": 1.0,
    "blind_char": 0.3,
    "mana_char": 0.5,
    "healamp_char": 0.8,
    "fanny_x_bagtacular": 2.0,
    "purse_x_bagtacular": 1.0,
    "sack_x_bagtacular": 1.0,
}


def analytic_score(index: ItemIndex, entries: Sequence[dict]) -> dict:
    """A/B 两级解析目标。返回 {A, B, detail}。

    A 类：无条件属性——每件在场物品的 namedParams 直接求和（含包自身 params）。
    B 类：覆盖加成型——assign_bonuses 的每条指派按效果权重计一次。
    """
    a = 0.0
    a_detail: Dict[str, float] = {}
    for e in entries:
        d = index.descr(e["id"])
        for k, v in d.get("namedParams", {}).items():
            if k in ("luck", "spikes", "heal", "block", "mana", "regen",
                     "vampirism", "empower", "stamina"):
                key = {"stamina": "stamina_reg"}.get(k, k)
                a += WEIGHTS.get(key, 0.0) * float(v)
                a_detail[key] = a_detail.get(key, 0.0) + float(v)
        d_min, d_max = float(d["minDam"]), float(d["maxDam"])
        if d_min or d_max:
            a += WEIGHTS["dmg"] * (d_min + d_max) / 2.0
    assign = assign_bonuses(index, entries)
    b = 0.0
    b_detail: Dict[str, int] = {}
    for _ii, edges in assign.items():
        for _bi, _bag, effect in edges:
            w = WEIGHTS.get(effect, 0.0)
            b += w
            b_detail[effect] = b_detail.get(effect, 0) + 1
    return {"A": round(a, 3), "B": round(b, 3),
            "A_detail": a_detail, "B_edges": b_detail}
