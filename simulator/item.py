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
from .buff import BuffType

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
        if base_rng is not None:
            self.damage_range_rng = base_rng
            self.chance_rng = base_rng
        else:
            self.damage_range_rng = random.Random(seed)
            self.chance_rng = random.Random(seed)

        # ---- descriptor 数值（对齐 ItemDescriptor 字段）----
        self.min_dam = int(data.get('min_dam', 0))
        self.max_dam = int(data.get('max_dam', self.min_dam))
        self.cd = float(data.get('cd', 0.0))
        self.base_accuracy = float(data.get('accuracy', 100.0))
        self.stamina_cost = float(data.get('stamina_cost', 0.0))
        self.block = int(data.get('block', 0))
        self.crit_chance_percent = float(data.get('crit', 0.0))
        self.trigger_priority = int(data.get('trigger_priority', 0))
        self.category = data.get('category', 'utility')
        self.damage_types = data.get('damage_type', 'effect')
        self.types = list(data.get('types', []))
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
        self.crit_severity: float = self.BASE_CRIT_SEVERITY
        self.base_cooldown_override: float = self.cd
        self.buff_powers: Dict[int, float] = {}
        self.buff_amplification_chances: Dict[int, float] = {}
        self.param_mult: Dict[str, float] = {}
        self.param_add: Dict[str, float] = {}

        # ---- 冷却运行状态 ----
        self.iteration_cooldown: float = 0.0
        self.trigger_time: float = 0.0
        self.activations_this_frame: int = 0
        self.last_activation_time: float = 0.0
        self.consumed: bool = False
        self.is_full: bool = True          # Potion.isFull

        # ---- 行为执行器（extract_items.py 提取的 GDScript 行为） ----
        self._behavior_executor: Optional[BehaviorExecutor] = None
        self._behavior_ready: bool = False
        self._signals: Dict[str, list] = {}

        # ---- 背包网格（extract_grid.py + grid.py） ----
        self.occupied_cells: list = []          # 背包中的占格（绝对格子）
        self.grid_inventory = None              # GridInventory 引用
        self.grid_row: int = 0
        self.grid_col: int = 0
        self.grid_rotation: int = 0
        self._affected_cache: Dict[int, list] = {}
        self.affectedItems: list = []   # 行为内缓存的邻接物品（对应 GDScript affectedItems）

        # ---- 宝石 ----
        self.is_gem_item: bool = False
        self._socket_item: Optional['Item'] = None   # 宝石的宿主物品
        self._gems: List['Item'] = []                # 宿主的宝石列表
        self.gem_power: float = 1.0

        # ---- 效果钩子标志 ----
        self.has_pre_deal_damage_early_effect = False
        self.has_pre_deal_damage_late_effect = False
        self.has_dealt_damage_effect = False

        # ---- 伤害源（对齐 Weapon._ready: DamageSource.new().setItem(self)）----
        self.damage_source = self._make_damage_source()

        # ---- 统计 ----
        self.metrics = {"damage": 0, "heal": 0, "activations": 0,
                        "misses": 0, "out_of_stamina": 0}

    # ================ 伤害源（对齐 DamageSource.setItem） ================
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
    def is_weapon(self) -> bool:
        return 'weapon' in self.types or self.category == 'weapon'

    def is_bag(self) -> bool:
        return 'bag' in self.types or self.category == 'bag'

    def has_type(self, t) -> bool:
        """hasType — 兼容 str 与 Type 枚举 int（对齐 Item.gd Type 枚举）"""
        if isinstance(t, int):
            t = TYPE_NAMES.get(t, '')
        return t in self.types

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
        if self.character is not None:
            if self.is_weapon() and self.can_damage():
                v += self.character.get_buff_damage_mod()
            v *= self.get_typed_damage_factor(dam_source or self.damage_source)
        v = round(v * self.bonus_damage_factor)
        return max(v, 0)

    def get_max_damage(self, dam_source=None) -> int:
        v = math.ceil(self.max_dam + self.bonus_max_dam)
        if self.character is not None:
            if self.is_weapon() and self.can_damage():
                v += self.character.get_buff_damage_mod()
            v *= self.get_typed_damage_factor(dam_source or self.damage_source)
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
        return self.has_cooldown() and self.character is not None

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

    # ================ 战斗生命周期 ================
    def prepare(self):
        """prepare() — 对齐 Item.gd：cacheAffectedItems → 宝石.prepare() → onPrepare 链"""
        if self.is_gem_item:
            self._prepare_as_gem()
            return
        self.consumed = False
        self.is_full = True
        self._cache_affected_items()
        for gem in self._gems:
            gem.character = self.character
            gem.log = self.log
            gem.prepare()
        self._run_prepare_behaviors()

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

    # ================ tick 驱动（_physics_process 还原） ================
    def physics_tick(self, delta: float, now: float):
        """每物理帧：冷却推进"""
        if not self.has_cooldown():
            return
        ch = self.character
        if ch is None or ch.is_stunned() or ch.is_dead:
            return
        self.trigger_time -= delta * self.get_speed()
        if self.trigger_time <= 0:
            self.trigger(now)

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
        attack_src = self.data.get("behavior", {}).get("methods", {}).get("attack", "")
        if self.has_behavior("attack") and "deal_damage" in attack_src:
            return self.call_behavior("attack", trigger_event)
        """attack — Weapon.attack: dealDamage + activate"""
        res = self.deal_damage(now)
        self.visual_activate(res)
        if self.has_behavior("attack"):
            self.call_behavior("attack", trigger_event)
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
        """dealtDamage — 每次带 item 的伤害结算后调用（命中计伤害，未命中计 miss）"""
        if res.has_hit():
            self.metrics["damage"] += res.damage
        else:
            self.metrics["misses"] += 1
        if self.has_behavior("onDealtDamage"):
            self.call_behavior("onDealtDamage", res)

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

    # ---- 信号注册（connectForCombat 还原） ----
    def connect_signal(self, signal: str, cb):
        self._signals.setdefault(signal, []).append(cb)

    def emit_signal(self, signal: str, *args):
        for cb in list(self._signals.get(signal, [])):
            try:
                cb(*args)
            except Exception:
                pass

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

    def _run_prepare_behaviors(self):
        """prepare 阶段行为：实例变量默认值 → onready 变量 → onPrepare → prepare（对齐 GDScript 调用链）"""
        if self._behavior_ready:
            return
        self._behavior_ready = True
        if not self.data.get("behavior"):
            return
        # 类级 var 默认值（GDScript 节点初始化即生效，Python 需手动补 0）
        for v in self.data.get("behavior", {}).get("instance_vars", []):
            if not hasattr(self, v):
                setattr(self, v, 0)
        self.call_behavior("_onready_init")
        self.has_pre_deal_damage_early_effect = self.has_behavior(
            "onPreDealDamage_early")
        self.has_pre_deal_damage_late_effect = self.has_behavior(
            "onPreDealDamage_late")
        self.has_dealt_damage_effect = self.has_behavior("onDealtDamage")
        # 效果字典兜底（Magic Ring 等融合构建型物品：effectDict[TriggerType.X] 访问不抛 KeyError）
        if hasattr(self, "effectDict") and isinstance(self.effectDict, dict) and not self.effectDict:
            from collections import defaultdict
            self.effectDict = defaultdict(list)
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

    def consume_potion(self, trigger_event=None):
        """consumePotion — 喝药并触发 onTriggerPotion"""
        if self.is_empty():
            return
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
        """getChance — CSV chance 列（如 '1:crit'/'70'）取前导数值"""
        raw = self.data.get('csv_chance', '') or ''
        return self._parse_chance(raw)

    def get_chance2(self) -> float:
        raw = self.data.get('csv_chance2', '') or ''
        return self._parse_chance(raw)

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
        tscn CollisionMap 是 40px 精细 tile，背包格 80px → 坐标 //2 合并。
        tscn 格 (x,y)：x=横向=背包 col、y=纵向=背包 row。
        """
        from .grid import rotate_cell, cells_from_grid_data
        self.grid_row = row
        self.grid_col = col
        self.grid_rotation = int(rotation) % 360
        base = cells_from_grid_data(self.data.get('grid') or {})
        # 40px 精细 tile：先旋转（锚点系），再归一化
        rotated = [rotate_cell(tuple(c), self.grid_rotation) for c in base]
        minx = min((c[0] for c in rotated), default=0)
        miny = min((c[1] for c in rotated), default=0)
        self._rotated40 = rotated
        self._min40 = (minx, miny)
        shape40 = sorted((c[0] - minx, c[1] - miny) for c in rotated)
        self._shape40 = shape40
        # 40px 格 -> 80px 背包格：//2 取唯一，再平移到 (row,col)
        cells = {}
        for c in shape40:
            cells[(c[1] // 2, c[0] // 2)] = True     # (y//2, x//2) -> (row, col) 序
        self.occupied_cells = [(r + row, c + col) for (r, c) in cells]
        self.grid_inventory = inventory
        if inventory is not None:
            inventory.add_item(self, self.occupied_cells, is_bag=self.is_bag())

    def grid_shape(self) -> list:
        """归一化后的 40px 占格形状（旋转后，左上角 0,0），(x,y) 序"""
        return list(getattr(self, '_shape40', None) or [])

    @staticmethod
    def _to_abs(cell, row: int, col: int):
        """tscn 格 (x,y) -> 背包绝对格 (row,col)"""
        return (cell[1] + row, cell[0] + col)

    def _affected_cells_abs(self, color: int = 0) -> list:
        """受影响格（绝对背包格子）：tscn Affected tile + 脚本补充，旋转 + 40px->80px 合并"""
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
            # 40px 偏移 //2 -> 80px 格，再平移到 (row,col)
            cells.add((self.grid_row + offy // 2, self.grid_col + offx // 2))
        for c in self._script_affected_cells(color):
            cells.add(c)
        return sorted(cells)

    def _script_affected_cells(self, color: int = 0) -> list:
        """脚本 getAffectedCellsAfterRotate 的补充格（基于旋转后 40px 占格形状）"""
        if color != 0:
            return []
        name = self.data.get('behavior', {}).get('extends', '')
        shape40 = self.grid_shape()
        if not shape40:
            return []
        out = []
        if name == 'Potion' or self.data.get('category') == 'potion':
            # Potion and Rainbow Potion override this anchor by face
            # direction.  The lineup rotation uses the same quarter-turn
            # convention as Item.gd's faceDirection.
            rainbow = name == 'RainbowPotion' or self.key == 'Rainbow Potion'
            use_second = (self.grid_rotation == (270 if rainbow else 180))
            anchor = shape40[1] if use_second and len(shape40) > 1 else shape40[0]
            upy = anchor[1] - 1          # +Vector2.UP（40px）
            upx = anchor[0]
            out.append((self.grid_row + upy // 2, self.grid_col + upx // 2))
        elif name == 'BagofStones':
            # getCellsInLine(rotatedCells, UP, 1)：占格上方 1 格直线
            for c in shape40:
                upy = c[1] - 1
                cell = (self.grid_row + upy // 2, self.grid_col + c[0] // 2)
                if cell not in out:
                    out.append(cell)
        return out

    def _cache_affected_items(self):
        """cacheAffectedItemsForCombat — prepare 时缓存邻接"""
        self._affected_cache = {0: self._compute_affected(0),
                                2: self._compute_affected(2),
                                4: self._compute_affected(4),
                                7: self._compute_affected(7)}

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
        """基类默认 canAffect（对应 GDScript 的 .canAffect(item) 超类调用）：相邻即可联动。"""
        parent = (self.data.get("behavior") or {}).get("extends", "")
        if color == 0 and parent == "Food":
            return (other.has_type("food") and
                    other.data.get("key", other.key) != self.data.get("key", self.key))
        if color == 0 and parent == "Potion":
            return other.has_type("potion")
        return False

    def _base_can_affect_secondary(self, other, color: int = 0) -> bool:
        return True

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
        """Item.gd sendCharge — 电荷沿 cells（相对格偏移）传播，途经物品 +1 charge 并触发 onChargeReceived。
        完整电荷动画不建模；核心计数与 onChargeReceived 效果保留。"""
        if self.grid_inventory is None:
            return
        for cell in cells or []:
            try:
                dr, dc = cell[0], cell[1]
                target = self.grid_inventory.get_item_in_cell(
                    (self.grid_row + dr, self.grid_col + dc))
            except Exception:
                continue
            if target is None or target is self:
                continue
            target.num_charges = getattr(target, "num_charges", 0) + 1
            if target.has_behavior("onChargeReceived"):
                try:
                    target.call_behavior("onChargeReceived", self, event)
                except Exception:
                    pass

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
        """canBeEmpowered — 可被强化（有魔法/力量相关参数）"""
        return bool(self.buff_powers.get(BuffType.EMPOWER, 0)) or "empower" in (self.data.get("named_params") or {})

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
        self.iteration_cooldown = 0.0
        self.trigger_time = float("inf")

    def count_items_in_affected_cells_cached(self, color=0) -> int:
        return len(self.get_affected_items(color))

    def give_max_stamina_temporary(self, amount, trigger_event=None, filled=True):
        if self.character:
            self.character.gain_max_stamina_temporary(amount, filled=filled)

    def change_spikes_crit_chance_percent(self, amount):
        if self.character:
            self.character.spike_damage_source.crit_chance_percent += amount

    def is_a(self, descriptor) -> bool:
        return False

    def check_block(self) -> bool:
        """checkBlock — Stoned 保护判定：有格挡时保护生效"""
        return bool(self.character and self.character.get_block() > 0) if self.character else False

    def inflict_fatigue_damage(self, amount, trigger_event=None):
        """inflictFatigueDamage — 给对方疲劳伤害"""
        if self.opponent():
            self.opponent().take_fatigue_damage(int(round(amount)))

    def get_num_affected_items(self, color=None) -> int:
        return len(self.get_affected_items(color))

    def get_num_cells(self) -> int:
        return len(self.occupied_cells)

    def get_relative_health(self) -> float:
        return self.character.get_relative_health() if self.character else 0.0

    def get_block(self) -> int:
        # Item.gd getBlock() reads this item's descriptor value.  The
        # character's current block is exposed by Character.get_block().
        return int(self.block)

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
            amount = self.get_p_m("block", self.get_p_m("Block", 0))
        if temporary:
            return self._give_stacks(self.character, BuffType.BLOCK, amount,
                                     trigger_event, temporary=True)
        return self._give_stacks(self.character, BuffType.BLOCK, amount, trigger_event)

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
        return []

    def get_num_affected_type(self, *a, **k):
        return 0

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

    def add_battle_rage_duration(self, amount):
        if self.character:
            self.character.battle_rage_active = True

    def give_random_buff(self, num=1, trigger_event=None):
        self.give_random_buffs(num, trigger_event)

    def get_rarity(self):
        return self.data.get('rarity', '')

    def start_battle_rage(self, *a, **k):
        if self.character:
            self.character.battle_rage_active = True

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

    def emit_charge(self, *a, **k):
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
        self.param_mult[param_name] = self.param_mult.get(param_name, 1.0) * amount

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
