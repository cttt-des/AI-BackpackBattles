"""
物品读取器 —— 结构性读取当前摆盘（背包网格）与储物箱内的物品

场景树布局（2026-07-26 活体实测，Backpack Battles / Godot 3.6 x64）
------------------------------------------------------------------
root(Viewport)
 └─ Main (current_scene)
     ├─ Player                     ← 玩家区
     │   ├─ Inventory              ← 背包网格锚点 (Node2D, local pos≈(50,60), 80px/格)
     │   ├─ <物品名> (Node2D)      ← 摆盘物品，脚本 res://Items/<Item>.gd
     │   └─ ...
     └─ Shop
         ├─ Items/<物品名>         ← 商店在售物品
         └─ Storagebox/<物品名>    ← 储物箱物品（有旋转，local≠global）

判定规则
--------
* 物品节点 = 脚本路径以 res://Items/ 开头的节点，且排除装饰性子节点
  （SocketsNode/GemSocket/BagBorder/GooglyEye/ItemPushZone/Tiles 等）。
* 物品名 = 节点名（游戏用显示名命名节点，如 "Gloves of Haste"）。
* 网格坐标 = (物品局部 pos - Inventory 局部 pos) / 80，四舍五入。
  物品 pos 是其锚点（通常在物品左上格中心附近），列/行取 floor。
"""
from __future__ import annotations

import logging
import struct
from typing import Dict, List, Optional

from .godot_reader import GodotReader
from .item_db import ItemDB, clean_name

logger = logging.getLogger(__name__)

# 排除的装饰/功能性脚本（不是真实物品）
_EXCLUDE_SCRIPT_SUFFIXES = (
    "SocketsNode.gd", "GemSocket.gd", "BagBorder.gd",
    "GooglyEye.gd", "ItemPushZone.gd",
)
_EXCLUDE_SCRIPT_PARTS = ("/Tiles/", "/Animations/")


class ItemInfo(dict):
    """物品信息（dict 子类，便于 JSON/GUI 直接用）。
    字段: name(英文), zh(中文), zone(backpack|storage|shop), is_bag(容器),
          row, col(锚点格), cells([(row,col)..] 占用格), rotation, x, y, script
    """


