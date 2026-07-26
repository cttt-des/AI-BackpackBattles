"""
状态追踪器 — 维护一个独立于游戏内存的游戏状态模型
追踪已购买物品、背包布局、回合信息等
"""

import logging
from typing import Dict, List, Optional, Tuple
from dataclasses import dataclass, field
from enum import Enum

logger = logging.getLogger(__name__)


class ItemCategory(Enum):
    WEAPON = "weapon"
    ARMOR = "armor"
    FOOD = "food"
    POTION = "potion"
    ACCESSORY = "accessory"
    BAG = "bag"
    UNKNOWN = "unknown"


@dataclass
class Item:
    """物品数据"""
    name: str
    category: ItemCategory = ItemCategory.UNKNOWN
    cost: int = 0
    sell_value: int = 0
    width: int = 1  # 占几列
    height: int = 1  # 占几行
    effects: List[str] = field(default_factory=list)

    def to_dict(self) -> dict:
        return {
            "name": self.name,
            "category": self.category.value,
            "cost": self.cost,
            "sell_value": self.sell_value,
            "width": self.width,
            "height": self.height,
            "effects": self.effects,
        }


@dataclass
class PlacedItem:
    """放置在背包中的物品"""
    item: Item
    row: int  # 左上角行
    col: int  # 左上角列
    rotated: bool = False

    @property
    def occupied_cells(self) -> List[Tuple[int, int]]:
        """返回该物品占用的所有格子坐标"""
        cells = []
        h = self.item.width if self.rotated else self.item.height
        w = self.item.height if self.rotated else self.item.width
        for r in range(self.row, self.row + h):
            for c in range(self.col, self.col + w):
                cells.append((r, c))
        return cells


class BackpackGrid:
    """背包网格：7 行 × 9 列"""

    ROWS = 7
    COLS = 9

    def __init__(self):
        # grid[row][col] = 物品名 或 None
        self.grid: List[List[Optional[str]]] = [
            [None] * self.COLS for _ in range(self.ROWS)
        ]
        self.items: Dict[str, PlacedItem] = {}  # item_name -> PlacedItem

    def can_place(self, row: int, col: int, width: int, height: int) -> bool:
        """检查能否在 (row, col) 放置 width×height 的物品"""
        if row < 0 or col < 0:
            return False
        if row + height > self.ROWS or col + width > self.COLS:
            return False
        for r in range(row, row + height):
            for c in range(col, col + width):
                if self.grid[r][c] is not None:
                    return False
        return True

    def place(self, item: Item, row: int, col: int, rotated: bool = False) -> bool:
        """放置物品到背包"""
        w = item.width if not rotated else item.height
        h = item.height if not rotated else item.width

        if not self.can_place(row, col, w, h):
            return False

        placed = PlacedItem(item=item, row=row, col=col, rotated=rotated)
        self.items[item.name] = placed

        for r, c in placed.occupied_cells:
            self.grid[r][c] = item.name

        logger.info(f"[背包] 放置 {item.name} 在 ({row},{col}) {'[旋转]' if rotated else ''}")
        return True

    def remove(self, row: int, col: int) -> Optional[str]:
        """移除指定格子的物品"""
        name = self.grid[row][col]
        if name is None:
            return None
        if name in self.items:
            placed = self.items.pop(name)
            for r, c in placed.occupied_cells:
                self.grid[r][c] = None
        logger.info(f"[背包] 移除 {name} 从 ({row},{col})")
        return name

    def find_empty_spot(self, width: int, height: int) -> Optional[Tuple[int, int]]:
        """找到第一个能放下 width×height 物品的位置"""
        for r in range(self.ROWS - height + 1):
            for c in range(self.COLS - width + 1):
                if self.can_place(r, c, width, height):
                    return (r, c)
        return None

    def get_item_pos(self, item_name: str) -> Optional[Tuple[int, int]]:
        """获取物品在背包中的位置"""
        if item_name in self.items:
            p = self.items[item_name]
            return (p.row, p.col)
        return None

    def to_dict(self) -> dict:
        result = []
        for name, placed in self.items.items():
            result.append({
                "name": name,
                "row": placed.row,
                "col": placed.col,
                "width": placed.item.width if not placed.rotated else placed.item.height,
                "height": placed.item.height if not placed.rotated else placed.item.width,
                "rotated": placed.rotated,
                "category": placed.item.category.value,
            })
        return result

    def clear(self):
        self.grid = [[None] * self.COLS for _ in range(self.ROWS)]
        self.items.clear()


