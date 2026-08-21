# -*- coding: utf-8 -*-
"""extract_grid.py — 从 tscn 场景提取物品网格数据（占格 + 受影响格）

真值源：每物品场景的 CollisionMap.tile_data（PoolIntArray，每 3 个 int = [格子, 瓦片ID, 0]）
瓦片 ID（对齐 Item.gd Tiles 枚举）：
  3=Collision, 4=Affected(Primary), 6=AffectedSecondary, 10=AffectedTertiary, 11=AffectedLightning

写入 battle_items.json 的 grid 字段：
  grid: {
    "collision_cells": [[x,y],...],        # 物品占格（相对物品锚点）
    "affected_cells": [[x,y],...],         # Primary 受影响格
    "affected_secondary": [[x,y],...],     # Secondary 受影响格
    "affected_tertiary": [[x,y],...],
    "affected_lightning": [[x,y],...],
    "script_affected_primary": {...},      # 脚本覆盖的额外受影响规则（Potion 等）
  }
"""
from __future__ import annotations
import os
import re
import json

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXTRACTED = os.path.join(ROOT, "extracted", "Items")
DB_PATH = os.path.join(ROOT, "assets", "battle_items.json")

# Item.gd Tiles 枚举
T_EXTENSION = 2      # bag 的占格（Extension）
T_COLLISION = 3
T_AFFECTED = 4
T_AFFECTED_SECONDARY = 6
T_AFFECTED_TERTIARY = 10
T_AFFECTED_LIGHTNING = 11

TILE_KEYS = {
    T_EXTENSION: "collision_cells",   # bag 占格
    T_COLLISION: "collision_cells",   # 普通物品占格（与 Extension 合并）
    T_AFFECTED: "affected_cells",
    T_AFFECTED_SECONDARY: "affected_secondary",
    T_AFFECTED_TERTIARY: "affected_tertiary",
    T_AFFECTED_LIGHTNING: "affected_lightning",
}


def decode_tile(v: int):
    """Godot TileMap 展平坐标解码：int = y<<16 | (x & 0xFFFF)（x 为 16 位有符号）"""
    y = v >> 16
    if y >= 32768:
        y -= 65536
    x = v & 0xFFFF
    if x >= 32768:
        x -= 65536
    return (x, y)


def parse_tscn_grid(path: str):
    """解析一个 tscn 的 CollisionMap tile_data，返回 {tile_id: set((x,y))}"""
    try:
        with open(path, encoding="utf-8", errors="replace") as f:
            txt = f.read()
    except OSError:
        return None
    m = re.search(r'tile_data = PoolIntArray\((.*?)\)', txt, re.S)
    if not m:
        return None
    nums = [int(t) for t in re.findall(r'-?\d+', m.group(1))]
    tiles = {}
    for i in range(0, len(nums) - 2, 3):
        cell = decode_tile(nums[i])
        tid = nums[i + 1]
        tiles.setdefault(tid, set()).add(cell)
    return tiles


def scan_tscn_index():
    """扫描所有 tscn，返回 {规范名(小写无空格): 完整路径}"""
    idx = {}
    for sub in ("", "Exclusive", "Gems"):
        d = os.path.join(EXTRACTED, sub)
        if not os.path.isdir(d):
            continue
        for fn in sorted(os.listdir(d)):
            if fn.endswith(".tscn"):
                idx[fn[:-5].lower().replace(" ", "")] = os.path.join(d, fn)
    return idx


def norm_cells(cells) -> list:
    return sorted([list(c) for c in cells])


def main():
    db = json.load(open(DB_PATH, encoding="utf-8"))
    items = db.get("items", db)
    idx = scan_tscn_index()
    print(f"tscn 索引: {len(idx)}  物品: {len(items)}")

    matched = 0
    no_tscn = []
    for key in items:
        sp = None
        scr = items[key].get("script")
        if scr:
            norm = scr[:-3].lower().replace(" ", "") if scr.endswith(".gd") else scr.lower().replace(" ", "")
            sp = idx.get(norm)
        if sp is None:
            sp = idx.get(key.lower().replace(" ", ""))
        if sp is None:
            base = key.rstrip("0123456789 ")
            for q in ("Chipped ", "Flawed ", "Regular ", "Flawless ", "Perfect ", "Strong "):
                if key.startswith(q):
                    base = key[len(q):]
                    break
            sp = idx.get(base.lower().replace(" ", ""))
        if sp is None:
            no_tscn.append(key)
            continue
        tiles = parse_tscn_grid(sp)
        if tiles is None:
            no_tscn.append(key)
            continue
        grid = {}
        for tid, keyname in TILE_KEYS.items():
            if tid in tiles and tiles[tid]:
                grid[keyname] = norm_cells(tiles[tid])
        if not grid:
            no_tscn.append(key)
        else:
            items[key]["grid"] = grid
            matched += 1

    # 兜底：非宝石/棋子且无 tscn 数据的物品，用 DB size 生成矩形占格
    rect_fallback = 0
    for key, v in items.items():
        if v.get("grid"):
            continue
        if v.get("category") in ("gem", "chess"):
            continue
        size = v.get("size") or [1, 1]
        w, h = int(size[0]), int(size[1])
        cells = [[x, y] for y in range(h) for x in range(w)]
        items[key]["grid"] = {"collision_cells": cells, "rect_fallback": True}
        rect_fallback += 1

    print(f"已写入 grid: {matched}  无 tscn/数据: {len(no_tscn)}  矩形兜底: {rect_fallback}")
    if no_tscn:
        print("无 grid 物品示例:", no_tscn[:25])
    json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print("已写出", DB_PATH)


if __name__ == "__main__":
    main()
