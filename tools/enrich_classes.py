# -*- coding: utf-8 -*-
"""enrich_classes.py — 从 ItemData_e.csv 提取职业归属位掩码写入 battle_items.json

引擎真值（ItemBook.gd 890-945 / ItemDescriptor.gd StuffedClasses）：
  shop == "" / "unique" / "special" -> Neutral (127)
  shop == "no"                      -> None (0)
  "Class>Subclass"                  -> 1 << Classes_Full[Class]
  "Class[,Class...] [rounds]"       -> sum(StuffedClasses[每段])（技能类）
  "Class"                           -> 1 << Classes_Full[Class]
class_override 列非空时覆盖（getEnuStuffed 按名解析）。

用法：
  python tools/enrich_classes.py            # 写库（自动 .bak 备份）
  python tools/enrich_classes.py --check    # 只报告覆盖率
"""
from __future__ import annotations

import csv
import json
import os
import shutil
import sys
from datetime import datetime

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_PATH = os.path.join(ROOT, "decompiled_full", "Sheets", "CSV", "ItemData_e.csv")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

# ItemDescriptor.gd StuffedClasses 枚举
STUFFED = {"Ranger": 1, "Reaper": 2, "Berserker": 4, "Pyromancer": 8,
           "Mage": 16, "Adventurer": 32, "Engineer": 64, "Neutral": 127}
# Game.gd 138 Classes_Full 枚举
CLASSES_FULL = {"Ranger": 0, "Reaper": 1, "Berserker": 2, "Pyromancer": 3,
                "Mage": 4, "Adventurer": 5, "Engineer": 6}


def shop_to_classes(shop: str):
    """ItemBook.gd 890-945 的 shop 列 -> StuffedClasses 位掩码"""
    shop = (shop or "").strip()
    if shop == "":
        return 127                                   # Neutral
    if shop == "no":
        return 0                                     # None
    if shop in ("unique", "special"):
        return 127                                   # Neutral
    if ">" in shop:
        cls = shop.split(">", 1)[0]
        if cls in CLASSES_FULL:
            return 1 << CLASSES_FULL[cls]
        return None
    # "Class[,Class...] [rounds]"（技能）或裸类名
    head = shop.split(" ")[0] if " " in shop else shop
    names = [s.strip() for s in head.split(",") if s.strip()]
    total = 0
    for n in names:
        if n in STUFFED:
            total += STUFFED[n]
        elif n in CLASSES_FULL:
            total += 1 << CLASSES_FULL[n]
        else:
            return None                              # 未识别（新类名？）
    return total


def apply_recipe_inheritance(items: dict) -> int:
    """ItemBook.calcClassAvailability（ItemBook.gd:1282-1297）+
    ItemDescriptor.calcClassAvailability（ItemDescriptor.gd:175-198）的还原。

    * gateItem 分支：classes==None(0) 且有 gateItem → classes = gateItem.classes
      （95 件，如 Amulet 系 ← Amulet Unidentified）。
    * 配方分支：originatingRecipes 非空 → 对每条配方
      recipeClasses = Neutral(127) 后逐成分 &= ingredient.classes，
      再 classes |= recipeClasses——成分表为空或成分全中性时恒吃满 127。

    实证（run634_r18 [TWINE] 标记）：Evil Cap shop="no" 解析期 classes=0，
    但它是 Leather Helm 配方 Corrupted Crystal>Evil Cap 的产物 → 运行期
    classes=127、isNeutral()=true；内核按 0 判非中性 → Twine totalChance
    40 vs 神谕 80（sec=1 vs 3），run634 首分歧直接来源。

    不动点迭代（合成深度序的等价：浅层先收敛，深层随之），≤16 轮。
    """
    gate = {}
    with open(CSV_PATH, encoding="utf-8-sig") as f:
        for r in csv.DictReader(f):
            g = (r.get("gateItem") or "").strip()
            if g:
                gate[r["name"]] = g

    classes = {k: int(v.get("classes") or 0) for k, v in items.items()}
    recipes = {}
    for k, v in items.items():
        for rec in v.get("originating_recipes") or []:
            recipes.setdefault(k, []).append([rec["b"]] + list(rec["i"]))

    changed_total = 0
    for _round in range(16):
        changed = False
        for k in items:
            cur = classes.get(k, 0)
            g = gate.get(k)
            if g and g in classes and cur == 0:
                cur = classes[g]
            if k in recipes:
                acc = 0
                for ings in recipes[k]:
                    rc = STUFFED["Neutral"]
                    for ing in ings:
                        rc &= classes.get(ing, 0)
                    acc |= rc
                cur |= acc
            if cur != classes.get(k, 0):
                classes[k] = cur
                changed = True
        if not changed:
            break
    diff = 0
    for k, v in items.items():
        want = classes.get(k, 0)
        if int(v.get("classes") or 0) != want:
            v["classes"] = want
            diff += 1
    changed_total = diff
    print(f"配方类继承/gate 覆写：变更 {changed_total} 件")
    return changed_total


def main():
    check_only = "--check" in sys.argv
    rows = {}
    with open(CSV_PATH, encoding="utf-8-sig") as f:
        for r in csv.DictReader(f):
            rows[r["name"]] = r
    print(f"ItemData_e.csv: {len(rows)} 行")

    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    covered = missing = changed = 0
    for key, v in items.items():
        r = rows.get(key)
        if r is None:
            missing += 1
            continue
        override = (r.get("class_override") or "").strip()
        if override:
            cls = STUFFED.get(override)
        else:
            cls = shop_to_classes(r.get("shop"))
        if cls is None:
            missing += 1
            continue
        covered += 1
        if v.get("classes") != cls:
            changed += 1
            v["classes"] = cls
    print(f"覆盖 {covered} / 缺失 {missing} / 本次变更 {changed}")

    # round3 追加：配方类继承 + gateItem 覆写（ItemDescriptor.calcClassAvailability）
    apply_recipe_inheritance(items)

    if check_only:
        return
    if changed:
        stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        shutil.copy2(DB_PATH, f"{DB_PATH}.bak_{stamp}")
        json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
        print(f"已写出 {DB_PATH}（备份 .bak_{stamp}）")
    else:
        print("无变更，不写库")


if __name__ == "__main__":
    main()
