# -*- coding: utf-8 -*-
"""character.py — 战斗角色（对齐 Core/Character.gd 全流程）

核心：takeDamage（命中/暴击/抗性/减伤/无敌/格挡/死亡）、dealDamage（攻击+吸血）、
applySpikes（反伤）、applyVampirism（吸血）、heal（治疗+不治）、onTick（1s 回血/中毒）、
体力系统、眩晕、buff 栈管理。
"""
from __future__ import annotations

from typing import Optional, TYPE_CHECKING

from .rng import BalancedRng
from .damage import (DamageSource, DamageResult, DS_Type, DS_Flags,
                     CHIP_FLAGS, UNHEALING_FLAGS)
from .buff import Buff, BuffType, is_buff

if TYPE_CHECKING:
    from .item import Item


class _OriginEvent:
    """轻量事件包装：buff 变化信号无 event 时提供 getOrigin()/get_origin()（源物品可空）。
    对齐 CombatEvent.getOrigin() 语义，供 onBuffsChanged 等行为读取来源。"""

    __slots__ = ("_origin",)

    def __init__(self, origin=None):
        self._origin = origin

    def get_origin(self):
        return self._origin

    def getOrigin(self):
        return self._origin

    def __getattr__(self, name):
        return None
    from .events import CombatLog


