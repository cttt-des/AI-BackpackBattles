# -*- coding: utf-8 -*-
"""behavior.py — 物品行为执行器

把 extract_items.py 生成的 behavior.methods（GDScript 转译的 Python 函数源码）
在运行时编译并执行。函数签名统一为 def <name>(_item, *args)，_item 即物品本身。
任何执行异常都只记录、不上抛，保证单物品行为 bug 不拖垮整场战斗。
"""
from __future__ import annotations

from types import SimpleNamespace
from typing import Any, Dict, Optional
import random as _random

_FLIP_RNG = _random.Random(12345)


class _StaminaResult:
    Sufficient = 0
    Insufficient = 1


class _Character:
    StaminaResult = _StaminaResult


class _Priority:
    Lowest = -10000
    Low = -1000
    Normal = 0
    High = 1000
    Highest = 10000


class _Type:
    Bag = 0
    Consumable = 1
    Food = 2
    Pet = 3
    Weapon = 4
    Shield = 5
    Armor = 6
    Gloves = 7
    Shoes = 8
    Helmet = 9
    Accessory = 10
    Potion = 11
    Card = 12
    Gem = 13
    Scroll = 14
    Book = 15
    Skill = 16
    ChessPiece = 17
    Spell = 18
    Melee = 19
    Ranged = 20
    Effect = 21
    Holy = 22
    Magic = 23
    Vampiric = 24
    Dark = 25
    Nature = 26
    Fire = 27
    Ice = 28
    Musical = 29


class _Tag:
    None_ = 0
    Lifesteal = 1
    Stone = 2
    Scroll = 8
    Dragon = 16
    Staff = 32
    BattleRage = 64
    Singular = 128
    Transient = 256
    Bow = 512


class _Stack:
    None_ = 0
    Block = 1
    Lucky = 2
    Regeneration = 4
    Vampirism = 8
    Spikes = 16
    Mana = 32
    Empower = 64
    Heat = 128
    Poison = 256
    Blind = 512
    Cold = 1024
    Buff = 254
    Debuff = 1792
    BuffNoLuck = 252


class _Util:
    """GDScript Util 全局的 Python 等价（视觉/工具方法；战斗相关按需实现）。"""
    def pickRandomElement(self, lst):
        return lst[0] if lst else None

    def dictAdd(self, d, k, v, default=0):
        d[k] = d.get(k, default) + v

    def tra(self, s, *a):
        return s

    @property
    def time(self):
        # 视觉粒子计时用；无战斗影响，返回 0 不触发粒子即可
        return 0.0

    def arrayAsIndexDict(self, arr):
        """Util.arrayAsIndexDict — 数组转 {元素: 索引} 字典（对齐 GDScript）。"""
        d = {}
        for i, v in enumerate(arr or []):
            d[v] = i
        return d

    def flip(self):
        """Util.flip — 硬币判定（Girl Power/Scale 平局时二选一）。固定种子保证可复现。"""
        return _FLIP_RNG.random() < 0.5



class _Noop:
    """全能兜底对象：任何属性/调用/运算都不崩溃（跨脚本引用、基类变量缺失时）"""

    def __getattr__(self, name):
        return _Noop()

    def __call__(self, *a, **k):
        return _Noop()

    def __bool__(self):
        return False

    def __lt__(self, other): return True
    def __le__(self, other): return True
    def __gt__(self, other): return False
    def __ge__(self, other): return False
    def __eq__(self, other): return self is other
    def __ne__(self, other): return self is not other
    def __add__(self, other): return _Noop()
    def __radd__(self, other): return _Noop()
    def __sub__(self, other): return _Noop()
    def __rsub__(self, other): return _Noop()
    def __mul__(self, other): return _Noop()
    def __rmul__(self, other): return _Noop()
    def __truediv__(self, other): return _Noop()
    def __rtruediv__(self, other): return _Noop()
    def __floordiv__(self, other): return _Noop()
    def __mod__(self, other): return _Noop()
    def __neg__(self): return _Noop()
    def __pos__(self): return _Noop()
    def __abs__(self): return _Noop()
    def __int__(self): return 0
    def __float__(self): return 0.0
    def __str__(self): return "?"
    def __repr__(self): return "<Noop>"
    def __len__(self): return 0
    def __getitem__(self, key): return _Noop()
    def __setitem__(self, key, val): pass
    def __iter__(self): return iter(())
    def __contains__(self, item): return False
    def __hash__(self): return 0
    def __round__(self, ndigits=None): return 0
    def connect_signal(self, *a, **k): return None
    def connect(self, *a, **k): return None
    def get_items(self, *a, **k): return []
    def getItems(self, *a, **k): return []


