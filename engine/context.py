# -*- coding: utf-8 -*-
"""engine/context.py — BattleContext：每场战斗的全部可变全局状态

对齐引擎的 autoload 单例（Game/EventBus/Util/ItemBook），但**按场实例化**：
无进程级单例、可并行、seed 决定一切随机。转译代码经 `_item.ctx.game` 等
访问（codegen 的 Name 替换）。
"""
from __future__ import annotations

import random
from types import SimpleNamespace
from typing import Any, Dict

from .events import CombatLog
from .namespaces import enum_ns
from .rng import BalancedRange, flip, flip_percent, roll
from .stubs import StubRegistry


class _EventTypeEnum:
    """Game.EventType 枚举（Game.gd:441-484）"""
    Activation = 0
    DealDamage = 1
    CriticalDamage = 2
    MissedAttack = 3
    TakeDamage = 4
    LoseHealth = 5
    AttackSpeed = 6
    InvulnerableStart = 7
    InvulnerableEnd = 8
    Stun = 9
    StunResisted = 10
    CriticalResisted = 11
    Health = 12
    Stamina = 13
    DrainStamina = 14
    OutofStamina = 15
    DamageBuff = 16
    DamReduction = 17
    DamIncrease = 18
    TemporaryMaxHealth = 19
    TemporaryMaxStamina = 20
    BattleRageStart = 21
    BattleRageEnd = 22
    Reincarnate = 23
    CooldownAdvance = 24
    Unhealing = 98
    Fatigue = 99
    Block = 100
    Lucky = 101
    Regeneration = 102
    Vampirism = 103
    Spikes = 104
    Mana = 105
    Empower = 106
    Heat = 107
    Poison = 108
    Blind = 109
    Cold = 110
    Win = 111
    Loss = 112


class _CombatSceneNode:
    """Game.combatSceneNode 的战斗语义面：advanceTime → CombatTimer.advanceTime
    （Combat.gd:920-921 转发链；疲劳起点提前，Power of the Moon 使用）。"""

    def __init__(self, game: "GameGlobal"):
        self._game = game

    def advanceTime(self, time: float):
        # CombatTimer.gd:184-194：timeAdvance 累积；若疲劳已开始（timeLeft 已耗尽）
        # 则无法再提前——与 startFatigue 幂等语义一致，此处仅累积
        self._game.timeAdvance += float(time or 0.0)


class CombatTimerNode:
    """Game.combatTimer 节点还原：疲劳信号（fatigue_start 等）的连接载体。
    Pumpkin.gd:20 connectForCombat(Game.combatTimer, "fatigue_start", ...) 依赖。"""

    def __init__(self):
        self._signals: dict = {}

    def connect_signal(self, signal: str, cb):
        self._signals.setdefault(signal, []).append(cb)

    def emit_signal(self, signal: str, *args):
        for cb in list(self._signals.get(signal, [])):
            cb(*args)


class GameGlobal:
    """Game.gd 的战斗级全局（Game.gd:361-362 ropeSpeedups/cubeAdvanced 等）"""

    def __init__(self):
        self.ropeSpeedups: Dict[Any, float] = {}
        self.cubeAdvanced: Dict[Any, bool] = {}
        self.fightEnded: bool = False
        self.curRound: int = 1
        self.curClass: int = 0            # Game.Classes 枚举（Shovel 挖掘用，商店期）
        self.combatLog: Any = None        # 由 BattleContext 注入真实 CombatLog
        self.combatTimer = CombatTimerNode()   # 疲劳信号载体（Pumpkin 等 connect）
        self.combatSceneNode = _CombatSceneNode(self)  # advanceTime 转发（Combat.gd:920）
        self.timeAdvance: float = 0.0     # CombatTimer.gd:185 advanceTime 累积
        self.EventType = _EventTypeEnum()
        self.PLAYER: Any = None
        self.OPPONENT: Any = None
        # Game.Classes 枚举（Shovel.gd: Classes.Ranger/Reaper；源码另有 None/Undefined）
        self.Classes = enum_ns(Neutral=0, Ranger=1, Reaper=2, **{"None": 0, "Undefined": 0})
        # Game.Mode 枚举（Game.gd:148；Chess Board.onPrepare 判 History 模式）
        self.Mode = enum_ns(Ranked=0, Unranked=1, Lobbies=2, Unselected=3, History=4)
        self.curMode: int = 0

    def getBuffs(self):
        return [101, 102, 103, 104, 105, 106, 107]

    def getDebuffs(self):
        return [108, 109, 110]

    def getConfigValue(self, *a, **k):
        return None                       # 设置项（ItemLibraryFreeAdd 等，商店期）

    def showExclusiveContent(self):
        return True