class Character:
    """战斗角色"""

    def __init__(self, player_id: int, character_name: str = "",
                 max_health: float = 25.0, max_stamina: float = 5.0,
                 stamina_regen: float = 1.0, seed: Optional[int] = None,
                 log: Optional['CombatLog'] = None, base_rng=None):
        self.player_id = player_id            # 0=PLAYER 1=OPPONENT
        self.character_name = character_name
        self.opponent: Optional['Character'] = None
        self.log = log

        # 平衡 RNG（对齐 BalancedRng，accuracyRng/critRng 各自独立）
        if base_rng is not None:
            self.accuracy_rng = BalancedRng(base_rng=base_rng)
            self.crit_rng = BalancedRng(base_rng=base_rng)
            self.crit_resistance_rng = BalancedRng(base_rng=base_rng)
            self.stun_resistance_rng = BalancedRng(base_rng=base_rng)
        else:
            self.accuracy_rng = BalancedRng(seed=seed)
            self.crit_rng = BalancedRng(seed=(seed + 0x9E3779B9 if seed is not None else None))
            self.crit_resistance_rng = BalancedRng(seed=(seed + 0x85EBCA6B if seed is not None else None))
            self.stun_resistance_rng = BalancedRng(seed=(seed + 0xC2B2AE35 if seed is not None else None))
        self._rng = base_rng if base_rng is not None else BalancedRng(seed=seed)._rng

        # ---- 生命 ----
        self.max_health: float = max_health
        self.cur_health: float = max_health
        self.temporary_max_health: float = 0.0
        self.temporary_max_health_gain: float = 1.0
        self.is_dead: bool = False

        # ---- 体力 ----
        self.base_max_stamina: float = max_stamina
        self.max_stamina: float = max_stamina
        self.cur_stamina: float = max_stamina
        self.temporary_max_stamina: float = 0.0
        self.base_stamina_regen: float = stamina_regen
        self.stamina_regen: float = stamina_regen
        self.allow_stamina_overflow: bool = False

        # ---- 状态 ----
        self.stunned_duration: float = 0.0
        self.invulnerable: bool = False
        self.invulnerability_remaining: float = 0.0
        self.unhealing_amount: float = 0.0
        self.healing_efficiency: float = 1.0
        self.damage_resistance: float = 0.0
        self.damage_reduction: int = 0
        self.dodge_stacks: int = 0
        self.crit_resistance: float = 0.0
        self.crit_resist_stacks: int = 0
        self.stun_resistance: float = 0.0
        self.debuff_resist_stacks: int = 0
        self.debuff_reflect_stacks: int = 0
        self.buff_protect_stacks: int = 0
        self.crit_tokens: int = 0
        self.bonus_fatigue_damage: int = 0
        self.battle_rage_active: bool = False

        # ---- 限制/系数 ----
        self.melee_spikes_limit: float = 1.0
        self.ranged_spikes_limit: float = 0.0
        self.effect_spikes_limit: float = 0.0
        self.melee_vampirism_limit: float = 1.0
        self.ranged_vampirism_limit: float = 0.0
        self.empower_damage: float = 1.0
        self.typed_damage_factors: dict = {
            DS_Type.MELEE: 0.0, DS_Type.RANGED: 0.0, DS_Type.EFFECT: 0.0,
            DS_Type.UNHEALING: 0.0, DS_Type.FATIGUE: 0.0, DS_Type.SPIKES: 0.0,
            DS_Type.POISON: 0.0,
        }

        # ---- buff 栈（Block..Cold）----
        self.buffs: dict[int, Buff] = {
            t: Buff(t, self) for t in range(BuffType.BLOCK, BuffType.COLD + 1)
        }

        # 伤害源（spikes/poison）
        self.spike_damage_source = DamageSource().init(self, DS_Type.SPIKES, 1)
        self.spike_damage_source.flags = CHIP_FLAGS + DS_Flags.CAN_CRIT
        self.poison_damage_source = DamageSource().init(self, DS_Type.POISON, 1)
        self.poison_damage_source.flags = CHIP_FLAGS + DS_Flags.CAN_CRIT

        # 物品列表（外部注入）
        self.inventory_items: list['Item'] = []

        # ---- 战斗运行期 ----
        self.tick_counter: int = 0
        self.tick_timer_remaining: float = 1.0

        # 战斗统计
        self.stats = {
            "damage_dealt": 0, "damage_taken": 0, "healing_done": 0,
            "crits": 0, "misses": 0, "activations": 0, "out_of_stamina": 0,
            "spikes_dealt": 0, "vampirism_heal": 0,
        }

        # 信号注册表（connectForCombat 还原）
        self._signals: dict = {}

    # ================ 信号系统（connectForCombat） ================
    def connect_signal(self, signal: str, cb):
        self._signals.setdefault(signal, []).append(cb)

    def emit_signal(self, signal: str, *args):
        for cb in list(self._signals.get(signal, [])):
            try:
                cb(*args)
            except Exception:
                pass

    def __getattr__(self, name: str):
        """camelCase -> snake_case 属性/方法兜底（行为脚本以 GDScript 名访问）"""
        if name.startswith("_"):
            raise AttributeError(name)
        import re as _re
        snake = _re.sub(r"(?<!^)(?=[A-Z])", "_", name).lower()
        if snake in self.__dict__:
            return self.__dict__[snake]
        meth = getattr(type(self), snake, None)
        if meth is not None and callable(meth):
            return meth.__get__(self)
        raise AttributeError(name)

    def _emit_debuff_changed(self, buff_type: int, amount: int, event, item=None):
        """减益栈变化：发通用 + 分类型信号"""
        if event is None:
            event = _OriginEvent(item)
        self.emit_signal("character_debuff_changed", amount, event)
        from .buff import BuffType
        name = BuffType.INV.get(buff_type, str(buff_type)).lower()
        self.emit_signal(f"character_{name}_changed", amount, event)

    # ---- 行为脚本常用的直接 HP/体力修改 ----
    def lose_health(self, amount, trigger_event=None):
        """loseHealth — 直接扣血（Book of Darkness 等）"""
        self.cur_health = max(0, self.cur_health - amount)
        self.stats["damage_taken"] += amount
        if self.cur_health <= 0:
            self.death()
        return amount

    def lose_stamina(self, amount, trigger_event=None):
        self.cur_stamina = max(0, self.cur_stamina - amount)
        return amount

    def set_max_health(self, v):
        self.max_health = v
        self.cur_health = min(self.cur_health, v)

    def set_max_stamina_attr(self, v):
        self.max_stamina = v

    # ================ 标识 ================
    def is_player(self) -> bool:
        return self.player_id == 0

    def name(self) -> str:
        return "player" if self.is_player() else "opponent"

    def display_name(self) -> str:
        return self.character_name or self.name()

    def set_opponent(self, opp: 'Character'):
        self.opponent = opp

    def set_items(self, items: list['Item']):
        self.inventory_items = items
        for it in items:
            it.character = self

    # ================ 生命周期 ================
    def prepare(self, log: Optional['CombatLog'] = None):
        """prepare()/cleanse() — 每场战斗前的完整重置"""
        if log is not None:
            self.log = log
        self.is_dead = False
        self.temporary_max_health = 0.0
        self.temporary_max_health_gain = 1.0
        self.stamina_regen = self.base_stamina_regen
        self.cur_health = self.get_max_health()
        self.temporary_max_stamina = 0.0
        self.fill_up_stamina()
        self.stunned_duration = 0.0   # endStun 但战斗日志尚未开始，不记录
        self.set_block(0)
        for b in self.buffs.values():
            b.reset()
        self.invulnerable = False
        self.invulnerability_remaining = 0.0
        self.damage_resistance = 0.0
        self.damage_reduction = 0
        self.dodge_stacks = 0
        self.crit_resistance = 0.0
        self.crit_resist_stacks = 0
        self.stun_resistance = 0.0
        self.unhealing_amount = 0.0
        self.healing_efficiency = 1.0
        self.crit_tokens = 0
        self.debuff_resist_stacks = 0
        self.debuff_reflect_stacks = 0
        self.buff_protect_stacks = 0
        self.bonus_fatigue_damage = 0
        self.melee_spikes_limit = 1.0
        self.ranged_spikes_limit = 0.0
        self.effect_spikes_limit = 0.0
        self.melee_vampirism_limit = 1.0
        self.ranged_vampirism_limit = 0.0
        self.empower_damage = 1.0
        for t in self.typed_damage_factors:
            self.typed_damage_factors[t] = 0.0
        self.poison_damage_source.crit_chance_percent = 0.0
        self.spike_damage_source.crit_chance_percent = 0.0
        for k in self.stats:
            self.stats[k] = 0
        self.accuracy_rng.reset()
        self.crit_rng.reset()
        self.crit_resistance_rng.reset()
        self.stun_resistance_rng.reset()
        self._signals.clear()

    def combat_start(self):
        """combatStart() — 清眩晕、tickCounter=0、TickTimer 1s"""
        self.stunned_duration = 0.0
        self.tick_counter = 0
        self.tick_timer_remaining = 1.0

    def character_tick(self, delta: float):
        """_physics_process — 眩晕计时 + 无条件体力恢复"""
        if self.stunned_duration > 0:
            self.stunned_duration -= delta
            if self.stunned_duration <= 0:
                self.end_stun()
        if self.invulnerable:
            self.invulnerability_remaining -= delta
            if self.invulnerability_remaining <= 0:
                self.invulnerability_ended()
        self.add_stamina(self.get_stamina_regeneration() * delta)

    def on_tick(self, now: float):
        """onTick() — 每 1s：偶数 tickCounter 回血 / 奇数 中毒"""
        if self.tick_counter % 2 == 0:
            regen = self.get_regeneration()
            if regen > 0:
                # heal() 内部已记 Health 事件，无需额外 tick 行（复刻原版）
                self.heal(regen, origin="Regeneration")
        else:
            poison = self.get_poison()
            if poison > 0:
                self.poison_damage_source.set_damage(poison)
                res = self.take_damage(self.poison_damage_source, origin_label="poison")
                if self.log and res.damage > 0:
                    self.log.lose_health(now, self.name(), res.damage, origin="Poison")
        self.tick_counter += 1

    def end_stun(self):
        if self.stunned_duration > 0 and self.log is not None:
            self.log.stun_end(self.log.current_time, self.name())
        self.stunned_duration = 0.0

    # ================ 基础状态 ================
    def get_max_health(self) -> float:
        return self.max_health + self.temporary_max_health

    def get_current_health(self) -> float:
        return self.cur_health

    def get_relative_health(self) -> float:
        return self.cur_health / self.get_max_health() if self.get_max_health() else 0.0

    def get_max_stamina(self) -> float:
        return self.max_stamina + self.temporary_max_stamina

    def get_current_stamina(self) -> float:
        return self.cur_stamina

    def get_stamina_regeneration(self) -> float:
        return self.stamina_regen

    def is_stunned(self) -> bool:
        return self.stunned_duration > 0

    # ================ 攻击（dealDamage 还原） ================
    def deal_damage(self, damage_source: DamageSource, trigger_event=None,
                    origin_label: Optional[str] = None) -> DamageResult:
        """dealDamage — 用伤害源攻击对手，附带吸血"""
        res = self.opponent.take_damage(damage_source, trigger_event, origin_label)
        self.apply_vampirism(res)
        return res

    # ================ 伤害结算（takeDamage 完整还原） ================
    def take_damage(self, damage_source: DamageSource, trigger_event=None,
                    origin_label: Optional[str] = None) -> DamageResult:
        now = getattr(trigger_event, 't', None)
        if now is None and self.log is not None:
            now = self.log.current_time

        ds = DamageSource().from_source(damage_source)
        res = DamageResult(damage_source=ds)
        res.reset()

        if self.is_dead:
            return res

        item = ds.origin if (ds.origin is not None and hasattr(ds.origin, 'roll_double_attack_effect')) else None
        if item is not None and getattr(item, 'character', None) is not None:
            actor_name = item.character.name()
        else:
            actor_name = self.opponent.name() if self.opponent else None
        target_name = self.name()

        attack_effect_count = 1
        if item is not None:
            attack_effect_count += item.roll_double_attack_effect()

        # ---- 命中判定（对齐原版：先 roll 命中） ----
        if ds.can_miss():
            accuracy = ds.accuracy
            res.hit = self.accuracy_rng.roll_percent(accuracy)
            if res.hit and self.dodge_stacks > 0:
                self.change_dodge_stacks(-1)
                res.hit = False
                # 原版无独立 dodge 行，未命中统一由下方的 missed 记录
        else:
            res.hit = True

        # ---- preDealDamage_early（对齐原版：命中判定之后调用） ----
        # 原版 Character.gd takeDamage: 先 roll 命中, 再 item.preDealDamage_early(damageRes)
        if item is not None and ds.is_attack():
            item.pre_deal_damage_early(res)
            for _ in range(attack_effect_count - 1):
                item.pre_deal_damage_early(res)

        # ---- 命中后伤害计算 ----
        if res.hit:
            res.damage += ds.rand_damage(self._rng)

            if ds.has_type(DS_Type.FATIGUE):
                res.damage += self.bonus_fatigue_damage

            # 暴击
            if ds.can_crit():
                critical = False
                crit_chance = ds.get_crit_chance_percent()
                if crit_chance > 0 and self.crit_rng.roll_percent(crit_chance):
                    critical = True
                if not critical and item is not None and item.get_crit_tokens() > 0:
                    item.use_crit_token()
                    critical = True
                if not critical and self.opponent is not None and self.opponent.get_crit_tokens() > 0:
                    self.opponent.use_crit_token()
                    critical = True
                if critical:
                    if self.crit_resisted():
                        if self.log:
                            self.log.crit_resisted(now, actor_name, target_name)
                    else:
                        res.make_critical(item)
                        self.stats["crits"] += 1

            # 伤害抗性（百分比）
            active_dmg_resi = max(-10.0, min(1.0, self.damage_resistance / 100.0))
            res.damage = int(round(res.damage * (1.0 - active_dmg_resi)))

            # 攻击类固定减伤
            if ds.is_attack():
                res.damage -= self.damage_reduction

            # 无敌
            if self.invulnerable:
                res.damage = 0

            # 格挡扣减（damageReduction 累计，来自护盾 beforeBlock）
            self.emit_signal('pre_take_damage', res)
            res.damage -= res.damage_reduction
            res.damage = max(0, res.damage)

            # preDealDamage_late 钩子
            if item is not None and ds.is_attack():
                item.pre_deal_damage_late(res)
                for _ in range(attack_effect_count - 1):
                    item.pre_deal_damage_late(res)

            self.emit_signal('pre_take_damage_late', res)
            res.health_damage = res.damage

            # 格挡 Block 栈
            block_absorbed = 0
            if ds.can_be_blocked():
                cur_block = self.get_block()
                if res.damage > cur_block:
                    res.health_damage -= cur_block
                    block_absorbed = cur_block
                    self.lose_block(cur_block, trigger_event=trigger_event)
                else:
                    block_absorbed = res.damage
                    self.lose_block(res.damage, trigger_event=trigger_event)
                    res.health_damage = 0
                # 攻击方 afterBlock 回调（破盾/吸收后）
                if item is not None and block_absorbed > 0:
                    item.after_block(res)

            self.cur_health -= res.health_damage
            self.stats["damage_taken"] += res.health_damage

            # 攻击方伤害统计
            if item is not None and getattr(item, 'character', None) is not None:
                item.character.stats["damage_dealt"] += res.damage

            # 日志
            if self.log and item is not None:
                if res.was_critical_hit():
                    self.log.attack(now, actor_name, target_name, item.key,
                                    res.damage, res.health_damage, hit=True,
                                    critical=True, block_absorbed=block_absorbed)
                else:
                    self.log.attack(now, actor_name, target_name, item.key,
                                    res.damage, res.health_damage, hit=True,
                                    critical=False, block_absorbed=block_absorbed)
            elif self.log:
                # 非物品伤害（毒/疲劳/反伤/不治）
                pass

        else:
            if self.log and item is not None:
                self.log.missed(now, actor_name, target_name, item.key)
            # 未命中计入攻击方统计
            if item is not None and getattr(item, 'character', None) is not None:
                item.character.stats["misses"] += 1

        # ---- 战后钩子 ----
        if item is not None:
            item.dealt_damage(res)
            if ds.is_attack() and item.has_dealt_damage_effect:
                for _ in range(attack_effect_count):
                    item.on_dealt_damage(res)

        # ---- 触发器：受击时检查本角色药水（character_damaged） ----
        self.emit_signal('character_attacked', res)
        for it in self.inventory_items:
            it.check_triggers('character_damaged', now, amount=res.health_damage)
            if self.opponent is not None and self.opponent.is_dead:
                break
        # 信号（connectForCombat 注册的回调）
        self.emit_signal('character_damaged', res.health_damage, trigger_event)
        if self.opponent is not None and self.opponent.is_dead:
            self.opponent.emit_signal('character_has_died', trigger_event)

        if self.cur_health <= 0:
            self.death()

        # 反伤 Spikes
        self.apply_spikes(res)

        return res

    # ================ 反伤 / 吸血 ================
    def apply_spikes(self, damage_res: DamageResult):
        """applySpikes — 受击后反伤（对齐 Character.gd）"""
        if self.get_spikes() > 0 and damage_res.can_trigger_spikes():
            if damage_res.damage_source.has_type(DS_Type.RANGED):
                spikes_limit = self.ranged_spikes_limit
            else:
                spikes_limit = self.melee_spikes_limit
            if damage_res.damage_source.has_type(DS_Type.EFFECT):
                spikes_limit = max(self.effect_spikes_limit, spikes_limit)
            spike_dam = min(self.get_spikes(), int(round(damage_res.damage * spikes_limit)))
            if spike_dam > 0 and self.opponent is not None:
                self.spike_damage_source.set_damage(spike_dam)
                self.opponent.take_damage(self.spike_damage_source, origin_label="spikes")
                self.stats["spikes_dealt"] += spike_dam
                if self.log:
                    self.log.spike_damage(self.log.current_time, self.name(),
                                          self.opponent.name(), spike_dam)

    def apply_vampirism(self, damage_res: DamageResult):
        """applyVampirism — 攻击吸血（对齐 Character.gd）"""
        if self.get_vampirism() > 0 and damage_res.can_trigger_vampirism():
            if damage_res.damage_source.has_type(DS_Type.RANGED):
                vamp_limit = self.ranged_vampirism_limit
            else:
                vamp_limit = self.melee_vampirism_limit
            heal_amount = min(self.get_vampirism(),
                              int(round(damage_res.damage * vamp_limit)))
            if heal_amount > 0:
                self.heal(heal_amount, origin="Vampirism")
                self.stats["vampirism_heal"] += heal_amount

    # ================ 治疗 ================
    def heal(self, amount, origin=None, trigger_event=None) -> int:
        """heal — 治疗（含不治反伤，对齐 Character.gd）"""
        now = getattr(trigger_event, 't', None)
        if now is None and self.log is not None:
            now = self.log.current_time
        amount = int(round(amount * self.get_healing_efficiency()))
        missing = self.get_max_health() - self.cur_health
        overheal = max(0, amount - missing)
        self.cur_health += amount
        self.cur_health = min(self.cur_health, self.get_max_health())
        self.stats["healing_done"] += amount

        if self.log:
            self.log.heal(now, self.name(), amount, overheal, origin)

        # 触发器：治疗时检查（character_healed，如 Pestilence Flask 毒反击）
        for it in self.inventory_items:
            it.check_triggers('character_healed', now, amount=amount)
            if self.opponent is not None and self.opponent.is_dead:
                break
        self.emit_signal('character_healed', amount, trigger_event)

        if self.get_unhealing() > 0:
            unhealing = int(self._ceil(
                amount * self.get_unhealing() * (1 + self.typed_damage_factors[DS_Type.UNHEALING])))
            if unhealing > 0 and self.opponent is not None:
                us = DamageSource().init(None, DS_Type.UNHEALING)
                us.flags = UNHEALING_FLAGS
                us.set_damage(unhealing)
                self.opponent.take_damage(us, origin_label="unhealing")
                if self.log:
                    self.log.unhealing(now, self.name(), self.opponent.name(), unhealing)
        return overheal

    def heal_to_full(self):
        self.cur_health = self.get_max_health()

    def set_current_health_safe(self, hp: float):
        """结算用：直接设置 HP（不触发死亡判定，不记录日志）"""
        self.cur_health = hp

    def get_healing_efficiency(self) -> float:
        return max(0.0, self.healing_efficiency)

    def get_unhealing(self) -> float:
        return self.unhealing_amount

    # ================ 体力 ================
    def gain_stamina(self, amount, item=None, trigger_event=None):
        self.cur_stamina += amount
        if not self.allow_stamina_overflow:
            self.clamp_stamina()
        if self.log:
            self.log.stamina_gain(getattr(trigger_event, 't', self.log.current_time),
                                  self.name(), amount, item.key if item else None)

    def add_stamina(self, amount):
        self.cur_stamina += amount
        self.clamp_stamina()

    def clamp_stamina(self):
        self.cur_stamina = max(0.0, min(self.cur_stamina, self.get_max_stamina()))

    def fill_up_stamina(self):
        self.add_stamina(self.max_stamina)

    def use_stamina(self, amount) -> int:
        """返回 0=Sufficient 1=Insufficient（对齐 StaminaResult）"""
        # 触发器：消耗体力前检查（character_pre_use_stamina，如 Heroic Potion）
        if self.log:
            now = self.log.current_time
            for it in self.inventory_items:
                it.check_triggers('character_pre_use_stamina', now, amount=amount)
                if self.opponent is not None and self.opponent.is_dead:
                    break
        self.emit_signal('character_pre_use_stamina', amount, None)
        if self.cur_stamina >= amount:
            self.cur_stamina = max(self.cur_stamina - amount, 0)
            self.clamp_stamina()
            return 0
        else:
            self.clamp_stamina()
            return 1

    def drain_stamina(self, amount, item=None, trigger_event=None):
        drained = min(self.cur_stamina, amount)
        self.cur_stamina -= drained
        if self.log:
            self.log.stamina_drain(getattr(trigger_event, 't', self.log.current_time),
                                   self.opponent.name() if self.opponent else None,
                                   self.name(), drained, item.key if item else None)
        return drained

    def gain_max_stamina_temporary(self, amount, filled=True):
        if amount != 0:
            self.temporary_max_stamina += amount
            if filled and amount > 0:
                self.cur_stamina += amount
            self.clamp_stamina()

    # ================ buff 栈 ================
    def _log_stack(self, buff_type: int, amount: int, target_name: str,
                   origin: str = None, permanent: bool = True, duration=None,
                   resisted=False, reflected=False, protected=False, gain=True):
        if self.log is None:
            return
        name = BuffType.INV.get(buff_type, str(buff_type))
        now = self.log.current_time
        if gain:
            self.log.stack_gain(now, target_name, target_name, origin, name,
                                amount, permanent, duration, None, resisted,
                                reflected, protected, buff_type)
        else:
            self.log.stack_lose(now, target_name, target_name, origin, name,
                                amount, buff_type=buff_type)

    def get_stacks(self, buff_type: int) -> int:
        return self.buffs[buff_type].get_stacks()

    def set_stacks(self, buff_type: int, amount: int):
        self.buffs[buff_type].set_stacks(amount)

    def gain_stacks(self, buff_type: int, amount: int, item=None, trigger_event=None) -> int:
        rng = getattr(self, '_rng', None)
        buff = self.buffs[buff_type]
        gained = buff.gain_temporary(amount, -1, item, trigger_event, rng=rng)
        if gained > 0 and self.log:
            self._log_stack(buff_type, gained, self.name(),
                            item.key if item else None, permanent=True,
                            resisted=buff.last_resisted, reflected=buff.last_reflected)
        if gained > 0:
            if not is_buff(buff_type):
                self._emit_debuff_changed(buff_type, gained, trigger_event, item)
            elif buff_type == BuffType.BLOCK:
                self.emit_signal('character_block_changed', self.get_block(),
                                 trigger_event or _OriginEvent(item))
            else:
                from .buff import BuffType as _BT
                name = _BT.INV.get(buff_type, '').lower()
                self.emit_signal(f'character_{name}_changed', gained,
                                 trigger_event or _OriginEvent(item))
        return gained

    def gain_stacks_temporary(self, buff_type: int, amount: int, duration: float,
                              item=None, trigger_event=None, reflect: bool = False) -> int:
        rng = getattr(self, '_rng', None)
        buff = self.buffs[buff_type]
        gained = buff.gain_temporary(amount, duration, item, trigger_event,
                                      reflect, rng=rng)
        if gained > 0 and self.log:
            self._log_stack(buff_type, gained, self.name(),
                            item.key if item else None, permanent=False,
                            duration=duration, reflected=reflect,
                            resisted=buff.last_resisted)
        return gained

    def lose_stacks(self, buff_type: int, amount: int, item=None, trigger_event=None,
                    used: bool = False) -> int:
        buff = self.buffs[buff_type]
        lost = buff.lose_stacks(amount, item, trigger_event, used)
        if lost > 0 and self.log:
            self._log_stack(buff_type, lost, self.name(),
                            item.key if item else None, gain=False,
                            protected=buff.last_protected)
        if lost > 0:
            if not is_buff(buff_type):
                self._emit_debuff_changed(buff_type, -lost, trigger_event, item)
            elif buff_type == BuffType.BLOCK:
                self.emit_signal('character_block_changed', self.get_block(),
                                 trigger_event or _OriginEvent(item))
            else:
                from .buff import BuffType as _BT
                name = _BT.INV.get(buff_type, '').lower()
                self.emit_signal(f'character_{name}_changed', -lost,
                                 trigger_event or _OriginEvent(item))
        return lost

    def use_stacks(self, buff_type: int, amount: int, item=None, trigger_event=None) -> int:
        return self.lose_stacks(buff_type, amount, item, trigger_event, used=True)

    def set_stacks_logged(self, buff_type: int, amount: int, item=None, trigger_event=None):
        cur = self.get_stacks(buff_type)
        if amount < cur:
            self.lose_stacks(buff_type, cur - amount, item, trigger_event)
        elif amount > cur:
            self.gain_stacks(buff_type, amount - cur, item, trigger_event)

    # Block
    def get_block(self) -> int:
        return self.get_stacks(BuffType.BLOCK)

    def set_block(self, amount: int):
        self.set_stacks(BuffType.BLOCK, amount)

    def gain_block(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.BLOCK, amount, item, trigger_event)

    def lose_block(self, amount, item=None, trigger_event=None):
        return self.lose_stacks(BuffType.BLOCK, amount, item, trigger_event)

    def use_block(self, amount, item=None, trigger_event=None):
        return self.use_stacks(BuffType.BLOCK, amount, item, trigger_event)

    # Spikes
    def lose_spikes(self, amount, item=None, trigger_event=None):
        return self.lose_stacks(BuffType.SPIKES, amount, item, trigger_event)

    def get_spikes(self) -> int:
        return self.get_stacks(BuffType.SPIKES)

    def gain_spikes(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.SPIKES, amount, item, trigger_event)

    # Vampirism
    def get_vampirism(self) -> int:
        return self.get_stacks(BuffType.VAMPIRISM)

    def gain_vampirism(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.VAMPIRISM, amount, item, trigger_event)

    # Poison
    def get_poison(self) -> int:
        return self.get_stacks(BuffType.POISON)

    def gain_poison(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.POISON, amount, item, trigger_event)

    def cleanse_poison(self, amount: int, item=None, trigger_event=None) -> int:
        return self.lose_stacks(BuffType.POISON, amount, item, trigger_event)

    # Regeneration
    def get_regeneration(self) -> int:
        return self.get_stacks(BuffType.REGENERATION)

    def gain_regeneration(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.REGENERATION, amount, item, trigger_event)

    # Lucky / Blind
    def get_lucky(self) -> int:
        return self.get_stacks(BuffType.LUCKY)

    def gain_lucky(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.LUCKY, amount, item, trigger_event)

    def get_blind(self) -> int:
        return self.get_stacks(BuffType.BLIND)

    def gain_blind(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.BLIND, amount, item, trigger_event)

    # Mana
    def get_mana(self) -> int:
        return self.get_stacks(BuffType.MANA)

    def gain_mana(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.MANA, amount, item, trigger_event)

    def use_mana(self, amount: int, item=None, trigger_event=None):
        return self.use_stacks(BuffType.MANA, amount, item, trigger_event)

    def lose_mana(self, amount: int, item=None, trigger_event=None):
        """removeMana 的引擎对应：从自身扣除 mana（对齐 Item.gd removeMana）。"""
        return self.use_stacks(BuffType.MANA, amount, item, trigger_event)

    def try_use_mana(self, amount: int, item=None, trigger_event=None):
        if self.get_mana() >= amount:
            self.use_mana(amount, item, trigger_event)
            return True
        return False

    # Empower
    def get_empower(self) -> int:
        return self.get_stacks(BuffType.EMPOWER)

    def gain_empower(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.EMPOWER, amount, item, trigger_event)

    def lose_empower(self, amount: int, item=None, trigger_event=None):
        return self.lose_stacks(BuffType.EMPOWER, amount, item, trigger_event)

    # Heat / Cold
    def get_heat(self) -> int:
        return self.get_stacks(BuffType.HEAT)

    def gain_heat(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.HEAT, amount, item, trigger_event)

    def get_cold(self) -> int:
        return self.get_stacks(BuffType.COLD)

    def gain_cold(self, amount: int, item=None, trigger_event=None):
        return self.gain_stacks(BuffType.COLD, amount, item, trigger_event)

    # ================ 状态修改 ================
    def change_damage_resistance(self, amount: float):
        self.damage_resistance += amount

    def change_damage_reduction(self, amount: int):
        self.damage_reduction += amount

    def change_dodge_stacks(self, amount: int):
        self.dodge_stacks = max(0, self.dodge_stacks + amount)

    def change_crit_resistance(self, amount: float):
        self.crit_resistance += amount

    def change_stun_resistance(self, amount: float):
        self.stun_resistance += amount

    def gain_crit_resist_stacks(self, num: int):
        self.crit_resist_stacks += num

    def gain_crit_tokens(self, amount):
        self.crit_tokens += amount

    def use_crit_token(self):
        self.crit_tokens -= 1

    def get_crit_tokens(self) -> int:
        return self.crit_tokens

    def give_unhealing(self, amount: float):
        self.unhealing_amount += amount

    def reduce_unhealing(self, amount: float):
        self.unhealing_amount = max(0.0, self.unhealing_amount - amount)

    def add_healing_efficiency(self, amount: float):
        self.healing_efficiency += amount

    def reduce_healing_efficiency(self, amount: float):
        self.healing_efficiency -= amount

    def give_stamina_regeneration(self, amount):
        self.stamina_regen += amount

    def change_buff_protection_chance(self, amount):
        self.change_buff_protect_stacks(int(round(amount)))

    def change_debuff_protection_chance(self, amount):
        self.change_buff_protect_stacks(int(round(amount)))

    def change_buff_protection_chance_all(self, amount):
        self.change_buff_protect_stacks(int(round(amount)))

    def change_poison_crit_chance_percent(self, amount):
        self.poison_damage_source.crit_chance_percent += amount

    def change_spikes_crit_chance_percent(self, amount):
        self.spike_damage_source.crit_chance_percent += amount

    def get_missing_health(self) -> float:
        return max(0, self.get_max_health() - self.cur_health)

    def is_battle_raging(self) -> bool:
        return bool(self.battle_rage_active)

    def add_battle_rage_duration(self, amount):
        self.battle_rage_active = True

    def count_socketed_gems(self) -> int:
        """countSocketedGems — 统计背包内宝石数"""
        return sum(len(it.get_gems_no_null()) for it in self.inventory_items)

    def get_debuff_stacks(self, debuff_type=None) -> int:
        from .buff import BuffType
        if debuff_type is not None:
            return self.get_stacks(debuff_type)
        return sum(self.get_stacks(t) for t in (BuffType.POISON, BuffType.BLIND, BuffType.COLD))

    def get_buff_stacks(self, buff_type=None) -> int:
        from .buff import BuffType
        if buff_type is not None:
            return self.get_stacks(buff_type)
        return sum(self.get_stacks(t) for t in range(BuffType.BLOCK, BuffType.HEAT + 1))

    def start_battle_rage(self, *a, **k):
        self.battle_rage_active = True

    def change_typed_damage_factor(self, damage_type: int, amount: float):
        self.typed_damage_factors[damage_type] = self.typed_damage_factors.get(damage_type, 0.0) + amount

    def change_effect_damage_factor(self, amount: float):
        self.typed_damage_factors[DS_Type.EFFECT] += amount
        self.typed_damage_factors[DS_Type.UNHEALING] += amount

    def change_melee_spikes_limit(self, amount):
        self.melee_spikes_limit += amount

    def change_ranged_spikes_limit(self, amount):
        self.ranged_spikes_limit += amount

    def change_effect_spikes_limit(self, amount):
        self.effect_spikes_limit += amount

    def change_melee_vampirism_limit(self, amount):
        self.melee_vampirism_limit += amount

    def change_ranged_vampirism_limit(self, amount):
        self.ranged_vampirism_limit += amount

    def change_empower_damage(self, amount):
        self.empower_damage += amount

    def change_debuff_resist_stacks(self, amount):
        self.debuff_resist_stacks = max(0, self.debuff_resist_stacks + amount)

    def change_debuff_reflect_stacks(self, amount):
        self.debuff_reflect_stacks = max(0, self.debuff_reflect_stacks + amount)

    def change_buff_protect_stacks(self, amount):
        self.buff_protect_stacks += amount

    def change_resist_chance(self, buff_type: int, chance: float):
        self.buffs[buff_type].change_resist_chance(chance)

    def change_resist_stacks(self, buff_type: int, amount: int):
        self.buffs[buff_type].change_resist_stacks(amount)

    def change_reflect_chance(self, buff_type: int, chance: float):
        self.buffs[buff_type].change_reflect_chance(chance)

    def change_debuff_resist_chances(self, chance: float):
        for t in range(BuffType.POISON, BuffType.COLD + 1):
            self.change_resist_chance(t, chance)

    def change_debuff_reflect_chances(self, chance: float):
        for t in range(BuffType.POISON, BuffType.COLD + 1):
            self.change_reflect_chance(t, chance)

    def change_all_debuffs_reflect_chance(self, amount):
        """Item.gd changeAllDebuffsReflectChance — 对所有减益改变反弹概率。"""
        self.change_debuff_reflect_chances(amount)

    def is_vulnerable(self) -> bool:
        """Item.gd isVulnerable — 未被无敌覆盖时为真。"""
        return not self.invulnerable

    def change_buff_nullify_chances(self, chance: float):
        for t in range(BuffType.BLOCK, BuffType.HEAT + 1):
            self.change_resist_chance(t, chance)

    def add_fatigue_damage(self, amount):
        self.bonus_fatigue_damage += amount

    def get_bonus_fatigue_damage(self) -> int:
        return self.bonus_fatigue_damage

    def take_fatigue_damage(self, damage: int = 1, now: float = 0.0):
        """takeFatigueDamage — 疲劳伤害（Game.fatigueDamageSource: type=FATIGUE, flags=CanBeBlocked）"""
        fs = DamageSource().init(self, DS_Type.FATIGUE)
        fs.flags = DS_Flags.CAN_BE_BLOCKED
        fs.set_damage(damage)
        self.take_damage(fs, origin_label="fatigue")

    # ================ 眩晕 / 无敌 ================
    def stun(self, duration, item=None, trigger_event=None):
        if self.stun_resisted():
            if self.log:
                self.log.stun_resisted(getattr(trigger_event, 't', self.log.current_time),
                                       self.opponent.name() if self.opponent else None,
                                       self.name(), item.key if item else None)
            return False
        self.stunned_duration = max(self.stunned_duration, duration)
        if self.log:
            self.log.stun(getattr(trigger_event, 't', self.log.current_time),
                          self.opponent.name() if self.opponent else None,
                          self.name(), duration, item.key if item else None)
        self.emit_signal('character_stunned', trigger_event)
        return True

    def stun_resisted(self) -> bool:
        return self.stun_resistance_rng.roll_percent(self.stun_resistance)

    def crit_resisted(self) -> bool:
        resisted = self.crit_resistance_rng.roll_percent(self.crit_resistance)
        if not resisted:
            if self.crit_resist_stacks > 0:
                self.crit_resist_stacks -= 1
                return True
        return resisted

    def make_invulnerable(self, dur, item=None, trigger_event=None):
        was_invulnerable = self.invulnerable
        self.invulnerable = True
        self.invulnerability_remaining = max(self.invulnerability_remaining, float(dur))
        if self.log and not was_invulnerable:
            self.log.invulnerable_start(getattr(trigger_event, 't', self.log.current_time),
                                        self.name(), dur, item.key if item else None)

    def invulnerability_ended(self):
        if not self.invulnerable:
            return
        self.invulnerable = False
        self.invulnerability_remaining = 0.0
        if self.log:
            self.log.invulnerable_end(self.log.current_time, self.name())

    # ================ 生命修改 ================
    def change_max_health_temporary(self, amount, item=None, trigger_event=None):
        if amount != 0:
            self.temporary_max_health += amount
            self.cur_health += amount

    def apply_temporary_max_health_gain(self, amount) -> int:
        return int(round(amount * self.temporary_max_health_gain))

    def change_max_health_gain(self, amount):
        self.temporary_max_health_gain += amount

    def give_max_health(self, amount):
        self.max_health += amount
        self.cur_health += amount

    def reduce_max_health(self, amount):
        self.max_health = max(1, self.max_health - amount)
        self.cur_health = min(self.max_health, self.cur_health)

    def set_max_stamina(self, s):
        self.max_stamina = s
        self.cur_stamina = s

    def give_max_stamina(self, amount):
        self.max_stamina += amount
        self.cur_stamina += amount

    # ================ buff 相关修正 ================
    def get_buff_damage_mod(self) -> int:
        return self.get_empower() * self.empower_damage

    def get_buff_accuracy_mod(self) -> float:
        return (self.get_lucky() - self.get_blind()) * 5

    def get_stack_speed_mods(self) -> float:
        return (self.get_heat() - self.get_cold()) * 0.02

    # ================ 杂项 ================
    def death(self):
        if self.is_dead:
            return
        self.is_dead = True
        if self.log:
            self.log.death(self.log.current_time, self.name())

    def get_typed_damage_factor(self, dtype: int) -> float:
        return self.typed_damage_factors.get(dtype, 0.0)

    def get_items(self):
        return self.inventory_items

    def get_buff_snapshot(self) -> dict:
        out = {}
        for t, b in self.buffs.items():
            if b.get_stacks() > 0:
                out[BuffType.INV.get(t, str(t))] = b.get_stacks()
        return out

    @staticmethod
    def _ceil(x: float) -> int:
        import math
        return math.ceil(x)