class _SafeDict(dict):
    """行为全局字典：未定义名字返回 _Noop（不抛 NameError）；内建名优先"""

    def __missing__(self, key):
        try:
            import builtins
            return getattr(builtins, key, _Noop())
        except Exception:
            return _Noop()


def _noop_call(*a, **k):
    return None


def _range_or_value(x):
    """GDScript `for i in <int>` 迭代 0..n-1；列表/数组直接返回"""
    return range(x) if isinstance(x, int) and not isinstance(x, bool) else x


class _Game:
    # Game.EventType 枚举（与引擎 BuffType 数值一致；影响 giveStacksTemporary 等 buff 类型参数）
    EventType = SimpleNamespace(
        Unhealing=98, Fatigue=99, Block=100, Lucky=101, Regeneration=102,
        Vampirism=103, Spikes=104, Mana=105, Empower=106, Heat=107,
        Poison=108, Blind=109, Cold=110, Win=111,
    )

    @staticmethod
    def getDebuffs():
        return [108, 109, 110]  # Poison/Blind/Cold

    @staticmethod
    def getBuffs():
        return [100, 101, 102, 103, 104, 105, 106, 107]  # Block..Heat

    # ---- 战斗全局状态（静态默认；战斗引擎开局可覆写） ----
    curRound = 3
    curMode = 0
    Mode = SimpleNamespace(Combat=0, History=1, Preparation=2, Shop=3)
    combatTimer = _Noop()
    PLAYER = _Noop()
    OPPONENT = _Noop()
    Owner = SimpleNamespace(PlayerInventory=0, OpponentInventory=1, Storage=2)
    CONNECT_ONESHOT = 0
    ActivationAni = SimpleNamespace(Throw=0, Melee=1, Ranged=2, Spell=3)
    time = 0.0

    @staticmethod
    def connect(*a, **k):
        return None

    def __getattr__(self, name):
        # 任何未定义的 Game.<x> 调用都安全降级为无副作用（视觉/引擎内部方法）
        return _noop_call


class _Vector2(tuple):
    """GDScript Vector2 的 Python 等价：可调用构造 + 方向常量（视觉方法用）。"""

    def __new__(cls, x=0.0, y=0.0):
        return tuple.__new__(cls, (float(x), float(y)))

    def rotated(self, angle):
        return self  # 视觉旋转不建模

    @property
    def x(self):
        return self[0]

    @property
    def y(self):
        return self[1]


_Vector2.DOWN = _Vector2(0, 1)
_Vector2.UP = _Vector2(0, -1)
_Vector2.LEFT = _Vector2(-1, 0)
_Vector2.RIGHT = _Vector2(1, 0)
_Vector2.ZERO = _Vector2(0, 0)


