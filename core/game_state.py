"""
Game state representation for Backpack Battles.
Parses the raw data from the Bridge into structured objects.
"""
from dataclasses import dataclass, field
from typing import Optional
import logging

logger = logging.getLogger(__name__)


@dataclass
class ShopItem:
    """An item available in the shop."""
    name: str
    item_id: str = ""
    price: int = 0
    position: tuple = (0, 0)
    index: int = 0  # ShopOffer1-5
    raw: dict = field(default_factory=dict)


@dataclass
class InventoryItem:
    """An item in the player's inventory/backpack."""
    name: str
    item_type: str = ""
    position: tuple = (0, 0)
    width: int = 1
    height: int = 1
    script: str = ""
    raw: dict = field(default_factory=dict)


@dataclass
class StorageItem:
    """An item in the storage box."""
    name: str
    position: tuple = (0, 0)
    raw: dict = field(default_factory=dict)


@dataclass
class PlayerState:
    """Player state."""
    health: int = 5
    max_health: int = 5
    gold: int = 0
    round_num: int = 1
    wins: int = 0
    tries: int = 0
    raw: dict = field(default_factory=dict)


@dataclass
class GameState:
    """Complete game state snapshot."""
    player: PlayerState = field(default_factory=PlayerState)
    shop_items: list[ShopItem] = field(default_factory=list)
    inventory_items: list[InventoryItem] = field(default_factory=list)
    storage_items: list[StorageItem] = field(default_factory=list)
    
    can_reroll: bool = False
    can_start_combat: bool = False
    is_shop_visible: bool = True
    is_combat: bool = False
    
    raw: dict = field(default_factory=dict)
    
    def __repr__(self) -> str:
        parts = [
            f"Round {self.player.round_num} | HP: {self.player.health}/{self.player.max_health} | Gold: {self.player.gold}",
            f"Shop: {len(self.shop_items)} items | Inventory: {len(self.inventory_items)} | Storage: {len(self.storage_items)}",
            f"Can reroll: {self.can_reroll} | Can fight: {self.can_start_combat}"
        ]
        return "\n".join(parts)


class GameStateParser:
    """Parses raw Bridge responses into structured GameState objects."""
    
    def parse_full_state(self, shop_data: dict, player_data: dict, inventory_data: dict) -> GameState:
        """Parse all game data into a complete state."""
        state = GameState(raw={
            "shop": shop_data,
            "player": player_data,
            "inventory": inventory_data
        })
        
        # Parse player state
        state.player = self._parse_player(player_data)
        
        # Parse shop items
        state.shop_items = self._parse_shop(shop_data)
        
        # Parse inventory items
        state.inventory_items = self._parse_inventory(inventory_data)
        
        # Parse storage items
        state.storage_items = self._parse_storage(shop_data)
        
        # Parse shop state flags
        state.is_shop_visible = shop_data.get("shop_visible", True)
        
        scb = shop_data.get("start_combat_button", {})
        state.can_start_combat = scb.get("visible", False) and not scb.get("disabled", True)
        
        reroll = shop_data.get("reroll", {})
        state.can_reroll = reroll.get("visible", False)
        
        return state
    
    def _parse_player(self, data: dict) -> PlayerState:
        props = data.get("properties", {})
        ui = data.get("ui", {})
        
        health = 5
        gold = 0
        round_num = 1
        wins = 0
        tries = 0
        
        # Try to extract from UI labels
        h = ui.get("health", {}).get("text", "")
        if h:
            try:
                health = int(h)
            except (ValueError, TypeError):
                pass
        
        g = ui.get("gold", {}).get("text", "")
        if g:
            try:
                gold = int(g)
            except (ValueError, TypeError):
                pass
        
        r = ui.get("round", "")
        if r:
            try:
                round_num = int(r.split()[0]) if r else 1
            except (ValueError, TypeError, IndexError):
                pass
        
        w = ui.get("wins", "")
        if w:
            try:
                wins = int(w.split()[0]) if w else 0
            except (ValueError, TypeError, IndexError):
                pass
        
        t = ui.get("tries", "")
        if t:
            try:
                tries = int(t.split()[0]) if t else 0
            except (ValueError, TypeError, IndexError):
                pass
        
        # Also try from properties
        if not gold:
            gold = props.get("gold", props.get("Gold", 0))
        if not health:
            health = props.get("health", props.get("Health", 5))
        
        return PlayerState(
            health=health,
            gold=gold,
            round_num=round_num,
            wins=wins,
            tries=tries,
            raw=data
        )
    
    def _parse_shop(self, data: dict) -> list[ShopItem]:
        items = []
        offers = data.get("offers", [])
        for i, offer in enumerate(offers):
            if not isinstance(offer, dict):
                continue
            props = offer.get("properties", {})
            name = props.get("item_name", props.get("name", f"ShopItem_{i+1}"))
            price = props.get("price", props.get("cost", 0))
            
            pos = props.get("position", props.get("global_position", {}))
            px = pos.get("x", 0) if isinstance(pos, dict) else 0
            py = pos.get("y", 0) if isinstance(pos, dict) else 0
            
            items.append(ShopItem(
                name=str(name),
                item_id=props.get("id", props.get("item_id", f"shop_{i}")),
                price=int(price) if price else 0,
                position=(float(px), float(py)),
                index=i + 1,
                raw=offer
            ))
        return items
    
    def _parse_inventory(self, data: dict) -> list[InventoryItem]:
        """Parse inventory/backpack items."""
        items = []
        
        # Check for items in the shop's Items node (which has backpack items)
        # The inventory data might come from different sources
        for key, val in data.items():
            if isinstance(val, list):
                for item_data in val:
                    if isinstance(item_data, dict):
                        items.append(self._make_inventory_item(item_data))
            elif isinstance(val, dict):
                if "name" in val and "type" in val:
                    items.append(self._make_inventory_item(val))
        
        return items
    
    def _parse_storage(self, shop_data: dict) -> list[StorageItem]:
        """Parse items in storage box."""
        items = []
        items_data = shop_data.get("items", [])
        if isinstance(items_data, list):
            for item_data in items_data:
                if isinstance(item_data, dict):
                    pos = item_data.get("position", {})
                    items.append(StorageItem(
                        name=item_data.get("name", "Unknown"),
                        position=(pos.get("x", 0), pos.get("y", 0)) if isinstance(pos, dict) else (0, 0),
                        raw=item_data
                    ))
        return items
    
    def _make_inventory_item(self, data: dict) -> InventoryItem:
        props = data.get("properties", {})
        name = props.get("item_name", props.get("name", data.get("name", "Unknown")))
        pos = data.get("position", props.get("position", {}))
        return InventoryItem(
            name=str(name),
            item_type=data.get("type", props.get("type", "")),
            position=(pos.get("x", 0), pos.get("y", 0)) if isinstance(pos, dict) else (0, 0),
            width=props.get("width", 1),
            height=props.get("height", 1),
            script=data.get("script", ""),
            raw=data
        )
