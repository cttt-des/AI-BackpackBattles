# -*- coding: utf-8 -*-
"""encoding.py — 阵容 JSON → 神经网络输入张量（AI 编码层）

把一局阵容（v4 平铺格式或内部 v3 形状，见 simulator/lineup.py 文件头）编码成
一组 numpy 数组。几何数据来自物品库（assets/gd_core_runtime.json 的 ``rot``
表，或 assets/battle_items.json 的原生 ``grid`` 字段——两种都认）。

坐标约定（与引擎逐字对齐，三处权威实现互为镜像）：
  * 物品库里的格是 **(x, y) = (col 偏移, row 偏移)**，锚点系（Vector2(x=col,
    y=row)），见 tools/gen_gd_core_data.py 文件头与 tools/gen_lineup_fixture.py
    ::placement_of:291 的注释。
  * 旋转围绕锚点 (0,0)：对齐 Godot Vector2.rotated（y 轴向下，正角=屏幕顺时针），
    与 simulator/grid.py:23 rotate_cell 逐字一致：
      90°:(x,y)->(-y,x)  180°:(-x,-y)  270°:(x,y)->(y,-x)
  * 旋转后按 collision 的 min 归一化到左上角（simulator/grid.py:47
    rotate_and_normalize；affected 用 **collision** 的 min 平移——
    simulator/item.py:1743 _affected_cells_abs / gen_lineup_fixture.py:302）。
  * 平移到摆位：绝对背包格 = (row + y, col + x)（simulator/item.py:1739
    _to_abs、simulator/gd_core_engine.py:540 _place_of）。
本模块自己复刻这套变换（不 import simulator/，编码层要能独立进推理进程）；
一致性由 ai/tests/test_encoding.py 对照两个引擎逐物品断言。

输出 dict（encode_lineup 返回）：
  item_grid     int32  (rows, cols)   物品序号格；-1=空格，否则物品在 ``ids``
                               里的下标。**只画引擎装配的根物品**（无 ``in``
                               的条目）——战斗内核只装配背包顶层的根物品
                               （simulator/lineup.py::_normalize_v4 的 roots、
                               simulator/gd_core_engine.py::_build_side 只遍历
                               backpack.items 顶层），袋内物品（``in`` 指向/
                               v3 嵌套 contents）不装配、因此也不画。编码层
                               与引擎的「可见物品集」逐件一致，代理分不掺入
                               引擎看不见的战力。
  rotation_grid int32  (rows, cols)   该格所属物品的旋转角序号 0..3（=度数/90）；
                               空格 -1。覆盖规则同 item_grid（根物品之间的
                               重叠按平铺序后画覆盖先画——真值实录的平铺
                               导出本就允许根物品坐标压叠，引擎装配同样
                               照单全收，见 gd_core_py CoreGrid.addItem）。
  collision_mask  int8  (rows, cols)   占格掩码：任一物品的 collision 绝对格。
  affected_masks  int8  (4, rows, cols)  四色影响格掩码，通道 0..3 = primary /
                               secondary / tertiary / lightning（对齐
                               gen_lineup_fixture.AFFECTED_KEYS 与
                               gd_core_engine._place_of 的颜色键）。物品库里的
                               affected 偏移按旋转+摆位平移到绝对格，出界的格
                               直接裁掉。
  gem_onehot    int8    (n_roots, n_gems)  多热（multi-hot）：行按 ``ids`` 顺序，
                               列按 ``gem_ids`` 顺序；根物品 i 含宝石 j 记 1
                               （同名多颗只记一次——one-hot 语义）。**只编码
                               根物品的宝石**——引擎只对根物品 setGem
                               （gd_core_engine._build_side 只遍历背包顶层），
                               袋内物品及其宝石不参战、不进任何通道。
  gem_ids       list[str]  宝石词表（根物品的宝石按首次出现顺序）。宝石本身
                               也是物品 id；库里没有的宝石照常进词表。
  ids           list[str]  根物品 id 列表（= 引擎装配的物品，按平铺序）。
                               item_grid 的序号与 gem_onehot 的行都基于它；
                               袋内物品不进编码（只在 scalars.bag_item_count
                               计数，见下）。
  root_ids      list[str]  同 ``ids``（保留键名以稳定下游接口：ai/train.py、
                               ai/placer.py 按此名读取）。
  unknown_ids   list[str]  物品库里查不到的物品 id（照常占 ids 下标，但不画格
                               ——真值实录里存在 GoldCounter 等不可装配物品，
                               引擎装配会抛 _MissingItem，编码层跳过不崩）。
  scalars       dict      标量：num_items（**根物品数** = 引擎装配的物品数，
                               不含袋内物品）、rarity_sum（根物品的
                               descr.rarity 合计，未知物品记 0）、bag_item_count
                               （**袋内件数**，仅作信息参考——袋内物品不参战，
                               见上）、class_id（lineup.character →
                               item_db['classes'] 枚举，查不到 -1）、
                               class_onehot（float32，按枚举值 one-hot，
                               长度 max(7, 最大枚举值+1)）。
  grid_shape    int32  (2,)  = (rows, cols)，默认 (7, 9)，可被阵容 grid 字段覆盖。

无效旋转角（非 90 的倍数）抛 ValueError；阵容物品库里查不到的 id 不抛（进
unknown_ids），因为真值实录的阵容确实带这类物品。
"""
from __future__ import annotations

