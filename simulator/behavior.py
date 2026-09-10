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
        """Util.flip — 硬币判定（Girl Power/Scale 平平局时二选一）。固定种子保证可复现。"""
        return _FLIP_RNG.random() < 0.5


def _gd_dictionary(*a, **k):
    """GDScript Dictionary() 构造：无参空字典；可选 (keys, values) 对拷贝。"""
    if len(a) == 2:
        return dict(zip(a[0] or [], a[1] or []))
    return {}


def _gd_array(*a):
    """GDScript Array() 构造：无参空数组；单 PoolArray/iterable 拷贝。"""
    if len(a) == 1 and hasattr(a[0], '__iter__') and not isinstance(a[0], (str, bytes)):
        return list(a[0])
    return []



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
        # 任何未定义的 Game.<x> 调用都安全降级为无副作用（视觉/引擎内部方法）。
        # 用 _Noop 而非函数：行为里形如 Game.combatLog.snapshotItemTooltipStat(...)
        # 或 Game.combatSceneNode.advanceTime(...) 的链式调用才能成立，否则
        # 「函数对象」上取属性会抛 AttributeError。
        return _Noop()


class _Vector2(tuple):
    """GDScript Vector2 的 Python 等价：可调用构造 + 向量运算 + 方向常量。

    必须是真正的向量语义：影响格计算依赖它，例如
      Potion.getAffectedCellsAfterRotate_primary: `rotatedCells[0] + Vector2.UP`
      Inventory.getCellsInLine:                  `cell + direction * offset`
    若沿用 tuple 的 `+`（拼接）会得到 4 元组，导致偏移完全失效。
    """

    def __new__(cls, x=0.0, y=0.0):
        return tuple.__new__(cls, (float(x), float(y)))

    @staticmethod
    def _coerce(other):
        if isinstance(other, (tuple, list)) and len(other) >= 2:
            return float(other[0]), float(other[1])
        return None

    def __add__(self, other):
        c = self._coerce(other)
        return _Vector2(self[0] + c[0], self[1] + c[1]) if c else NotImplemented

    def __radd__(self, other):
        return self.__add__(other)

    def __sub__(self, other):
        c = self._coerce(other)
        return _Vector2(self[0] - c[0], self[1] - c[1]) if c else NotImplemented

    def __rsub__(self, other):
        c = self._coerce(other)
        return _Vector2(c[0] - self[0], c[1] - self[1]) if c else NotImplemented

    def __mul__(self, other):
        if isinstance(other, (int, float)) and not isinstance(other, bool):
            return _Vector2(self[0] * other, self[1] * other)
        c = self._coerce(other)
        return _Vector2(self[0] * c[0], self[1] * c[1]) if c else NotImplemented

    def __rmul__(self, other):
        return self.__mul__(other)

    def __neg__(self):
        return _Vector2(-self[0], -self[1])

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


