#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""enrich_recipes.py — 把原版配方图写进 battle_items.json（isCraftedItem 数据面）

缺口（docs/alignment_fix_workflow.md 阶段1 逐行对齐实证，run1160_r18 首分歧）：
  `ItemDescriptor.originatingRecipes`（ItemDescriptor.gd:61，由 ItemBook.parseRecipe
  → Recipe.init 注册：`fusedItem.originatingRecipes.push_back(self)`，Recipe.gd:68）
  在 battle_items.json 未导出 ⇒ 内核 `isCraftedItem()`（CoreItemData.gd:203）恒假 ⇒
  Cog.canAffect(item)=item.isCrafted() 恒空 → Cog 的开战 block/activation 整个消失
  （原版里它给相邻合成品 block×件数，gd_core 里什么都不发）。

对齐的原版注册语义（ItemBook.gd:1108-1116 → Recipe.gd:8-73）：
  1. ItemData_e.csv `recipes` 列（逗号分隔多条），每条 "A+B*>C"：
     baseItem = 行物品；`*` 后缀 = 催化剂标记；
     Recipe.init 的**丢弃规则**：任一具名成分不在已发布物品集（isReleased()==false
     的等价判定：不在 battle_items.json）→ 整条配方不注册；fusedItem 不在 → 同弃。
     类型名成分（"Any Weapon" 等 ∈ Item.Type，CoreConst.gd:344）不查发布、不进
     recipesAsIngredient，但配方照常注册。
  2. addCauldronRecipes（ItemBook.gd:1277-1291，loadExclusiveContent()==true 的正式包
     恒跑）：每件 Potion X，若 "Strong X" 存在 → 注册 X + Cauldron*(催化剂) → Strong X。

产出：battle_items.json 每件物品追加 `originating_recipes`（注册到它身上的配方列表，
元素 = {"b": 基础物品, "i": [成分], "c": [催化剂 bool], "f": 被省略（=键自身）}）。
战斗语义只消费**非空性**（isCraftedItem）；保留结构供后续战时合成（Hammer/
CraftingManager 的 getRecipes/curRecipe 链）接线。

用法：
  python tools/enrich_recipes.py            # 写入（幂等：同数据则跳过）
  python tools/enrich_recipes.py --check    # 只校验是否已同步
"""
from __future__ import annotations

import io
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

from item_sheet import load_rows  # noqa: E402  — tools/ 在 sys.path

DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

# CoreConst.gd:344 Item.Type 的键集（类型名成分的判定表，1:1）
TYPE_NAMES = {
    "Bag", "Consumable", "Food", "Pet", "Weapon", "Shield", "Armor", "Gloves",
    "Shoes", "Helmet", "Accessory", "Potion", "Card", "Gem", "Scroll", "Book",
    "Skill", "ChessPiece", "Spell", "Melee", "Ranged", "Magic", "Musical",
    "Ultimate", "Container", "Skin", "Material",
}


def compute_originating(known_items: set) -> dict:
    """→ {物品键: [注册到它的配方, …]}（Recipe.init 注册语义，见文件头）。"""
    rows = load_rows()
    originating: dict = {}

    def register(fused: str, recipe: dict) -> None:
        originating.setdefault(fused, []).append(recipe)

    # 1) CSV recipes 列
    for base, row in rows.items():
        col = (row.get("recipes") or "").strip()
        if not col:
            continue
        for recipe_str in col.split(","):
            recipe_str = recipe_str.strip()
            if not recipe_str or ">" not in recipe_str:
                continue
            formula = recipe_str.split(">")
            # ★ 催化剂 `*` 后缀必须剥掉再查发布集（对齐 decomp Recipe.gd:19-25
            #   fromString：`ingredientNames[i] = name.trim_suffix("*")`）。此前
            #   names 保留 `*`（如 "Forging Hammer*"）→ not in known_items →
            #   整条配方被丢 → 28 件合成品（Armored Wisdom Puppy / Whetstone2/
            #   3 / Dragonscale Armor…）originatingRecipes 恒空 → isCraftedItem()
            #   恒假 → Cog numAffected 1v2、开战 block 7v14、胜负翻转
            #   （run683_r9 idx0 定谳，alignment.json 实跑）。
            raw_parts = [x.strip() for x in formula[0].split("+") if x.strip()]
            catalysts = [x.endswith("*") for x in raw_parts]
            names = [x[:-1] if x.endswith("*") else x for x in raw_parts]
            fused = formula[1].strip()
            # Recipe.init 丢弃规则：具名成分/产物不在已发布物品集 → 整条不注册
            ok = fused in known_items
            for nm in names:
                if nm in TYPE_NAMES:
                    continue
                if nm not in known_items:
                    ok = False
            if not ok:
                continue
            register(fused, {"b": base, "i": names, "c": catalysts})

    # 2) 大锅配方（ItemBook.addCauldronRecipes；正式包恒跑）
    for name in known_items:
        if not name.startswith("Strong "):
            continue
        base_potion = name[len("Strong "):]
        # CSV 的类型列名是 `type`（ItemBook.gd:762 table.getEnu("type", …)）
        if base_potion in known_items and \
                str(rows.get(base_potion, {}).get("type") or "") == "Potion":
            register(name, {"b": base_potion, "i": ["Cauldron"], "c": [True]})

    return originating


def main() -> int:
    check_only = "--check" in sys.argv
    db = json.load(io.open(DB_PATH, encoding="utf-8"))
    items = db["items"]
    originating = compute_originating(set(items))

    changed = []
    for key, entry in items.items():
        want = originating.get(key) or []
        have = entry.get("originating_recipes") or []
        if have != want:
            changed.append(key)
            entry["originating_recipes"] = want
    print("配方图：%d 件物品有 origin 配方（共 %d 条），battle_items.json 需更新 %d 件"
          % (len(originating), sum(len(v) for v in originating.values()), len(changed)))
    if check_only:
        return 1 if changed else 0
    if changed:
        with io.open(DB_PATH, "w", encoding="utf-8", newline="\n") as fh:
            json.dump(db, fh, ensure_ascii=False, indent=1)
            fh.write("\n")
        print("已写入 %s" % os.path.relpath(DB_PATH, ROOT))
    else:
        print("battle_items.json 已同步")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
