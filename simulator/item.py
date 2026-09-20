# -*- coding: utf-8 -*-
"""item.py — 战斗物品（对齐 Items/Item.gd + Weapon.gd 核心机制）

冷却系统（preCombatStart / _physics_process / trigger）：
  preCombatStart: iterationCooldown = adjustCooldown(); triggerTime = iterationCooldown
  _physics_process: if not stunned: triggerTime -= delta * getSpeed(); if <=0: trigger()
  trigger(): iterationCooldown = adjustCooldown(); triggerTime += iterationCooldown;
             doCooldownEffect(); doubleActivationChance 时再执行一次

武器模板（Weapon.gd）：
  doCooldownEffect(): useStamina() Sufficient → attack()
  attack(): dealDamage + activate
"""
from __future__ import annotations

import math
import random
import re
from typing import Any, Dict, List, Optional, TYPE_CHECKING

from .damage import DamageSource, DamageResult, DS_Type, EFFECT_FLAGS
from .behavior import BehaviorExecutor, _Noop
from . import behavior as beh_module
from .buff import BuffType

import re as _re
_CAMEL_1 = _re.compile(r'(?<=[a-z0-9])(?=[A-Z])')
_CAMEL_2 = _re.compile(r'(?<=[A-Z])(?=[A-Z][a-z])')


class _SeededRandom(random.Random):
    """random.Random + reset()（GDScript BalancedRng.reset() 的等价桩）。"""

    def reset(self, seed=None):
        self.seed(seed)


def _camel_to_snake(name: str) -> str:
    """GDScript camelCase（含 _type 这类带下划线后缀）转 Python snake_case。

    例：getNumAffectedInside_type -> get_num_affected_inside_type
        baseCooldownOverride     -> base_cooldown_override
    """
    s = _CAMEL_2.sub('_', name)
    s = _CAMEL_1.sub('_', s)
    return s.lower()


# __setattr__ 重定向的白名单：camelCase 写入是有意保留独立属性（或引擎已按
# 该名字声明成员），不做 snake_case 改写
_ITEM_ATTR_ALIASES = frozenset({
    "affectedItems",   # Item.gd 基类数组（引擎读 get_affected_items 快照）
    "descriptor",      # descriptor property 的种类标识（str），勿与 property 冲突
})

# 引擎管理的实例属性全集（snake_case）：由探针 Item 实例的 __dict__ 生成。
# onready / instance_vars 默认值循环写入这些名字（camelCase 形式经重定向）
# 会清零引擎冷却/暴击/联动状态，必须跳过。
_ENGINE_MANAGED_ATTRS: Optional[frozenset] = None


def engine_managed_attrs() -> frozenset:
    """惰性构建引擎管理属性名集（需待 Item 类定义完成后才能探针实例化）"""
    global _ENGINE_MANAGED_ATTRS
    if _ENGINE_MANAGED_ATTRS is None:
        try:
            probe = Item("__probe__", {})
            _ENGINE_MANAGED_ATTRS = frozenset(vars(probe).keys())
        except Exception:  # noqa: BLE001
            _ENGINE_MANAGED_ATTRS = frozenset()
    return _ENGINE_MANAGED_ATTRS


class DescriptorView:
    """GDScript item.descriptor（ItemDescriptor 实例）的模拟器视图。

    行为脚本通过它做种类比较（`item.descriptor != descriptor`）与类型判定
    （isMeleeWeapon/isRangedWeapon/isNeutral...）。按 key 判等，与旧字符串
    语义兼容。
    """

    def __init__(self, item: 'Item'):
        self._item = item
        self.key = item.key
        self.name = item.key

    def __eq__(self, other):
        other_key = getattr(other, 'key', other)
        return self.key == other_key

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return hash(self.key)

    def __repr__(self):
        return f"<Descriptor {self.key!r}>"

    # ---- 类型判定（对齐 ItemDescriptor.gd）----
    def isWeapon(self) -> bool:
        return self._item.is_weapon()

    def isMeleeWeapon(self) -> bool:
        return self._item.is_melee_weapon()

    def isRangedWeapon(self) -> bool:
        return self._item.is_ranged_weapon()

    def isNeutral(self) -> bool:
        return self._item.is_neutral()

    def getName(self) -> str:
        return self.key


# 触发顺序权威值：源自 Items/*.gd 的 getTriggerPriority()（Partial/Exclusive 覆盖
# Item.gd 基类默认的 Priority.Normal=0）。数值对齐 Priority 枚举
#   Low=-1000, Normal=0, High=1000, Highest=10000
# 原 CSV 的 trigger_priority 缺省为 0（全部同序），会导致排序退化为随机；这里用
# 源码真实优先级覆盖，使 activateItems 阶段按 getTriggerPriority 降序触发。
TRIGGER_PRIORITY_OVERRIDES: Dict[str, int] = {
    "Strong Health Potion": 1001,
    "Mr Struggles": 1003,
    "Lucky Piggy": 1005,
    "Leather Boots": 1002,
    "Holy Spear": 2,
    "Heart of Darkness": 1000,
    "Health Potion": 1000,
    "Amulet of Fortune": 1005,
    "Automanaton": 1002,
    "Arcane Boots": 1002,
    "Berserker Bag": 1010,
    "Battery": 1005,
    "Wolf Badge": 1010,
    "Winged Boots": 1002,
    "Time Melting": 1100,
    "Deer Totem": 10000,
    "Stone Shoes": 1003,
    "Dark Lantern": 1000,
    "Stone Golem": 1001,
    "Stone Armor": 1003,
    "Fedora": 1005,
    "Generator": 1005,
    "Shelly": 1000,
    "Fortunas Kiss": 1005,
    "Hedgehog": 1003,
    "King Crown": 1,
    "Just Stats": -1000,
    "Puzzlebag J": 1100,
    "More Stats": -1000,
}


# Item.gd Type 枚举（行为脚本 hasType(Type.X) 传 int）
TYPE_NAMES = {
    0: 'bag', 1: 'consumable', 2: 'food', 3: 'pet', 4: 'weapon', 5: 'shield',
    6: 'armor', 7: 'gloves', 8: 'shoes', 9: 'helmet', 10: 'accessory',
    11: 'potion', 12: 'card', 13: 'gem', 14: 'scroll', 15: 'book', 16: 'skill',
    17: 'chess', 18: 'spell', 19: 'melee', 20: 'ranged', 21: 'effect',
    22: 'holy', 23: 'magic', 24: 'vampiric', 25: 'dark', 26: 'nature',
    27: 'fire', 28: 'ice', 29: 'musical',
}
# type 字符串 -> Type 枚举 int（count_types 用）
_TYPE_ENUM = {v: k for k, v in TYPE_NAMES.items()}


def _type_name_to_enum(name: str) -> int:
    return _TYPE_ENUM.get(name, -1)


# Item.gd Tag 枚举
TAG_NAMES = {
    0: 'none', 1: 'lifesteal', 2: 'stone', 8: 'scroll', 16: 'dragon',
    32: 'staff', 64: 'battlerage', 128: 'singular', 256: 'transient', 512: 'bow',
}

if TYPE_CHECKING:
    from .character import Character
    from .events import CombatLog