from typing import Dict, List, Optional, Tuple

import numpy as np

# 背包网格（docs/simulator_architecture.md §2：7 行 × 9 列）
ROWS, COLS = 7, 9
ROTATIONS = (0, 90, 180, 270)

# 四色影响格：gen_lineup_fixture.py:271 AFFECTED_KEYS 的「颜色枚举 → tscn 字段」表
# （0=primary, 1=secondary, 2=tertiary, 3=lightning；gd_core_runtime.json 的
#   rot.affected 键、gd_core_engine._place_of 的 affected 键同此枚举）
AFFECTED_GRID_KEYS = {
    0: "affected_cells",
    1: "affected_secondary",
    2: "affected_tertiary",
    3: "affected_lightning",
}
AFFECTED_COLORS = (0, 1, 2, 3)


# ─────────────────────────── 旋转几何（对齐 simulator/grid.py） ───────────────────────────

def rotate_cell(cell: Tuple[int, int], rot_deg: int) -> Tuple[int, int]:
    """围绕锚点 (0,0) 旋转一格（simulator/grid.py:23 rotate_cell 的复刻：
    对齐 Godot rotated()，y 向下、正角=屏幕顺时针）。cell=(x, y)。"""
    x, y = cell
    r = int(rot_deg) % 360
    if r == 0:
        return (x, y)
    if r == 90:
        return (-y, x)
    if r == 180:
        return (-x, -y)
    if r == 270:
        return (y, -x)
    raise ValueError("旋转角必须是 90 的倍数: %r" % (rot_deg,))


def normalize_cells(cells) -> List[Tuple[int, int]]:
    """格集合平移到左上角 (0,0)，返回有序列表（simulator/grid.py:38）。"""
    if not cells:
        return []
    min_x = min(c[0] for c in cells)
    min_y = min(c[1] for c in cells)
    return sorted((c[0] - min_x, c[1] - min_y) for c in cells)


def rotate_and_normalize(cells, rot_deg: int) -> List[Tuple[int, int]]:
    """先旋转（锚点系）再按自身 min 归一化（simulator/grid.py:47 的复刻）。"""
    if not cells:
        return []
    return normalize_cells([rotate_cell(tuple(c), rot_deg) for c in cells])


def rot_index(rotation: int) -> int:
    """旋转角度 → 通道序号 0..3；非 90 的倍数抛 ValueError。"""
    r = int(rotation) % 360
    if r % 90 != 0:
        raise ValueError("旋转角必须是 90 的倍数（0/90/180/270），得到 %r" % (rotation,))
    return r // 90