class GameStateTracker:
    """
    游戏状态追踪器
    维护一个不依赖直接内存读取的游戏状态模型
    """

    def __init__(self):
        self.gold: int = 10
        self.hp: int = 5
        self.max_hp: int = 5
        self.current_round: int = 1
        self.max_rounds: int = 18
        self.is_shop_phase: bool = True

        self.backpack = BackpackGrid()
        self.storage: List[Item] = []  # 储存箱中的物品
        self.shop_items: Dict[int, str] = {}  # slot_index -> item_name
        self.owned_items: Dict[str, Item] = {}  # 拥有的所有物品

        self.action_log: List[str] = []
        self.round_history: List[dict] = []

    def reset_round(self):
        """新回合开始"""
        self.shop_items.clear()
        self.storage.clear()
        self.is_shop_phase = True
        self.action_log.clear()

    def new_game(self):
        """新游戏开始"""
        self.gold = 10
        self.hp = 5
        self.current_round = 1
        self.is_shop_phase = True
        self.backpack.clear()
        self.storage.clear()
        self.shop_items.clear()
        self.owned_items.clear()
        self.action_log.clear()
        self.round_history.clear()

    def buy_item(self, item: Item, cost: int, slot: int):
        """记录购买物品"""
        self.gold -= cost
        self.storage.append(item)
        self.owned_items[item.name] = item
        self.shop_items.pop(slot, None)
        msg = f"购买 {item.name} (-{cost}金) → 储存箱"
        self.action_log.append(msg)
        logger.info(msg)

    def place_item(self, item_name: str, row: int, col: int, rotated: bool = False):
        """记录放置物品到背包"""
        if item_name not in self.owned_items:
            return
        item = self.owned_items[item_name]
        if self.backpack.place(item, row, col, rotated):
            # 从储存箱移除
            self.storage = [i for i in self.storage if i.name != item_name]
            msg = f"放置 {item_name} 到背包 ({row},{col}){' [旋转]' if rotated else ''}"
            self.action_log.append(msg)

    def sell_item(self, item_name: str):
        """记录出售物品"""
        if item_name not in self.owned_items:
            return
        item = self.owned_items.pop(item_name)
        self.gold += item.sell_value
        # 从背包移除
        for r in range(self.backpack.ROWS):
            for c in range(self.backpack.COLS):
                if self.backpack.grid[r][c] == item_name:
                    self.backpack.remove(r, c)
                    break
        # 从储存箱移除
        self.storage = [i for i in self.storage if i.name != item_name]
        msg = f"出售 {item_name} (+{item.sell_value}金)"
        self.action_log.append(msg)
        logger.info(msg)

    def start_combat(self):
        """开始战斗"""
        self.is_shop_phase = False
        self.round_history.append({
            "round": self.current_round,
            "gold": self.gold,
            "hp": self.hp,
            "backpack": self.backpack.to_dict(),
            "actions": list(self.action_log),
        })
        msg = f"=== 第 {self.current_round} 回合 开始战斗 === HP:{self.hp} 金:{self.gold}"
        self.action_log.append(msg)
        logger.info(msg)

    def end_combat(self, hp_lost: bool = False):
        """战斗结束"""
        if hp_lost:
            self.hp -= 1
        self.current_round += 1
        self.is_shop_phase = True
        logger.info(f"战斗结束 → 第 {self.current_round} 回合 HP:{self.hp}")

    def sync_from_memory(self, mem_state: dict):
        """从内存读取同步关键数值"""
        if "gold" in mem_state and mem_state["gold"] is not None:
            self.gold = mem_state["gold"]
        if "hp" in mem_state and mem_state["hp"] is not None:
            self.hp = mem_state["hp"]
        if "round" in mem_state and mem_state["round"] is not None:
            self.current_round = mem_state["round"]

    def get_summary(self) -> dict:
        """获取当前状态摘要"""
        return {
            "gold": self.gold,
            "hp": self.hp,
            "max_hp": self.max_hp,
            "round": self.current_round,
            "max_rounds": self.max_rounds,
            "phase": "shop" if self.is_shop_phase else "combat",
            "backpack_items": len(self.backpack.items),
            "storage_items": len(self.storage),
            "shop_items": len(self.shop_items),
            "total_owned": len(self.owned_items),
            "backpack": self.backpack.to_dict(),
            "storage": [i.to_dict() for i in self.storage],
            "recent_actions": self.action_log[-10:],
        }