class Item:
    """战斗物品基类（对齐 Item.gd）"""

    BASE_CRIT_SEVERITY = 2.0        # Item.BASE_CRIT_SEVERITY

    def __init__(self, key: str, data: Dict[str, Any],
                 seed: Optional[int] = None, base_rng=None):
        self.key = key
        self.data = data
        self.character: Optional['Character'] = None
        self.log: Optional['CombatLog'] = None
        # RNG 源（onready 覆盖后用于恢复：BalancedRng 在模拟器中不可用）
        self._rng_base = base_rng
        self._rng_seed = seed
        if base_rng is not None:
            self.damage_range_rng = base_rng
            self.chance_rng = base_rng
        else:
            self.damage_range_rng = _SeededRandom(seed)
            self.chance_rng = _SeededRandom(seed)

        # ---- descriptor 数值（对齐 ItemDescriptor 字段）----
        self.min_dam = int(data.get('min_dam', 0))
        self.max_dam = int(data.get('max_dam', self.min_dam))
        self.cd = float(data.get('cd', 0.0))
        self.base_accuracy = float(data.get('accuracy', 100.0))
        self.stamina_cost = float(data.get('stamina_cost', 0.0))
        self.block = int(data.get('block', 0))
        self.crit_chance_percent = float(data.get('crit', 0.0))
        self.trigger_priority = int(data.get('trigger_priority', 0))
        # 用源码 getTriggerPriority() 的权威值覆盖（CSV 缺省为 0 -> 随机顺序）
        if key in TRIGGER_PRIORITY_OVERRIDES:
            self.trigger_priority = TRIGGER_PRIORITY_OVERRIDES[key]
        self.category = data.get('category', 'utility')
        self.damage_types = data.get('damage_type', 'effect')
        self.types = list(data.get('types', []))
        # 脚本继承链补类型（对齐引擎描述符类型）：
        # 棋子脚本（extends ChessPiece）hasType(Type.ChessPiece=17→'chess') 判定
        # 依赖此类型，数据表中棋子 types 为空（ChessPiece.gd canAffect）
        chain = ((data.get('behavior') or {}).get('extends_chain') or [])
        if 'ChessPiece' in chain:
            for t in ('chess', 'chesspiece'):
                if t not in self.types:
                    self.types.append(t)
        if 'Card' in chain and 'card' not in self.types:
            self.types.append('card')
        self.effect = data.get('effect', {})
        self.effects = list(data.get('effects', []))
        self.triggers = list(data.get('triggers', []))
        self.on_start = data.get('on_start')
        self.passive = data.get('passive')
        self.gems = list(data.get('gems', []))

        # ---- 运行期修改（对齐 Item.gd 的 bonus 字段）----
        self.bonus_min_dam: float = 0.0
        self.bonus_max_dam: float = 0.0
        self.removable_dam: float = 0.0
        self.bonus_damage_factor: float = 1.0
        self.stamina_factor: float = 1.0
        self.bonus_accuracy: float = 0.0
        self.speed_scale: float = 0.0
        self.double_activation_chance: float = 0.0
        self.double_attack_effect_chance: float = 0.0
        self.crit_tokens: int = 0
        self.num_charges: int = 0
        self.crit_severity: float = self.BASE_CRIT_SEVERITY
        self.base_cooldown_override: float = self.cd
        self.buff_powers: Dict[int, float] = {}
        self.buff_amplification_chances: Dict[int, float] = {}
        self.param_mult: Dict[str, float] = {}
        self.param_add: Dict[str, float] = {}
        # 概率加成（Item.gd 484-486）与冷却/触发限流状态
        self.bonus_chance_percent_additive1: float = 0.0
        self.bonus_chance_percent_additive2: float = 0.0
        self._cooldown_deactivated: bool = False
        self._last_trigger_check_time: float = -1.0
        self._triggers_this_frame: int = 0
        # stat_display_overrides（GDScript statDisplayOverrides，camelCase 读写经
        # __getattr__/__setattr__ 重定向）：GDScript 预填全部 Stat 键，缺省读出
        # null——模拟器用缺失返回 None 的字典等价（Greatsword.getStaminaCost 等）
        from collections import defaultdict
        self.stat_display_overrides = defaultdict(lambda: None)

        # ---- 冷却运行状态 ----
        self.iteration_cooldown: float = 0.0
        self.trigger_time: float = 0.0
        self.activations_this_frame: int = 0
        self.last_activation_time: float = 0.0
        self.consumed: bool = False
        self.is_full: bool = True          # Potion.isFull
        self.dragged: bool = False         # Item.dragged（UI 拖拽态；模拟中恒为 False）

        # ---- 行为执行器（extract_items.py 提取的 GDScript 行为） ----
        self._behavior_executor: Optional[BehaviorExecutor] = None
        self._behavior_ready: bool = False
        self._item_ready_done: bool = False
        self._signals: Dict[str, list] = {}

        # ---- 背包网格（extract_grid.py + grid.py） ----
        self.occupied_cells: list = []          # 背包中的占格（绝对格子）
        self.grid_inventory = None              # GridInventory 引用
        self.grid_row: int = 0
        self.grid_col: int = 0
        self.grid_rotation: int = 0
        self._rot_cells40: list = []     # 旋转后未归一化的 40px 占格（锚点系）
        self._affected_cache: Dict[int, list] = {}
        self.affectedItems: list = []   # 行为内缓存的邻接物品（对应 GDScript affectedItems）

        # ---- 联动关系（对齐 Item.gd currentAffectedItems）----
        #   _affected_items[color]  = 被本物品影响的物品
        #   _affecting_items[color] = 影响本物品的物品
        self._affected_items: Dict[int, list] = {}
        self._affecting_items: Dict[int, list] = {}

        # ---- 动态类型（Item.gd addDynamicType/removeDynamicType 3586）----
        #   {类型枚举: [来源物品 id]} —— 联动物品可临时给邻居加类型（如 SunArmor 给
        #   火焰物品加 Holy、CorruptedArmor 给神圣物品加 Dark）
        self.dynamic_types: Dict[int, list] = {}
        self.bonus_chance_percent_mult: float = 0.0

        # ---- 宝石 ----
        self.is_gem_item: bool = False
        self._socket_item: Optional['Item'] = None   # 宝石的宿主物品
        self._gems: List['Item'] = []                # 宿主的宝石列表
        self.gem_power: float = 1.0
        self._timers: Dict[str, Dict] = {}           # MultiTimer 仿真（name -> 状态）

        # ---- 效果钩子标志 ----
        self.has_pre_deal_damage_early_effect = False
        self.has_pre_deal_damage_late_effect = False
        self.has_dealt_damage_effect = False

        # ---- 伤害源（对齐 Weapon._ready: DamageSource.new().setItem(self)）----
        # 先置 None 占位：_make_damage_source -> get_min_damage 会读 self.damage_source
        object.__setattr__(self, 'damage_source', None)
        self.damage_source = self._make_damage_source()

        # ---- 统计 ----
        self.metrics = {"damage": 0, "heal": 0, "activations": 0,
                        "misses": 0, "out_of_stamina": 0}

    # ================ 伤害源（对齐 DamageSource.setItem） ================
    def _new_damage_source(self) -> DamageSource:
        """DamageSource.new().setItem(self) 的转译落点（_ready 行为调用）"""
        return self._make_damage_source()

    def _make_damage_source(self) -> DamageSource:
        ds = DamageSource()
        ds.origin = self
        if self.damage_types == 'melee':
            ds.types = [DS_Type.MELEE]
            from .damage import MELEE_FLAGS
            ds.flags = MELEE_FLAGS
        elif self.damage_types == 'ranged':
            ds.types = [DS_Type.RANGED]
            from .damage import RANGED_FLAGS
            ds.flags = RANGED_FLAGS
        else:
            ds.types = [DS_Type.EFFECT]
            from .damage import EFFECT_FLAGS
            ds.flags = EFFECT_FLAGS
        ds.set_damage(self.get_min_damage(), self.get_max_damage())
        ds.accuracy = self.get_accuracy()
        return ds

    # ================ 归属 ================
    def character_(self) -> Optional['Character']:
        return self.character

    def opponent(self):
        return self.character.opponent if self.character else None

    # ================ 类型 ================
    def is_melee_weapon(self) -> bool:
        """isMeleeWeapon — 近战武器（含通过物品名匹配的描述符字符串场景）"""
        return self.is_weapon() and ('melee' in str(self.damage_types).lower()
                                     or self.has_type('melee'))

    def is_ranged_weapon(self) -> bool:
        """isRangedWeapon — 远程武器"""
        return self.is_weapon() and ('ranged' in str(self.damage_types).lower()
                                     or self.has_type('ranged'))

    def is_weapon(self) -> bool:
        return 'weapon' in self.types or self.category == 'weapon'

    def is_bag(self) -> bool:
        return 'bag' in self.types or self.category == 'bag'

    def has_type(self, t) -> bool:
        """hasType — 兼容 str 与 Type 枚举 int（对齐 Item.gd Type 枚举）

        含联动物品临时赋予的动态类型（addDynamicType，见 Item.gd 3586）：
        如 SunArmor 给相邻的火焰物品加 Holy、CorruptedArmor 给神圣物品加 Dark。
        """
        if isinstance(t, int):
            if self.has_dynamic_type(t):
                return True
            t = TYPE_NAMES.get(t, '')
        else:
            for tid in self.dynamic_types:
                if TYPE_NAMES.get(tid, '') == t:
                    return True
        return t in self.types

    # ---------------- 联动判定谓词（供其他物品的 canAffect 调用） ----------------
    # 默认返回值严格取自 Items/Item.gd 的基类实现。
    # 注：can_be_empowered / can_activate / give_buff_power / gains_stack /
    #     modify_param* 在文件后部已有实现（后定义者优先），此处不重复定义，
    #    需要修正语义时改后部那一份（见文件末尾附近的同名方法）。

    def can_block(self) -> bool:
        """Item.gd 3645: getBlock() > 0"""
        return self.get_block() > 0

    def can_modify_chance(self) -> bool:
        """Item.gd 3865: getBaseChance() > 0"""
        return self.get_chance() > 0

    def get_price(self):
        """Item.gd 3937: descriptor.getPrice()"""
        return self.data.get('price', 0)

    def get_sell_price(self):
        """Item.gd 3943: descriptor.getSellPrice()"""
        return self.data.get('price', 0)

    def get_base_sell_price(self):
        return self.data.get('price', 0)

    def change_heal_amp(self, amount):
        """Item.gd 4868: modifyParam("heal") + modifyParam("lifesteal")"""
        self.modify_param("heal", amount)
        self.modify_param("lifesteal", amount)

    def add_bonus_chance(self, amount):
        """Item.gd 4013: bonusChancePercent_mult += amount"""
        self.bonus_chance_percent_mult += float(amount)

    def has_startof_battle(self) -> bool:
        """Item.gd 3373: has_method("onCombatStart")"""
        return self.has_behavior('onCombatStart') or bool(self.on_start)

    def can_heal_or_lifesteal(self) -> bool:
        """Item.gd 5362: descriptor.hasParam("heal") or hasParam("lifesteal")"""
        np = self.data.get('named_params') or {}
        return ('heal' in np) or ('lifesteal' in np)

    # Stack 位枚举（Item.gd 96-111）：Buff=2+4+8+16+32+64+128，Debuff=256+512+1024
    _STACK_BUFF_BITS = (2, 4, 8, 16, 32, 64, 128)
    _STACK_DEBUFF_BITS = (256, 512, 1024)

    def _behavior_src_all(self) -> str:
        """自身 + 继承链基类的全部转译方法源码（含未编译的 methods_raw，
        usesStack 近似判定用，带缓存）"""
        cached = getattr(self, "_src_all_cache", None)
        if cached is not None:
            return cached
        beh = self.data.get("behavior") or {}
        parts = list((beh.get("methods") or {}).values())
        parts.extend((beh.get("methods_raw") or {}).values())
        from . import behavior as _b
        for cls in beh.get("extends_chain") or []:
            cm = _b.CLASS_METHODS.get(cls) or {}
            parts.extend((cm.get("methods") or {}).values())
        cached = "\n".join(parts)
        self._src_all_cache = cached
        return cached

    def gains_stack(self, stack_enum) -> bool:
        """gainsStack — 物品是否与指定 Stack（位枚举）交互（canAffect 用）"""
        from .buff import BuffType
        mapping = {1: BuffType.BLOCK, 2: BuffType.LUCKY, 4: BuffType.REGENERATION,
                   8: BuffType.VAMPIRISM, 16: BuffType.SPIKES, 32: BuffType.MANA,
                   64: BuffType.EMPOWER, 128: BuffType.HEAT, 256: BuffType.POISON,
                   512: BuffType.BLIND, 1024: BuffType.COLD}
        bt = mapping.get(int(stack_enum))
        if bt is None:
            return False
        if self.buff_powers.get(bt, 0) > 0:
            return True
        name = BuffType.INV.get(bt, '').lower()
        return name in self.types or name in (self.data.get('named_params') or {})

    def uses_stack(self, stack_enum) -> bool:
        """usesStack — descriptor.usedStacks 位掩码数据未入库；
        按行为源码中的 use<Stack> 调用近似（useMana/useRegeneration/…，
        同时匹配编译后 snake_case 与原始 GDScript camelCase）。
        入参为 Stack 位枚举（Mana=32/Regeneration=4/Heat=128/Lucky=2/Empower=64）"""
        tokens = {32: ("use_mana(", "try_use_mana(", "useMana(", "tryUseMana("),
                  4: ("use_regeneration(", "useRegeneration("),
                  128: ("use_heat(", "useHeat("),
                  2: ("use_lucky(", "useLucky("),
                  64: ("use_empower(", "useEmpower(")}
        toks = tokens.get(stack_enum)
        if not toks:
            return False
        src = self._behavior_src_all()
        return any(t in src for t in toks)

    def gains_buffs(self) -> bool:
        """Item.gd 5375: descriptor.gainedStacks & Stack.Buff"""
        return any(self.gains_stack(b) for b in self._STACK_BUFF_BITS)

    def uses_buffs(self) -> bool:
        """Item.gd 5378: descriptor.usedStacks & Stack.Buff"""
        return any(self.uses_stack(b) for b in self._STACK_BUFF_BITS)

    def inflicts_debuffs(self) -> bool:
        """Item.gd 5381: descriptor.gainedStacks & Stack.Debuff"""
        return any(self.gains_stack(b) for b in self._STACK_DEBUFF_BITS)

    def reacts_to_charges(self) -> bool:
        """Item.gd 5148: hasOnChargeReceivedEffect or hasOnChargeLeftEffect
        （是否存在 onChargeReceived/onChargeLeft 行为方法）"""
        return (self.has_behavior("onChargeReceived")
                or self.has_behavior("onChargeLeft"))

    def is_crafted(self) -> bool:
        """Item.gd 5719: descriptor.isCraftedItem() —— 合成产物数据未入库，默认 False"""
        return False

    def is_treasure(self) -> bool:
        """Item.gd 5722: descriptor.randomUniquePool"""
        return False

    def is_base_item(self) -> bool:
        """isBaseItem — 是否为合成基础件（bondedIngredients 非空）；绑定未建模 → False"""
        return False

    def is_available_for_crafting(self) -> bool:
        """isAvailableForCrafting — 未绑定/未锁定/未融合；战斗内物品恒满足"""
        return True

    def can_start_new_recipe(self) -> bool:
        """Item.gd 5840: not isBaseItem() and isAvailableForCrafting()"""
        return (not self.is_base_item()) and self.is_available_for_crafting()

    def is_class_item(self, class_index=None) -> bool:
        """Item.gd 973 + ItemDescriptor.gd 163：
        isClassItem() = classes 非 None(0) 且非 Neutral(127)；
        isClassItem(classIndex) = 上述且 isAvailableFor(classIndex)
        = classes & (1 << classIndex)（Classes_Full 枚举序）。
        classes 位掩码由 tools/enrich_classes.py 从 ItemData_e.csv shop 列提取。"""
        classes = self.data.get('classes')
        if not classes:                              # None/0 = None 类（非商店）
            return False
        if classes == 127:                           # Neutral
            return False
        if class_index is None:
            return True
        return bool(classes & (1 << int(class_index)))

    def is_neutral(self) -> bool:
        """ItemDescriptor.gd 160: classes == StuffedClasses.Neutral(127)"""
        return self.data.get('classes') == 127

    def is_available_for(self, class_index) -> bool:
        """ItemDescriptor.gd 153: isAvailableFor(classId) = classes & (1 << classId)"""
        classes = self.data.get('classes')
        if not classes:
            return False
        return bool(classes & (1 << int(class_index)))

    def charge_left(self) -> int:
        """电荷系统未建模，恒 0"""
        return 0

    # ---------------- 视觉/引擎成员占位（避免视觉残留语句中断战斗逻辑） ----------------
    # 部分物品脚本把战斗逻辑与视觉语句写在同一个方法里（如 onDealtDamage 中先改
    # sprite 再加成），若视觉属性缺失会抛 AttributeError，导致**后续战斗逻辑不执行**。
    # 这里为常见的视觉/引擎成员提供安全占位。
    @property
    def sprite(self):
        if not hasattr(self, "_sprite_noop"):
            from .behavior import _Noop
            self._sprite_noop = _Noop()
        return self._sprite_noop

    @property
    def placed(self) -> bool:
        """Item.gd `var placed`：是否已摆放在背包网格中（否则在储物箱/商店）。"""
        return self.grid_inventory is not None and bool(self.occupied_cells)

    @property
    def owner_type(self) -> int:
        """Item.gd ownerType（Owner 枚举真实值）：1=PlayerInventory / 3=Opponent"""
        return 3 if (self.character is not None and getattr(self.character, "index", 0)) else 1

    ownerType = owner_type

    # num_charges：电荷数（工程师体系）。Item.gd 中 numCharges 是可变状态
    # （chargeReceived += 1 / chargeLeft -= 1），必须可写——曾是只读 property
    # 导致 Mana Crystal.emitCharge 一发电荷就 AttributeError。

    # ---------------- 联动派生查询 ----------------
    def get_items_in_affected_cells(self, color: int = 0):
        """getItemsInAffectedCells：影响格内的**全部**物品（未经 canAffect 过滤）。"""
        if self.grid_inventory is None:
            return []
        return self.grid_inventory.get_items_in_cells(self._affected_cells_abs(color))

    get_items_in_affected_cells_cached = get_items_in_affected_cells

    def get_affected_gold_value(self, color: int = 0):
        """getAffectedGoldValue：受影响物品的价格之和（Piggybank/Lucky Cat 等）。"""
        return sum((it.get_price() or 0) for it in self.get_affected_items(color))

    def __getattr__(self, name: str):
        """兜底：行为脚本遗留的 camelCase 方法/属性名（如 getAffectedGoldValue、
        getNumAffectedInside_type、baseCooldownOverride、addSpeed）按 snake_case 解析。

        仅对缺失属性触发；dunder 直接放行以免干扰解释器内部协议。
        """
        if name.startswith('__') and name.endswith('__'):
            raise AttributeError(name)
        snake = _camel_to_snake(name)
        if snake != name:
            try:
                return getattr(self, snake)
            except AttributeError:
                pass
        # 行为链跳板：继承链上的 GDScript 方法可像成员方法一样调用
        # （如 Gold Cube.onDamaged → advanceAffectedItem()，方法定义在 Cube 基类）
        beh = self.__dict__.get('_behavior_executor')
        if beh is not None:
            try:
                if beh.resolve(name)[1] is not None:
                    def _trampoline(*args, **kwargs):
                        return self.call_behavior(name, *args, **kwargs)
                    return _trampoline
            except Exception:  # noqa: BLE001
                pass
        raise AttributeError(name)

    def __setattr__(self, name: str, value):
        """camelCase 属性赋值重定向到 snake_case 成员。

        行为脚本会写 `_item.baseCooldownOverride = x`、`_item.curHitCount = n`
        等 camelCase 名（GDScript 成员名）。若不做重定向，赋值会创建一个同名的
        分裂实例属性（Python 对未知属性名默认直接写入 __dict__），后续读取拿到
        分裂值、而引擎读 snake_case 成员看不到——写入完全丢失。
        """
        if not name.startswith('_') and name not in _ITEM_ATTR_ALIASES \
                and not hasattr(type(self), name):
            snake = _camel_to_snake(name)
            if snake != name:
                # snake 名是引擎已声明的成员（类属性/实例 __dict__/property）才重定向
                if hasattr(type(self), snake) or snake in getattr(
                        self, '__dict__', {}):
                    name = snake
        object.__setattr__(self, name, value)

    def get_num_affected_inside_type(self, item_type, color: int = 0) -> int:
        """getNumAffectedInside_type：袋内受影响物品中指定类型的数量。"""
        try:
            inside = self.get_affected_items_inside()
        except Exception:  # noqa: BLE001
            return 0
        return sum(1 for it in inside if it.has_type(item_type))

    def get_num_affected_inside(self, color: int = 0) -> int:
        try:
            return len(self.get_affected_items_inside())
        except Exception:  # noqa: BLE001
            return 0

    def on_affected_item_inside_added(self, other, color: int = 0):
        """onAffectedItemInsideAdded：物品被放入袋中（Bag.gd 覆写）。"""
        if self.has_behavior("onAffectedItemInsideAdded"):
            try:
                self.call_behavior("onAffectedItemInsideAdded", other)
            except Exception:  # noqa: BLE001
                pass

    def on_affected_item_inside_removed(self, other, color: int = 0):
        if self.has_behavior("onAffectedItemInsideRemoved"):
            try:
                self.call_behavior("onAffectedItemInsideRemoved", other)
            except Exception:  # noqa: BLE001
                pass

    # ---------------- 战斗向 API 补齐 ----------------
    def remove_lucky(self, amount=1, trigger_event=None):
        """removeLucky：移除幸运栈（LOSE lucky）。"""
        if self.character is not None:
            return self.character.lose_stacks(BuffType.LUCKY, amount, self, trigger_event)
        return None

    def remove_most_buffs(self, amount=1, trigger_event=None):
        """removeMostBuffs：移除大部分增益（源码逐个移除 Buff 集合）。"""
        if self.character is None:
            return None
        for bt in (BuffType.BLOCK, BuffType.LUCKY, BuffType.REGENERATION,
                   BuffType.VAMPIRISM, BuffType.SPIKES, BuffType.MANA,
                   BuffType.EMPOWER, BuffType.HEAT):
            try:
                self.character.lose_stacks(bt, amount, self, trigger_event)
            except Exception:  # noqa: BLE001
                pass
        return None

    def change_amplification_chance_percent_all_debuffs(self, amount):
        """changeAmplificiationChancePercent_allDebuffs：对全部减益调整增幅几率。

        与 changeAmplificationChancePercent_allBuffs（增益）对应，减益为
        Poison / Blind / Cold 三类。
        """
        for bt in (BuffType.POISON, BuffType.BLIND, BuffType.COLD):
            self.change_amplification_chance_percent(bt, amount)

    def has_attack_effect(self) -> bool:
        return bool(self.data.get('effects')) or bool(self.effect)

    def has_inventory_duration(self) -> bool:
        """hasInventoryDuration — descriptor.hasParam("dur")：named_params 含 dur"""
        return 'dur' in (self.data.get('named_params') or {})

    def has_method(self, method_name) -> bool:
        """GDScript has_method — 行为方法池中是否存在该方法"""
        return self.has_behavior(str(method_name))

    def get_base_stamina_cost(self) -> float:
        return float(self.data.get('stamina_cost', 0.0))

    def repeat_combat_start(self):
        """repeatCombatStart：重复执行 onCombatStart（由引擎在需要时调用）。"""
        self.combat_start()

    def add_bonus_block(self, amount):
        """addBonusBlock：累加额外格挡（Garlic 等被联动物品调用）。

        GDScript 侧由物品自己的 addBonusBlock 累加实例变量 extraBlock，
        在 doCooldownEffect 中 `giveBlock(getBlock() + extraBlock)` 生效；
        这里作为兜底实现（物品自身有脚本实现时优先走脚本）。
        """
        self.extraBlock = (getattr(self, 'extraBlock', 0) or 0) + int(amount)

    def has_tag(self, tag) -> bool:
        """hasTag — 对齐 Item.gd Tag 枚举"""
        tags = self.data.get('tags') or []
        if isinstance(tag, int):
            tag = TAG_NAMES.get(tag, '')
        return tag in tags or (isinstance(tag, str) and tag in self.types)

    def has_damage_type(self, dtype: int) -> bool:
        if self.damage_types == 'melee':
            return dtype == DS_Type.MELEE
        if self.damage_types == 'ranged':
            return dtype == DS_Type.RANGED
        if self.damage_types == 'effect':
            return dtype == DS_Type.EFFECT
        return False

    def can_damage(self) -> bool:
        return self.max_dam > 0

    def can_activate(self) -> bool:
        return self.data.get('can_activate', True)

    # ================ 数值 ================
    def get_typed_damage_factor(self, dam_source) -> float:
        factor = 1.0
        if self.character is None:
            return factor
        for t in dam_source.types:
            factor += self.character.get_typed_damage_factor(t)
        return factor

    def get_min_damage(self, dam_source=None) -> int:
        v = math.ceil(self.min_dam + self.bonus_min_dam)
        src = dam_source or self.damage_source
        if self.character is not None:
            if self.is_weapon() and self.can_damage():
                v += self.character.get_buff_damage_mod()
            if src is not None:
                v *= self.get_typed_damage_factor(src)
        v = round(v * self.bonus_damage_factor)
        return max(v, 0)

    def get_max_damage(self, dam_source=None) -> int:
        v = math.ceil(self.max_dam + self.bonus_max_dam)
        src = dam_source or self.damage_source
        if self.character is not None:
            if self.is_weapon() and self.can_damage():
                v += self.character.get_buff_damage_mod()
            if src is not None:
                v *= self.get_typed_damage_factor(src)
        v = round(v * self.bonus_damage_factor)
        return max(v, 0)

    def get_accuracy(self) -> float:
        acc = self.base_accuracy + self.bonus_accuracy
        if self.character is not None:
            acc += self.character.get_buff_accuracy_mod()
        return acc

    def get_crit_chance_percent(self) -> float:
        return max(0.0, min(100.0, self.crit_chance_percent))

    def get_crit_severity(self) -> float:
        return self.crit_severity

    def get_crit_tokens(self) -> int:
        return self.crit_tokens

    def use_crit_token(self):
        self.crit_tokens -= 1

    def get_stamina_cost(self) -> float:
        return self.stamina_cost * self.stamina_factor

    def get_modified_effect_damage(self, damage: int) -> int:
        """getModifiedEffectDamage — 效果伤害修正"""
        v = damage
        if self.character is not None:
            v *= self.get_typed_damage_factor(self.damage_source)
        return round(v * self.bonus_damage_factor)

    # ================ 冷却 ================
    def has_cooldown(self) -> bool:
        # Gem.hasCooldown：镶嵌在武器/护甲上的宝石不走自身冷却
        if self.is_gem_item and self.get_gem_mode() != 'inventory':
            return False
        return self.cd != 0

    def is_cooldown_active(self) -> bool:
        return (self.has_cooldown() and self.character is not None
                and not self._cooldown_deactivated)

    def get_cooldown(self) -> float:
        return self.base_cooldown_override

    def get_speed(self) -> float:
        """getSpeed — 速度修正：(heat-cold)*0.02，clamp 0.1~10"""
        if self.character is None:
            return 1.0
        speed_ = self.speed_scale + self.character.get_stack_speed_mods()
        if speed_ >= 0:
            modified = 1.0 + speed_
        else:
            modified = 1.0 / (1.0 - speed_)
        return max(0.1, min(10.0, modified))

    def get_modified_cooldown(self) -> float:
        return self.get_cooldown() / self.get_speed()

    def adjust_cooldown(self) -> float:
        """adjustCooldown — 冷却时长固定 = cd（不随 RNG 波动）。

        原版 Item.gd 中该函数为 cd × randf_range(0.95, 1.05)（exe 字节已确认
        0.95/1.05 常量相邻），但那只是让同冷却物品在同一帧触发时按 roll 出的
        微小时差分先后，对冷却时长不产生显著影响（游戏内视觉上冷却固定）。
        因此按游戏实际行为：冷却 = get_cooldown()，同帧触发的先后由
        combat.ordered_items（shuffle + TriggerPriority 排序）决定。
        """
        return self.get_cooldown()

    def set_base_cooldown(self, new_cd: float):
        self.base_cooldown_override = new_cd

    def reset_base_cooldown(self):
        self.base_cooldown_override = self.cd

    # ---- 冷却基值 API（对齐 Item.gd 3754/3757/4429/5307）----
    def get_base_cooldown(self) -> float:
        """getBaseCooldown — baseCooldownOverride"""
        return self.base_cooldown_override

    def get_base_cooldown_index(self, index) -> float:
        """getBaseCooldownIndex — index 0 取主冷却 cd，其余取 extraCds[index-1]"""
        if int(index) == 0:
            return self.cd
        extra = self.data.get('extra_cds') or []
        i = int(index) - 1
        return float(extra[i]) if 0 <= i < len(extra) else self.cd

    def update_base_cooldown(self):
        """updateBaseCooldown — 保持冷却进度比例，按新基值重算迭代冷却"""
        if self.iteration_cooldown:
            progress = self.trigger_time / self.iteration_cooldown
        else:
            progress = 1.0
        self.iteration_cooldown = self.adjust_cooldown()
        self.trigger_time = progress * self.iteration_cooldown

    def activate_cooldown(self):
        """activateCooldown — 恢复冷却推进（deactivate 后重新激活，如 Deer Totem 战怒）"""
        self._cooldown_deactivated = False
        if self.iteration_cooldown <= 0 or self.trigger_time == float("inf"):
            self.iteration_cooldown = self.adjust_cooldown()
            self.trigger_time = self.iteration_cooldown

    def check_trigger_count(self, limit) -> bool:
        """checkTriggerCount — 同一时刻内限流（Mr Struggles 等）。

        GDScript 用 Util.time 帧时钟；模拟器用战斗日志时钟，同一时刻内
        第 limit 次之后的触发被拒绝。
        """
        now = self.log.current_time if self.log else 0.0
        if now > getattr(self, '_last_trigger_check_time', -1.0):
            self._last_trigger_check_time = now
            self._triggers_this_frame = 1
        else:
            self._triggers_this_frame = getattr(self, '_triggers_this_frame', 0) + 1
            if self._triggers_this_frame > limit:
                return False
        return True

    def steal_stack(self, buff_type, amount, trigger_event=None):
        """stealStack — 从对手夺走 buff 层并给予己方角色"""
        opp = self.opponent()
        if opp is None:
            return None
        remove_event = opp.lose_stacks(buff_type, amount, item=self,
                                       trigger_event=trigger_event)
        return self.give_stacks(self.character, buff_type, amount,
                                trigger_event=remove_event)

    def check_mana(self, amount) -> bool:
        """checkMana — 角色当前 mana 是否足够（Crown/Holy Spear/King Goobert 触发门槛）"""
        return self.character is not None and self.character.get_mana() >= amount

    def use_block(self, amount, trigger_event=None):
        """Item 级 useBlock（Item.gd 4938：转发给角色；Djinn Lamp 等行为调用）"""
        if self.character is None:
            return 0
        return self.character.use_block(amount, item=self, trigger_event=trigger_event)

    def get_base_chance(self) -> float:
        """getBaseChance — 未加成的 chance 基值"""
        return self._parse_chance(self.data.get('csv_chance', '') or '')

    def get_face_direction(self) -> int:
        return self.face_direction

    def get_param_modified(self, param_name, base_val=None) -> float:
        """getParamModified — 模拟器 paramMult/paramAdd 按参数名键控（与 get_p_m 一致）"""
        if base_val is None:
            base_val = (self.data.get('named_params', {}).get(param_name, 0.0)
                        if isinstance(param_name, str) else 0.0)
        mult = self.param_mult.get(param_name, 1.0)
        add = self.param_add.get(param_name, 0.0)
        return (base_val + add) * mult

    def reduce_crit_chance_percent(self, amount):
        """reduceCritChancePercent — Item.gd 3988"""
        self.crit_chance_percent -= amount

    def can_use_stamina(self) -> bool:
        """canUseStamina — Item.gd 5359"""
        return self.get_base_stamina_cost() > 0

    def set_bag_of_stones(self):
        """setBagOfStones — Bag of Stones 开局给 Stone 填弹（Stone.gd 覆写 9000）"""
        if self.has_behavior("setBagOfStones"):
            self.call_behavior("setBagOfStones")

    def add_bonus_chance_additive(self, amount1, amount2=None):
        """addBonusChance_additive — Item.gd 4018（Shielded 给盾加格挡触发率）"""
        self.bonus_chance_percent_additive1 += amount1
        if amount2 is None:
            self.bonus_chance_percent_additive2 += amount1
        else:
            self.bonus_chance_percent_additive2 += amount2

    def change_all_items_crit_rate(self, amount):
        """changeAllItemsCritRate — Item.gd 5672：全部可强化物品改暴击率（Black Rook）"""
        for it in self.get_items():
            if it.can_be_empowered():
                it.change_crit_chance_percent(amount)

    def count_all_placed_of_type(self, descr) -> int:
        """countAllPlacedOfType — Item.gd 5783：按种类描述符计数已摆放物品（Dragon Set）"""
        key = getattr(descr, 'key', None) or getattr(descr, 'name', None)
        if not key or not isinstance(key, str):
            return 0
        return sum(1 for it in self.get_items() if it.key == key)

    def is_neutral(self) -> bool:
        """isNeutral — ItemDescriptor.classes == StuffedClasses.Neutral(127)。

        classes 位掩码由 tools/enrich_classes.py 从 ItemData_e.csv shop 列提取
        （518/518 全覆盖）；无字段视为非 Neutral（未入库 = None 类）。"""
        return self.data.get('classes') == 127

    def is_a(self, descriptor) -> bool:
        key = getattr(descriptor, 'key', None) or getattr(descriptor, 'name', None)
        if isinstance(key, str):
            return self.key == key
        return False

    def count_all_in_inventory_of_type(self, item_type) -> int:
        if isinstance(item_type, str) and not item_type.isdigit():
            # 描述符形态（ItemBook.getDescriptor 产物）：按物品名计数
            return sum(1 for it in self.get_all_in_inventory() if it.key == item_type)
        return len(self.get_all_of_type_in_inventory(item_type))


    # ================ 战斗生命周期 ================
    def prepare(self):
        """prepare() — 对齐 Item.gd：onready/行为初始化 → cacheAffectedItems → 宝石 → onPrepare 链

        行为初始化（onready/_ready）先于缓存：canAffect 需要行为侧的描述符
        变量（如 StoneGolem.bagOfStonesDescriptor），且 GDScript 里这些变量在
        物品入背包（_ready）时就已就绪。
        """
        if self.is_gem_item:
            self._prepare_as_gem()
            return
        self.consumed = False
        self.is_full = True
        self._run_prepare_behaviors()
        self._cache_affected_items()
        for gem in self._gems:
            gem.character = self.character
            gem.log = self.log
            gem.prepare()

    def _pre_combat_start_legacy(self):
        """preCombatStart — 有冷却：iterationCooldown = adjustCooldown(); triggerTime = iterationCooldown"""
        if self.has_cooldown():
            self.iteration_cooldown = self.adjust_cooldown()
            self.trigger_time = self.iteration_cooldown

    def combat_start(self):
        """combatStart — 执行 on_start 效果（对齐 onCombatStart）；先分发宝石"""
        for gem in self._gems:
            gem._gem_combat_start()
        if self.has_behavior("onCombatStart"):
            self.call_behavior("onCombatStart")
            return
        if self.on_start:
            from .effects import EffectExecutor
            EffectExecutor(self).execute(self.on_start, None)

    def pre_combat_start(self):
        """preCombatStart — 对齐：先宝石，再有冷却则初始化迭代冷却"""
        for gem in self._gems:
            gem.pre_combat_start()
        if self.has_cooldown():
            self.iteration_cooldown = self.adjust_cooldown()
            self.trigger_time = self.iteration_cooldown
        if self.has_behavior("onPreCombatStart"):
            self.call_behavior("onPreCombatStart")

    def post_combat_start(self):
        for gem in self._gems:
            gem.post_combat_start()
        if self.has_behavior("onPostCombatStart"):
            self.call_behavior("onPostCombatStart")

    def combat_end(self):
        for gem in self._gems:
            gem._gem_combat_end()
        if self.has_behavior("onCombatEnd"):
            self.call_behavior("onCombatEnd")
        # GDScript 钩子原名（Stone.combatEnd 重置弹药等；Item.gd 基类实现被引擎托管，
        # 不入 class_methods，因此仅实际定义了 combatEnd 的物品会触发）
        if self.has_behavior("combatEnd"):
            self.call_behavior("combatEnd")
        # 引擎战斗结束 Timer 随场景失效（Game.gd disconnectAll 同层清理）
        self._timers = {}

    # ================ tick 驱动（_physics_process 还原） ================
    def physics_tick(self, delta: float, now: float):
        """每物理帧：冷却推进 + 计时器（MultiTimer）驱动"""
        self._tick_timers(delta, now)
        if not self.has_cooldown():
            return
        ch = self.character
        if ch is None or ch.is_stunned() or ch.is_dead:
            return
        self.trigger_time -= delta * self.get_speed()
        if self.trigger_time <= 0:
            self.trigger(now)

    # ---- Timer 仿真（Utility/MultiTimer.gd 语义） ----
    # 引擎里脚本级 Timer（speedTimer/buffTimer…）的 timeout 信号连接声明在
    # tscn [connection] 中，由 extract 落入 behavior.timer_connections；
    # start 在已运行时把**绝对到期时刻**（Util.time + time）排队而非覆盖
    # （MultiTimer.start 39），超时逐个回退。
    def _timer_now(self) -> float:
        return self.log.current_time if self.log else 0.0

    def start_timer(self, name: str, duration: float):
        t = self._timers.setdefault(name, {'left': None, 'queue': [], 'method': None})
        if t['method'] is None:
            conns = (self.data.get('behavior') or {}).get('timer_connections') or {}
            t['method'] = conns.get(name.lower())
        due = self._timer_now() + float(duration)
        if t['left'] is None:
            t['left'] = float(duration)
        else:
            t['queue'].append(due)
        return None

    def stop_timer(self, name: str):
        self._timers.pop(name, None)
        return None

    def change_timer(self, name: str, t: float):
        """Util.changeTimer(timer, t)（Util.gd 1591：start(t + timeLeft)）——
        在当前剩余时间上再延长 t（MultiTimer 语义下进入排队）"""
        tm = self._timers.get(name)
        extra = float(t)
        if tm is None or tm['left'] is None:
            return self.start_timer(name, extra)
        self._timers.setdefault(name, tm)['queue'].append(self._timer_now() + extra + tm['left'])
        return None

    def _tick_timers(self, delta: float, now: float):
        """MultiTimer.onTimeout 语义：到点触发回调；随后若队列非空，取队头
        到期时刻算 dif = due - now，dif>0.05 以 dif 重启，否则立即串行再触发。"""
        for name in list(self._timers.keys()):
            t = self._timers.get(name)
            if not t or t['left'] is None:
                continue
            t['left'] -= delta
            if t['left'] > 0:
                continue
            # 到点（回调内可能 start/stop 同名 timer，每轮重取状态）
            while True:
                t = self._timers.get(name)
                if not t:
                    break
                self._fire_timer(t)
                t = self._timers.get(name)
                if not t:
                    break
                if t['queue']:
                    dif = t['queue'].pop(0) - now
                    if dif > 0.05:
                        t['left'] = dif
                        break
                    continue          # 引擎：dif<=0.05 立即再触发
                self._timers.pop(name, None)
                break

    def _fire_timer(self, t: Dict):
        method = t.get('method')
        if method:
            self.call_behavior(method)

    def trigger(self, now: float):
        """trigger — 冷却归零触发（对齐 Item.gd）"""
        self.iteration_cooldown = self.adjust_cooldown()
        self.trigger_time += self.iteration_cooldown
        self.do_cooldown_effect(now)
        if self.double_activation_chance > 0 and \
                self.chance_rng.random() < self.double_activation_chance:
            self.do_cooldown_effect(now)

    def do_cooldown_effect(self, now: float = None):
        """doCooldownEffect — 效果入口（GDScript 行为优先，否则武器模板/DSL）"""
        if now is None:
            now = self.log.current_time if self.log else 0.0
        if self.has_behavior("doCooldownEffect"):
            ev = self.log.item_activate(now, self.character.name() if self.character else None,
                                        self.key) if self.log else None
            if self.log:
                self.log.begin_activation(ev.id if ev is not None else None)
            try:
                self.call_behavior("doCooldownEffect")
                self.metrics["activations"] += 1
            finally:
                if self.log:
                    self.log.end_activation()
            return
        if self.is_weapon() and self.effect.get('type') == 'attack':
            self._weapon_do_cooldown_effect(now)
            return
        from .effects import EffectExecutor
        executor = EffectExecutor(self)
        effects = self.effect.get('effects', [self.effect]) if self.effect else self.effects
        if not effects:
            effects = self.effects
        ev = self.log.item_activate(now, self.character.name() if self.character else None, self.key) \
            if self.log else None
        if self.log:
            self.log.begin_activation(ev.id if ev is not None else None)
        try:
            for eff in effects:
                if eff and eff.get('type'):
                    executor.execute(eff, now)
            # DSL 兜底路径无转译行为可调 activate()，此处补发（对齐游戏内
            # 每次物品激活必经 activate() -> EventBus "activated"）
            self.visual_activate()
            self.metrics["activations"] += 1
        finally:
            if self.log:
                self.log.end_activation()

    # ---- 武器模板（Weapon.gd）----
    def _weapon_do_cooldown_effect(self, now: float):
        ev = self.log.item_activate(now, self.character.name() if self.character else None, self.key) \
            if self.log else None
        if self.log:
            self.log.begin_activation(ev.id if ev is not None else None)
        try:
            if self.use_stamina() == 0:
                self.attack(now)
                # 对齐 Weapon.gd attack()：dealDamage 后 activate(res) 发 "activated"
                self.visual_activate()
                self.metrics["activations"] += 1
        finally:
            if self.log:
                self.log.end_activation()

    def use_stamina(self, amount=None) -> int:
        """useStamina — 返回 0=Sufficient 1=Insufficient"""
        amt = amount if amount is not None else self.get_stamina_cost()
        res = self.character.use_stamina(amt)
        if res == 1:
            self.metrics["out_of_stamina"] += 1
            if self.log:
                self.log.out_of_stamina(self.log.current_time,
                                        self.character.name() if self.character else None,
                                        self.key)
        return res

    def attack(self, now: float = None, trigger_event=None) -> DamageResult:
        """attack — Weapon.attack: dealDamage + activate（GDScript 虚派发）。

        有 attack 行为（自身或继承链，如 Weapon.gd attack / 特殊武器覆写）时
        只调行为——此前"引擎模板 + 行为"双执行曾导致武器同帧攻击两次。
        行为译码含 deal_damage 调用与 visual_activate(res)，与源码一致。
        """
        if self.has_behavior("attack"):
            return self.call_behavior("attack", trigger_event)
        res = self.deal_damage(now)
        self.visual_activate(res)
        return res

    def deal_damage(self, now: float = None, trigger_event=None) -> DamageResult:
        """dealDamage — 用自身伤害源攻击对手"""
        if now is None:
            now = self.log.current_time if self.log else 0.0
        self.damage_source.update_item(self)
        res = self.character.deal_damage(self.damage_source, origin_label=self.key)
        self.emit_signal("attacked", res)
        if self.has_behavior("onWeaponAttacked"):
            self.call_behavior("onWeaponAttacked", res)
        return res

    def deal_effect_damage(self, damage: int, now: float = None, trigger_event=None) -> DamageResult:
        """dealEffectDamage — 效果伤害（对齐 Item.gd）"""
        if now is None:
            now = self.log.current_time if self.log else 0.0
        ds = DamageSource()
        ds.update_effect(self, damage)
        if not ds.types:
            ds.types = [DS_Type.EFFECT]
        ds.flags = EFFECT_FLAGS
        res = self.opponent().take_damage(ds, origin_label=self.key)
        return res

    # ================ 条件触发器（对齐 Potion/connectForCombat） ================
    def check_triggers(self, event: str, now: float, amount=None, event_obj=None):
        """在角色事件发生时检查并执行触发器。
        event: character_damaged / character_healed / character_pre_use_stamina ...
        """
        # 有 GDScript 行为(信号连接)的物品走行为路径，不再用旧 DSL 触发器，避免双触发
        if self.data.get("behavior"):
            return False
        if self.consumed or self.character is None:
            return False
        fired = False
        for trig in self.triggers:
            if trig.get('on') != event:
                continue
            cond = trig.get('if', {})
            if not self._check_condition(cond, now, amount, event_obj):
                continue
            self._fire_trigger(trig, now, amount, event_obj)
            fired = True
        return fired

    def _check_condition(self, cond: dict, now: float, amount=None, event_obj=None) -> bool:
        if not cond:
            return True
        ch = self.character
        if ch is None:
            return False
        for key, val in cond.items():
            if key == 'relative_health_lt':
                threshold = self._resolve_value(val)
                if ch.get_relative_health() >= threshold:
                    return False
            elif key == 'stamina_lt':
                ref = self._resolve_value(val)
                amt = amount if amount is not None else ref
                if ch.get_current_stamina() >= amt:
                    return False
            elif key == 'always':
                pass
            else:
                return False
        return True

    def _resolve_value(self, v) -> float:
        """解析 'p:1' / 'p:heal' / 纯数值"""
        if isinstance(v, (int, float)):
            return float(v)
        if isinstance(v, str) and v.startswith('p:'):
            ref = v[2:]
            if '/' in ref:
                base, div = ref.split('/')
                val = self.get_p(base) if not base.isdigit() else self.get_p(int(base))
                return float(val) / float(div)
            return self.get_p(ref)
        return float(v or 0)

    def _fire_trigger(self, trig: dict, now: float, amount=None, event_obj=None):
        """执行触发器动作（consume_and_effect = 药水喝完触发效果）"""
        action = trig.get('action', {})
        if action.get('type') == 'consume_and_effect':
            self.consumed = True
            from .effects import EffectExecutor
            executor = EffectExecutor(self)
            eff = self.effect
            effects = eff.get('effects', [eff]) if eff else []
            ev = self.log.item_activate(now, self.character.name() if self.character else None,
                                       self.key) if self.log else None
            if self.log:
                self.log.begin_activation(ev.id if ev is not None else None)
            try:
                for e in effects:
                    if e and e.get('type'):
                        executor.execute(e, now)
            finally:
                if self.log:
                    self.log.end_activation()

    # ================ 效果钩子（联动） ================
    def roll_double_attack_effect(self) -> int:
        """rollDoubleAttackEffect — 双倍触发次数"""
        return 1 if (self.double_attack_effect_chance > 0
                     and self.chance_rng.random() < self.double_attack_effect_chance) else 0

    def pre_deal_damage_early(self, res: DamageResult):
        if self.has_behavior("onPreDealDamage_early"):
            self.call_behavior("onPreDealDamage_early", res)

    def pre_deal_damage_late(self, res: DamageResult):
        if self.has_behavior("onPreDealDamage_late"):
            self.call_behavior("onPreDealDamage_late", res)

    def dealt_damage(self, res: DamageResult):
        """dealtDamage — 每次带 item 的伤害结算后调用（命中计伤害，未命中计 miss）。

        注意：onDealtDamage 行为不在派发——Character.gd 643-646 在 take_damage
        中按 attackEffectCount 次数派发（此前此处多派发一次导致 Dragon Knight
        等物品命中治疗双发）。
        """
        if res.has_hit():
            self.metrics["damage"] += res.damage
        else:
            self.metrics["misses"] += 1

    def on_dealt_damage(self, res: DamageResult):
        if self.has_behavior("onDealtDamage"):
            self.call_behavior("onDealtDamage", res)

    def after_block(self, res: DamageResult):
        """afterBlock — 攻击被格挡吸收后回调（如破盾后增伤物品）"""
        if self.has_behavior("afterBlock"):
            self.call_behavior("afterBlock", res)

    def get_amplification_chance_percent(self, buff_type: int) -> float:
        """getAmplificationChancePercent — 对指定类型 buff 的抗性削减"""
        return self.buff_amplification_chances.get(buff_type, 0.0)

    # ================ 数值修改 ================
    def add_bonus_damage(self, damage, removable=True):
        self.bonus_min_dam += damage
        self.bonus_max_dam += damage

    def add_min_damage(self, damage):
        self.bonus_min_dam += damage

    def add_max_damage(self, damage):
        self.bonus_max_dam += damage

    def reduce_bonus_damage(self, damage, show_label=True, removable=True):
        self.bonus_min_dam = max(0, self.bonus_min_dam - damage)
        self.bonus_max_dam = max(0, self.bonus_max_dam - damage)
        if removable and hasattr(self, 'removable_dam'):
            self.removable_dam = max(0, self.removable_dam - damage)

    def give_double_activation_chance(self, chance):
        self.double_activation_chance += chance

    def give_double_attack_effect_chance(self, chance):
        self.double_attack_effect_chance += chance

    def change_accuracy(self, amount):
        self.bonus_accuracy += amount

    def add_speed(self, amount):
        self.speed_scale += amount

    def reduce_speed(self, amount):
        self.speed_scale -= amount

    def add_stamina_factor(self, amount):
        self.stamina_factor += amount

    def give_crit_tokens(self, amount):
        self.crit_tokens += amount

    def add_crit_severity(self, amount):
        self.crit_severity += amount

    def give_buff_power(self, buff_type: int, power: float):
        self.buff_powers[buff_type] = self.buff_powers.get(buff_type, 1.0) + power

    def change_amplification_chance_percent_all(self, amount, trigger_event=None):
        """changeAmplificiationChancePercent_allBuffs — 给自身全部增益的增幅几率"""
        if self.character:
            self.character.change_buff_nullify_chances(amount)

    def change_amplification_chance_percent(self, buff_type: int, chance: float):
        self.buff_amplification_chances[buff_type] = \
            self.buff_amplification_chances.get(buff_type, 0.0) + chance

    def change_resist_stacks(self, buff_type: int, amount: int):
        if self.character is not None:
            self.character.change_resist_stacks(buff_type, amount)

    def advance_cooldown_percent(self, amount: float):
        if not self.has_cooldown():
            return
        reduction = amount / 100.0 * self.iteration_cooldown
        self.trigger_time -= reduction

    def advance_cooldown_seconds(self, amount: float):
        if not self.has_cooldown():
            return
        self.trigger_time -= amount * self.get_speed()

    def give_stamina(self, amount=1, trigger_event=None):
        self.character.gain_stamina(amount, self, trigger_event)

    def fill_up_stamina(self):
        self.character.fill_up_stamina()

    def give_max_health(self, amount=None, trigger_event=None):
        amt = amount if amount is not None else self.get_p_m("maxhealth", 0)
        amt = self.character.apply_temporary_max_health_gain(amt)
        if amt > 0:
            self.character.change_max_health_temporary(amt, self, trigger_event)

    def heal(self, amount=None, trigger_event=None):
        amt = amount if amount is not None else self.get_p_m("heal", 0)
        self.character.heal(amt, origin=self.key, trigger_event=trigger_event)

    def stun(self, duration, trigger_event=None):
        self.opponent().stun(duration, self, trigger_event)

    def drain_stamina(self, amount, trigger_event=None):
        return self.opponent().drain_stamina(amount, self, trigger_event)

    # ================ 行为执行器（extract_items.py GDScript 行为） ================
    @property
    def behavior(self) -> BehaviorExecutor:
        if self._behavior_executor is None:
            self._behavior_executor = BehaviorExecutor(self.data.get("behavior"))
        return self._behavior_executor

    def has_behavior(self, name: str) -> bool:
        return self.behavior.has(name)

    def call_behavior(self, name: str, *args):
        return self.behavior.execute(self, name, *args)

    def _behavior_call(self, name: str, *args):
        """脚本内同级方法互调（GDScript self.method() 语义）。"""
        return self.behavior.execute(self, name, *args)

    def _behavior_super(self, name: str, from_cls, *args):
        """转译的 `.method()` 超类调用：沿 extends_chain 向上找最近实现。

        编译形态为 `_behavior_super('method', 'Cls')(args...)`——必须返回
        可调用对象（此前立即执行并返回结果值，超类收不到实参
        （item=None），且布尔结果被当函数调用抛 TypeError，
        异常又被执行器记为永久失败，联动从此静默失效）。
        """
        return lambda *a, **k: self.behavior.super_execute(self, name, from_cls, *a, **k)

    # ---- 信号注册（connectForCombat 还原） ----
    def connect_signal(self, signal: str, cb):
        self._signals.setdefault(signal, []).append(cb)

    def emit_signal(self, signal: str, *args):
        for cb in list(self._signals.get(signal, [])):
            try:
                cb(*args)
            except Exception as exc:  # noqa: BLE001
                # 回调异常不再静默吞掉（此前联动监听者失效无从排查）
                from .behavior import _warn
                _warn(self, f"signal {signal!r} callback {getattr(cb, '__name__', cb)!r} error: {exc!r}")

    def connect_for_combat(self, target, signal: str, method_name: str, binds=None):
        """connectForCombat — 在目标(角色/物品)上注册信号回调"""
        if target is None:
            return
        target.connect_signal(signal, lambda *a: self.call_behavior(method_name, *a))

    def connect_to_opponent_debuffs(self, method_name: str):
        opp = self.opponent()
        if opp is not None:
            opp.connect_signal("character_debuff_changed",
                               lambda amount, ev: self.call_behavior(method_name, amount, ev))

    def _run_item_ready(self):
        """放置期初始化（≈ GDScript add_child → _ready）：默认值 + onready + _ready。

        与战斗 prepare 分离：摆盘期的 canAffect/联动需要这些成员已就绪。
        """
        if self._item_ready_done:
            return
        self._item_ready_done = True
        if not self.data.get("behavior"):
            return
        beh = self.behavior
        for cls in [None] + beh.extends_chain:
            iv = (self.data.get("behavior", {}).get("instance_vars", [])
                  if cls is None else
                  (beh_module.CLASS_METHODS.get(cls, {}).get("instance_vars", [])))
            for v in iv:
                if _camel_to_snake(v) in engine_managed_attrs():
                    continue
                if not hasattr(self, v):
                    setattr(self, v, 0)
        for cls in reversed(beh.extends_chain):
            beh.execute_class(self, cls, "_onready_init")
        self.call_behavior("_onready_init")
        if self.grid_inventory is not None:
            self._init_grid_metadata()
            self.grid_inventory.add_item(self, self.occupied_cells,
                                         is_bag=self.is_bag())
        snap_affected = {c: list(v) for c, v in self._affected_items.items() if v}
        snap_affecting = {c: list(v) for c, v in self._affecting_items.items() if v}
        snap_dynamic = {c: list(v) for c, v in self.dynamic_types.items() if v}
        if type(self.chance_rng).__name__ not in ('Random', '_SeededRandom', 'BalancedRandom'):
            self.chance_rng = (self._rng_base if self._rng_base is not None
                               else random.Random(self._rng_seed))
        if type(self.damage_range_rng).__name__ not in ('Random', '_SeededRandom', 'BalancedRandom'):
            self.damage_range_rng = (self._rng_base if self._rng_base is not None
                                     else random.Random(self._rng_seed))
        self.damage_source = self._make_damage_source()
        # GDScript _ready：物品入背包时执行（Stone ammunition=1、Weapon damageSource 等）
        self.call_behavior("_ready")
        # 基类池跳过 ENGINE_LIFECYCLE（_ready 不入池），其初始化由引擎侧还原：
        #   ChessPiece._ready 按节点名定色（"White" in name → White=1 否则 Black=0）；
        #   Card 的 deck——战斗中卡牌在牌座内恒真值（Card.gd canAffect placed 分支依赖）
        chain = (self.data.get('behavior') or {}).get('extends_chain') or []
        if 'ChessPiece' in chain:
            self.pieceColor = 1 if 'White' in self.key else 0
        if 'Card' in chain:
            self.deck = True
        self._affected_items = snap_affected
        self._affecting_items = snap_affecting
        self.dynamic_types = snap_dynamic

    def _run_prepare_behaviors(self):
        """战斗 prepare 阶段行为：ready 初始化 → 缓存 → onPrepare → prepare 行为

        （ready 初始化在 _run_item_ready 中，放置期已执行；本函数幂等。）
        """
        self._run_item_ready()
        if self._behavior_ready:
            self._cache_affected_items()
            return
        self._behavior_ready = True
        if not self.data.get("behavior"):
            return
        self.has_pre_deal_damage_early_effect = self.has_behavior(
            "onPreDealDamage_early")
        self.has_pre_deal_damage_late_effect = self.has_behavior(
            "onPreDealDamage_late")
        self.has_dealt_damage_effect = self.has_behavior("onDealtDamage")
        # 效果字典兜底（Magic Ring 等融合构建型物品：effectDict[TriggerType.X] 访问不抛 KeyError）
        if hasattr(self, "effectDict") and isinstance(self.effectDict, dict) and not self.effectDict:
            from collections import defaultdict
            self.effectDict = defaultdict(list)
        # Bag.prepare() 语义：袋内缓存必须先于 onPrepare（袋子的 onPrepare 会遍历
        # getAffectedItemsInside()；引擎里 Bag.prepare 在 Item.prepare 开头执行）
        self._cache_inside_items()
        self.call_behavior("onPrepare")
        self.call_behavior("prepare")

    # ================ 行为脚本调用的 API（对齐 Item.gd） ================
    def visual_activate(self, *args, **kwargs):
        """activate()/miniActivate()/playActivationAnimation() — 纯视觉，无战斗逻辑。
        返回 _Noop 以承接 createAnimation() 链（ani.randomizePosition()/ani.animation.play()）。"""
        from types import SimpleNamespace
        event = SimpleNamespace(
            origin=self,
            type="Activation",
            params={},
            get_origin=lambda: self,
            getParam=lambda key, default=None: default,
        )
        self.emit_signal("activated", event)
        return _Noop()

    def is_empty(self) -> bool:
        """Potion.isEmpty — 药水已喝空"""
        return self.consumed or not self.is_full

    def consume_potion(self, trigger_event=None, *_ignored):
        self.emit_signal('potion_emptied', self, trigger_event)
        """consumePotion — 喝药并触发 onTriggerPotion"""
        if self.is_empty():
            return
        # 对齐 Item.gd consume()：activate(damageRes, playCombatAni, true) 发 "activated"
        self.visual_activate()
        self.consumed = True
        self.is_full = False
        now = getattr(trigger_event, 't', None)
        if now is None and self.log is not None:
            now = self.log.current_time
        ev = None
        if self.log is not None:
            ev = self.log.item_activate(now, self.character.name() if self.character else None,
                                        self.key)
        if self.log is not None:
            self.log.begin_activation(ev.id if ev is not None else None)
        try:
            if not self.has_behavior("onTriggerPotion"):
                # 兜底：旧 DSL effects
                from .effects import EffectExecutor
                eff = self.effect
                effects = eff.get('effects', [eff]) if eff else self.effects
                for e in effects:
                    if e and e.get('type'):
                        EffectExecutor(self).execute(e, now)
            else:
                self.call_behavior("onTriggerPotion", trigger_event)
            # Potion.gd consumePotion：触发相邻药水（affected[0].triggerPotion + miniActivate）
            affected = self.get_affected_items()
            if affected:
                affected[0].trigger_potion(trigger_event)
                affected[0].visual_activate()
            self.emit_signal("potion_triggered", [self])
        finally:
            if self.log is not None:
                self.log.end_activation()

    def trigger_potion(self, trigger_event=None):
        """triggerPotion — onTriggerPotion + 事件（相邻药水联动入口）"""
        now = getattr(trigger_event, 't', None)
        if now is None and self.log is not None:
            now = self.log.current_time
        ev = None
        if self.log is not None:
            ev = self.log.item_activate(now, self.character.name() if self.character else None,
                                        self.key)
        if self.log is not None:
            self.log.begin_activation(ev.id if ev is not None else None)
        try:
            self.call_behavior("onTriggerPotion", trigger_event)
            self.emit_signal("potion_triggered", [self])
        finally:
            if self.log is not None:
                self.log.end_activation()

    def consume(self, trigger_event=None):
        """consume — 非药水消耗（卷轴等）：标记已消耗并执行效果"""
        if self.consumed:
            return
        self.consumed = True
        self.call_behavior("onConsume", trigger_event)

    def get_chance(self) -> float:
        """getChance — (基值 + additive1) × (100 + mult)/100，clamp 0~100（对齐 Item.gd 3843）"""
        base = self._parse_chance(self.data.get('csv_chance', '') or '')
        return max(0.0, min(100.0, (base + self.bonus_chance_percent_additive1)
                            * ((100.0 + self.bonus_chance_percent_mult) / 100.0)))

    def get_chance2(self) -> float:
        base = self._parse_chance(self.data.get('csv_chance2', '') or '')
        return max(0.0, min(100.0, (base + self.bonus_chance_percent_additive2)
                            * ((100.0 + self.bonus_chance_percent_mult) / 100.0)))

    @staticmethod
    def _parse_chance(raw: str) -> float:
        if isinstance(raw, (int, float)):
            return float(raw)
        m = re.match(r'[-+]?\d*\.?\d+', str(raw).strip())
        return float(m.group(0)) if m else 0.0

    def roll_chance(self, chance=None) -> bool:
        """rollChance — 用物品 chance_rng 掷骰"""
        if chance is None:
            chance = self.get_chance()
        return self.chance_rng.random() * 100.0 < float(chance)

    def roll_chance2(self) -> bool:
        return self.roll_chance(self.get_chance2())

    def get_gem_power(self) -> float:
        return max(0.0, self.gem_power)

    # ================ 背包网格 / 邻接（对齐 Item.gd + Inventory.gd） ================
    def set_grid_position(self, row: int, col: int, rotation: int = 0,
                          inventory=None, is_bag: bool = False):
        """按 lineup (row,col,rotation) 放置。
        1 collision tile = 1 背包格（cellSize=80 即 tile 尺寸，无换算）。
        tscn 格 (x,y)：x=横向=背包 col、y=纵向=背包 row。

        放置即触发行为初始化（≈ GDScript add_child → _ready）：摆盘期的
        canAffect/联动需要 onready 变量已就绪。
        """
        self.grid_row = row
        self.grid_col = col
        self.grid_rotation = int(rotation) % 360
        self._init_grid_metadata()
        self.grid_inventory = inventory
        if inventory is not None:
            inventory.add_item(self, self.occupied_cells, is_bag=self.is_bag())
        self._run_item_ready()

    def _init_grid_metadata(self):
        """按当前 (grid_row, grid_col, grid_rotation) 从 tscn 网格数据重算占格。

        onready 重置（Item.gd occupiedCells=[]）后调用可恢复占位元数据。
        """
        from .grid import rotate_cell, cells_from_grid_data
        row, col = self.grid_row, self.grid_col
        base = cells_from_grid_data(self.data.get('grid') or {})
        if not base:
            # 无网格数据的物品（煤/宝石/符文/棋子等）在游戏中均为 1x1 占格；
            # 不兜底会导致它们不占格、邻接联动全部失效
            base = [(0, 0)]
        # 40px 精细 tile：先旋转（锚点系），再归一化
        rotated = [rotate_cell(tuple(c), self.grid_rotation) for c in base]
        minx = min((c[0] for c in rotated), default=0)
        miny = min((c[1] for c in rotated), default=0)
        self._rotated40 = rotated
        self._min40 = (minx, miny)
        shape40 = sorted((c[0] - minx, c[1] - miny) for c in rotated)
        self._shape40 = shape40
        # 1 collision tile = 1 背包格（cellSize=80 即 tile 尺寸），直接平移到 (row,col)
        cells = {}
        for c in shape40:
            cells[(c[1], c[0])] = True     # (y, x) -> (row, col) 序
        self.occupied_cells = [(r + row, c + col) for (r, c) in cells]

    def grid_shape(self) -> list:
        """归一化后的 40px 占格形状（旋转后，左上角 0,0），(x,y) 序"""
        return list(getattr(self, '_shape40', None) or [])

    @staticmethod
    def _to_abs(cell, row: int, col: int):
        """tscn 格 (x,y) -> 背包绝对格 (row,col)"""
        return (cell[1] + row, cell[0] + col)

    def _affected_cells_abs(self, color: int = 0) -> list:
        """受影响格（绝对背包格子）：tscn Affected tile + 脚本补充，1 tile = 1 格直接映射"""
        from .grid import rotate_cell
        grid = self.data.get('grid') or {}
        key = {0: 'affected_cells', 2: 'affected_secondary',
               4: 'affected_tertiary', 7: 'affected_lightning'}.get(
                   color, 'affected_cells')
        rel = grid.get(key) or []
        minx, miny = getattr(self, '_min40', (0, 0))
        cells = set()
        for c in rel:
            rc = rotate_cell(tuple(c), self.grid_rotation)   # 旋转（锚点系 40px）
            offx = rc[0] - minx
            offy = rc[1] - miny
            # 1 tile = 1 背包格，直接平移到 (row,col)
            cells.add((self.grid_row + offy, self.grid_col + offx))
        for c in self._script_affected_cells(color):
            cells.add(c)
        return sorted(cells)

    def _script_affected_cells(self, color: int = 0) -> list:
        """脚本覆写的影响格：执行转译后的 getAffectedCellsAfterRotate_*（数据驱动）。

        对齐 Item.gd getAffectedCells_noRotate：入参 rotatedCells 为**背包绝对格**
        （物品旋转后的占格），返回值同坐标系。

        此前这里按 extends 名硬编码了 Potion / BagofStones 两个分支；现改为执行
        simulator/extract_linkage.py 从源码提取（含 extends 继承）的方法。
        """
        method = {0: 'getAffectedCellsAfterRotate_primary',
                  2: 'getAffectedCellsAfterRotate_secondary'}.get(color)
        if not method or not self.has_behavior(method):
            return []
        rot40 = getattr(self, '_rotated40', None) or []
        if not rot40:
            return []
        minx, miny = getattr(self, '_min40', (0, 0))
        # 1 tile = 1 背包格：锚点系 -> 背包绝对格，元素顺序与源码 getCollisionPoints() 一致（不排序）。
        # 以 Vector2(x=col, y=row) 传入，便于 +Vector2.UP 直接上移一行。
        rotated_cells = [(self.grid_col + (c[0] - minx),
                          self.grid_row + (c[1] - miny)) for c in rot40]
        try:
            res = self.call_behavior(method, rotated_cells)
        except Exception:  # noqa: BLE001
            return []
        out = []
        for c in (res or []):
            try:
                x, y = c[0], c[1]
                out.append((int(y), int(x)))     # Vector2(col,row) -> (row,col)
            except Exception:  # noqa: BLE001
                continue
        return out

    def get_cells_in_line(self, cells, direction, distance=7):
        """Inventory.gd getCellsInLine(686)：每个 cell 沿 direction 取 1..distance 格。

        排除自身占格与重复项（Bag of Stones 用它取占格上方 1 格作为影响格）。
        """
        base = list(cells or [])
        out = []
        try:
            dx, dy = direction[0], direction[1]
        except Exception:  # noqa: BLE001
            return out
        for cell in base:
            for step in range(1, int(distance) + 1):
                nb = (cell[0] + dx * step, cell[1] + dy * step)
                if nb not in base and nb not in out:
                    out.append(nb)
        return out

    def _cache_affected_items(self):
        """cacheAffectedItemsForCombat — prepare 时缓存邻接。

        袋内缓存对齐 Bag.gd prepare()：cachedInsideItems（占格上的物品）
        + cachedAffectedInsideItems（canApplyEffect 过滤）。
        """
        self._affected_cache = {0: self._compute_affected(0),
                                2: self._compute_affected(2),
                                4: self._compute_affected(4),
                                7: self._compute_affected(7)}
        self._cache_inside_items()

    def _compute_affected(self, color: int) -> list:
        if self.grid_inventory is None:
            return []
        cells = self._affected_cells_abs(color)
        result = []
        checked = []
        for cell in cells:
            it = self.grid_inventory.get_item_in_cell(cell)
            if it is None or it is self:
                continue
            if color != 7 and it in checked:
                continue
            if color != 7 and self.is_affecting_distinct(color):
                descriptor = it.data.get("key", it.key)
                if any(descriptor == old.data.get("key", old.key)
                       for old in checked):
                    checked.append(it)
                    continue
            checked.append(it)
            if self.can_affect(it, color):
                result.append(it)
        return result

    def get_affected_items(self, color=0) -> list:
        """getAffectedItems — 相邻联动物品（prepare 后为缓存值）"""
        if color is None:
            color = 0
        if color in self._affected_cache:
            return self._affected_cache[color]
        return self._compute_affected(color)

    def get_affected_items_nocache(self, color=0) -> list:
        if color is None:
            color = 0
        return self._compute_affected(color)

    def get_num_affected_items(self, color=None) -> int:
        return len(self.get_affected_items(color or 0))

    def get_first_affected_item(self, color=None):
        aff = self.get_affected_items(color or 0)
        return aff[0] if aff else None

    def get_num_affected_type(self, item_type, color=0) -> int:
        return sum(1 for it in self.get_affected_items(color) if it.has_type(item_type))

    def can_affect(self, other, color: int = 0) -> bool:
        """canAffect/canAffect_secondary — 执行已提取的行为函数"""
        methods = {
            0: "canAffect",
            2: "canAffect_secondary",
            4: "canAffect_tertiary",
            7: "canAffect_lightning",
        }
        method = methods.get(color)
        if method and self.has_behavior(method):
            try:
                return bool(self.call_behavior(method, other))
            except Exception:
                return False
        return self._base_can_affect(other, color)

    def _base_can_affect(self, other, color: int = 0) -> bool:
        """基类 canAffect 兜底（Item.gd 3527：返回 false）。

        Food/Potion/Bow/Card 等基类实现已入 class_methods 池并沿继承链派发，
        此处仅作行为缺失（编译失败等）时的兜底。
        """
        parent = (self.data.get("behavior") or {}).get("extends", "")
        if color == 0 and parent == "Food":
            return (other.has_type("food") and
                    other.data.get("key", other.key) != self.data.get("key", self.key))
        if color == 0 and parent == "Potion":
            return other.has_type("potion")
        return False

    def _base_can_affect_secondary(self, other, color: int = 0) -> bool:
        return False    # Item.gd canAffect_secondary 基类同样返回 false

    def affects_empty(self, color: int = 0) -> bool:
        if self.has_behavior("affectsEmpty"):
            try:
                return bool(self.call_behavior("affectsEmpty", color))
            except Exception:
                return False
        return False

    def is_affecting_distinct(self, color: int = 0) -> bool:
        if self.has_behavior("isAffectingDistinct"):
            try:
                return bool(self.call_behavior("isAffectingDistinct", color))
            except Exception:
                return False
        return False

    # ================ 物品身份 / 朝向（对齐 Item.gd 成员） ================
    @property
    def descriptor(self):
        """Item.gd 的 descriptor（物品描述符）——DescriptorView 实例。

        联动判定用它做「种类」比较（Food.gd: `item.descriptor != descriptor`，
        按 key 判等）与类型判定（isMeleeWeapon/isNeutral...）。
        """
        return DescriptorView(self)

    @property
    def face_direction(self) -> int:
        """FaceDirection 枚举：UP=0 / RIGHT=1 / DOWN=2 / LEFT=3。

        原版由物品实际朝向决定；阵容只给 rotation（顺时针角度），
        按 0°->UP、90°->RIGHT、180°->DOWN、270°->LEFT 换算。
        """
        return (int(self.grid_rotation) % 360) // 90

    # GDScript 侧以 camelCase 访问成员（descriptor / faceDirection / bonusDamage …）
    faceDirection = face_direction

    # ================ 动态类型（Item.gd 3586 addDynamicType） ================
    # 联动物品可临时给邻居加类型：SunArmor 给火焰物品加 Holy、
    # CorruptedArmor/Cthulhu 给神圣/食物物品加 Dark。
    def add_dynamic_type(self, type_id, by_item=None):
        src = id(by_item) if by_item is not None else id(self)
        self.dynamic_types.setdefault(type_id, [])
        if src not in self.dynamic_types[type_id]:
            self.dynamic_types[type_id].append(src)

    def remove_dynamic_type(self, type_id, by_item=None):
        src = id(by_item) if by_item is not None else id(self)
        lst = self.dynamic_types.get(type_id)
        if not lst:
            return
        if src in lst:
            lst.remove(src)
        if not lst:
            self.dynamic_types.pop(type_id, None)

    def has_dynamic_type(self, type_id, from_item=None) -> bool:
        if type_id not in self.dynamic_types:
            return False
        if from_item is None:
            return True
        return id(from_item) in self.dynamic_types[type_id]

    # 转译后的行为代码以 GDScript 原名调用（addDynamicType / removeDynamicType …）
    addDynamicType = add_dynamic_type
    removeDynamicType = remove_dynamic_type
    hasDynamicType = has_dynamic_type

    def get_types(self) -> list:
        """getTypes — dynamicTypes.keys() + descriptor.types（Item.gd 3574）"""
        return list(self.dynamic_types.keys()) + list(self.types)

    def get_type_multiplicity(self, item_type) -> int:
        """getTypeMultiplicity — hasType?1:0（Item.gd 3583，
        getNumAffected_type/getNumAffectedInside_type 的计数单位）"""
        return 1 if self.has_type(item_type) else 0

    def get_main_type(self):
        """getMainType — descriptor.types[0]（Item.gd 3571）"""
        return self.types[0] if self.types else None

    # camelCase 别名（转译脚本以原名调用）
    getTypes = get_types
    getTypeMultiplicity = get_type_multiplicity
    getMainType = get_main_type

    # ================ 联动回调（Item.gd 1517 起） ================
    def on_affected_item_added(self, other, color: int = 0):
        """onAffectedItemAdded — 有物品进入本物品影响范围（放置/类型变化时触发）"""
        self._affected_items.setdefault(color, [])
        if other not in self._affected_items[color]:
            self._affected_items[color].append(other)
        other._affecting_items.setdefault(color, [])
        if self not in other._affecting_items[color]:
            other._affecting_items[color].append(self)
        if self.has_behavior("onAffectedItemAdded"):
            try:
                self.call_behavior("onAffectedItemAdded", other, color)
            except Exception:  # noqa: BLE001
                pass

    def on_affected_item_removed(self, other, color: int = 0):
        """onAffectedItemRemoved — 物品离开影响范围"""
        lst = self._affected_items.get(color)
        if lst and other in lst:
            lst.remove(other)
        olst = other._affecting_items.get(color)
        if olst and self in olst:
            olst.remove(self)
        if self.has_behavior("onAffectedItemRemoved"):
            try:
                self.call_behavior("onAffectedItemRemoved", other, color)
            except Exception:  # noqa: BLE001
                pass

    def set_state(self, new_state, with_next_event=False, event=None):
        """Item.gd setState — 状态切换入口（camelCase setState 调用经 __getattr__ 到达）"""
        self.state_changed(new_state)

    def state_changed(self, new_state):
        """Item.setState -> onStateChanged（44 个物品覆写）"""
        if self.has_behavior("onStateChanged"):
            try:
                self.call_behavior("onStateChanged", new_state)
            except Exception:  # noqa: BLE001
                pass

    def get_related_item_columns(self):
        """getRelatedItemColumns — 同类目按列联动（护符/Badge 系，17 个物品覆写）"""
        if self.has_behavior("getRelatedItemColumns"):
            try:
                res = self.call_behavior("getRelatedItemColumns")
                return list(res) if res else []
            except Exception:  # noqa: BLE001
                return []
        return []

    def can_apply_effect(self, other) -> bool:
        if self.has_behavior("canApplyEffect"):
            try:
                return bool(self.call_behavior("canApplyEffect", other))
            except Exception:
                return False
        return False

    def is_distinct(self, other, checked=None) -> bool:
        checked = checked or []
        descriptor = other.data.get("key", other.key)
        return not any(
            descriptor == it.data.get("key", it.key) for it in checked
        )

    def get_adjacent_items(self):
        """getAdjacentItems — 四邻格物品"""
        from .grid import GridInventory
        if self.grid_inventory is None:
            return []
        out = []
        for dr, dc in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            it = self.grid_inventory.get_item_in_cell((self.grid_row + dr, self.grid_col + dc))
            if it is not None and it not in out and it is not self:
                out.append(it)
        return out

    def send_charge(self, dur_per_tile, cells, speed_factor, event=None):
        """Item.gd sendCharge + ElectricalCharge.onNewCellEntered — 电荷沿 cells 传播。

        对齐源码（ElectricalCharge.gd 204-233）：回调 cellIndex = 1..size，
        且 inventoryCells[cellIndex] 为【直接索引】——cells[0] 是发射器锚点格，
        永不充能；cellIndex == size 时 curChargedItem = null（电荷离场）。
        每步：last=cur; cur=该格物品; 发射器 onChargeEnteredCell(charge, cellIndex)
        （电池系据此 changeChargedItemStat 增减途经物品属性）；换物时
        last.chargeLeft / cur.chargeReceived。充能加成为途经瞬态（离场回退）。
        """
        if self.grid_inventory is None:
            return
        cells = list(cells or [])
        from types import SimpleNamespace
        charge = SimpleNamespace(lastChargedItem=None, curChargedItem=None,
                                 emitter=self, cells=cells)
        for cell_index in range(1, len(cells) + 1):
            charge.lastChargedItem = charge.curChargedItem
            if cell_index >= len(cells):
                cur = None          # cellIndex == inventoryCells.size() → 电荷离场
            else:
                try:
                    dr, dc = cells[cell_index][0], cells[cell_index][1]
                    cur = self.grid_inventory.get_item_in_cell(
                        (self.grid_row + dr, self.grid_col + dc))
                except Exception:
                    cur = None
            charge.curChargedItem = cur
            if self.has_behavior("onChargeEnteredCell"):
                self.call_behavior("onChargeEnteredCell", charge, cell_index)
            if cur is not charge.lastChargedItem:
                if charge.lastChargedItem is not None:
                    charge.lastChargedItem.charge_left(charge)
                if cur is not None:
                    cur.charge_received(charge)

    def charge_received(self, charge=None):
        """Item.gd chargeReceived — 途经电荷 +1 充能并触发 onChargeReceived 效果"""
        self.num_charges = getattr(self, "num_charges", 0) + 1
        if self.has_behavior("onChargeReceived"):
            self.call_behavior("onChargeReceived", charge)

    def charge_left(self, charge=None):
        """Item.gd chargeLeft — 电荷离开 -1 充能并触发 onChargeLeft 效果"""
        self.num_charges = max(0, getattr(self, "num_charges", 0) - 1)
        if self.has_behavior("onChargeLeft"):
            self.call_behavior("onChargeLeft", charge)

    def change_charged_item_stat(self, charge, cell_index, flat_val, val_per_tile):
        """Item.gd changeChargedItemStat — 电池系按途经格位增减受充能物品的属性。

        cellIndex 语义：1=第一格（加 flat），之后每进一格追加 valPerTile，
        换物时对旧物按其已累积值回退。
        """
        previous_val = flat_val + (cell_index - 2) * val_per_tile
        new_val = previous_val + val_per_tile
        last = getattr(charge, "lastChargedItem", None)
        cur = getattr(charge, "curChargedItem", None)
        if last is not None:
            if cur is None:
                self._charged_item_stat_change(last, -previous_val)
            elif cur is last:
                self._charged_item_stat_change(cur, val_per_tile)
            else:
                self._charged_item_stat_change(last, -previous_val)
                self._charged_item_stat_change(cur, new_val)
        elif cur is not None:
            self._charged_item_stat_change(cur, new_val)

    def _charged_item_stat_change(self, target, value):
        """chargedItemStatChange — 各电池物品的覆写点（Battery→addSpeed 等）"""
        if self.has_behavior("chargedItemStatChange"):
            self.call_behavior("chargedItemStatChange", target, value)

    def get_items_inside(self, *a, **k):
        return []

    def get_num_distinct_affected_items(self, *a, **k):
        return 0

    def pre_hit(self):
        """preHit — Stone 等：攻击前移除对方格挡"""
        self.remove_block(self.get_p(0))

    def remove_block(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.opponent():
            self.opponent().lose_stacks(BuffType.BLOCK, int(round(amount)), self, trigger_event)

    def get_gems_no_null(self):
        """getGemsNoNull — 宿主物品的宝石列表"""
        return self._gems

    def change_gem_power(self, amount: float):
        self.gem_power += amount

    def change_debuff_protection_chance(self, amount):
        if self.character:
            self.character.change_buff_protect_stacks(int(round(amount)))

    def get_stun_protect_chance(self) -> float:
        """getStunProtectChance — 眩晕保护几率（Leather Helm）"""
        return self.get_p_m("stun", self.get_chance())

    def give_reflect_stacks(self, amount, trigger_event=None):
        """giveReflectStacks — 给角色减益反射层"""
        if self.character:
            self.character.change_debuff_reflect_stacks(int(round(amount)))

    def get_counter_value(self) -> int:
        """getCounterValue — Little Mimic：按金币计数的反击值"""
        gold = self.character.stats.get("gold", 0) if self.character else 0
        return max(0, int(gold)) if gold else 0

    def can_affect_global(self, other) -> bool:
        """canAffect_global — 全局影响判定（行为函数优先）"""
        if self.has_behavior("canAffect_global"):
            try:
                return bool(self.call_behavior("canAffect_global", other))
            except Exception:
                return False
        return True

    def can_be_empowered(self) -> bool:
        """canBeEmpowered — Item.gd 3639: `isWeapon() and canDamage()`。

        联动物品（如 Whetstone）用它筛选可被强化（加伤害）的目标。
        """
        return self.is_weapon() and self.can_damage()

    def count_socketed_gems(self) -> int:
        """countSocketedGems — 统计宝石数量"""
        return sum(len(it.get_gems_no_null()) for it in self.get_items())

    def on_hit(self):
        """onHit — Stone 命中回调（对齐 Stone.gd：移除对方格挡）"""
        self.remove_block(self.get_p(0))

    def get_base_chance2(self) -> float:
        return self.get_chance2()

    def give_stacks(self, target, buff_type, amount, trigger_event=None):
        return self._give_stacks(target, buff_type, amount, trigger_event)

    def drink_strong_demonic_flask(self, trigger_event=None):
        self.consume_potion(trigger_event)

    def multiply_buffs_limit(self, factor, limit=None):
        """multiplyBuffsLimit — buff 上限缩放（近似：buff_powers 乘 factor）"""
        for bt in list(self.buff_powers):
            self.buff_powers[bt] = self.buff_powers.get(bt, 1.0) * factor

    def steal_buffs_fraction(self, fraction, limit=1000):
        self.give_buffs_from_opponent(fraction, limit)

    def remove_buffs_fraction(self, fraction, limit=1000):
        self.remove_buffs_from_self(fraction, limit)

    def give_buffs_from_opponent(self, fraction, limit=1000):
        if self.opponent():
            for t in range(100, 108):
                cur = self.opponent().get_stacks(t)
                if cur > 0:
                    amt = int(round(cur * min(1.0, max(0.0, fraction))))
                    if amt > 0:
                        self.opponent().lose_stacks(t, amt, self)
                        self._give_stacks(self.character, t, amt)

    def remove_buffs_from_self(self, fraction, limit=1000):
        if self.character:
            for t in range(100, 108):
                cur = self.character.get_stacks(t)
                if cur > 0:
                    amt = int(round(cur * min(1.0, max(0.0, fraction))))
                    if amt > 0:
                        self.character.lose_stacks(t, amt, self)

    def deactivate_cooldown(self):
        """deactivateCooldown — 停止冷却推进（Dragon Set 满编时停用等）"""
        self._cooldown_deactivated = True
        self.iteration_cooldown = 0.0
        self.trigger_time = float("inf")

    def count_items_in_affected_cells_cached(self, color=0):
        """countItemsInAffectedCells_cached — GDScript 返回 {物品: 数量} 字典
        （ThunderDrake 的 lightningMultiplicity[item] 按物品取倍率），非计数。"""
        from collections import Counter
        return dict(Counter(self.get_affected_items(color)))

    def give_max_stamina_temporary(self, amount, trigger_event=None, filled=True):
        if self.character:
            self.character.gain_max_stamina_temporary(amount, filled=filled)

    def change_spikes_crit_chance_percent(self, amount):
        if self.character:
            self.character.spike_damage_source.crit_chance_percent += amount

    def check_block(self) -> bool:
        """checkBlock — Stoned 保护判定：有格挡时保护生效"""
        return bool(self.character and self.character.get_block() > 0) if self.character else False

    def inflict_fatigue_damage(self, amount=None, trigger_event=None):
        if amount is None:
            amount = 1
        """inflictFatigueDamage — 给对方疲劳伤害"""
        if self.opponent():
            self.opponent().take_fatigue_damage(int(round(amount)))

    def get_num_affected_items(self, color=None) -> int:
        return len(self.get_affected_items(color))

    def get_num_cells(self) -> int:
        return len(self.occupied_cells)

    def get_relative_health(self) -> float:
        return self.character.get_relative_health() if self.character else 0.0

    def get_items_in_cells(self, cells):
        """Inventory.getItemsInCells — filled 层查物去重"""
        inv = self.grid_inventory
        return inv.get_items_in_cells(cells) if inv is not None else []

    def is_cell_empty(self, cell) -> bool:
        """Inventory.isCellEmpty — filled 层无物品（Inventory.gd 716）"""
        inv = self.grid_inventory
        return inv is None or not inv.is_cell_occupied(cell)

    def get_empty_cells(self):
        """Bag.getEmptyCells — 自身占格中的空格"""
        return [c for c in (self.occupied_cells or []) if self.is_cell_empty(c)]

    def get_items(self):
        return self.character.get_items() if self.character else []

    # ---- 增/减益给子（giveStacks 语义：round(amount * buffPowers[type])） ----
    def _give_stacks(self, target, buff_type: int, amount, trigger_event=None, temporary=False, duration=1.0):
        if amount is None or amount <= 0:
            return None
        from .buff import BuffType
        power = self.buff_powers.get(buff_type, 1.0)
        amt = int(round(amount * power))
        if amt <= 0:
            return None
        if temporary:
            return target.gain_stacks_temporary(buff_type, amt, duration, self, trigger_event)
        return target.gain_stacks(buff_type, amt, self, trigger_event)

    def give_stacks(self, target, buff_type: int, amount, trigger_event=None):
        return self._give_stacks(target, buff_type, amount, trigger_event)

    def give_stacks_temporary(self, target, buff_type: int, amount, duration, trigger_event=None):
        return self._give_stacks(target, buff_type, amount, trigger_event,
                                 temporary=True, duration=duration)

    def gain_stacks(self, buff_type: int, amount, trigger_event=None):
        if self.character:
            return self.character.gain_stacks(buff_type, int(round(amount)), self, trigger_event)
        return None

    def gain_stacks_temporary(self, buff_type: int, amount, duration, trigger_event=None):
        if self.character:
            return self.character.gain_stacks_temporary(buff_type, int(round(amount)),
                                                        duration, self, trigger_event)
        return None

    def lose_stacks(self, buff_type: int, amount, trigger_event=None):
        if self.character:
            return self.character.lose_stacks(buff_type, int(round(amount)), self, trigger_event)
        return None

    # ---- 随机增减益（对齐 inflictRandomDebuffs/removeRandomBuffs/cleanseRandomDebuffs） ----
    def _pick_random_stacks_to_give(self, stack_types, num: int) -> dict:
        """pickRandomStacksToGive — num 次独立随机挑选，统计各类型次数"""
        picked = {}
        for _ in range(max(0, int(num or 0))):
            t = self.chance_rng.choice(list(stack_types))
            picked[t] = picked.get(t, 0) + 1
        return picked

    def _pick_random_stacks(self, stack_types, num: int, target) -> dict:
        """pickRandomStacks — 优先从 target 已有栈的类型中随机扣减"""
        avail = [t for t in stack_types if target is not None and target.get_stacks(t) > 0]
        if not avail:
            avail = list(stack_types)
        picked = {}
        for _ in range(max(0, int(num or 0))):
            t = self.chance_rng.choice(avail)
            picked[t] = picked.get(t, 0) + 1
        return picked

    def inflict_random_debuffs(self, num_debuffs, trigger_event=None):
        """inflictRandomDebuffs — 给对方随机毒/盲/冰"""
        from .buff import BuffType
        debuffs = [BuffType.POISON, BuffType.BLIND, BuffType.COLD]
        picked = self._pick_random_stacks_to_give(debuffs, num_debuffs)
        for t, n in picked.items():
            self._give_stacks(self.opponent(), t, n, trigger_event)

    def cleanse_random_debuffs(self, num_debuffs, trigger_event=None):
        """cleanseRandomDebuffs — 随机净化自己身上的减益"""
        from .buff import BuffType
        debuffs = [BuffType.POISON, BuffType.BLIND, BuffType.COLD]
        picked = self._pick_random_stacks(debuffs, num_debuffs, self.character)
        for t, n in picked.items():
            self.character.lose_stacks(t, n, self, trigger_event)

    def remove_random_buffs(self, num_buffs, trigger_event=None):
        """removeRandomBuffs — 随机移除对方身上的增益"""
        from .buff import BuffType
        buffs = [BuffType.BLOCK, BuffType.LUCKY, BuffType.REGENERATION,
                 BuffType.VAMPIRISM, BuffType.SPIKES, BuffType.MANA,
                 BuffType.EMPOWER, BuffType.HEAT]
        picked = self._pick_random_stacks(buffs, num_buffs, self.opponent())
        for t, n in picked.items():
            self.opponent().lose_stacks(t, n, self, trigger_event)

    def steal_random_buff(self, num_buffs, trigger_event=None, *a, **k):
        from .buff import BuffType
        buffs = [BuffType.BLOCK, BuffType.LUCKY, BuffType.REGENERATION,
                 BuffType.VAMPIRISM, BuffType.SPIKES, BuffType.MANA,
                 BuffType.EMPOWER, BuffType.HEAT]
        picked = self._pick_random_stacks(buffs, num_buffs, self.opponent())
        for t, n in picked.items():
            self.opponent().lose_stacks(t, n, self, trigger_event)
            self._give_stacks(self.character, t, n, trigger_event)

    def use_random_buffs(self, num_buffs, trigger_event=None):
        from .buff import BuffType
        buffs = [BuffType.BLOCK, BuffType.LUCKY, BuffType.REGENERATION,
                 BuffType.VAMPIRISM, BuffType.SPIKES, BuffType.MANA,
                 BuffType.EMPOWER, BuffType.HEAT]
        picked = self._pick_random_stacks(buffs, num_buffs, self.character)
        for t, n in picked.items():
            self.character.use_stacks(t, n, self, trigger_event)

    def get_most_stacks(self, target, available_stacks):
        """Item.gd getMostStacks — 返回 target 上栈数最多的 buff 类型列表。"""
        if target is None:
            return []
        counts = {b: target.get_stacks(b) for b in available_stacks}
        if not counts:
            return []
        mx = max(counts.values())
        return [b for b, c in counts.items() if c == mx]

    def get_least_stacks(self, num_buffs, target, available_buffs):
        """getLeastStacks — 挑选 num_buffs 个栈数最少的 buff 类型，各给 1 栈。"""
        if target is None:
            return {}
        counts = {b: target.get_stacks(b) for b in available_buffs}
        picked = {}
        for b, _ in sorted(counts.items(), key=lambda kv: kv[1])[:max(0, int(num_buffs or 0))]:
            picked[b] = 1
        return picked

    def give_least_buffs(self, num_buffs, target=None, trigger_event=None, available_buffs=None):
        from .buff import BuffType
        if target is None:
            target = self.character
        if available_buffs is None:
            available_buffs = list(BuffType.ALL)
        picked = self.get_least_stacks(num_buffs, target, available_buffs)
        for t, n in picked.items():
            self._give_stacks(target, t, n, trigger_event)
        return picked

    def give_most_buffs(self, num_buffs, trigger_event=None, available_buffs=None):
        from .buff import BuffType
        target = self.character
        if available_buffs is None:
            available_buffs = list(BuffType.ALL)
        maxb = self.get_most_stacks(target, available_buffs)
        if not maxb:
            return None
        bt = self.chance_rng.choice(maxb)
        return self._give_stacks(target, bt, num_buffs, trigger_event)

    def remove_most_buffs(self, num_buffs, trigger_event=None, use=False, available_buffs=None):
        from .buff import BuffType
        target = self.character if use else self.opponent()
        if available_buffs is None:
            available_buffs = list(BuffType.ALL)
        maxb = self.get_most_stacks(target, available_buffs)
        if not maxb:
            return None
        bt = self.chance_rng.choice(maxb)
        return target.lose_stacks(bt, num_buffs, self, trigger_event)

    def remove_mana(self, amount, trigger_event=None):
        """Item.gd removeMana — 从对手扣除 mana。"""
        opp = self.opponent()
        if opp is not None:
            return opp.lose_mana(amount, self, trigger_event)

    def inflict_poison(self, amount, trigger_event=None):
        from .buff import BuffType
        self._give_stacks(self.opponent(), BuffType.POISON, amount, trigger_event)

    def self_inflict_poison(self, amount, trigger_event=None):
        from .buff import BuffType
        self._give_stacks(self.character, BuffType.POISON, amount, trigger_event)

    def inflict_blind(self, amount, trigger_event=None):
        from .buff import BuffType
        self._give_stacks(self.opponent(), BuffType.BLIND, amount, trigger_event)

    def self_inflict_blind(self, amount, trigger_event=None):
        from .buff import BuffType
        self._give_stacks(self.character, BuffType.BLIND, amount, trigger_event)

    def inflict_debuff(self, debuff, amount, trigger_event=None):
        from .buff import BuffType
        if isinstance(debuff, str):
            t = BuffType.NAMES.get(debuff.lower())
        else:
            t = debuff
        if t is not None:
            self._give_stacks(self.opponent(), t, amount, trigger_event)

    def cleanse_poison(self, amount, trigger_event=None):
        if self.character is None:
            return 0
        cur = self.character.get_poison()
        if cur == 0:
            return 0
        amount = int(min(cur, amount))
        self.character.lose_stacks(BuffType.POISON, amount, self, trigger_event)
        return amount

    def cleanse_blind(self, amount, trigger_event=None):
        if self.character is None:
            return 0
        cur = self.character.get_blind()
        if cur == 0:
            return 0
        amount = int(min(cur, amount))
        self.character.lose_stacks(BuffType.BLIND, amount, self, trigger_event)
        return amount

    def cleanse_cold(self, amount, trigger_event=None):
        if self.character is None:
            return 0
        cur = self.character.get_cold()
        if cur == 0:
            return 0
        amount = int(min(cur, amount))
        self.character.lose_stacks(BuffType.COLD, amount, self, trigger_event)
        return amount

    def cleanse_debuff(self, debuff, amount=None, trigger_event=None):
        from .buff import BuffType
        if isinstance(debuff, str):
            t = BuffType.NAMES.get(debuff.lower())
        else:
            t = debuff
        if t is None or self.character is None:
            return 0
        cur = self.character.get_stacks(t)
        if cur == 0:
            return 0
        amt = int(min(cur, amount if amount is not None else cur))
        self.character.lose_stacks(t, amt, self, trigger_event)
        return amt

    def cleanse_all_debuffs(self, trigger_event=None):
        from .buff import BuffType
        for t in (BuffType.POISON, BuffType.BLIND, BuffType.COLD):
            self.character.lose_stacks(t, self.character.get_stacks(t), self, trigger_event)

    # ---- 增益给子（对齐 giveXxx） ----
    def give_block(self, amount=None, temporary=False, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            # GDScript giveBlock(amount = getBlock())：默认取 CSV block 列
            amount = self.block
        if temporary:
            return self._give_stacks(self.character, BuffType.BLOCK, amount,
                                     trigger_event, temporary=True)
        gained = self._give_stacks(self.character, BuffType.BLOCK, amount, trigger_event)
        # GDScript Item.gd 4920-4925: 给块成功后发 gave_block（Amulet of Steel 联动）
        if gained:
            self.emit_signal('gave_block', gained, trigger_event)
        return gained

    def give_lucky(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("lucky")
        return self._give_stacks(self.character, BuffType.LUCKY, amount, trigger_event)

    def give_spikes(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("spikes")
        return self._give_stacks(self.character, BuffType.SPIKES, amount, trigger_event)

    def give_empower(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("empower")
        return self._give_stacks(self.character, BuffType.EMPOWER, amount, trigger_event)

    def give_heat(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("heat")
        return self._give_stacks(self.character, BuffType.HEAT, amount, trigger_event)

    def give_cold(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("cold")
        return self._give_stacks(self.character, BuffType.COLD, amount, trigger_event)

    def give_mana(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("mana")
        return self._give_stacks(self.character, BuffType.MANA, amount, trigger_event)

    def give_regeneration(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("regen", self.get_p_m("regeneration", 0))
        return self._give_stacks(self.character, BuffType.REGENERATION, amount, trigger_event)

    def give_vampirism(self, amount=None, trigger_event=None):
        from .buff import BuffType
        if amount is None:
            amount = self.get_p_m("vampirism", 0)
        return self._give_stacks(self.character, BuffType.VAMPIRISM, amount, trigger_event)

    def add_vampirism(self, amount, trigger_event=None):
        return self.give_vampirism(amount, trigger_event)

    def add_spikes(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.SPIKES, amount, trigger_event)

    def add_empower(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.EMPOWER, amount, trigger_event)

    def add_mana(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.MANA, amount, trigger_event)

    def add_heat(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.HEAT, amount, trigger_event)

    def add_cold(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.COLD, amount, trigger_event)

    def add_lucky(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.LUCKY, amount, trigger_event)

    def add_lifesteal(self, amount):
        """Lifesteal 属性：提升吸血上限"""
        if self.character:
            self.character.change_melee_vampirism_limit(amount)
            self.character.change_ranged_vampirism_limit(amount)

    def add_dodge_chance(self, amount):
        if self.character:
            self.character.change_dodge_stacks(int(round(amount)))

    def add_counter_attack(self, amount):
        if self.opponent():
            self.opponent().change_debuff_reflect_stacks(int(round(amount)))

    def add_invulnerable(self, duration, trigger_event=None):
        if self.character:
            self.character.make_invulnerable(duration, self, trigger_event)

    def reflect_damage(self, chance):
        if self.character:
            self.character.change_debuff_reflect_chances(chance)

    def block_next_attack(self, amount):
        if self.character:
            self.character.gain_block(int(round(amount)), self)

    def curse(self, amount, trigger_event=None):
        """curse — 给对方不治（简化：unhealing）"""
        if self.opponent():
            self.opponent().give_unhealing(amount)

    # ---- 数值修正（对齐 addCritChancePercent 等） ----
    def add_crit_chance_percent(self, amount):
        self.crit_chance_percent += amount

    def add_accuracy(self, amount):
        self.bonus_accuracy += amount

    def add_bonus_damage_factor(self, amount):
        self.bonus_damage_factor += amount

    def reduce_bonus_damage_factor(self, amount):
        self.bonus_damage_factor = max(0.0, self.bonus_damage_factor - amount)

    def add_damage_percent(self, amount):
        self.bonus_damage_factor += amount / 100.0

    def set_damage_multiplier(self, amount):
        self.bonus_damage_factor = amount

    def add_damage_multiplier(self, amount):
        self.bonus_damage_factor *= amount

    def add_max_health(self, amount, trigger_event=None):
        if self.character:
            amt = self.character.apply_temporary_max_health_gain(amount)
            self.character.change_max_health_temporary(amt, self, trigger_event)

    def add_max_health_percent(self, amount):
        if self.character:
            amt = self.character.get_max_health() * amount / 100.0
            self.character.change_max_health_temporary(amt, self)

    def add_stamina_to_all(self, amount, trigger_event=None):
        self.give_stamina_to_all(amount, trigger_event)

    def give_stamina_to_all(self, amount=1, trigger_event=None):
        if self.character:
            self.character.gain_stamina(amount, self, trigger_event)

    def health_to_block(self, health_amount, block_amount, trigger_event=None):
        """healthToBlock — 扣血换格挡（Stoneskin Potion）"""
        if self.character is None:
            return
        self.character.cur_health = max(0, self.character.cur_health - health_amount)
        self._give_stacks(self.character, BuffType.BLOCK, block_amount, trigger_event)

    def convert_stamina_to_damage(self, amount=None):
        if self.character:
            amt = amount if amount is not None else self.character.get_current_stamina()
            self.character.cur_stamina = 0
            self.add_bonus_damage(amt)

    def duplicate_item(self, *a, **k):
        return None

    def fuse(self, *a, **k):
        return None

    # ================ 桩 API（行为脚本可能调用；缺等效实现时安全兜底） ================
    def get_socket(self):
        """socket — 宝石的宿主物品"""
        return getattr(self, '_socket_item', None)

    def is_gem(self) -> bool:
        return self.is_gem_item

    def get_gem_mode(self) -> str:
        """getGemMode — 宿主是武器->weapon，否则 armor；无宿主->inventory"""
        if self._socket_item is not None:
            return 'weapon' if self._socket_item.is_weapon() else 'armor'
        return 'inventory'

    def get_item(self):
        """getItem — 宝石返回宿主物品，普通物品返回自身"""
        return self._socket_item if self._socket_item is not None else self

    def _prepare_as_gem(self):
        """宝石 prepare：onready 变量 -> prepare -> 按 mode 分发 prepareWeapon/Armor/Inventory"""
        if self._behavior_ready:
            return
        self._behavior_ready = True
        if not self.data.get("behavior"):
            return
        for v in self.data.get("behavior", {}).get("instance_vars", []):
            if not hasattr(self, v):
                setattr(self, v, 0)
        self.call_behavior("_onready_init")
        self.call_behavior("prepare")
        mode = self.get_gem_mode()
        if mode == 'weapon':
            self.call_behavior("prepareWeapon")
        elif mode == 'armor':
            self.call_behavior("prepareArmor")
        else:
            self.call_behavior("prepareInventory")

    def _gem_combat_start(self):
        """宝石 combatStart 分发"""
        mode = self.get_gem_mode()
        if mode == 'weapon':
            self.call_behavior("combatStartWeapon")
        elif mode == 'armor':
            self.call_behavior("combatStartArmor")
        else:
            self.call_behavior("combatStartInventory")

    def _gem_combat_end(self):
        mode = self.get_gem_mode()
        if mode == 'weapon':
            self.call_behavior("combatEndWeapon")
        elif mode == 'armor':
            self.call_behavior("combatEndArmor")
        else:
            self.call_behavior("combatEndInventory")

    def mount_gems(self, gem_entries: list, item_db=None):
        """把 lineup 的 gems 条目构造为宝石 Item 并挂到宿主"""
        from .item import Item as _ItemCls
        for ge in gem_entries or []:
            gkey = ge.get('id') if isinstance(ge, dict) else ge
            gdata = None
            if item_db is not None:
                gdata = item_db.get(gkey)
            if gdata is None:
                continue
            gd = dict(gdata)
            gd['gems'] = []
            gem = _ItemCls(gkey, gd, base_rng=self.chance_rng)
            gem.is_gem_item = True
            gem._socket_item = self
            gem.character = self.character
            gem.log = self.log
            self._gems.append(gem)

    def connect_to_character_buffs(self, method_name):
        """connectToCharacterBuffs — 连接自身角色所有 buff 变化信号"""
        if self.character:
            for name in ("character_block_changed", "character_lucky_changed",
                         "character_regen_changed", "character_vampirism_changed",
                         "character_spikes_changed", "character_mana_changed",
                         "character_empower_changed", "character_heat_changed",
                         "character_poison_changed", "character_blind_changed",
                         "character_cold_changed"):
                self.character.connect_signal(
                    name, lambda amount, ev, _m=method_name: self.call_behavior(_m, amount, ev))

    def get_shop_chance(self):
        return self._parse_chance(self.data.get('csv_chance', ''))

    def give_most_buffs(self, num=1, trigger_event=None):
        """giveMostBuffs — 给自己最多的 buff 类型加（近似随机）"""
        from .buff import BuffType
        buffs = [BuffType.BLOCK, BuffType.LUCKY, BuffType.REGENERATION,
                 BuffType.VAMPIRISM, BuffType.SPIKES, BuffType.MANA,
                 BuffType.EMPOWER, BuffType.HEAT]
        picked = self._pick_random_stacks_to_give(buffs, num)
        for t, n in picked.items():
            self._give_stacks(self.character, t, n, trigger_event)

    def get_affected_items_inside(self, *a):
        """getAffectedItemsInside — 袋内联动物品（对齐 Bag.gd 176：非空缓存优先，
        否则实时按 canApplyEffect 过滤；未摆盘时 []）"""
        cached = getattr(self, "_cache_affected_inside_items", None)
        if cached:
            return list(cached)
        out = []
        for it in self.get_items_inside_real():
            if self.can_apply_effect(it):
                out.append(it)
        return out

    def get_items_inside(self):
        """getItemsInside — 袋自身占格上的物品（Inventory.getItemsInCells，
        查 filled 层；prepare 后为缓存，之前实时计算）。"""
        cached = getattr(self, "_cache_inside_items_raw", None)
        if cached is not None:
            return list(cached)
        return self.get_items_inside_real()

    def get_items_inside_real(self):
        """getItemsInside 的实时版：袋占格 → filled 层查物"""
        inv = self.grid_inventory
        if inv is None or not self.occupied_cells:
            return []
        return inv.get_items_in_cells(self.occupied_cells)

    def get_num_affected_inside(self, *a) -> int:
        """getNumAffectedInside — 袋内联动数（Bag.gd 281）"""
        return len(self.get_affected_items_inside())

    def get_num_affected_inside_type(self, item_type, *a) -> int:
        """getNumAffectedInside_type — 按 getTypeMultiplicity 计数（Bag.gd 288）"""
        return sum(1 for it in self.get_affected_items_inside()
                   if it.has_type(item_type))

    def get_bag_multiplicity(self, for_item=None, *a) -> int:
        """getBagMultiplicity — Bag.gd 294 基类恒 1"""
        return 1

    def _cache_inside_items(self):
        """Bag.prepare() 前半：缓存袋内物品与 canApplyEffect 过滤结果。

        先置空再实时取（get_items_inside 命中缓存时返回旧值），
        canApplyEffect 走行为方法（如 BagofGiving 检查物品类型）。
        """
        self._cache_inside_items_raw = None
        self._cache_affected_inside_items = None
        inside = self.get_items_inside_real()
        self._cache_inside_items_raw = inside
        affected = []
        if getattr(self, "placed", True):
            for it in inside:
                if self.can_apply_effect(it):
                    affected.append(it)
        self._cache_affected_inside_items = affected

    def can_apply_effect(self, other) -> bool:
        """Bag.canApplyEffect — 基类 false（Bag.gd 35），由各袋子脚本覆写"""
        if self.has_behavior("canApplyEffect"):
            try:
                return bool(self.call_behavior("canApplyEffect", other))
            except Exception:  # noqa: BLE001
                return False
        return False

    def get_all_in_inventory(self, *a, **k):
        return self.get_items()

    def get_all_of_type_in_inventory(self, item_type, *a, **k):
        return [it for it in self.get_items() if it.has_type(item_type)]

    def get_items_in_sockets(self, *a, **k):
        return []

    def use_mana(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            return self.character.use_stacks(BuffType.MANA, int(round(amount)), self, trigger_event)
        return 0

    def use_regeneration(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            return self.character.use_stacks(BuffType.REGENERATION, int(round(amount)), self, trigger_event)
        return 0

    def use_heat(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            return self.character.use_stacks(BuffType.HEAT, int(round(amount)), self, trigger_event)
        return 0

    def use_lucky(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            return self.character.use_stacks(BuffType.LUCKY, int(round(amount)), self, trigger_event)
        return 0

    def inflict_cold(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.opponent(), BuffType.COLD, amount, trigger_event)

    def self_inflict_cold(self, amount, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.COLD, amount, trigger_event)

    def pick_random_stacks(self, stack_types, num_stacks, target=None, priority_stack=None):
        return self._pick_random_stacks(stack_types, num_stacks, target)

    def get_debuff_stacks(self, debuff_type=None) -> int:
        """getDebuffStacks — 对手身上的减益总层数（可指定类型）"""
        if self.opponent() is None:
            return 0
        from .buff import BuffType
        if debuff_type is not None:
            return self.opponent().get_stacks(debuff_type)
        return sum(self.opponent().get_stacks(t)
                   for t in (BuffType.POISON, BuffType.BLIND, BuffType.COLD))

    def connect_to_character_debuffs(self, method_name):
        if self.character:
            for name in ("character_debuff_changed", "character_poison_changed",
                         "character_blind_changed", "character_cold_changed"):
                self.character.connect_signal(
                    name, lambda amount, ev, _m=method_name: self.call_behavior(_m, amount, ev))

    def count_all_in_inventory_of_type(self, item_type) -> int:
        return len(self.get_all_of_type_in_inventory(item_type))

    def add_battle_rage_duration(self, amount, trigger_event=None):
        if self.character:
            self.character.add_battle_rage_duration(amount, trigger_event)

    def give_random_buff(self, num=1, trigger_event=None):
        self.give_random_buffs(num, trigger_event)

    _RARITY_INT = {'Common': 0, 'Rare': 1, 'Epic': 2,
                   'Legendary': 3, 'Godly': 4, 'Unique': 5}

    def get_rarity(self):
        """getRarity — Item.gd Rarity 枚举 int（Common=0…Unique=5）。
        行为脚本以 `get_rarity() == Rarity.Common` 比较，须返回枚举值。"""
        r = self.data.get('rarity', '')
        if isinstance(r, str):
            return self._RARITY_INT.get(r, -1)
        return r

    def get_block(self) -> int:
        """Item.gd getBlock() = 描述符 block 参数：先取 CSV block 列，
        缺省时读 named_params['block']（Shield of Valor 等护盾的格挡值所在）。
        The character's current block is exposed by Character.get_block()."""
        if self.block:
            return int(self.block)
        return int((self.data.get('named_params') or {}).get('block', 0) or 0)

    def has_script(self, script_name) -> bool:
        """GDScript `item is <Script>` 的运行时等价：物品脚本/继承链匹配"""
        beh = self.data.get('behavior') or {}
        stem = beh.get('script_file', '') or ''
        if stem.endswith('.gd'):
            stem = stem[:-3]
        if stem == script_name or script_name in (beh.get('extends_chain') or []):
            return True
        return False

    def start_battle_rage(self, duration=0.0, trigger_event=None, apply_bonus=True, *a, **k):
        """Item 级 startBattleRage（Berserker Bag/Toolbox/Wolf Badge 等行为调用：
        character().startBattleRage(self, dur, event[, false])，self 参数在转译后略去）"""
        if self.character:
            self.character.start_battle_rage(self, duration, trigger_event, apply_bonus)

    def get_num_empty_affected_cells(self, *a, **k):
        color = a[0] if a else k.get("color", 0)
        if self.grid_inventory is None:
            return 0
        cells = self._affected_cells_abs(color or 0)
        return sum(
            1 for cell in cells
            if cell in self.grid_inventory.bags
            and cell not in self.grid_inventory.filled
        )

    def try_use_lucky(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character and self.character.get_lucky() >= amount:
            self.character.use_stacks(BuffType.LUCKY, int(round(amount)), self, trigger_event)
            return True
        return False

    def is_type_in_inventory(self, item_type) -> bool:
        return any(it.has_type(item_type) for it in self.get_items())

    def lose_spikes(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            self.character.lose_stacks(BuffType.SPIKES, int(round(amount)), self, trigger_event)

    def use_spikes(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            return self.character.use_stacks(BuffType.SPIKES, int(round(amount)), self, trigger_event)
        return 0

    def add_temp_stamina(self, amount):
        if self.character:
            self.character.gain_max_stamina_temporary(amount)

    def give_cooldown_percent_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.change_cooldown_percent(amount)

    def get_total_damage(self) -> int:
        return self.metrics.get("damage", 0)

    def get_total_heal(self) -> int:
        return self.metrics.get("heal", 0)

    def change_armor_damage_reduction(self, amount):
        if self.character:
            self.character.change_damage_reduction(amount)

    def give_double_activation_chance_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.give_double_activation_chance(amount)

    def give_crit_tokens_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.give_crit_tokens(amount)

    def give_stamina_regeneration(self, amount):
        if self.character:
            self.character.stamina_regen += amount

    def change_stamina_regeneration(self, amount):
        self.give_stamina_regeneration(amount)

    def change_stamina_factor(self, amount):
        self.add_stamina_factor(amount)

    def change_debuff_protection_chance(self, amount):
        if self.character:
            self.character.change_buff_protect_stacks(int(round(amount)))

    def connect_to_opponent_buffs(self, method_name):
        """connectToOpponentBuffs — 连接对手所有 buff 变化信号"""
        opp = self.opponent()
        if opp:
            for name in ("character_block_changed", "character_lucky_changed",
                         "character_regen_changed", "character_vampirism_changed",
                         "character_spikes_changed", "character_mana_changed",
                         "character_empower_changed", "character_heat_changed"):
                opp.connect_signal(
                    name, lambda amount, ev, _m=method_name: self.call_behavior(_m, amount, ev))

    def is_battle_raging(self) -> bool:
        return bool(getattr(self.character, 'battle_rage_active', False)) if self.character else False

    def change_block_power(self, amount):
        self.give_buff_power(100, amount)

    def change_lucky_power(self, amount):
        self.give_buff_power(101, amount)

    def change_regen_power(self, amount):
        self.give_buff_power(102, amount)

    def change_vampirism_power(self, amount):
        self.give_buff_power(103, amount)

    def change_spikes_power(self, amount):
        self.give_buff_power(104, amount)

    def change_mana_power(self, amount):
        self.give_buff_power(105, amount)

    def change_empower_power(self, amount):
        self.give_buff_power(106, amount)

    def change_heat_power(self, amount):
        self.give_buff_power(107, amount)

    def change_cold_power(self, amount):
        self.give_buff_power(110, amount)

    def change_poison_power(self, amount):
        self.give_buff_power(108, amount)

    def change_blind_power(self, amount):
        self.give_buff_power(109, amount)

    def change_crit_chance_percent(self, amount):
        self.crit_chance_percent += amount

    def change_crit_severity(self, amount):
        self.add_crit_severity(amount)

    def change_damage_percent(self, amount):
        self.bonus_damage_factor += amount / 100.0

    def change_accuracy(self, amount):
        self.bonus_accuracy += amount

    def change_cooldown_percent(self, amount):
        if self.has_cooldown():
            self.base_cooldown_override = self.base_cooldown_override * (1.0 + amount / 100.0)

    def change_cooldown(self, amount):
        if self.has_cooldown():
            self.base_cooldown_override += amount

    def reduce_cooldown_percent(self, amount):
        self.change_cooldown_percent(-amount)

    def reduce_cooldown(self, amount):
        self.change_cooldown(-amount)

    def change_item_damage_percent(self, amount):
        self.bonus_damage_factor += amount / 100.0

    def change_stamina_cost(self, amount):
        self.stamina_cost += amount

    def change_max_stamina(self, amount):
        if self.character:
            self.character.gain_max_stamina_temporary(amount)

    def give_damage_percent_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.change_damage_percent(amount)

    def give_speed_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.add_speed(amount)

    def give_accuracy_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.add_accuracy(amount)

    def gains_stack(self, stack_enum) -> bool:
        """gainsStack — 物品是否与指定 Stack（位枚举）交互（canAffect 用）"""
        from .buff import BuffType
        mapping = {1: BuffType.BLOCK, 2: BuffType.LUCKY, 4: BuffType.REGENERATION,
                   8: BuffType.VAMPIRISM, 16: BuffType.SPIKES, 32: BuffType.MANA,
                   64: BuffType.EMPOWER, 128: BuffType.HEAT, 256: BuffType.POISON,
                   512: BuffType.BLIND, 1024: BuffType.COLD}
        bt = mapping.get(int(stack_enum))
        if bt is None:
            return False
        if self.buff_powers.get(bt, 0) > 0:
            return True
        name = BuffType.INV.get(bt, '').lower()
        return name in self.types or name in (self.data.get('named_params') or {})

    def get_buff_stacks(self, buff_type=None) -> int:
        if self.character:
            return self.character.get_buff_stacks(buff_type)
        return 0

    def change_speed(self, amount):
        self.add_speed(amount)

    def give_mana_capped(self, amount, maximum=None, trigger_event=None):
        """Item.gd giveMana_capped — 给 mana，超出上限的溢出返回（Blueberries 用）。"""
        from .buff import BuffType
        if not self.character:
            return amount
        amt = int(round((amount or 0) * self.buff_powers.get(BuffType.MANA, 1.0)))
        cur = self.character.get_mana()
        if maximum is not None and maximum > cur:
            missing = maximum - cur
            given = min(amt, missing)
            self.character.gain_mana(given, self, trigger_event)
            return amt - given
        self.character.gain_mana(amt, self, trigger_event)
        return amt

    def give_stamina_capped(self, amount, trigger_event=None):
        self.give_stamina(amount, trigger_event)

    def try_use_mana(self, amount, item=None, trigger_event=None):
        return self.character.try_use_mana(amount, self, trigger_event) if self.character else False

    def steal_life(self, amount, trigger_event=None, *a, **k):
        if self.opponent() is not None and self.character is not None:
            self.opponent().cur_health = max(0, self.opponent().cur_health - amount)
            self.character.heal(amount, origin=self.key, trigger_event=trigger_event)

    def emit_charge(self, speed_factor=1.0, *a, **k):
        """Item 级 emitCharge（跨物品调用入口；电池物品自身有行为覆写）"""
        if self.has_behavior("emitCharge"):
            return self.call_behavior("emitCharge", speed_factor)
        return None

    def change_poison_crit_chance_percent(self, amount):
        if self.character:
            self.character.poison_damage_source.crit_chance_percent += amount

    def get_num_affected_inside(self, *a):
        return 0

    def get_all_in_inventory_of_type(self, *a, **k):
        return []

    def count_types(self, items=None, *a, **k) -> dict:
        """countTypes — 统计类型计数（Prismatic Sword: affectedTypes[Type.X]），
        返回含全部 Type 键的 dict（缺失键为 0，行为内直接下标访问不抛 KeyError）"""
        items = items if items is not None else self.get_affected_items()
        out = {v: 0 for v in TYPE_NAMES}
        for it in items or []:
            for t in it.types:
                tid = _type_name_to_enum(t)
                if tid >= 0:
                    out[tid] += 1
        return out

    def remove_vampirism(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.opponent():
            self.opponent().lose_stacks(BuffType.VAMPIRISM, int(round(amount)), self, trigger_event)

    def lose_vampirism(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            self.character.lose_stacks(BuffType.VAMPIRISM, int(round(amount)), self, trigger_event)

    def use_vampirism(self, amount, trigger_event=None):
        from .buff import BuffType
        if self.character:
            return self.character.use_stacks(BuffType.VAMPIRISM, int(round(amount)), self, trigger_event)
        return None

    def give_all_buffs(self, num=1, trigger_event=None):
        from .buff import BuffType
        for t in range(BuffType.BLOCK, BuffType.HEAT + 1):
            self._give_stacks(self.character, t, num, trigger_event)

    def give_random_buffs(self, num=1, trigger_event=None, *a, **k):
        from .buff import BuffType
        buffs = [BuffType.BLOCK, BuffType.LUCKY, BuffType.REGENERATION,
                 BuffType.VAMPIRISM, BuffType.SPIKES, BuffType.MANA,
                 BuffType.EMPOWER, BuffType.HEAT]
        picked = self._pick_random_stacks_to_give(buffs, num)
        for t, n in picked.items():
            self._give_stacks(self.character, t, n, trigger_event)

    def give_buff(self, buff_type, amount, trigger_event=None):
        from .buff import BuffType
        if isinstance(buff_type, str):
            t = BuffType.NAMES.get(buff_type.lower())
        else:
            t = buff_type
        if t is not None:
            return self._give_stacks(self.character, t, amount, trigger_event)
        return None

    def lose_buff(self, buff_type, amount, trigger_event=None):
        from .buff import BuffType
        if isinstance(buff_type, str):
            t = BuffType.NAMES.get(buff_type.lower())
        else:
            t = buff_type
        if t is not None and self.character:
            return self.character.lose_stacks(t, int(round(amount)), self, trigger_event)
        return None

    def give_buff_temporary(self, buff_type, amount, duration, trigger_event=None):
        from .buff import BuffType
        if isinstance(buff_type, str):
            t = BuffType.NAMES.get(buff_type.lower())
        else:
            t = buff_type
        if t is not None:
            return self._give_stacks(self.character, t, amount, trigger_event,
                                     temporary=True, duration=duration)
        return None

    def inflict_debuff_temporary(self, debuff, amount, duration, trigger_event=None):
        from .buff import BuffType
        if isinstance(debuff, str):
            t = BuffType.NAMES.get(debuff.lower())
        else:
            t = debuff
        if t is not None:
            return self._give_stacks(self.opponent(), t, amount, trigger_event,
                                     temporary=True, duration=duration)
        return None

    def give_regeneration_temporary(self, amount, duration, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.REGENERATION, amount,
                                 trigger_event, temporary=True, duration=duration)

    def give_block_temporary(self, amount, duration, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.BLOCK, amount,
                                 trigger_event, temporary=True, duration=duration)

    def give_vampirism_temporary(self, amount, duration, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.VAMPIRISM, amount,
                                 trigger_event, temporary=True, duration=duration)

    def give_spikes_temporary(self, amount, duration, trigger_event=None):
        from .buff import BuffType
        return self._give_stacks(self.character, BuffType.SPIKES, amount,
                                 trigger_event, temporary=True, duration=duration)

    def change_max_health(self, amount, trigger_event=None):
        self.add_max_health(amount, trigger_event)

    def add_healing_efficiency(self, amount):
        if self.character:
            self.character.add_healing_efficiency(amount)

    def change_damage_resistance(self, amount):
        if self.character:
            self.character.change_damage_resistance(amount)

    def change_damage_reduction(self, amount):
        if self.character:
            self.character.change_damage_reduction(amount)

    def change_dodge_stacks(self, amount):
        if self.character:
            self.character.change_dodge_stacks(amount)

    def change_crit_resistance(self, amount):
        if self.character:
            self.character.change_crit_resistance(amount)

    def change_stun_resistance(self, amount):
        if self.character:
            self.character.change_stun_resistance(amount)

    def gain_crit_resist_stacks(self, amount):
        if self.character:
            self.character.gain_crit_resist_stacks(amount)

    def give_unhealing(self, amount):
        if self.character:
            self.character.give_unhealing(amount)

    def reduce_unhealing(self, amount):
        if self.character:
            self.character.reduce_unhealing(amount)

    def change_empower_damage(self, amount):
        if self.character:
            self.character.change_empower_damage(amount)

    def change_melee_spikes_limit(self, amount):
        if self.character:
            self.character.change_melee_spikes_limit(amount)

    def change_ranged_spikes_limit(self, amount):
        if self.character:
            self.character.change_ranged_spikes_limit(amount)

    def change_effect_spikes_limit(self, amount):
        if self.character:
            self.character.change_effect_spikes_limit(amount)

    def change_melee_vampirism_limit(self, amount):
        if self.character:
            self.character.change_melee_vampirism_limit(amount)

    def change_ranged_vampirism_limit(self, amount):
        if self.character:
            self.character.change_ranged_vampirism_limit(amount)

    def change_effect_vampirism_limit(self, amount):
        # 引擎无 effect 吸血上限，近似用 melee
        if self.character:
            self.character.change_melee_vampirism_limit(amount)

    def make_invulnerable(self, duration, trigger_event=None):
        if self.character:
            self.character.make_invulnerable(duration, self, trigger_event)

    def invulnerability_ended(self):
        if self.character:
            self.character.invulnerability_ended()

    def change_typed_damage_factor(self, damage_type, amount):
        if self.character:
            self.character.change_typed_damage_factor(damage_type, amount)

    def change_effect_damage_factor(self, amount):
        if self.character:
            self.character.change_effect_damage_factor(amount)

    def add_vampirism_all(self, amount, trigger_event=None):
        if self.character:
            self.character.gain_vampirism(amount, self, trigger_event)

    def add_damage_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.add_bonus_damage(amount)

    def give_crit_chance_to_all(self, amount):
        if self.character:
            for it in self.character.get_items():
                it.add_crit_chance_percent(amount)

    def change_debuff_resist_stacks(self, amount):
        if self.character:
            self.character.change_debuff_resist_stacks(amount)

    def change_debuff_reflect_stacks(self, amount):
        if self.character:
            self.character.change_debuff_reflect_stacks(amount)

    def change_buff_protect_stacks(self, amount):
        if self.character:
            self.character.change_buff_protect_stacks(amount)

    def change_resist_chance(self, buff_type, chance):
        if self.character:
            self.character.change_resist_chance(buff_type, chance)

    def change_reflect_chance(self, buff_type, chance):
        if self.character:
            self.character.change_reflect_chance(buff_type, chance)

    def change_debuff_resist_chances(self, chance):
        if self.character:
            self.character.change_debuff_resist_chances(chance)

    def change_debuff_reflect_chances(self, chance):
        if self.character:
            self.character.change_debuff_reflect_chances(chance)

    def change_buff_nullify_chances(self, chance):
        if self.character:
            self.character.change_buff_nullify_chances(chance)

    def can_miss(self):
        return self.damage_source.can_miss() if hasattr(self.damage_source, 'can_miss') else True

    def is_attack(self):
        return self.damage_source.is_attack() if hasattr(self.damage_source, 'is_attack') else False

    def get_stamina_regeneration(self):
        return self.character.get_stamina_regeneration() if self.character else 0.0

    def get_current_stamina(self):
        return self.character.get_current_stamina() if self.character else 0.0

    def get_max_stamina(self):
        return self.character.get_max_stamina() if self.character else 0.0

    def get_max_health(self):
        return self.character.get_max_health() if self.character else 0.0

    def get_current_health(self):
        return self.character.get_current_health() if self.character else 0.0

    def get_modified_cooldown(self):
        return self.get_cooldown() / self.get_speed()

    def give_max_health_flat(self, amount, trigger_event=None):
        if self.character:
            self.character.change_max_health_temporary(amount, self, trigger_event)

    # ================ 参数（对齐 getP/getP_m） ================
    def get_p(self, index) -> float:
        params = self.data.get('params', [])
        if isinstance(index, str):
            return self.data.get('named_params', {}).get(index, 0.0)
        if isinstance(index, int) and 0 <= index < len(params):
            return float(params[index])
        return 0.0

    def get_p_m(self, param_name: str, default: float = 0.0) -> float:
        """getP_m — 带 paramMult/paramAdd 修正"""
        base = default
        if isinstance(param_name, str):
            base = self.data.get('named_params', {}).get(param_name, default)
        else:
            base = self.get_p(param_name)
        mult = self.param_mult.get(param_name, 1.0)
        add = self.param_add.get(param_name, 0.0)
        return (base + add) * mult

    def modify_param(self, param_name: str, amount: float):
        """Item.gd 3916: Util.dictAdd(paramMult, name, amount, 1.0) —— **累加**（默认倍率 1.0）。

        此前误实现为乘法，会把倍率直接乘成 amount（如 1.0*0.1=0.1），与源码不符。
        """
        self.param_mult[param_name] = self.param_mult.get(param_name, 1.0) + float(amount)

    def modify_param_add(self, param_name: str, amount: float):
        self.param_add[param_name] = self.param_add.get(param_name, 0.0) + amount

    # ================ 工具 ================
    @staticmethod
    def _buff_name_to_type(name: str) -> Optional[int]:
        from .buff import BuffType
        if isinstance(name, int):
            return name
        return BuffType.NAMES.get(name)

    def __repr__(self):
        return f"<Item {self.key}>"


# ---------------------------------------------------------------------------
# GDScript 调用名（camelCase）-> 引擎方法（snake_case）别名
#
# 转译后的行为代码里，对**其他物品**的调用保留 GDScript 原名（如
# `item.canActivate()`、`item.addBonusBlock(x)`）；extract_items.METHOD_RENAME
# 会在重新生成行为库时做重命名，但历史数据与个别未覆盖的名字仍可能以原名出现。
# 这里统一补别名，保证联动判定不会因为命名风格差异而静默失效。
# 放在类定义之后，确保引用到的是最终生效（含后部覆盖）的方法。
# ---------------------------------------------------------------------------
_GDSCRIPT_ALIASES = {
    "canActivate": "can_activate",
    "canBlock": "can_block",
    "canModifyChance": "can_modify_chance",
    "canHealOrLifesteal": "can_heal_or_lifesteal",
    "canStartNewRecipe": "can_start_new_recipe",
    "canBeEmpowered": "can_be_empowered",
    "giveBuffPower": "give_buff_power",
    "gainsBuffs": "gains_buffs",
    "gainsStack": "gains_stack",
    "usesBuffs": "uses_buffs",
    "inflictsDebuffs": "inflicts_debuffs",
    "addBonusChance": "add_bonus_chance",
    "addBonusBlock": "add_bonus_block",
    "changeHealAmp": "change_heal_amp",
    "changeAmplificiationChancePercent_allDebuffs":
        "change_amplification_chance_percent_all_debuffs",
    "hasStartofBattle": "has_startof_battle",
    "hasAttackEffect": "has_attack_effect",
    "hasInventoryDuration": "has_inventory_duration",
    "isCrafted": "is_crafted",
    "isClassItem": "is_class_item",
    "isTreasure": "is_treasure",
    "reactsToCharges": "reacts_to_charges",
    "chargeLeft": "charge_left",
    "getPrice": "get_price",
    "getSellPrice": "get_sell_price",
    "getBaseStaminaCost": "get_base_stamina_cost",
    "modifyParam": "modify_param",
    "modifyParam_add": "modify_param_add",
    "repeatCombatStart": "repeat_combat_start",
    "addDynamicType": "add_dynamic_type",
    "removeDynamicType": "remove_dynamic_type",
    "hasDynamicType": "has_dynamic_type",
    "getItemsInAffectedCells": "get_items_in_affected_cells",
    "getItemsInAffectedCells_cached": "get_items_in_affected_cells",
}

for _gd, _py in _GDSCRIPT_ALIASES.items():
    _target = getattr(Item, _py, None)
    if _target is not None and not hasattr(Item, _gd):
        setattr(Item, _gd, _target)
