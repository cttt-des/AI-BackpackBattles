# -*- coding: utf-8 -*-
"""effects.py — 效果 DSL 执行器（对齐解包 Items/*.gd 的 doCooldownEffect 语义）

将 battle_items.json 中声明式的 effect/effects/triggers 翻译为实际的
角色/物品操作。效果类型与解包脚本中的常见调用一一对应：

  giveBlock / giveStamina / giveLucky / giveVampirism / giveSpikes
  giveRegeneration / giveMana / giveEmpower / giveHeat / giveCold
  inflictPoison / inflictBlind / selfInflictPoison / cleansePoison
  heal / dealEffectDamage / stun / drainStamina / giveMaxHealth
  giveCritTokens / changeDodgeStacks / changeDamageResistance
  changeDamageReduction / fillUpStamina / giveStacks / attack
"""
from __future__ import annotations

import random
from typing import Any, Dict, List, Optional, TYPE_CHECKING

from .buff import BuffType

if TYPE_CHECKING:
    from .item import Item


class EffectExecutor:
    """把效果 DSL 对象翻译为角色/物品操作"""

    def __init__(self, item: 'Item'):
        self.item = item

    # ---------------- 入口 ----------------
    def execute(self, effect: Any, now: float):
        if not effect:
            return
        # 支持单个效果 dict 或 效果列表（on_start / doCooldownEffect 多语句）
        if isinstance(effect, list):
            for sub in effect:
                self.execute(sub, now)
            return
        if not isinstance(effect, dict):
            return
        etype = effect.get('type')
        handler = getattr(self, f'_ef_{etype}', None)
        if handler is None:
            return  # 未实现的效果，静默跳过
        handler(effect, now)

    # ---------------- 目标解析 ----------------
    @property
    def ch(self):
        return self.item.character_()

    @property
    def opp(self):
        return self.item.opponent()

    def _target(self, effect: Dict[str, Any]):
        return self.opp if effect.get('target') == 'opponent' else self.ch

    def _buff_type(self, effect: Dict[str, Any]) -> int:
        name = effect.get('buff')
        if isinstance(name, int):
            return name
        return BuffType.NAMES.get(name, BuffType.BLOCK)

    def _amount(self, effect: Dict[str, Any], key: str = 'amount') -> int:
        return int(effect.get(key, 0))

    def _chance_ok(self, effect: Dict[str, Any]) -> bool:
        chance = effect.get('chance')
        if chance is None:
            return True
        return self.item.roll_chance(chance)

    # ---------------- 效果实现 ----------------
    def _ef_attack(self, effect, now):
        """武器攻击（走 Item.attack 模板）"""
        if self.item.use_stamina() == 0:
            self.item.attack(now)

    def _ef_attack_no_stamina(self, effect, now):
        self.item.attack(now)

    def _ef_deal_effect_damage(self, effect, now):
        if not self._chance_ok(effect):
            return
        dmg = self._amount(effect)
        self.item.deal_effect_damage(dmg, now)

    def _ef_heal(self, effect, now):
        if not self._chance_ok(effect):
            return
        amt = self._amount(effect)
        self.ch.heal(amt, origin=self.item.key)

    def _ef_gain_stamina(self, effect, now):
        amt = effect.get('amount', 1)
        self.ch.gain_stamina(amt, self.item)

    def _ef_fill_stamina(self, effect, now):
        self.ch.fill_up_stamina()

    def _ef_gain_stacks(self, effect, now):
        if not self._chance_ok(effect):
            return
        btype = self._buff_type(effect)
        amt = self._amount(effect)
        target = self._target(effect)
        duration = effect.get('duration')
        if duration:
            target.gain_stacks_temporary(btype, amt, duration, self.item)
        else:
            target.gain_stacks(btype, amt, self.item)

    def _ef_gain_stacks_self(self, effect, now):
        effect = dict(effect)
        effect['target'] = 'self'
        self._ef_gain_stacks(effect, now)

    def _ef_gain_stacks_opponent(self, effect, now):
        effect = dict(effect)
        effect['target'] = 'opponent'
        self._ef_gain_stacks(effect, now)

    def _ef_give_block(self, effect, now):
        amt = effect.get('amount', self.item.data.get('block', 0) or 0)
        if not amt:
            amt = self.item.get_p('block')
        self.ch.gain_block(int(amt), self.item)

    def _ef_give_spikes(self, effect, now):
        self.ch.gain_spikes(self._amount(effect), self.item)

    def _ef_give_vampirism(self, effect, now):
        self.ch.gain_vampirism(self._amount(effect), self.item)

    def _ef_give_regeneration(self, effect, now):
        self.ch.gain_regeneration(self._amount(effect), self.item)

    def _ef_give_lucky(self, effect, now):
        self.ch.gain_lucky(self._amount(effect), self.item)

    def _ef_give_mana(self, effect, now):
        self.ch.gain_mana(self._amount(effect), self.item)

    def _ef_give_empower(self, effect, now):
        self.ch.gain_empower(self._amount(effect), self.item)

    def _ef_give_heat(self, effect, now):
        self.ch.gain_heat(self._amount(effect), self.item)

    def _ef_give_cold(self, effect, now):
        self.ch.gain_cold(self._amount(effect), self.item)

    def _ef_inflict_poison(self, effect, now):
        self.opp.gain_poison(self._amount(effect), self.item)

    def _ef_self_inflict_poison(self, effect, now):
        self.ch.gain_poison(self._amount(effect), self.item)

    def _ef_inflict_blind(self, effect, now):
        self.opp.gain_blind(self._amount(effect), self.item)

    def _ef_cleanse_poison(self, effect, now):
        self.ch.cleanse_poison(self._amount(effect), self.item)

    def _ef_cleanse_debuff(self, effect, now):
        btype = self._buff_type(effect)
        if btype in (BuffType.POISON, BuffType.BLIND, BuffType.COLD):
            self.ch.lose_stacks(btype, self._amount(effect), self.item)

    def _ef_drain_stamina(self, effect, now):
        self.opp.drain_stamina(effect.get('amount', 1), self.item)

    def _ef_stun(self, effect, now):
        if not self._chance_ok(effect):
            return
        self.opp.stun(effect.get('duration', 1.0), self.item)

    def _ef_give_max_health(self, effect, now):
        self.ch.change_max_health_temporary(self._amount(effect), self.item)

    def _ef_give_max_stamina(self, effect, now):
        self.ch.gain_max_stamina_temporary(self._amount(effect))

    def _ef_give_crit_tokens(self, effect, now):
        self.ch.gain_crit_tokens(self._amount(effect))

    def _ef_give_dodge(self, effect, now):
        self.ch.change_dodge_stacks(self._amount(effect))

    def _ef_change_damage_resistance(self, effect, now):
        self.ch.change_damage_resistance(effect.get('amount', 0))

    def _ef_change_damage_reduction(self, effect, now):
        self.ch.change_damage_reduction(self._amount(effect))

    def _ef_change_crit_resistance(self, effect, now):
        self.ch.change_crit_resistance(effect.get('amount', 0))

    def _ef_give_crit_resist_stacks(self, effect, now):
        self.ch.gain_crit_resist_stacks(self._amount(effect))

    def _ef_change_stun_resistance(self, effect, now):
        self.ch.change_stun_resistance(effect.get('amount', 0))

    def _ef_give_unhealing(self, effect, now):
        self.ch.give_unhealing(effect.get('amount', 0))

    def _ef_give_healing_efficiency(self, effect, now):
        self.ch.add_healing_efficiency(effect.get('amount', 0))

    def _ef_empower_weapons(self, effect, now):
        self.ch.gain_empower(self._amount(effect), self.item)

    def _ef_change_typed_damage_factor(self, effect, now):
        dtype_map = {'melee': 0, 'ranged': 1, 'effect': 2}
        dtype = dtype_map.get(effect.get('damage_type'), 2)
        self.ch.change_typed_damage_factor(dtype, effect.get('amount', 0))

    def _ef_change_effect_damage_factor(self, effect, now):
        self.ch.change_effect_damage_factor(effect.get('amount', 0))

    def _ef_change_melee_spikes_limit(self, effect, now):
        self.ch.change_melee_spikes_limit(effect.get('amount', 0))

    def _ef_change_melee_vampirism_limit(self, effect, now):
        self.ch.change_melee_vampirism_limit(effect.get('amount', 0))

    def _ef_steal_life(self, effect, now):
        """stealLife — 吸血（lifesteal 因子）"""
        dmg = self._amount(effect)
        lifesteal = effect.get('lifesteal', 1.0)
        res = self.item.deal_effect_damage(dmg, now)
        if res.has_hit():
            heal = int(round(res.damage * lifesteal))
            if heal > 0:
                self.ch.heal(heal, origin=self.item.key)

    def _ef_random_buff(self, effect, now):
        options = effect.get('options', ['block', 'lucky', 'regen'])
        pick = options[self.item.chance_rng.randrange(len(options))]
        btype = BuffType.NAMES.get(pick, BuffType.BLOCK)
        amt = effect.get('amount', 1)
        target = self._target(effect)
        target.gain_stacks(btype, amt, self.item)

    def _ef_random_debuff(self, effect, now):
        options = effect.get('options', ['poison', 'blind', 'cold'])
        pick = options[self.item.chance_rng.randrange(len(options))]
        btype = BuffType.NAMES.get(pick, BuffType.POISON)
        amt = effect.get('amount', 1)
        self.opp.gain_stacks(btype, amt, self.item)

    def _ef_use_mana(self, effect, now):
        """耗蓝效果：若蓝足够则消耗并执行次效果，否则跳过"""
        mana = effect.get('mana', 0)
        if self.ch.get_mana() >= mana:
            self.ch.use_mana(mana, self.item)
            sub = effect.get('then')
            if sub:
                self.execute(sub, now)

    def _ef_use_empower(self, effect, now):
        amt = effect.get('amount', 1)
        self.ch.use_stacks(BuffType.EMPOWER, amt, self.item)

    def _ef_use_heat(self, effect, now):
        amt = effect.get('amount', 1)
        self.ch.use_stacks(BuffType.HEAT, amt, self.item)

    def _ef_fatigue_damage(self, effect, now):
        """inflictFatigueDamage — 增加对手疲劳伤害"""
        self.opp.add_fatigue_damage(self._amount(effect))
        self.opp.take_fatigue_damage(0, now)

    def _ef_give_invulnerable(self, effect, now):
        self.ch.make_invulnerable(effect.get('duration', 1.0), self.item)

    def _ef_advance_cooldown_percent(self, effect, now):
        self.item.advance_cooldown_percent(effect.get('amount', 0))

    def _ef_advance_cooldown_seconds(self, effect, now):
        self.item.advance_cooldown_seconds(effect.get('amount', 0))

    def _ef_none(self, effect, now):
        pass