def to_abs(cells, row: int, col: int) -> List[Tuple[int, int]]:
    """锚点系 (x, y) 偏移 → 绝对背包格 (row, col)：
    绝对 = (row + y, col + x)。对齐 simulator/item.py:1739 _to_abs 与
    simulator/gd_core_engine.py:540（occupied = {(c[0]+col, c[1]+row)}）。"""
    return [(int(row) + int(y), int(col) + int(x)) for (x, y) in cells]


# ─────────────────────────── 物品库适配 ───────────────────────────

def _items_map(item_db: dict) -> Dict[str, dict]:
    """兼容两种物品库形状：gd_core_runtime.json 整包（含 'items' 键）或直接的
    {物品key: 条目} 映射。"""
    if not isinstance(item_db, dict):
        raise TypeError("item_db 必须是 dict")
    inner = item_db.get("items")
    if isinstance(inner, dict):
        return inner
    return item_db


def _rotate_geometry(collision0, affected0, idx: int):
    """通用旋转：把 0°（或任意锚点系）的 collision/affected 转到指定旋转角。

    对齐 tools/gen_lineup_fixture.py:279 placement_of：
      collision 旋转后按自身 min 归一化；affected 旋转后用 **collision** 的
      min 平移（affected 允许落在物品占格之外——上方/左侧的负偏移）。
    """
    base = [tuple(c) for c in (collision0 or [])]
    if not base:
        base = [(0, 0)]          # 无网格数据 → 1×1（对齐 simulator/item.py:1719）
    rotated = [rotate_cell(c, idx * 90) for c in base]
    min_x = min(c[0] for c in rotated)
    min_y = min(c[1] for c in rotated)
    collision = sorted((c[0] - min_x, c[1] - min_y) for c in rotated)
    affected: Dict[int, List[Tuple[int, int]]] = {}
    for color, cells in (affected0 or {}).items():
        if color not in AFFECTED_COLORS:
            continue
        got = {(rc[0] - min_x, rc[1] - min_y)
               for rc in (rotate_cell(tuple(c), idx * 90) for c in cells)}
        if got:
            affected[color] = sorted(got)
    return collision, affected


def _entry_geometry(entry: dict, idx: int):
    """单条物品库条目 → (collision 相对偏移, {颜色: 相对偏移})，均已归一化
    （锚点系、左上角 (0,0)，即「place 在 (0,0)」的偏移）。"""
    rot_tab = entry.get("rot") if isinstance(entry, dict) else None
    if isinstance(rot_tab, dict) and rot_tab:
        ang = str(idx * 90)
        if ang in rot_tab:
            pl = rot_tab[ang] or {}
            collision = sorted(tuple(int(v) for v in c)
                               for c in (pl.get("collision") or [(0, 0)]))
            affected: Dict[int, List[Tuple[int, int]]] = {}
            for color, cells in (pl.get("affected") or {}).items():
                if int(color) not in AFFECTED_COLORS:
                    continue
                got = sorted(tuple(int(v) for v in c) for c in cells or [])
                if got:
                    affected[int(color)] = got
            return collision, affected
        # 缺该角度的表 → 从 0° 表现场推导（gen_gd_core_data 产物恒有 4 角，
        # 此分支只服务手写/裁剪过的物品库）
        base = rot_tab.get("0") or {}
        return _rotate_geometry(base.get("collision"), base.get("affected") or {}, idx)

    grid = entry.get("grid") if isinstance(entry, dict) else None
    if isinstance(grid, dict):
        # battle_items.json 原生 tscn 字段（锚点系、未归一化）
        collision0 = [tuple(c) for c in (grid.get("collision_cells") or [])]
        affected0 = {color: [tuple(c) for c in (grid.get(key) or [])]
                     for color, key in AFFECTED_GRID_KEYS.items()}
        return _rotate_geometry(collision0, affected0, idx)

    # 无任何网格数据 → 1×1（对齐 simulator/item.py:1717-1719 的兜底）
    return [(0, 0)], {}