class UtilFacade:
    """Util.gd 的战斗相关面（随机量走 ctx.rng；纯助手直连）"""

    def __init__(self, ctx: "BattleContext"):
        self._ctx = ctx

    # ---- 随机（走 battle rng，确定性） ----
    def flip(self, chance: float = 0.5):
        return flip(self._ctx.rng, chance) if isinstance(chance, (int, float)) else \
            flip(self._ctx.rng, 0.5)

    def roll(self, maximum: float = 100.0):
        return roll(self._ctx.rng, maximum)

    def flipPercent(self, chance: float):
        return flip_percent(self._ctx.rng, chance)

    def randPitch(self, _amt=0.05):
        return 1.0                        # 音高（视觉）

    @property
    def time(self):
        return self._ctx.time             # Util.time 物理时间累加器（Util.gd:141-146）

    # ---- 字典/数组助手（纯函数） ----
    @staticmethod
    def dictAdd(d, k, v, default=0):
        d[k] = d.get(k, default) + v

    @staticmethod
    def dictSub(d, k, v, default=0):
        d[k] = d.get(k, default) - v

    @staticmethod
    def dictAppend(d, k, v):
        d.setdefault(k, []).append(v)

    @staticmethod
    def dictErase(d, k, v):
        lst = d.get(k)
        if isinstance(lst, list) and v in lst:
            lst.remove(v)

    def pickRandomElement(self, lst):
        """Util.gd:453 randi_range 取随机元素"""
        if not lst:
            return None
        return lst[self._ctx.rng.randrange(len(lst))]

    @staticmethod
    def arrayAsIndexDict(arr):
        return {v: i for i, v in enumerate(arr or [])}

    @staticmethod
    def filterNull(arr):
        return [x for x in (arr or []) if x is not None]

    def flipWeighted(self, weights):
        total = sum(weights or [])
        r = self._ctx.rng.random() * (total if total else 1.0)
        acc = 0.0
        for i, w in enumerate(weights or []):
            acc += w
            if r <= acc:
                return i
        return len(weights) - 1 if weights else 0


class _Descriptor(SimpleNamespace):
    """物品描述符：按 key 判等/哈希（GDScript Dictionary 键语义；转译代码把
    descriptor 当 dict 键、做 != 比较，SimpleNamespace 默认不可哈希会炸）"""

    def __hash__(self):
        return hash(("Descriptor", self.key))

    def __eq__(self, other):
        if isinstance(other, _Descriptor):
            return self.key == other.key
        if isinstance(other, str):
            return self.key == other
        return NotImplemented


class ItemBook:
    """ItemBook：描述符按 key 判等（is_a 联动判定）"""

    def __init__(self, keys):
        self._keys = list(keys)

    def getDescriptor(self, name):
        from . import behavior as _beh
        rarity = _beh.rarity_table().get(name, 0)
        r = rarity
        return _Descriptor(key=name, name=name, rarity=rarity,
                           getRarity=lambda r=r: r,
                           get_rarity=lambda r=r: r,
                           isReleased=lambda: True)

    def __getattr__(self, name):
        # <x>Descriptor 引用 → 转物品名精确/规范化匹配
        if name.endswith("Descriptor") and len(name) > len("Descriptor"):
            base = name[:-len("Descriptor")]
            import re
            words = re.sub(r"([A-Z])", r" \1", base).strip()
            for key in self._keys:
                if key.lower() == words.lower():
                    return self.getDescriptor(key)
        from .stubs import StubRegistry
        stub = StubRegistry()             # 轻量 no-op（结构对齐旧 _ItemBook）
        return stub.make_noop(f"ItemBook.{name}")

    def isItemInInventory(self, descriptor):
        return False


class BattleContext:
    """一场战斗的全部全局状态。seed 决定一切随机（AI 训练确定性）。"""

    def __init__(self, seed: int, item_keys=None):
        self.seed = seed
        self.rng = random.Random(seed)
        self.time: float = 0.0
        self.stubs = StubRegistry()
        self.combat_log = CombatLog(self.stubs)
        self.game = GameGlobal()
        self.game.combatLog = self.combat_log
        self.event_bus = EventBus(ctx=self)
        self.item_book = ItemBook(item_keys or [])
        self.util = UtilFacade(self)

    # 便捷转发（引擎内部用）
    def flip(self, chance: float = 0.5):
        return flip(self.rng, chance)


class EventBus:
    """EventBus.gd 还原（按（源,信号）定向派发；fightEnded 后丢弃）"""

    def __init__(self, ctx: BattleContext):
        self._ctx = ctx
        self._conns: Dict[Any, list] = {}

    @staticmethod
    def _key(emitter, signal_name):
        return (id(emitter), signal_name)

    def connectEvent(self, emitter, signal_name, receiver, method):
        if emitter is None or receiver is None:
            return
        register = getattr(emitter, "connect_signal", None)
        if not callable(register):
            return

        def _cb(*args, _recv=receiver, _m=method):
            call = getattr(_recv, "call_behavior", None)
            if callable(call):
                call(_m, *args)
            else:
                fn = getattr(_recv, _m, None)
                if callable(fn):
                    fn(*args)

        register(signal_name, _cb)

    def emitEvent(self, emitter, signal_name, event=None, arguments=None):
        self.emitAndLog(emitter, signal_name, event, arguments)

    def emitSignal(self, emitter, signal_name, arguments=None):
        self.emitEvent(emitter, signal_name, None, arguments)

    def emitAndLog(self, emitter, signal_name, event=None, arguments=None):
        if getattr(self._ctx.game, "fightEnded", False):
            return                       # EventBus.gd:93-94
        if emitter is None or not signal_name:
            return
        emit = getattr(emitter, "emit_signal", None)
        if callable(emit):
            emit(signal_name, *(arguments or []))

    def queueSignal(self, *a, **k):
        pass

    def flushLoggingQueue(self):
        pass

    def setLoggingMode(self, mode):
        pass

    def getLoggingMode(self):
        return 1

    def disconnectAll(self):
        pass                              # 连接随对象销毁；每场新 ctx
