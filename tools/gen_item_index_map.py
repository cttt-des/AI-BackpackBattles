# -*- coding: utf-8 -*-
"""gen_item_index_map.py — 生成历史记录解码所需的物品索引映射表

真值源：
  * decompiled_full/Sheets/CSV/ItemData_e.csv 的 `id` 列 = ItemBook.itemIndex
    （ItemBook.gd:949 `item.itemIndex = table.getInt("id", line)`）
  * numSockets：tscn 场景 GemSocket 节点计数（ItemBook.gd:968-976 同源逻辑）
  * gemList：CSV 行序中 types[0]==Gem 的物品（ItemBook.gd:962-965 同源逻辑）

输出 assets/item_index_map.json：core/build_history.py 解码 buildInfo 用。
用法: python tools/gen_item_index_map.py
"""
import glob
import json
import math
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CSV_PATH = os.path.join(ROOT, "decompiled_full", "Sheets", "CSV", "ItemData_e.csv")
TSCN_DIR = os.path.join(ROOT, "decompiled_full", "Items")
OUT_PATH = os.path.join(ROOT, "assets", "item_index_map.json")


def main():
    import csv
    with open(CSV_PATH, encoding="utf-8", errors="replace") as f:
        rows = list(csv.reader(f))
    header = rows[0]
    i_name = header.index("name")
    i_id = header.index("id")
    i_type = header.index("type")

    index_to_name = {}
    gem_order = []
    for r in rows[1:]:
        if len(r) <= max(i_name, i_id, i_type):
            continue
        name, idx, typ = r[i_name].strip(), r[i_id].strip(), r[i_type].strip()
        if not name or not idx:
            continue
        index_to_name[int(idx)] = name
        if typ == "Gem":
            gem_order.append(name)

    # numSockets：tscn 内 GemSocket 节点计数；tscn 去空格名 ↔ CSV 去空格名
    def norm(s):
        return s.replace(" ", "").replace("_", "").lower()

    tscn_sockets = {}
    for p in glob.glob(os.path.join(TSCN_DIR, "**", "*.tscn"), recursive=True):
        base = os.path.splitext(os.path.basename(p))[0]
        try:
            with open(p, encoding="utf-8", errors="replace") as f:
                cnt = f.read().count("GemSocket")
        except Exception:
            continue
        if cnt:
            tscn_sockets[norm(base)] = cnt

    num_sockets = {}
    missing_scene = []
    for idx, name in sorted(index_to_name.items()):
        cnt = tscn_sockets.get(norm(name))
        if cnt is None:
            num_sockets[name] = 0
            if norm(name) not in tscn_sockets and any(
                    norm(name) in k or k in norm(name) for k in tscn_sockets):
                missing_scene.append(name)
        else:
            num_sockets[name] = cnt

    total_num_gems_ceil = 2 ** math.ceil(math.log2(len(gem_order) + 1))

    out = {
        "version": "v1.1.7",
        "total_items": max(index_to_name) + 1,
        "index_to_name": {str(k): v for k, v in sorted(index_to_name.items())},
        "gem_order": gem_order,
        "total_num_gems_ceil": total_num_gems_ceil,
        "empty_socket_id": total_num_gems_ceil - 1,
        "num_sockets": num_sockets,
    }
    with open(OUT_PATH, "w", encoding="utf-8") as f:
        json.dump(out, f, ensure_ascii=False, indent=1)

    covered = sum(1 for v in num_sockets.values() if v > 0)
    print(f"物品 {len(index_to_name)}（max index {max(index_to_name)}），"
          f"Gem {len(gem_order)}，totalNumGems={total_num_gems_ceil}")
    print(f"numSockets>0 的物品 {covered}；tscn 未匹配 {len(missing_scene)}")
    if missing_scene:
        print("  未匹配样例:", missing_scene[:10])
    print(f"已写出 {OUT_PATH}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
