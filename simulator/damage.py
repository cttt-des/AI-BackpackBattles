# -*- coding: utf-8 -*-
"""damage.py — DamageSource / DamageResult（对齐 Utility/DamageSource.gd + DamageResult.gd）"""
from __future__ import annotations

from typing import Any, List, Optional, TYPE_CHECKING

if TYPE_CHECKING:
    from .item import Item


class DS_Type:
    """DamageSource.Type"""
    MELEE = 0
    RANGED = 1
    EFFECT = 2
    SELFDAMAGE = 3
    UNHEALING = 98
    FATIGUE = 99
    SPIKES = 104
    POISON = 108
    # GDScript 大小写别名
    Melee = MELEE
    Ranged = RANGED
    Effect = EFFECT
    SelfDamage = SELFDAMAGE
    Unhealing = UNHEALING
    Fatigue = FATIGUE



class DS_Flags:
    """DamageSource.Flags（位标志）"""
    NONE = 0
    CAN_BE_BLOCKED = 1
    CAN_TRIGGER_SPIKES = 2
    CAN_TRIGGER_VAMPIRISM = 4
    CAN_TRIGGER_ITEMS = 8
    CAN_MISS = 16
    CAN_CRIT = 32
    ALL = 63


# 原版 flags 常量
MELEE_FLAGS = DS_Flags.ALL                       # 63
RANGED_FLAGS = DS_Flags.ALL                      # 63
EFFECT_FLAGS = DS_Flags.CAN_BE_BLOCKED + DS_Flags.CAN_TRIGGER_ITEMS + DS_Flags.CAN_CRIT   # 41
UNHEALING_FLAGS = DS_Flags.CAN_BE_BLOCKED + DS_Flags.CAN_TRIGGER_ITEMS                   # 9
SELFDAMAGE_FLAGS = DS_Flags.CAN_BE_BLOCKED + DS_Flags.CAN_TRIGGER_ITEMS                  # 9
CHIP_FLAGS = DS_Flags.CAN_BE_BLOCKED               # 1（spikes/poison 基础）


