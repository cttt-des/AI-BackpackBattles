# -*- coding: utf-8 -*-
"""extract_translations.py — 从 pck .translation 提取物品中文名（比例线性映射 + 人工修正表）

原理：en 与 zh_Hans_CN 的 .translation 是同一 CSV 集编译的哈希翻译，名段（物品名）
在各自 strings 池中按相同哈希顺序排列；zh 池含 en 表未翻译的额外条目（插入），
故用"比例线性映射"（en 名段序号 k -> zh 名段序号 round(k*len_zh/len_en)）对齐。

人工修正表 assets/zh_override.json：{英文名: 正确中文名}，优先于自动映射。
"""
from __future__ import annotations
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")
OVERRIDE_PATH = os.path.join(ROOT, "assets", "zh_override.json")
TR_DIR = "C:/tmp/bb_tr/Sheets/CSV"

TITLE = re.compile(r"^[A-Z][a-z]+(?: [A-Z][a-z]+)*$")
HAN = re.compile(r"^[\u4e00-\u9fff]{2,10}$")


def segs(path: str):
    with open(path, "rb") as f:
        d = f.read()
    return [s.decode("utf-8", "ignore") for s in d.split(b"\x00")]


def names(sheet: str):
    en = segs(os.path.join(TR_DIR, f"{sheet}.en.translation"))
    zh = segs(os.path.join(TR_DIR, f"{sheet}.zh_Hans_CN.translation"))
    en_n = [s for s in en if TITLE.match(s) and len(s) >= 3 and "\n" not in s]
    zh_n = [s for s in zh if HAN.match(s)]
    return en_n, zh_n


def main():
    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    override = {}
    if os.path.exists(OVERRIDE_PATH):
        override = json.load(open(OVERRIDE_PATH, encoding="utf-8"))

    pairs = {}
    for sheet in ("Items", "ExclusiveItems", "Full"):
        en_n, zh_n = names(sheet)
        if not en_n or not zh_n:
            continue
        ratio = len(zh_n) / len(en_n)
        for k, enk in enumerate(en_n):
            zk = min(len(zh_n) - 1, int(round(k * ratio)))
            if enk not in pairs:      # 后面的表不覆盖前面的
                pairs[enk] = zh_n[zk]

    matched = 0
    for k, v in items.items():
        zh = override.get(k) or pairs.get(k)
        if zh:
            v["zh"] = zh
            matched += 1
    json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print(f"已写入中文名: {matched} / {len(items)}（含人工修正 {len(override)}）")
    print("抽查:")
    for k in ["Flute", "Banana", "Dagger", "Cursed Dagger", "Health Potion", "Poison Bow",
              "Greatsword", "Amulet of the Wild", "Ruby", "Garlic", "Leather Armor",
              "Dark Ritual", "Acorn Ace"]:
        print(f"  {k} -> {items.get(k, {}).get('zh', '?')}")


if __name__ == "__main__":
    main()