class _ItemBook:
    """GDScript ItemBook 全局的 Python 等价（战斗内只用 getDescriptor 做种类标识）。

    DragonSet 等物品在 onready 里 `ItemBook.getDescriptor("Dragonscale Armor")`，
    随后 countAllPlacedOfType(descr) 按种类计数。这里返回带 key 的命名空间，
    由 Item.count_all_placed_of_type 按 key 匹配背包内物品。
    """
    def getDescriptor(self, name):
        from types import SimpleNamespace as _NS
        # 描述符命名空间：支持 isA/isMeleeWeapon/isRangedWeapon 等
        # 联动判定（Mercury Elemental/Villain Sword 等按类型匹配物品）
        return _NS(key=name, name=name,
                   types=None,
                   isMeleeWeapon=lambda: False,
                   isRangedWeapon=lambda: False,
                   isWeapon=lambda: False)

    def __getattr__(self, name):
        # Shop/GridStorage/ItemLibrary/isReleased/Owner 枚举等商店侧引用 → 安全兜底
        return _Noop()

    def __getattr__(self, name):
        return _Noop()


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
    "DamageResult": __import__("simulator.damage", fromlist=["DamageResult"]).DamageResult,
    "DamageSource": __import__("simulator.damage", fromlist=["DamageSource"]).DamageSource,
    "Util": _Util(),
    "ChessPiece": SimpleNamespace(PieceColor=SimpleNamespace(White=0, Black=1)),
    "Owner": SimpleNamespace(PlayerInventory=0, OpponentInventory=1, Storage=2),
    "CONNECT_ONESHOT": 0,
    "ActivationAni": SimpleNamespace(Throw=0, Melee=1, Ranged=2, Spell=3),
    "Item": SimpleNamespace(Type=SimpleNamespace(
        Bag=0, Consumable=1, Food=2, Pet=3, Weapon=4, Shield=5, Armor=6,
        Gloves=7, Shoes=8, Helmet=9, Accessory=10, Potion=11, Card=12, Gem=13,
        Scroll=14, Book=15, Skill=16, ChessPiece=17, Spell=18, Melee=19,
        Ranged=20, Effect=21, Holy=22, Magic=23, Vampiric=24, Dark=25,
        Nature=26, Fire=27, Ice=28, Musical=29, EFFECT=21, HOLY=22,
    ), Tag=SimpleNamespace(
        None_=0, Lifesteal=1, Stone=2, Scroll=8, Dragon=16, Staff=32,
        BattleRage=64, Singular=128, Transient=256, Bow=512,
    )),  # 行为脚本可能引用 Item.Type.X / Item.Tag.X
    "ObjectPool": _Noop(),
    "ItemBook": _ItemBook(),
    "Stat": SimpleNamespace(
        Damage=0, Accuracy=1, Chance=2, Chance2=3, CritChance=4, CritSeverity=5,
        BaseCooldown=6, Cooldown=7, Speed=8, StaminaCost=9, Block=10, MaxHealth=11,
        Regen=12, Lucky=13, Vampirism=14, Spikes=15, Mana=16, Empower=17, Heat=18,
        Poison=19, Blind=20, Cold=21, BattleRage=22,
    ),
    "Sound": _Noop(),
    "EventBus": _Noop(),
    "sprite": None,
    "descriptor": SimpleNamespace(params=[], chance=0.0, paramBases={}),
    "placed": False,
    "me": None,
    "_range_or_value": _range_or_value,
    "Dictionary": _gd_dictionary,
    "Array": _gd_array,
    "ceil": __import__("math").ceil,
    "floor": __import__("math").floor,
    "BuffType": __import__("simulator.buff", fromlist=["BuffType"]).BuffType,
    "Vector2": _Vector2,
    "Vector2i": _Vector2,
}


# 严格模式开关：默认 False，保持既有战斗行为（异常静默降级）不变；
# 审计/验证工具把它置 True 后，行为方法的编译与运行异常会被记录到
# executor.failures（方法名 -> 错误），从而可被统计与归因，而不是被悄悄吞掉。
STRICT = False


# ---------------------------------------------------------------------------
# 基类行为池（GDScript 继承链）
#
# 游戏源码里物品脚本通过 extends 继承基类脚本（Weapon.gd/Food.gd/Shield.gd/
# Greatsword.gd ... Item.gd），并覆写/沿用其方法（如 Shield.beforeBlock、
# Greatsword.onStateChanged）。extract_items.py 把这些基类脚本的转译方法
# 集中存入 battle_items.json 顶层 "class_methods"（每类一份，避免按物品复制），
# 并给每个物品的 behavior 写入 "extends_chain"（最近基类在前，"Item" 收尾）。
# 运行时由 BehaviorExecutor 按链解析：自身 methods -> 最近祖先 -> ... -> Item。
# ---------------------------------------------------------------------------
CLASS_METHODS: Dict[str, Dict[str, str]] = {}


def set_class_methods(class_methods: Optional[Dict[str, Dict[str, str]]]) -> None:
    """由数据加载层注入 battle_items.json 的 class_methods（键=脚本类名）。"""
    global CLASS_METHODS
    CLASS_METHODS = class_methods or {}