def item_geometry(key: str, rotation: int, item_db: dict,
                  row: int = 0, col: int = 0) -> Optional[dict]:
    """单物品几何（逐物品断言/调试用）。物品库查不到返回 None。

    返回 {'collision': [(row,col),…], 'affected': {颜色: [(row,col),…]}}，
    全是绝对背包格（collision 至少一格；affected 只含库里有数据的颜色）。
    """
    entry = _items_map(item_db).get(key)
    if entry is None:
        return None
    idx = rot_index(rotation)
    collision_rel, affected_rel = _entry_geometry(entry, idx)
    return {
        "collision": sorted(set(to_abs(collision_rel, row, col))),
        "affected": {color: sorted(set(to_abs(cells, row, col)))
                     for color, cells in affected_rel.items()},
    }


# ─────────────────────────── 阵容平铺 ───────────────────────────

def _gem_id(g) -> str:
    """宝石条目 → id（兼容 v4 的 str 与 v3 内部形状的 {'id': …}）。"""
    if isinstance(g, dict):
        return str(g.get("id") or "")
    return str(g)


def _grid_shape(lineup: dict) -> Tuple[int, int]:
    bp = lineup.get("backpack") if isinstance(lineup.get("backpack"), dict) else {}
    grid = lineup.get("grid")
    if not (isinstance(grid, (list, tuple)) and len(grid) >= 2):
        grid = bp.get("grid")
    if isinstance(grid, dict):
        return int(grid.get("rows", ROWS)), int(grid.get("cols", COLS))
    if isinstance(grid, (list, tuple)) and len(grid) >= 2:
        return int(grid[0]), int(grid[1])
    return ROWS, COLS


def _flatten(lineup: dict) -> List[dict]:
    """把阵容平铺成 [{id,row,col,rotation,gems,parent}]，顺序 = ids 列表顺序。

    v4 平铺（lineup['items']，'in' 指向袋子的平铺下标）与内部 v3 形状
    （lineup['backpack']['items'] + 嵌套 contents）都收；两者并存时按内部
    形状处理（lineup.py 的规范化方向）。parent = 承载袋在平铺序里的下标
    （根物品为 None）。
    """
    bp = lineup.get("backpack") if isinstance(lineup.get("backpack"), dict) else {}
    bp_items = bp.get("items")
    out: List[dict] = []

    if isinstance(bp_items, list):
        # 内部 v3 形状：DFS（先根后袋内），parent = 袋子的平铺下标
        def walk(entries, parent):
            for e in entries or []:
                if not isinstance(e, dict) or not e.get("id"):
                    continue
                idx = len(out)
                out.append({
                    "id": str(e["id"]),
                    "row": int(e.get("row", 0) or 0),
                    "col": int(e.get("col", 0) or 0),
                    "rotation": int(e.get("rotation", 0) or 0),
                    "gems": [_gem_id(g) for g in (e.get("gems") or []) if _gem_id(g)],
                    "parent": parent,
                })
                walk(e.get("contents"), idx)

        walk(bp_items, None)
        return out

    raw = lineup.get("items")
    if not isinstance(raw, list):
        return out
    # v4 平铺
    for e in raw:
        if not isinstance(e, dict) or not e.get("id"):
            continue
        at = e.get("at") or [0, 0]
        out.append({
            "id": str(e["id"]),
            "row": int(at[0]),
            "col": int(at[1]),
            "rotation": int(e.get("r", 0) or 0),
            "gems": [_gem_id(g) for g in (e.get("gems") or []) if _gem_id(g)],
            "parent": None,          # 'in' 第二趟回填
        })
    for i, e in enumerate(raw):
        if not (isinstance(e, dict) and e.get("id")):
            continue
        parent = e.get("in")
        if parent is None:
            continue
        if not isinstance(parent, int) or parent == i or parent < 0 or parent >= len(out):
            raise ValueError("items[%d].in=%r 非法（须为其他物品的平铺下标）" % (i, parent))
        out[i]["parent"] = parent
    return out


# ─────────────────────────── 编码主入口 ───────────────────────────