class ItemReader:
    """从场景树结构性读取摆盘/储物箱/商店的物品清单。"""

    def __init__(self, godot_reader: GodotReader, item_db: Optional[ItemDB] = None):
        self.gr = godot_reader
        self.db = item_db or ItemDB()

    def node_rotation(self, node: int) -> float:
        """读取 Node2D.rotation（实测位于 position 之后 +0x278）。"""
        off = self.gr.off.get("node2d_rot_off", 0x278)
        d = self.gr.reader.read(node + off, 4)
        if not d or len(d) < 4:
            return 0.0
        (rot,) = struct.unpack("<f", d)
        if rot != rot or abs(rot) > 100:  # NaN/离谱值
            return 0.0
        return rot

    # ---------- 内部工具 ----------
    def _is_item_script(self, sp: Optional[str]) -> bool:
        if not sp or not sp.startswith("res://Items/"):
            return False
        if sp.endswith(_EXCLUDE_SCRIPT_SUFFIXES):
            return False
        return not any(p in sp for p in _EXCLUDE_SCRIPT_PARTS)

    def _find_main(self) -> Optional[int]:
        """定位 current_scene 'Main'（root 的直接子节点里找）。"""
        root = self.gr.get_root()
        if not root:
            return None
        for c in self.gr.get_children(root):
            if self.gr.node_name(c) == "Main":
                return c
        return None

    def _child_by_name(self, node: int, name: str) -> Optional[int]:
        for c in self.gr.get_children(node):
            if self.gr.node_name(c) == name:
                return c
        return None

    def _find_by_name(self, node: int, name: str, max_depth: int = 12) -> Optional[int]:
        """在 node 子树内 BFS 递归查找名为 name 的节点（支持任意层级嵌套）。

        游戏场景树的 Player/Inventory/Shop/Storagebox/Items 未必都是直接子节点，
        用递归深搜避免漏读储物箱/商店/背包物品。
        """
        if not node:
            return None
        queue = [(node, 0)]
        i = 0
        while i < len(queue):
            cur, depth = queue[i]
            i += 1
            if self.gr.node_name(cur) == name:
                return cur
            if depth < max_depth:
                for c in self.gr.get_children(cur):
                    queue.append((c, depth + 1))
        return None

    def _collect_items(self, parent: int, zone: str,
                       inv_origin: Optional[tuple]) -> List[ItemInfo]:
        """收集 parent 直接子节点中的物品。"""
        out: List[ItemInfo] = []
        cell = self.gr.off.get("inv_cell_px", 80)
        for c in self.gr.get_children(parent):
            sp = self.gr.node_script_path(c)
            if not self._is_item_script(sp):
                continue
            raw = self.gr.node_name(c) or sp.rsplit("/", 1)[-1][:-3]
            name = clean_name(raw)
            pos = self.gr.node_pos(c)
            rot = self.node_rotation(c)
            info = ItemInfo(name=name, zh=self.db.zh(name), zone=zone,
                            script=sp, is_bag=self.db.is_bag(name),
                            rotation=round(rot, 4),
                            x=None, y=None, row=None, col=None, cells=[],
                            price=None)
            if pos:
                info["x"], info["y"] = round(pos[0], 1), round(pos[1], 1)
                if zone == "backpack" and inv_origin:
                    # 锚点格（物品原点所在格）
                    gx = (pos[0] - inv_origin[0]) / cell
                    gy = (pos[1] - inv_origin[1]) / cell
                    if -2 <= gx < 30 and -2 <= gy < 30:
                        info["col"] = int(gx)
                        info["row"] = int(gy)
                    # 完整占格（tscn CollisionMap 形状 + 旋转）
                    info["cells"] = self.db.occupied_cells(
                        name, pos, rot, inv_origin, cell)
            if zone == "shop":
                # 商店在售物品读取价格（运行时 GDScriptInstance 成员）
                info["price"] = self._read_price(c)
            out.append(info)
        # 容器排前面（GUI 先画袋子再画物品）
        out.sort(key=lambda i: (not i["is_bag"], i["name"]))
        return out

    def _read_price(self, node: int) -> Optional[int]:
        """读取商店物品当前显示价格。

        游戏模型：物品有初始价格 base；商店中只可能是原价（base）或打折价
        ceil(base/2)。本函数按下列顺序确定：
          1) 若 config 显式指定 member_price（及可选 member_discount），直接用：
             显示价 = base  若 member_discount 为假；否则 ceil(base/2)。
          2) 否则启发式：物品脚本成员里常同时存 base 与 ceil(base/2)，检测满足
             b == ceil(a/2) 且 a>b>=2 的整数对 (a=原价, b=折后)，返回折后价；
             若没有这样的对，视为未打折，返回最像价格的整型候选。
          3) 兜底：取 1..1000 范围内最大的整型候选；仍无则 None。
        """
        cfg = self.gr.off
        idx_price = cfg.get("member_price", None)
        idx_disc = cfg.get("member_discount", None)
        # 1) 显式配置优先
        if idx_price is not None and idx_price >= 0:
            base = self.gr.read_member(node, idx_price)
            if base is not None and 0 < base < 10_000_000:
                if idx_disc is not None and idx_disc >= 0:
                    disc = self.gr.read_member(node, idx_disc)
                    if disc:
                        return -int(-base // 2)  # ceil(base/2)
                return base
        # 2) 启发式：半价对 (a=原价, b=折后=ceil(a/2))
        members = self.gr.read_members(node)
        ints = [m for m in members if isinstance(m, int) and 1 <= m <= 100_000]
        best = None
        for a in ints:
            b = -int(-a // 2)  # ceil(a/2)
            if b >= 2 and b < a and b in ints:
                if best is None or a > best[0]:
                    best = (a, b)
        if best:
            return best[1]
        # 3) 兜底：无折半对 → 视为未打折，取最像价格的候选
        cands = [m for m in ints if m <= 1000]
        if cands:
            price = max(cands)
            logger.debug("价格启发式兜底(未标定 member_price): 候选=%s → 取 %s",
                         sorted(set(ints)), price)
            return price
        return None

    # ---------- 对外 API ----------
    def read_items(self) -> Dict[str, List[ItemInfo]]:
        """读取当前摆盘/储物箱/商店的全部物品。

        返回 {"backpack": [...], "storage": [...], "shop": [...]}
        读不到（进程/场景不可用）时返回三个空列表。
        """
        empty = {"backpack": [], "storage": [], "shop": []}
        try:
            main = self._find_main()
            if not main:
                return empty

            result = dict(empty)

            player = self._find_by_name(main, "Player")
            if player:
                inv = self._find_by_name(player, "Inventory")
                inv_origin = self.gr.node_pos(inv) if inv else None
                result["backpack"] = self._collect_items(player, "backpack", inv_origin)

            shop = self._find_by_name(main, "Shop")
            if shop:
                storage = self._find_by_name(shop, "Storagebox")
                if storage:
                    result["storage"] = self._collect_items(storage, "storage", None)
                shop_items = self._find_by_name(shop, "Items")
                if shop_items:
                    result["shop"] = self._collect_items(shop_items, "shop", None)
            return result
        except Exception as e:  # noqa: BLE001
            logger.debug("物品读取失败: %s", e)
            return empty

    def summary_lines(self) -> List[str]:
        """人类可读的物品清单（供日志/CLI 使用）。"""
        data = self.read_items()
        lines: List[str] = []
        for it in data["backpack"]:
            tag = "容器" if it["is_bag"] else "摆盘"
            if it["cells"]:
                cells = ",".join(f"({r},{c})" for r, c in it["cells"])
                lines.append(f"[{tag}] {it['zh']}({it['name']}) 占格 {cells}")
            elif it["row"] is not None:
                lines.append(f"[{tag}] {it['zh']}({it['name']}) @ 格({it['row']},{it['col']})")
            else:
                lines.append(f"[{tag}] {it['zh']}({it['name']}) @ px({it['x']},{it['y']})")
        for it in data["storage"]:
            lines.append(f"[储物箱] {it['zh']}({it['name']})")
        for it in data["shop"]:
            lines.append(f"[商店] {it['zh']}({it['name']})")
        return lines
