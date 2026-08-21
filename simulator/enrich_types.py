# -*- coding: utf-8 -*-
"""enrich_types.py — 从 ItemData_e.csv 补全 DB 的 types/tags 字段

CSV 列：type(3) / extraTypes(4) / tags(25)。Type 枚举名 -> 小写：
  Bag->bag, Potion->potion, ChessPiece->chess, Spell->spell, ...
"""
from __future__ import annotations
import csv
import json
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_PATH = os.path.join(ROOT, "extracted", "Sheets", "CSV", "ItemData_e.csv")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

TYPE_NORM = {
    "bag": "bag", "consumable": "consumable", "food": "food", "pet": "pet",
    "weapon": "weapon", "shield": "shield", "armor": "armor", "gloves": "gloves",
    "shoes": "shoes", "helmet": "helmet", "accessory": "accessory",
    "potion": "potion", "card": "card", "gem": "gem", "scroll": "scroll",
    "book": "book", "skill": "skill", "chesspiece": "chess", "spell": "spell",
    "melee": "melee", "ranged": "ranged", "effect": "effect",
    "holy": "holy", "magic": "magic", "vampiric": "vampiric", "dark": "dark",
    "nature": "nature", "fire": "fire", "ice": "ice", "musical": "musical",
}


def load_csv() -> dict:
    out = {}
    with open(CSV_PATH, encoding="utf-8", errors="replace") as f:
        r = csv.reader(f)
        next(r)
        for row in r:
            if not row or not row[0]:
                continue
            name = row[0].strip()
            types = []
            for col in (3, 4):  # type / extraTypes
                raw = row[col] if col < len(row) else ""
                for tok in re.split(r"[,;|]", raw or ""):
                    tok = TYPE_NORM.get(tok.strip().lower())
                    if tok and tok not in types:
                        types.append(tok)
            tags = []
            raw_tags = row[25] if len(row) > 25 else ""
            for tok in re.split(r"[,;|]", raw_tags or ""):
                tok = tok.strip().lower()
                if tok and tok not in tags:
                    tags.append(tok)
            out[name] = {"types": types, "tags": tags}
    return out


def main():
    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    csv_data = load_csv()
    print(f"CSV 条目: {len(csv_data)}")
    filled_types = filled_tags = 0
    for key, v in items.items():
        src = csv_data.get(key)
        if not src:
            continue
        cur = list(v.get("types") or [])
        for t in src["types"]:
            if t not in cur:
                cur.append(t)
        if cur:
            v["types"] = cur
            filled_types += 1
        tags = list(v.get("tags") or [])
        for t in src["tags"]:
            if t not in tags:
                tags.append(t)
        if tags:
            v["tags"] = tags
            filled_tags += 1
    json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print(f"已补 types: {filled_types}  已补 tags: {filled_tags}")


if __name__ == "__main__":
    main()
