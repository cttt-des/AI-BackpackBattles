# -*- coding: utf-8 -*-
"""repack_lineups.py — 占格形状修正后重摆内置阵容

背景：引擎修复"1 collision tile = 1 背包格"（移除 //2 坍缩）后，多格物品的
真实占格变大，旧阵容（按 1 格/物品摆盘）必然重叠。本工具对 lineups/*.json
按原物品顺序 + 旋转做 first-fit 重摆并回写。

占格规则（对齐 Inventory.gd filledCells/bagCells 双层模型）：
  * 普通物品占 filled：形状 = rotate_and_normalize(collision_cells, rotation)
    平移到 (row,col)；不得与其他 filled 相撞
  * container（包/袋）占 bags： bags 之间不得相撞；物品压在包占格上是
    合法摆放（= 放入包内，canAddItem 只查 filledCells 不查 bagCells），
    故跨层重叠不视为冲突

用法：
  python tools/repack_lineups.py            # 重摆 lineups/ 下全部阵容（就地回写）
  python tools/repack_lineups.py --check    # 只检测重叠，不修改
"""
from __future__ import annotations

import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from simulator.grid import rotate_and_normalize  # noqa: E402
from simulator.data import load_items  # noqa: E402

LINEUPS_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                           'lineups')


def item_cells(db, key: str, rotation: int):
    """物品在指定旋转下的归一化占格形状 [(dx,dy)..]，(dx=col 偏移, dy=row 偏移)"""
    data = db.get(key) or {}
    grid = data.get('grid') or {}
    cells = grid.get('collision_cells') or []
    if not cells:
        cells = [[0, 0]]           # rect_fallback / 无数据：按 1 格处理
    # tscn (x,y) -> rotate_and_normalize 期望 (x,y)，返回 (x,y)
    return rotate_and_normalize([tuple(c) for c in cells], int(rotation) % 360)


def abs_cells(shape, row: int, col: int):
    """形状 (x,y) 偏移 + 锚点 (row,col) -> 绝对 (row,col) 集合"""
    return {(row + dy, col + dx) for (dx, dy) in shape}


def first_fit(db, key: str, rotation: int, rows: int, cols: int,
              occupied_filled: set, occupied_bags: set, is_bag: bool):
    """行优先扫描第一个可容纳位置，返回 (row,col) 或 None

    同层查重：包只避开包（occupied_bags），物品只避开物品（occupied_filled）；
    跨层重叠 = 物品放入包内，合法。
    """
    shape = item_cells(db, key, rotation)
    for r in range(rows):
        for c in range(cols):
            cells = abs_cells(shape, r, c)
            if any(cr < 0 or cr >= rows or cc < 0 or cc >= cols for cr, cc in cells):
                continue
            if cells & (occupied_bags if is_bag else occupied_filled):
                continue
            return r, c
    return None


def repack(data: dict, db: dict, check_only: bool = False):
    """重摆单个阵容。返回 (moved 数, 冲突列表)；check_only 只报不改。"""
    bp = data.get('backpack') or {}
    grid_cfg = bp.get('grid') or {'rows': 7, 'cols': 10}
    rows, cols = int(grid_cfg.get('rows', 7)), int(grid_cfg.get('cols', 10))
    items = bp.get('items') or []

    occupied_filled: set = set()
    occupied_bags: set = set()
    conflicts = []
    moved = 0
    # 第一遍：按现有坐标检测
    placed = []
    for e in items:
        if e.get('container'):
            continue
        shape = item_cells(db, e.get('id'), e.get('rotation', 0))
        cells = abs_cells(shape, int(e.get('row', 0)), int(e.get('col', 0)))
        placed.append((e, cells, shape))
        oob = any(cr < 0 or cr >= rows or cc < 0 or cc >= cols for cr, cc in cells)
        hit = cells & occupied_filled
        if oob or hit:
            conflicts.append({'id': e.get('id'), 'oob': oob, 'hit': sorted(hit)})
        occupied_filled |= cells
    for e in items:
        if not e.get('container'):
            continue
        shape = item_cells(db, e.get('id'), e.get('rotation', 0))
        cells = abs_cells(shape, int(e.get('row', 0)), int(e.get('col', 0)))
        oob = any(cr < 0 or cr >= rows or cc < 0 or cc >= cols for cr, cc in cells)
        hit = cells & occupied_bags   # 物品压包 = 放入包内，合法；只查包∩包
        if oob or hit:
            conflicts.append({'id': e.get('id'), 'oob': oob, 'hit': sorted(hit)})
        occupied_bags |= cells

    if check_only or not conflicts:
        return moved, conflicts

    # 第二遍：冲突阵容整体重摆（保持原顺序，先试原位再 first-fit）
    occupied_filled.clear()
    occupied_bags.clear()
    conflicts = []   # 第一遍的冲突已进入重摆流程，只保留重摆后仍放不下的
    for e in items:
        is_bag = bool(e.get('container'))
        key = e.get('id')
        rotation = int(e.get('rotation', 0) or 0)
        shape = item_cells(db, key, rotation)
        target = None
        orig = (int(e.get('row', 0) or 0), int(e.get('col', 0) or 0))
        for cand in [orig] + [None]:
            if cand is None:
                target = first_fit(db, key, rotation, rows, cols,
                                   occupied_filled, occupied_bags, is_bag)
                break
            cells = abs_cells(shape, cand[0], cand[1])
            oob = any(cr < 0 or cr >= rows or cc < 0 or cc >= cols for cr, cc in cells)
            if oob:
                continue
            if is_bag and cells & occupied_bags:
                continue
            if not is_bag and cells & occupied_filled:
                continue
            target = cand
            break
        if target is None:
            conflicts.append({'id': key, 'oob': True, 'hit': ['NO-FIT']})
            continue
        if target != orig:
            moved += 1
        e['row'], e['col'] = target[0], target[1]
        cells = abs_cells(shape, target[0], target[1])
        if is_bag:
            occupied_bags |= cells
        else:
            occupied_filled |= cells
    return moved, conflicts


def main():
    check_only = '--check' in sys.argv
    db = load_items()
    names = sorted(f for f in os.listdir(LINEUPS_DIR) if f.endswith('.json'))
    total_moved = 0
    for name in names:
        path = os.path.join(LINEUPS_DIR, name)
        with open(path, encoding='utf-8') as f:
            data = json.load(f)
        moved, conflicts = repack(data, db, check_only=check_only)
        if conflicts:
            print(f'{name}: {len(conflicts)} 处冲突/越界: '
                  + '; '.join(str(c) for c in conflicts[:5]))
        if moved and not check_only:
            with open(path, 'w', encoding='utf-8', newline='\n') as f:
                json.dump(data, f, ensure_ascii=False, indent=1)
                f.write('\n')
        print(f'{name}: {"检测" if check_only else "重摆"}完成, 移动 {moved} 件')
        total_moved += moved
    print(f'\n合计移动 {total_moved} 件'
          + ('（--check 未修改文件）' if check_only else ''))


if __name__ == '__main__':
    main()
