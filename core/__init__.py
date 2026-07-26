"""
背包乱斗 AI 机器人 - 外置模式
无需修改游戏文件，通过内存读取 + 坐标操作控制游戏
"""

from .window_manager import WindowManager, GameLayout
from .memory_reader import MemoryReader, MemoryGameState
from .state_tracker import GameStateTracker, Item, ItemCategory, BackpackGrid
from .actions import GameActions
from .ai_interface import HeuristicStrategy, LLMStrategy, Action, ActionType
from .bot import BackpackBot

__all__ = [
    "WindowManager",
    "GameLayout",
    "MemoryReader",
    "MemoryGameState",
    "GameStateTracker",
    "Item",
    "ItemCategory",
    "BackpackGrid",
    "GameActions",
    "HeuristicStrategy",
    "LLMStrategy",
    "Action",
    "ActionType",
    "BackpackBot",
]
__version__ = "0.2.0"
