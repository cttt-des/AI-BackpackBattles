"""
AI 决策接口 — 外置模式（dict 驱动）

设计要点：
  * bot.run_round() 会把当前状态打包成一个 dict(context) 传给 strategy.decide()
  * decide() 返回一个 Action 列表，bot._execute_action() 逐个执行
  * 由于外置模式没有视觉识别、内存也只提供金币/血量/回合等数值，
    策略对"商店里具体是什么物品/价格"是不可见的（盲操作）。
    因此启发式策略基于槽位与金币做保守决策；LLM 接口预留同样的 dict 契约。

context 结构（见 core/bot.py run_round）:
  {
    "gold": int,
    "hp": int,
    "current_round": int,
    "max_rounds": int,
    "backpack": [ {name,row,col,width,height,rotated,category}, ... ],  # 已放置物品
    "storage_count": int,      # 储存箱内待放置数量
    "owned_items": [name, ...] # 拥有的所有物品名
  }
"""
from abc import ABC, abstractmethod
from dataclasses import dataclass, field
from enum import Enum
from typing import List, Optional, Tuple, Set
import logging

logger = logging.getLogger(__name__)

# 背包尺寸：7 行 × 9 列
GRID_ROWS = 7
GRID_COLS = 9


class ActionType(Enum):
    BUY = "buy"        # params: slot(int 0-4), item(str), cost(int)
    PLACE = "place"    # params: row, col, item(str), rotated(bool)
    SELL = "sell"      # params: item(str)
    MOVE = "move"      # params: from_row, from_col, to_row, to_col
    REROLL = "reroll"  # params: {}
    ROTATE = "rotate"  # params: {}
    WAIT = "wait"      # params: seconds(float)
    COMBAT = "combat"  # params: {} (战斗由 run_round 处理)


@dataclass
class Action:
    """单个待执行动作。bot._execute_action 通过 .type 和 .params 消费。"""
    type: ActionType
    params: dict = field(default_factory=dict)

    def __repr__(self) -> str:
        return f"Action({self.type.value}, {self.params})"


class AIStrategy(ABC):
    """AI 决策策略基类。契约：decide(context: dict) -> List[Action]"""

    @abstractmethod
    def decide(self, context: dict) -> List[Action]:
        ...


# ---------------------------------------------------------------------------
# 网格辅助
# ---------------------------------------------------------------------------
def _occupied_cells(backpack: list) -> Set[Tuple[int, int]]:
    """根据 backpack.to_dict() 结果计算已占用的格子集合"""
    occ: Set[Tuple[int, int]] = set()
    for it in backpack or []:
        r0, c0 = int(it.get("row", 0)), int(it.get("col", 0))
        w, h = int(it.get("width", 1)), int(it.get("height", 1))
        for r in range(r0, r0 + h):
            for c in range(c0, c0 + w):
                occ.add((r, c))
    return occ


def _next_free_cell(occ: Set[Tuple[int, int]]) -> Optional[Tuple[int, int]]:
    """从左上到右下寻找第一个空格（1×1）。行优先。"""
    for r in range(GRID_ROWS):
        for c in range(GRID_COLS):
            if (r, c) not in occ:
                return (r, c)
    return None


