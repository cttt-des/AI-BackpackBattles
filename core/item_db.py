"""
物品资源库 —— 加载逆向提取的游戏资源（assets/item_db.json + assets/sprites/）

由 tools/extract_assets.py 从 BackpackBattles.pck 生成：
* zh        —— 官方简体中文名（Items/ExclusiveItems 翻译表）
* is_bag    —— 是否容器（tscn 中 Icon 下含 TileMap）
* cell_px   —— CollisionMap 占格的像素偏移列表（相对物品节点原点，每格左上角）
* sprite    —— 贴图文件名（assets/sprites/*.png）

占格几何
--------
物品节点原点即其在 Player 空间的 position；占格 g 的中心相对原点为
cell_px[g] + (40,40)，绕原点旋转 rotation 后加上 position 得到绝对像素，
再对 Inventory 锚点取格：(row,col) = floor((abs - inv_origin) / 80)。
"""
from __future__ import annotations

import json
import math
import re
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from .paths import get_base_dir, get_resource_dir

_RUNTIME_NAME = re.compile(r"^@?(.*?)@\d+$")  # "@Leather Bag@3537" → "Leather Bag"


def clean_name(name: str) -> str:
    """去掉 Godot 运行时重名节点的 @Name@id 修饰。"""
    if not name:
        return name
    m = _RUNTIME_NAME.match(name)
    return m.group(1) if m else name


class ItemDB:
    """物品静态数据库（中文名/贴图/占格形状/容器判定）。"""

    def __init__(self, assets_dir: Optional[Path] = None):
        self.assets_dir = Path(assets_dir) if assets_dir else self._locate_assets()
        self.db: Dict[str, dict] = {}
        self._by_key: Dict[str, dict] = {}
        if self.assets_dir:
            f = self.assets_dir / "item_db.json"
            if f.exists():
                try:
                    self.db = json.loads(f.read_text(encoding="utf-8"))
                    self._by_key = {v.get("key", k): v for k, v in self.db.items()}
                except Exception:
                    self.db = {}

    @staticmethod
    def _locate_assets() -> Optional[Path]:
        for base in (get_base_dir(), get_resource_dir()):
            d = Path(base) / "assets"
            if (d / "item_db.json").exists():
                return d
        return None

    # ---------- 查询 ----------
    def entry(self, name: str) -> Optional[dict]:
        name = clean_name(name)
        e = self.db.get(name)
        if e is None:
            e = self._by_key.get(name.replace(" ", ""))
        return e

    def zh(self, name: str) -> str:
        """中文名；没有翻译时回退英文名。"""
        e = self.entry(name)
        return (e.get("zh") or clean_name(name)) if e else clean_name(name)

    def label(self, name: str) -> str:
        """GUI 标签：中文（无翻译时英文）。"""
        return self.zh(name)

    def is_bag(self, name: str) -> bool:
        e = self.entry(name)
        return bool(e and e.get("is_bag"))

    def sprite_path(self, name: str) -> Optional[Path]:
        e = self.entry(name)
        if not e or not e.get("sprite") or not self.assets_dir:
            return None
        p = self.assets_dir / "sprites" / e["sprite"]
        return p if p.exists() else None

    # ---------- 联动位置（逆向自 tscn Connector 场景相对偏移）----------
    # 键: 物品原始英文名（clean_name 前的节点名）, 值: (offset_x, offset_y, connector_type)
    _CONNECTOR_OFFSETS: Dict[str, tuple] = {
        "Ace of Spades": (-13, -93, "Card"),
        "Darkest Lotus": (-13, -93, "Card"),
        "Deck of Cards": (-13, -93, "Card"),
        "Joker": (-13, -93, "Card"),
        "Reverse": (-13, -93, "Card"),
        "Holo Fire Lizard": (-13, -93, "Card"),
        "The Fool": (-13, -93, "Card"),
        "The Lovers": (-13, -93, "Card"),
        "White-Eyes Blue Dragon": (-13, -93, "Card"),
    }

    def connector_offset(self, name: str) -> Optional[tuple]:
        """返回 (offset_x, offset_y, connector_type)，无连接器返回 None。"""
        cleaned = clean_name(name)
        e = self.entry(cleaned)
        if e:
            raw = e.get("key", cleaned)
            off = self._CONNECTOR_OFFSETS.get(raw)
            if off:
                return off
        return None

    # ---------- 背包格子素材（游戏内 res://Items/Tiles/Slot|FilledSlot）----------
    def cell_empty_path(self) -> Optional[Path]:
        if not self.assets_dir:
            return None
        p = self.assets_dir / "cell_empty.png"
        return p if p.exists() else None

    def cell_filled_path(self) -> Optional[Path]:
        if not self.assets_dir:
            return None
        p = self.assets_dir / "cell_filled.png"
        return p if p.exists() else None

    # ---------- 占格几何 ----------
    def occupied_cells(self, name: str, pos: Tuple[float, float],
                       rotation: float, inv_origin: Tuple[float, float],
                       cell: int = 80, grid_w: int = 30, grid_h: int = 30,
                       ) -> List[Tuple[int, int]]:
        """计算物品占用的格子列表 [(row, col), ...]（按行列排序）。

        pos/rotation 为物品节点局部变换（相对 Player），inv_origin 为
        Inventory 锚点局部坐标。占格形状来自 tscn CollisionMap。
        """
        e = self.entry(name)
        cell_px = e.get("cell_px") if e else None
        if not cell_px:
            # 无形状数据 → 退化为单格（物品原点所在格）
            gx = math.floor((pos[0] - inv_origin[0]) / cell)
            gy = math.floor((pos[1] - inv_origin[1]) / cell)
            return [(gy, gx)] if 0 <= gx < grid_w and 0 <= gy < grid_h else []
        cos_r, sin_r = math.cos(rotation), math.sin(rotation)
        out = set()
        half = cell / 2.0
        for cx, cy in cell_px:
            # 格中心（相对物品原点）
            lx, ly = cx + half, cy + half
            # 旋转
            rx = lx * cos_r - ly * sin_r
            ry = lx * sin_r + ly * cos_r
            ax, ay = pos[0] + rx, pos[1] + ry
            gx = math.floor((ax - inv_origin[0]) / cell)
            gy = math.floor((ay - inv_origin[1]) / cell)
            if -2 <= gx < grid_w and -2 <= gy < grid_h:
                out.add((gy, gx))
        return sorted(out)