# 行为函数可访问的全局命名空间（GDScript 全局/枚举的 Python 等价）
BEHAVIOR_GLOBALS: Dict[str, Any] = {
    "Character": _Character,
    "StaminaResult": _StaminaResult,
    "Priority": _Priority,
    "Type": _Type,
    "Stack": _Stack,
    "Game": _Game(),
    "Affected": SimpleNamespace(Primary=0, Secondary=2, Tertiary=4, Lightning=7),
    "FaceDirection": SimpleNamespace(UP=0, RIGHT=1, DOWN=2, LEFT=3,
                                     flip=lambda d: (d + 2) % 4 if isinstance(d, int) else d),
    "GemMode": SimpleNamespace(Weapon=0, Armor=1, Inventory=2, None_=None),
    "Tag": _Tag,
    "TriggerType": SimpleNamespace(Every=0, StartOfBattle=1, PlayerLow=2, OppoLow=3),
    "EventType": SimpleNamespace(),
    "DamageResult": object,
    "DamageSource": object,
    "Util": _Util(),
    "ChessPiece": SimpleNamespace(PieceColor=SimpleNamespace(White=0, Black=1)),
    "Owner": SimpleNamespace(PlayerInventory=0, OpponentInventory=1, Storage=2),
    "CONNECT_ONESHOT": 0,
    "ActivationAni": SimpleNamespace(Throw=0, Melee=1, Ranged=2, Spell=3),
    "Item": object,
    "ObjectPool": _Noop(),
    "ItemBook": _Noop(),
    "Sound": _Noop(),
    "EventBus": _Noop(),
    "sprite": None,
    "descriptor": SimpleNamespace(params=[], chance=0.0, paramBases={}),
    "placed": False,
    "me": None,
    "_range_or_value": _range_or_value,
    "ceil": __import__("math").ceil,
    "floor": __import__("math").floor,
    "BuffType": __import__("simulator.buff", fromlist=["BuffType"]).BuffType,
    "Vector2": _Vector2,
    "Vector2i": _Vector2,
}


class BehaviorExecutor:
    """按需编译并缓存行为函数。"""

    def __init__(self, spec: Optional[Dict[str, Any]] = None):
        self.spec: Dict[str, Any] = spec or {}
        self.methods: Dict[str, str] = self.spec.get("methods", {}) or {}
        self.methods_raw: Dict[str, str] = self.spec.get("methods_raw", {}) or {}
        self._cache: Dict[str, Any] = {}
        self._failed: set = set()

    def has(self, name: str) -> bool:
        return name in self.methods

    def has_any(self, names) -> bool:
        return any(self.has(n) for n in names)

    def _compile(self, item, name: str):
        src = self.methods.get(name)
        if not src:
            return None
        try:
            ns: Dict[str, Any] = _SafeDict(BEHAVIOR_GLOBALS)
            exec(compile(src, f"<behavior:{item.key}:{name}>", "exec"), ns)
            self._cache[name] = ns[name]
            return ns[name]
        except Exception as e:
            self._failed.add(name)
            _warn(item, f"behavior {name} 编译失败: {e}")
            return None

    def execute(self, item, name: str, *args):
        """执行行为方法。不存在或失败时返回 None。"""
        if name not in self.methods or name in self._failed:
            return None
        fn = self._cache.get(name)
        if fn is None:
            fn = self._compile(item, name)
            if fn is None:
                return None
        try:
            return fn(item, *args)
        except TypeError as e:
            # 参数个数不匹配（如 GDScript 无参方法被传了 res）-> 降级为无参重试
            if "positional argument" in str(e) and args:
                try:
                    return fn(item)
                except Exception as e2:
                    self._failed.add(name)
                    _warn(item, f"behavior {name} 执行异常: {e2!r}")
                    return None
            self._failed.add(name)
            _warn(item, f"behavior {name} 执行异常: {e!r}")
            return None
        except Exception as e:
            self._failed.add(name)
            _warn(item, f"behavior {name} 执行异常: {e!r}")
            return None

    def call(self, item, name: str, *args):
        return self.execute(item, name, *args)


def _warn(item, msg: str):
    key = getattr(item, "key", "?")
    log = getattr(item, "log", None)
    if log is not None and hasattr(log, "warn"):
        try:
            log.warn(f"[{key}] {msg}")
        except Exception:
            pass