def encode_lineup(lineup: dict, item_db: dict) -> dict:
    """阵容 dict → 张量 dict（结构见模块 docstring）。"""
    items_map = _items_map(item_db)
    flat = _flatten(lineup)
    rows, cols = _grid_shape(lineup)
    n = len(flat)

    item_grid = np.full((rows, cols), -1, dtype=np.int32)
    rotation_grid = np.full((rows, cols), -1, dtype=np.int32)
    collision_mask = np.zeros((rows, cols), dtype=np.int8)
    affected_masks = np.zeros((len(AFFECTED_COLORS), rows, cols), dtype=np.int8)
    unknown_ids: List[str] = []

    # 只画引擎装配的根物品：战斗内核只装背包顶层（simulator/lineup.py:98 的
    # roots、simulator/gd_core_engine.py:_build_side 只遍历 backpack.items），
    # 袋内物品（in/嵌套 contents）不装配——编码层照引擎口径，把袋内物品从
    # 网格里剔除，代理模型对「引擎看不见的物品」同样看不见。
    order = [i for i, e in enumerate(flat) if e["parent"] is None]
    for k, i in enumerate(order):
        e = flat[i]
        geo = item_geometry(e["id"], e["rotation"], items_map,
                            row=e["row"], col=e["col"])
        if geo is None:
            unknown_ids.append(e["id"])
            continue
        idx = rot_index(e["rotation"])
        for (r, c) in geo["collision"]:
            if 0 <= r < rows and 0 <= c < cols:
                item_grid[r, c] = i
                rotation_grid[r, c] = idx
                collision_mask[r, c] = 1
        idx = rot_index(e["rotation"])
        for (r, c) in geo["collision"]:
            if 0 <= r < rows and 0 <= c < cols:
                item_grid[r, c] = k
                rotation_grid[r, c] = idx
                collision_mask[r, c] = 1
        for color, cells in geo["affected"].items():
    # ── 宝石多热：只编码根物品（引擎只对根物品 setGem——gd_core_engine
    #    ._build_side:716-721 在装配根物品时挂宝石；袋内物品及其宝石不装配、
    #    不进编码）。词表 = 根物品的宝石按首次出现顺序。 ──
    gem_ids: List[str] = []
    seen = set()
    for i in order:
        for g in flat[i]["gems"]:
            if g not in seen:
                seen.add(g)
                gem_ids.append(g)
    gem_col = {g: j for j, g in enumerate(gem_ids)}
    gem_onehot = np.zeros((n_roots, len(gem_ids)), dtype=np.int8)
    for row, i in enumerate(order):
        for g in flat[i]["gems"]:
            gem_onehot[row, gem_col[g]] = 1

    # ── 标量（只统计引擎装配的根物品——袋内物品不参战） ──
    rarity_sum = 0
    for i in order:
        entry = items_map.get(flat[i]["id"])
        if entry is None:
            continue
        descr = entry.get("descr") or {}
        try:
            rarity_sum += int(descr.get("rarity", 0) or 0)
        except (TypeError, ValueError):
            pass

    classes = item_db.get("classes") if isinstance(item_db.get("classes"), dict) else {}
    character = str(lineup.get("character") or "")
    class_id = int(classes.get(character, -1)) if classes else -1
    if classes:
        onehot_len = max(7, max(int(v) for v in classes.values()) + 1)
    else:
        onehot_len = 7
    class_onehot = np.zeros(onehot_len, dtype=np.float32)
    if 0 <= class_id < onehot_len:
        class_onehot[class_id] = 1.0

    root_id_list = [flat[i]["id"] for i in order]
    return {
        "item_grid": item_grid,
        "rotation_grid": rotation_grid,
        "collision_mask": collision_mask,
        "affected_masks": affected_masks,
        "gem_onehot": gem_onehot,
        "gem_ids": gem_ids,
        "ids": root_id_list,
        "root_ids": root_id_list,
        "unknown_ids": unknown_ids,
        "scalars": {
            "num_items": np.int32(n_roots),
            "rarity_sum": np.int32(rarity_sum),
            # 袋内件数：仅作信息参考（引擎不装配袋内物品，不参与战斗）
            "bag_item_count": np.int32(n - n_roots),
            "class_id": np.int32(class_id),
            "class_onehot": class_onehot,
        },
        "grid_shape": np.array([rows, cols], dtype=np.int32),
    }