class DamageSource:
    """伤害源：类型 / flags / 伤害范围 / 命中 / 暴击"""

    Type = DS_Type        # GDScript DamageSource.Type.Ranged 等枚举访问
    Flags = DS_Flags      # GDScript DamageSource.Flags.CAN_MISS 等

    @classmethod
    def new(cls, *a, **k):
        return cls(*a, **k)

    def __init__(self):
        self.min_damage: int = 0
        self.max_damage: int = 0
        self.types: List[int] = []
        self.accuracy: float = 100.0
        self.crit_chance_percent: float = 0.0
        self.origin: Any = None          # Item 或 None
        self.flags: int = DS_Flags.ALL

    def from_source(self, other: 'DamageSource') -> 'DamageSource':
        self.min_damage = other.min_damage
        self.max_damage = other.max_damage
        self.types = list(other.types)
        self.accuracy = other.accuracy
        self.crit_chance_percent = other.crit_chance_percent
        self.flags = other.flags
        self.origin = other.origin
        return self

    def init(self, origin=None, dtype: int = DS_Type.EFFECT, min_damage: int = 0,
             max_damage: Optional[int] = None, accuracy: float = 100.0) -> 'DamageSource':
        self.origin = origin
        self.types = list(dtype) if isinstance(dtype, (list, tuple)) else [dtype]
        self.set_damage(min_damage, max_damage)
        self.accuracy = accuracy
        return self

    # ---------------- 修改 ----------------
    def set_damage(self, min_dmg: int, max_dmg: Optional[int] = None):
        self.min_damage = min_dmg
        self.max_damage = max_dmg if max_dmg is not None else min_dmg

    def add_damage(self, dmg: int):
        self.min_damage += dmg
        self.max_damage += dmg

    def add_crit_chance_percent(self, c: float):
        self.crit_chance_percent += c

    def set_flag(self, flag: int):
        self.flags |= flag

    def unset_flag(self, flag: int):
        self.flags = self.flags & ~flag

    def make_spectral(self):
        """makeSpectral — 不可被格挡"""
        self.unset_flag(DS_Flags.CAN_BE_BLOCKED)

    # ---------------- 查询 ----------------
    def has_type(self, t: int) -> bool:
        return t in self.types

    def can_miss(self) -> bool:
        return bool(self.flags & DS_Flags.CAN_MISS)

    def can_trigger_spikes(self) -> bool:
        return bool(self.flags & DS_Flags.CAN_TRIGGER_SPIKES)

    def can_trigger_vampirism(self) -> bool:
        return bool(self.flags & DS_Flags.CAN_TRIGGER_VAMPIRISM)

    def can_be_blocked(self) -> bool:
        return bool(self.flags & DS_Flags.CAN_BE_BLOCKED)

    def can_crit(self) -> bool:
        return bool(self.flags & DS_Flags.CAN_CRIT)

    def is_attack(self) -> bool:
        return self.has_type(DS_Type.MELEE) or self.has_type(DS_Type.RANGED)

    def is_effect_damage(self) -> bool:
        return self.has_type(DS_Type.EFFECT) or self.has_type(DS_Type.UNHEALING)

    # camelCase 别名（行为脚本以 damageRes.isEffectDamage() 访问的是 DamageResult，
    # 但 DamageSource 侧同样存在该查询，统一提供）
    def isEffectDamage(self) -> bool:
        return self.is_effect_damage()

    def canApplyLifesteal(self) -> bool:
        return self.can_apply_lifesteal()

    def makeSpectral(self):
        return self.make_spectral()

    def unsetFlag(self, flag):
        return self.unset_flag(flag)

    def setFlag(self, flag):
        return self.set_flag(flag)

    def setItem(self, item):
        return self.set_item(item)

    def can_apply_lifesteal(self) -> bool:
        return self.is_attack() or self.has_type(DS_Type.EFFECT)

    def get_crit_chance_percent(self) -> float:
        return max(0.0, min(100.0, self.crit_chance_percent))

    def rand_damage(self, rng) -> int:
        """randDamage — 物品源：刷新 min/max 后用物品 damageRangeRng；否则全局 rng

        对齐 GDScript randi_range(a, b)：参数必须是整数。伤害边界可能因加成
        变成 float（如中毒层数带小数），这里统一按 Godot 的 int() 语义取整，
        并对浮点误差（3.9999997）做就近修正，避免 randint 抛 TypeError。
        """
        if self.origin is not None and hasattr(self.origin, 'get_min_damage'):
            md = _to_godot_int(self.origin.get_min_damage(self))
            xd = _to_godot_int(self.origin.get_max_damage(self))
            self.set_damage(md, xd)
            return self.origin.damage_range_rng.randint(md, xd)
        return rng.randint(_to_godot_int(self.min_damage),
                           _to_godot_int(self.max_damage))

    def set_item(self, item: 'Item') -> 'DamageSource':
        """setItem — DamageSource.new().setItem(item)（Weapon/Stone 的 _ready）"""
        built = item._make_damage_source()
        self.__dict__.update(built.__dict__)
        self.origin = item
        return self

    def update_item(self, item: 'Item'):
        """updateItem — 攻击前从物品刷新命中率"""
        self.accuracy = item.get_accuracy()
        self.crit_chance_percent = item.get_crit_chance_percent()

    def update_effect(self, item: 'Item', damage: int):
        """updateEffect — 效果伤害：取物品修正后的效果伤害 + 暴击率"""
        self.origin = item
        self.set_damage(item.get_modified_effect_damage(damage))
        self.crit_chance_percent = item.get_crit_chance_percent()