class BehaviorExecutor:
    """按需编译并缓存行为函数。"""

    def __init__(self, spec: Optional[Dict[str, Any]] = None, strict: bool = False):
        self.spec: Dict[str, Any] = spec or {}
        self.methods: Dict[str, str] = self.spec.get("methods", {}) or {}
        self.methods_raw: Dict[str, str] = self.spec.get("methods_raw", {}) or {}
        # 继承链（最近基类在前，"Item" 收尾；与 CLASS_METHODS 配合解析）
        self.extends_chain: list = list(self.spec.get("extends_chain", []) or [])
        self._cache: Dict[str, Any] = {}
        self._failed: set = set()
        self.strict: bool = strict
        # 严格模式下收集 {(cls, 方法名): 错误信息}（供 tools/audit_item_effects.py 等审计）
        self.failures: Dict[Any, str] = {}

    def _record_failure(self, item, name: str, exc: BaseException, phase: str, cls=None):
        self._failed.add((cls, name))
        if self.strict or STRICT:
            self.failures[(cls, name)] = f"{phase}: {type(exc).__name__}: {exc}"
        _warn(item, f"behavior {name} {phase}: {exc!r}")

    # ---- 继承链解析 ----
    def _class_src(self, cls: str, name: str) -> Optional[str]:
        cm = CLASS_METHODS.get(cls)
        if not cm:
            return None
        return cm.get("methods", {}).get(name)

    def resolve(self, name: str):
        """GDScript 方法解析：自身 -> 沿 extends_chain 逐级向上。返回 (cls, src)。

        cls 为 None 表示自身 methods 命中。找不到返回 (None, None)。
        """
        if name in self.methods:
            return None, self.methods[name]
        for cls in self.extends_chain:
            src = self._class_src(cls, name)
            if src:
                return cls, src
        return None, None

    def has(self, name: str) -> bool:
        _, src = self.resolve(name)
        return src is not None

    def has_any(self, names) -> bool:
        return any(self.has(n) for n in names)

    def _compile(self, item, name: str, cls=None):
        cache_key = (cls, name)
        if cache_key in self._cache:
            return self._cache[cache_key]
        if cls is None:
            src = self.methods.get(name)
        else:
            src = self._class_src(cls, name)
        if not src:
            return None
        try:
            ns: Dict[str, Any] = _SafeDict(BEHAVIOR_GLOBALS)
            exec(compile(src, f"<behavior:{cls or item.key}:{name}>", "exec"), ns)
            self._cache[cache_key] = ns[name]
            return ns[name]
        except Exception as e:
            self._record_failure(item, name, e, "编译失败", cls)
            return None

    def execute(self, item, name: str, *args):
        """执行行为方法（沿继承链解析）。不存在或失败时返回 None。"""
        cls, src = self.resolve(name)
        if src is None:
            return None
        if (cls, name) in self._failed:
            return None
        fn = self._cache.get((cls, name))
        if fn is None:
            fn = self._compile(item, name, cls)
            if fn is None:
                return None
        try:
            return fn(item, *args)
        except TypeError as e:
            # 参数个数不匹配（GDScript EventBus 回调会多带一个 event 参数）->
            # 逐级丢弃尾部参数重试（对齐回调按声明形参数量接收的语义）
            if "positional argument" in str(e) and args:
                for n in range(len(args) - 1, 0, -1):
                    try:
                        return fn(item, *args[:n])
                    except TypeError as e2:
                        last_err = e2
                        continue
                    except Exception as e2:
                        self._record_failure(item, name, e2, "执行异常", cls)
                        return None
                self._record_failure(item, name, last_err, "执行异常", cls)
                return None
            self._record_failure(item, name, e, "执行异常", cls)
            return None
        except Exception as e:
            self._record_failure(item, name, e, "执行异常", cls)
            return None

    def execute_class(self, item, cls: str, name: str, *args):
        """显式执行指定基类的方法（多级 _onready_init 初始化用）。"""
        src = self._class_src(cls, name)
        if not src:
            return None
        fn = self._cache.get((cls, name))
        if fn is None:
            fn = self._compile(item, name, cls)
            if fn is None:
                return None
        try:
            return fn(item, *args)
        except Exception as e:
            self._record_failure(item, name, e, "执行异常", cls)
            return None

    def super_classes(self, from_cls) -> list:
        """GDScript super 语义：from_cls 之上的链段（from_cls=None 表示自身）。"""
        chain = self.extends_chain
        if from_cls is None:
            return chain
        try:
            idx = chain.index(from_cls)
        except ValueError:
            return chain
        return chain[idx + 1:]

    def super_execute(self, item, name: str, from_cls, *args):
        """`.method()` 超类调用：在 from_cls 之上找最近实现并调用。"""
        for cls in self.super_classes(from_cls):
            src = self._class_src(cls, name)
            if src:
                return self.execute_class(item, cls, name, *args)
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