class HeuristicStrategy(AIStrategy):
    """
    启发式盲操作策略。

    因为看不到商店内容/价格，策略遵循简单稳健的规则：
      1. 若金币充裕（高于保留下限），按槽位从左到右尝试购买若干个商品
         —— 买不起的拖拽会被游戏忽略，不会报错。
      2. 把储存箱中的物品（以及本回合买入的）依次放入背包左上→右下的空格。
      3. 若无任何可做的操作则直接开战。
    """

    def __init__(self, config: Optional[dict] = None):
        config = config or {}
        # 兼容：既可能传入整个 ai 配置，也可能只传 heuristic 段
        h = config.get("heuristic", config) if isinstance(config, dict) else {}
        self.buys_per_round: int = int(h.get("buys_per_round", 2))
        self.min_gold_reserve: int = int(h.get("min_gold_reserve", 0))
        self.max_rerolls_per_round: int = int(h.get("max_rerolls_per_round", 0))
        self.auto_start_combat: bool = bool(h.get("auto_start_combat", True))

    def decide(self, context: dict) -> List[Action]:
        actions: List[Action] = []
        gold = int(context.get("gold", 0) or 0)
        storage_count = int(context.get("storage_count", 0) or 0)
        backpack = context.get("backpack", []) or []

        occ = _occupied_cells(backpack)

        # --- 1. 购买阶段（盲买槽位）---
        planned_buys = 0
        if gold > self.min_gold_reserve:
            for slot in range(self.buys_per_round):
                actions.append(Action(
                    ActionType.BUY,
                    {"slot": slot, "item": f"shop_{slot}", "cost": 0},
                ))
                planned_buys += 1

        # --- 2. 放置阶段（储存箱内已有 + 本回合买入）---
        to_place = storage_count + planned_buys
        for _ in range(to_place):
            cell = _next_free_cell(occ)
            if cell is None:
                break  # 背包已满
            r, c = cell
            actions.append(Action(
                ActionType.PLACE,
                {"row": r, "col": c, "item": "", "rotated": False},
            ))
            occ.add((r, c))

        # --- 3. 没有任何可做的操作 → 直接开战 ---
        if not actions and self.auto_start_combat:
            actions.append(Action(ActionType.COMBAT, {}))

        logger.info("启发式决策: %d 步 (金币=%d, 储存=%d)",
                    len(actions), gold, storage_count)
        return actions


class LLMStrategy(AIStrategy):
    """
    LLM 决策策略（预留接口）。

    契约与启发式一致：decide(context: dict) -> List[Action]。
    未配置有效 endpoint 时回退到启发式策略，保证不崩溃。
    接入真实 LLM 时在 _call_llm / _parse_response 中实现即可。
    """

    def __init__(self, config: Optional[dict] = None):
        config = config or {}
        llm = config.get("llm", {}) if isinstance(config, dict) else {}
        self.provider = llm.get("provider", "openai")
        self.model = llm.get("model", "")
        self.api_key = llm.get("api_key", "")
        self.api_base = llm.get("api_base", "")
        self.temperature = float(llm.get("temperature", 0.3))
        self.max_tokens = int(llm.get("max_tokens", 500))
        self._enabled = bool(self.api_key)
        # 回退策略
        self._fallback = HeuristicStrategy(config)

    def decide(self, context: dict) -> List[Action]:
        if not self._enabled:
            logger.info("LLM 未配置 api_key，回退到启发式策略")
            return self._fallback.decide(context)
        try:
            prompt = self._build_prompt(context)
            reply = self._call_llm(prompt)
            actions = self._parse_response(reply)
            if actions:
                return actions
        except Exception as e:  # noqa: BLE001
            logger.warning("LLM 调用失败，回退到启发式: %s", e)
        return self._fallback.decide(context)

    # --- 以下为接入真实 LLM 时需实现的部分 ---
    def _build_prompt(self, context: dict) -> str:
        lines = [
            "你正在玩《背包乱斗》。请根据以下状态给出本回合的操作序列。",
            f"回合: {context.get('current_round')}/{context.get('max_rounds')}",
            f"生命: {context.get('hp')}",
            f"金币: {context.get('gold')}",
            f"背包已放置: {len(context.get('backpack', []))} 件",
            f"储存箱待放置: {context.get('storage_count', 0)} 件",
            f"背包尺寸: {GRID_ROWS} 行 × {GRID_COLS} 列",
            "",
            "请输出 JSON 动作数组，动作类型: buy/place/sell/move/reroll/rotate/combat。",
        ]
        return "\n".join(lines)

    def _call_llm(self, prompt: str) -> str:
        """TODO: 调用真实 LLM API（openai/anthropic/local）并返回文本。"""
        raise NotImplementedError("LLM endpoint 尚未接入")

    def _parse_response(self, reply: str) -> List[Action]:
        """把 LLM 返回的 JSON 解析为 Action 列表。"""
        import json
        actions: List[Action] = []
        try:
            data = json.loads(reply)
        except Exception:
            return actions
        type_map = {t.value: t for t in ActionType}
        for step in data if isinstance(data, list) else []:
            t = type_map.get(str(step.get("type", "")).lower())
            if t is None:
                continue
            params = {k: v for k, v in step.items() if k != "type"}
            actions.append(Action(t, params))
        return actions
