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
