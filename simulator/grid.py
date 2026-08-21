# -*- coding: utf-8 -*-
"""grid.py — 背包网格模型与邻接计算

对齐原版 Inventory.gd + Item.gd 的格子机制：
  * 物品占格 = tscn CollisionMap 的 Collision/Extension tile（相对物品锚点的格子）
  * lineup (row,col) = 占格形状的左上角（归一化后 (0,0) 对应此格）
  * 受影响格 = tscn Affected tile + 脚本 getAffectedCellsAfterRotate 补充（同一锚点系）
  * 邻接物品 = 受影响格落点 → filledCells 查物 → canAffect 过滤

旋转：原版 collisionCells 随物品旋转（围绕锚点 (0,0)），再归一化 min 到左上角。
顺时针 rotation：90°:(x,y)->(y,-x)  180°:(-x,-y)  270°:(-y,x)
"""
from __future__ import annotations

from typing import Dict, List, Optional, Set, Tuple

Cell = Tuple[int, int]


def rotate_cell(cell: Cell, rot_deg: int) -> Cell:
    """围绕锚点 (0,0) 顺时针旋转格子"""
    x, y = cell
    r = rot_deg % 360
    if r == 0:
        return (x, y)
    if r == 90:
        return (y, -x)
    if r == 180:
        return (-x, -y)
    if r == 270:
        return (-y, x)
    return (x, y)


def normalize_cells(cells) -> List[Cell]:
    """把格集合平移到左上角 (0,0) 起始，返回有序列表"""
    if not cells:
        return []
    min_x = min(c[0] for c in cells)
    min_y = min(c[1] for c in cells)
    return sorted((c[0] - min_x, c[1] - min_y) for c in cells)


def rotate_and_normalize(cells, rot_deg: int) -> List[Cell]:
    """先按 rotation 旋转（围绕锚点），再归一化到左上角。返回 [(0,0)..] 形状。"""
    if not cells:
        return []
    rot = [rotate_cell(tuple(c), rot_deg) for c in cells]
    return normalize_cells(rot)


class GridInventory:
    """背包网格：cell -> item（对齐 Inventory.filledCells / bagCells）"""

    def __init__(self, rows: int = 7, cols: int = 10):
        self.rows = rows
        self.cols = cols
        self.filled: Dict[Cell, object] = {}
        self.bags: Dict[Cell, object] = {}

    def clear(self):
        self.filled.clear()
        self.bags.clear()

    def add_item(self, item, cells, is_bag: bool = False):
        target = self.bags if is_bag else self.filled
        for c in cells:
            target[c] = item

    def remove_item(self, item, cells, is_bag: bool = False):
        target = self.bags if is_bag else self.filled
        for c in cells:
            if target.get(c) is item:
                del target[c]

    def get_item_in_cell(self, cell) -> object:
        return self.filled.get(cell)

    def get_items_in_cells(self, cells) -> List[object]:
        items = []
        for c in cells:
            it = self.filled.get(c)
            if it is not None and it not in items:
                items.append(it)
        return items

    def get_bags_in_cells(self, cells) -> List[object]:
        items = []
        for c in cells:
            it = self.bags.get(c)
            if it is not None and it not in items:
                items.append(it)
        return items

    def is_cell_occupied(self, cell) -> bool:
        return cell in self.filled

    def is_cell_empty_for_bag(self, cell) -> bool:
        return cell in self.bags and cell not in self.filled


def cells_from_grid_data(grid_data: dict) -> List[Cell]:
    """从 battle_items.json 的 grid 字段取占格（Collision/Extension）"""
    cells = grid_data.get("collision_cells") or []
    return [tuple(c) for c in cells]
