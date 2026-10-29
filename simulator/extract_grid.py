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
# np24 根因A2：源树由 extracted/Items（1.1.7，已清理）改指 oracle/Items（1.1.9 真值，
# 与 P1-2 CSV 对齐同源）。oracle/ 只读——本工具只读 tscn、写 battle_items.json。
EXTRACTED = os.path.join(ROOT, "oracle", "Items")
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
    m = re.search(r'tile_data = PoolIntArray\(([^)]+)\)', txt)
    if not m:
        return None
    nums = [int(t) for t in re.findall(r'-?\d+', m.group(1))]
    tiles = {}
    for i in range(2, len(nums), 3):
        cell = decode_tile(nums[i - 2])
        tid = nums[i - 1]
        tiles.setdefault(tid, set()).add(cell)
    return tiles


# np24 根因A2（run602_r14 RubyWhelp 实证）：不覆写 CollisionMap 的 tscn（实例化
# 基座 Items/Item.tscn）继承基座 CollisionMap 的 tile_data——此前按 size [1,1]
# 兜底，把蛋/幼龙/盾/王冠等 19 件真身 2×2 的物品截成 1 格 → 袋内容物/affected
# 几何全错（Fanny Pack 包内 Ruby Whelp 丢失 → 开战激活差 → 全链漂移）。
BASE_ITEM_TSCN = os.path.join(EXTRACTED, "Item.tscn")


def load_base_tiles():
    """基座 Items/Item.tscn 的 CollisionMap tile_data（无覆写物品的真身）。"""
    return parse_tscn_grid(BASE_ITEM_TSCN)


def scan_tscn_index():
    """扫描所有 tscn，返回 {规范名(小写无空格): 完整路径}

    ★ np25棋盘面：由固定三层（""/Exclusive/Gems）改为**递归**——12 件棋子的
      tscn 在 Exclusive/Chess/ 第四层，旧扫描恒索引不到（白/黑棋子 key 查询
      落空 → grid 恒为 np23 手补裸 1×1、affected 移动模式从未落库）。遍历序
      确定性排序，覆盖优先级与旧三层一致（后写胜：Gems > Exclusive > 基座）。
    """
    idx = {}
    for root, dirs, files in os.walk(EXTRACTED):
        dirs.sort()
        for fn in sorted(files):
            if fn.endswith(".tscn"):
                idx[fn[:-5].lower().replace(" ", "")] = os.path.join(root, fn)
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
    inherited = []
    base_tiles = load_base_tiles()
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
            # 无自有 tile_data：若该 tscn 实例化基座 Items/Item.tscn 且未覆写
            # CollisionMap 节点 → 继承基座占格（np24 根因A2）；否则保持兜底。
            # ★ 宝石排除：宝石恒 1×1（装在宿主 socket 内，无背包占格语义），
            #   其 tscn 无 CollisionMap 属常态，继承基座 2×2 会把 gem 占格撑爆。
            # ★ np25棋盘面：'chess' 从本排除移除——棋子在背包恒 1×1 占格
            #   （collision 与 tscn 一致），但 **tscn tile id=4 的 affected_cells
            #   是棋子移动模式真值**（ChessPiece.prepare 的
            #   getAffectedCells_tilemap→moveCells→捕获/移动全靠它；WhitePawn
            #   2 格、BlackBishop 20 格斜线，parse_tscn_grid 实测可解析）。旧
            #   排除把棋子连坐 → grid 恒为 np23 手补裸 1×1 → moveCells 恒空
            #   → 棋盘捕获恒空转（run644_r7 Gshuffle:100 size=0 铁证）。
            if items[key].get("category") in ("gem",):
                no_tscn.append(key)
                continue
            txt = open(sp, encoding="utf-8", errors="replace").read()
            has_cm_override = re.search(r'\[node name="CollisionMap"[^\]]*\]', txt)
            base = base_tiles if (base_tiles and not has_cm_override) else None
            if base is None:
                no_tscn.append(key)
                continue
            tiles = base
            inherited.append(key)
        grid = {}
        for tid, keyname in TILE_KEYS.items():
            if tid in tiles and tiles[tid]:
                grid[keyname] = norm_cells(tiles[tid])
        if not grid:
            no_tscn.append(key)
        else:
            items[key]["grid"] = grid
            matched += 1

    # 兜底：非宝石且无 tscn 数据的物品，用 DB size 生成矩形占格
    #（np25棋盘面：'chess' 从兜底排除移除——12 件棋子均有自有 tile_data
    #  走上方匹配路径，不走矩形兜底；留此防未来新增棋子缺 tscn 时静默裸 1×1）
    rect_fallback = 0
    for key, v in items.items():
        if v.get("grid"):
            continue
        if v.get("category") in ("gem",):
            continue
        size = v.get("size") or [1, 1]
        w, h = int(size[0]), int(size[1])
        cells = [[x, y] for y in range(h) for x in range(w)]
        items[key]["grid"] = {"collision_cells": cells, "rect_fallback": True}
        rect_fallback += 1

    print(f"已写入 grid: {matched}  无 tscn/数据: {len(no_tscn)}  矩形兜底: {rect_fallback}")
    print(f"继承基座 2x2: {len(inherited)} {sorted(inherited)}")
    if no_tscn:
        print("无 grid 物品示例:", no_tscn[:25])
    json.dump(db, open(DB_PATH, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    print("已写出", DB_PATH)


if __name__ == "__main__":
    main()
