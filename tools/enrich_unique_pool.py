#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
enrich_unique_pool.py — 把 CSV shop 列=="unique" 的物品标记为 random_unique_pool

依据（1.1.8 反编译源码）：
  * Sheets/ItemBook.gd:899-901：`elif shop == "unique": … item.randomUniquePool = true`
    ——随机 unique 池物品的唯一判定来源；
  * Items/Item.gd:5723-5724：`isTreasure() -> return descriptor.randomUniquePool`
    ——Fedora 等物品的 canAffect 用它计数（run634_r18 实证：玩家 Fedora
    幸运 7 = 1 nature(Stone)×1 + 2 treasure(Cog Badge/Leaf Badge)×3；
    内核 randomUniquePool 恒缺 → treasure 计 0 → 幸运 1）。
  * CoreItemData.gd:316 已读 descr.randomUniquePool（truth()），此前数据从未携带。

数据源：decompiled_full/Sheets/CSV/ItemData_e.csv（已解密明文 CSV，
列头 `shop`；encrypted 原件为 extracted_running/decomp/Sheets/CSV/ 的 GDEC 容器）。

用法：python -X utf8 tools/enrich_unique_pool.py [--csv PATH] [--dry-run]
写入：assets/battle_items.json 各物品条目新增 "random_unique_pool": true（只增不改）。
"""
from __future__ import annotations

import argparse
import csv
import io
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
# ★ np23 data_r2：数据源切 oracle 语料版（1.1.9 录制真值）。shop==unique 集合与
#   decompiled ItemData_e.csv 全等（oracle 仅多 Time Pendant——库外行、语料零引用），
#   切源不改值，只统一战斗数据链 provenance（与 enrich_stack_flags 同口径）。
CSV_PATH = os.path.join(ROOT, "oracle", "Sheets", "CSV", "ItemData.csv")


def main() -> int:
    ap = argparse.ArgumentParser(description="标记 random_unique_pool（shop==unique）")
    ap.add_argument("--csv", default=CSV_PATH)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    rows = list(csv.DictReader(io.open(args.csv, encoding="utf-8-sig")))
    uniq = sorted({(r.get("name") or "").strip() for r in rows
                   if (r.get("shop") or "").strip().lower() == "unique"})
    print("[csv] 共 %d 行，shop==unique %d 件" % (len(rows), len(uniq)))

    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    if isinstance(items, dict):
        items = list(items.values())
    hit, miss = [], []
    for it in items:
        if not isinstance(it, dict) or "key" not in it:
            continue
        if it["key"] in uniq:
            hit.append(it["key"])
        elif it.get("random_unique_pool"):
            miss.append(it["key"])
    absent = sorted(set(uniq) - set(hit))
    print("[match] battle_items 命中 %d 件；CSV 有而库无 %d 件%s"
          % (len(hit), len(absent), ("：" + ",".join(absent[:10])) if absent else ""))

    if args.dry_run:
        print("[dry-run] 命中清单：%s" % ",".join(hit))
        return 0
    changed = 0
    for it in items:
        if isinstance(it, dict) and it.get("key") in set(hit) \
                and not it.get("random_unique_pool"):
            it["random_unique_pool"] = True
            changed += 1
    with io.open(DB_PATH, "w", encoding="utf-8", newline="\n") as fh:
        json.dump(db, fh, ensure_ascii=False, indent=1)
        fh.write("\n")
    print("[write] %s：新增标记 %d 件" % (DB_PATH, changed))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