def _to_godot_int(value) -> int:
    """按 Godot 的 int() 语义取整（向零截断），并容忍浮点误差。"""
    try:
        f = float(value)
    except (TypeError, ValueError):
        return 0
    if f != f or f in (float('inf'), float('-inf')):
        return 0
    r = round(f)
    return int(r) if abs(f - r) < 1e-6 else int(f)


class DamageResult:
    """伤害结算结果（对齐 DamageResult.gd）"""

    Type = DS_Type

    def __init__(self, damage_source: Optional[DamageSource] = None):
        self.damage_source: Optional[DamageSource] = damage_source
        self.damage: int = 0
        self.health_damage: int = 0
        self.hit: bool = False
        self.critical: bool = False
        self.damage_reduction: int = 0      # 格挡累计扣减
        self.event: Any = None

    def reset(self):
        self.hit = False
        self.damage = 0
        self.health_damage = 0
        self.critical = False
        self.event = None

    def get_damage(self) -> int:
        return self.damage

    def getAmount(self) -> int:
        return self.damage

    def hasHit(self) -> bool:
        return self.has_hit()

    def getDamage(self) -> int:
        return self.damage

    def willBeLethal(self, character) -> bool:
        return self.will_be_lethal(character)

    def isMelee(self) -> bool:
        return self.damage_source.has_type(DS_Type.MELEE) if self.damage_source else False

    @property
    def damageSource(self):
        """camelCase 别名（行为脚本以 damageSource 访问）"""
        return self.damage_source

    def has_hit(self) -> bool:
        return self.hit

    def was_critical_hit(self) -> bool:
        return self.hit and self.critical

    def make_critical(self, item: Optional['Item'] = None, base_crit_severity: float = 2.0):
        """makeCritical — 暴击伤害 = 伤害 × 暴击倍率（Item.BASE_CRIT_SEVERITY=2.0）"""
        if self.damage_source is not None and self.damage_source.origin is not None \
                and hasattr(self.damage_source.origin, 'get_crit_severity'):
            self.damage = int(round(self.damage * self.damage_source.origin.get_crit_severity()))
        else:
            self.damage = int(round(self.damage * base_crit_severity))
        self.critical = True

    def apply_damage_reduction(self, amount: int, item: Optional['Item'] = None):
        """applyDamageReduction — 格挡扣减（累加，后续在 takeDamage 里减）"""
        self.damage_reduction += amount

    # ---------------- 触发判定 ----------------
    def _can_trigger_items(self) -> bool:
        return bool(self.damage_source.flags & DS_Flags.CAN_TRIGGER_ITEMS)

    def trigger_on_hit(self) -> bool:
        return self.has_hit() and self._can_trigger_items()

    def trigger_on_damaged(self) -> bool:
        return self.damage > 0 and self._can_trigger_items()

    def trigger_on_melee_attacked(self) -> bool:
        return (self.has_hit() and self._can_trigger_items()
                and self.damage_source.has_type(DS_Type.MELEE))

    def trigger_on_attacked(self) -> bool:
        return (self.has_hit() and self._can_trigger_items()
                and self.damage_source.is_attack())

    def triggerOnAttacked(self) -> bool:
        """camelCase 别名（行为脚本以 triggerOnAttacked 访问）"""
        return self.trigger_on_attacked()

    def triggerOnHit(self) -> bool:
        """camelCase 别名"""
        return self.trigger_on_hit()

    def triggerOnDamaged(self) -> bool:
        """camelCase 别名"""
        return self.trigger_on_damaged()

    def triggerOnMeleeAttacked(self) -> bool:
        """camelCase 别名"""
        return self.trigger_on_melee_attacked()

    def can_trigger_spikes(self) -> bool:
        return (self.has_hit() and self.damage > 0
                and self.damage_source.can_trigger_spikes())

    def can_trigger_vampirism(self) -> bool:
        return (self.has_hit() and self.damage > 0
                and self.damage_source.can_trigger_vampirism())

    def will_be_lethal(self, character) -> bool:
        return self.damage >= (character.get_current_health() + character.get_block())
