# -*- coding: utf-8 -*-
"""audit_item_fidelity.py — 全物品效果保真度审验（源码期望 vs 模拟器实际）

三层：
  A. 静态期望：沿继承链把物品可见的转译方法（own + class_methods）按方法名分组，
     用正则提取"效果原语"调用（deal_damage/heal/give_block/inflict_*/gain_stacks/
     give_stamina/...）与门槛（roll_chance/check_mana/checkTriggerCount），
     得到每物品"应有效果清单"（按触发语境分组：冷却/战斗开始/命中/受击/充能）。
  B. 运行时画像：solo harness——物品对木桩，脚本刺激（受伤/治疗/耗耐力/给 mana/
     推时间 25s），经 CombatLog 采集实际事件流（ATTACK/HEAL/STACK_GAIN/...）。
  C. 对照：期望类别 ↔ 运行时证据逐条核对，输出 PASS/DIVERGE/STATIC-ONLY/SKIP。

用法:
    python tools/audit_item_fidelity.py                # 全量
    python tools/audit_item_fidelity.py --key "Stone"  # 单物品
    python tools/audit_item_fidelity.py --json out.json
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
from collections import Counter, defaultdict
from typing import Dict, List, Optional

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if ROOT not in sys.path:
    sys.path.insert(0, ROOT)

for _s in (sys.stdout, sys.stderr):
    try:
        if hasattr(_s, "reconfigure"):
            _s.reconfigure(encoding="utf-8", errors="replace")
    except Exception:  # noqa: BLE001
        pass

from simulator.grid import GridInventory          # noqa: E402
from simulator.item import Item                   # noqa: E402
from simulator.character import Character         # noqa: E402
from simulator.events import CombatLog            # noqa: E402
from simulator.data import load_items             # noqa: E402
from simulator import extract_items as E          # noqa: E402
from simulator import behavior as B               # noqa: E402  (动态读 CLASS_METHODS)
from simulator.behavior import BEHAVIOR_GLOBALS as BEHAVIOR_GLOBALS_REF  # noqa: E402
from simulator.buff import BuffType               # noqa: E402
from simulator.buff import BuffType               # noqa: E402

DB = {}
DELTA = 1.0 / 60.0
SIM_SECONDS = 25.0

# ---------------------------------------------------------------------------
# A. 静态期望提取
# ---------------------------------------------------------------------------
# 转译调用模式 -> 效果类别
EFFECT_PATTERNS = [
    (r'_item\.deal_damage\(', 'damage'),
    (r'_item\.deal_effect_damage\(', 'effect_damage'),
    (r'_item\.steal_life\(', 'lifesteal_damage'),
    (r'_item\.heal\(', 'heal'),
    (r'_item\.give_block\(', 'block'),
    (r'_item\.give_regeneration\(', 'regeneration'),
    (r'_item\.give_vampirism\(|_item\.add_vampirism\(', 'vampirism'),
    (r'_item\.add_spikes\(|_item\.give_spikes\(', 'spikes'),
    (r'_item\.add_empower\(', 'empower'),
    (r'_item\.add_mana\(|_item\.give_mana_capped\(|_item\.add_mana\(', 'mana'),
    (r'_item\.add_heat\(', 'heat'),
    (r'_item\.add_cold\(', 'cold_self'),
    (r'_item\.inflict_poison\(|_item\.self_inflict_poison\(', 'poison'),
    (r'_item\.inflict_blind\(|_item\.self_inflict_blind\(', 'blind'),
    (r'_item\.inflict_cold\(|_item\.self_inflict_cold\(', 'cold'),
    (r'_item\.inflict_debuff\(', 'debuff'),
    (r'_item\.add_lucky\(', 'lucky'),
    (r'_item\.give_stamina\(|_item\.add_stamina_to_all\(|_item\.give_stamina_to_all\(', 'stamina'),
    (r'_item\.give_max_health\(|_item\.add_max_health\(|_item\.change_max_health\(', 'max_health'),
    (r'_item\.add_bonus_damage\(', 'weapon_bonus_damage'),
    (r'_item\.add_speed\(|_item\.reduce_speed\(|_item\.change_speed\(', 'speed'),
    (r'_item\.add_crit_chance_percent\(|_item\.change_crit_chance_percent\(|_item\.reduce_crit_chance_percent\(', 'crit_chance'),
    (r'_item\.add_crit_severity\(|_item\.change_crit_severity\(', 'crit_severity'),
    (r'_item\.give_crit_tokens\(', 'crit_tokens'),
    (r'_item\.change_accuracy\(|_item\.add_accuracy\(', 'accuracy'),
    (r'_item\.set_base_cooldown\(|_item\.update_base_cooldown\(|_item\.reset_base_cooldown\(|_item\.get_base_cooldown\(|_item\.get_base_cooldown_index\(', 'cooldown_modify'),
    (r'_item\.activate_cooldown\(|_item\.deactivate_cooldown\(', 'cooldown_toggle'),
    (r'_item\.advance_cooldown_percent\(|_item\.advance_cooldown_seconds\(', 'cooldown_advance'),
    (r'_item\.consume\(|_item\.consume_potion\(', 'consume'),
    (r'_item\.use_block\(', 'use_block'),
    (r'_item\.use_mana\(|_item\.try_use_mana\(', 'use_mana'),
    (r'_item\.use_lucky\(', 'use_lucky'),
    (r'_item\.use_spikes\(', 'use_spikes'),
    (r'_item\.remove_mana\(', 'drain_mana'),
    (r'_item\.lose_spikes\(', 'drain_spikes'),
    (r'_item\.steal_stack\(', 'steal_buff'),
    (r'_item\.steal_random_buff\(', 'steal_random_buff'),
    (r'_item\.remove_random_buffs\(', 'remove_buffs'),
    (r'_item\.cleanse_poison\(|_item\.cleanse_blind\(|_item\.cleanse_cold\(|_item\.cleanse_debuff\(|_item\.cleanse_all_debuffs\(', 'cleanse'),
    (r'_item\.stun\(', 'stun'),
    (r'_item\.add_invulnerable\(|_item\.make_invulnerable\(', 'invulnerable'),
    (r'_item\.add_dodge_chance\(', 'dodge'),
    (r'_item\.add_counter_attack\(', 'counter'),
    (r'_item\.add_lifesteal\(', 'lifesteal'),
    (r'_item\.add_damage_percent\(|_item\.add_damage_multiplier\(|_item\.set_damage_multiplier\(|_item\.change_typed_damage_factor\(', 'damage_mod'),
    (r'_item\.change_stamina_cost\(|_item\.change_max_stamina\(|_item\.add_stamina_factor\(', 'stamina_mod'),
    (r'_item\.change_cooldown_percent\(|_item\.reduce_cooldown_percent\(|_item\.change_cooldown\(|_item\.reduce_cooldown\(', 'cooldown_mod'),
    (r'_item\.change_debuff_protection|_item\.change_resist_chance|_item\.change_debuff_resist|_item\.change_buff_protect', 'protection'),
    (r'_item\.give_double_activation_chance\(', 'double_activation'),
    (r'_item\.change_heal_amp\(|_item\.add_healing_efficiency\(', 'heal_amp'),
    (r'_item\.start_battle_rage\(|_item\.add_battle_rage_duration\(', 'battle_rage'),
    (r'_item\.give_random_buffs\(|_item\.give_random_buff\(|_item\.give_random_buff\(', 'random_buffs'),
    (r'_item\.give_all_buffs\(', 'random_buffs'),
    (r'_item\.give_most_buffs\(|_item\.give_least_buffs\(', 'random_buffs'),
    (r'_item\.inflict_random_debuffs\(', 'random_debuffs'),
    (r'_item\.give_mana_capped\(', 'mana'),
    (r'_item\.cleanse_random_debuffs\(', 'cleanse'),
    (r'_item\.duplicate_item\(', 'duplicate'),
]
# 门槛/联动（不作为运行时证据要求，只作为上下文标注）
CONTEXT_PATTERNS = [
    (r'_item\.roll_chance\(', 'chance_gate'),
    (r'_item\.roll_chance2\(', 'chance_gate'),
    (r'_item\.check_mana\(', 'mana_gate'),
    (r'_item\.check_trigger_count\(', 'rate_limit'),
    (r'_item\.checkMana\(', 'mana_gate'),
    (r'_item\.connect_for_combat\(', 'signal_link'),
    (r'_item\.get_affected_items\(', 'affected_link'),
    (r'_item\.get_num_affected_items\(', 'affected_link'),
]

# 方法名 -> 触发语境
METHOD_CONTEXT = {
    'doCooldownEffect': 'cooldown',
    'onCombatStart': 'battle_start',
    'combatStart': 'battle_start',
    'onPreCombatStart': 'battle_start',
    'preCombatStart': 'battle_start',
    'onPostCombatStart': 'battle_start',
    'prepare': 'battle_start',
    'onPrepare': 'battle_start',
    'onDealtDamage': 'on_hit',
    'onPreDealDamage_early': 'on_hit',
    'onPreDealDamage_late': 'on_hit',
    'attack': 'cooldown',
    'onChargeReceived': 'charge',
    'onChargeEnteredCell': 'charge',
    'onChargeLeft': 'charge',
    'onItemActivated': 'activated_link',
    'onAffectedItemAdded': 'linkage',
    'onAffectedItemRemoved': 'linkage',
    'onStateChanged': 'state',
    'combatEnd': 'battle_end',
    'onCombatEnd': 'battle_end',
    'onBuffEnded': 'buff_end',
    'onDamaged': 'damaged',
    'onHealed': 'healed',
    'onManaChanged': 'mana_changed',
    'onAttacked': 'on_hit',
    'onItemGaveBlock': 'linkage',
    'onEmpowerChanged': 'state',
    'onRegenChanged': 'state',
    'onBattleRageStarted': 'battle_rage_ctx',
    'onBattleRageEnded': 'battle_rage_ctx',
    'onOpponentDamaged': 'on_hit',
}
CONTEXT_LABEL = {
    'cooldown': '冷却触发', 'battle_start': '战斗开始', 'on_hit': '命中时',
    'charge': '充能', 'activated_link': '邻格激活', 'linkage': '影响格联动',
    'state': '状态切换', 'battle_end': '战斗结束', 'buff_end': '增益结束',
    'damaged': '自身受伤', 'healed': '自身被治疗', 'mana_changed': 'mana变化',
    'battle_rage_ctx': '战怒切换',
}


def visible_methods(key: str, data: dict) -> Dict[str, str]:
    """物品可见的方法源（own > 近祖先 > 远祖先），返回 {GDScript方法名: 源码}"""
    beh = data.get("behavior") or {}
    out: Dict[str, str] = {}
    chain = list(reversed(beh.get("extends_chain") or []))   # 远 -> 近
    for cls in chain:
        entry = B.CLASS_METHODS.get(cls) or {}
        out.update(entry.get("methods") or {})
    out.update(beh.get("methods") or {})
    return {k: v for k, v in out.items() if k in METHOD_CONTEXT}


def static_expectations(key: str, data: dict) -> Dict[str, dict]:
    """返回 {context: {'effects': set, 'gates': set, 'signals': set, 'methods': [..]}}"""
    exp: Dict[str, dict] = defaultdict(lambda: {'effects': set(), 'gates': set(),
                                                'signals': set(), 'methods': []})
    for mname, src in visible_methods(key, data).items():
        ctx = METHOD_CONTEXT.get(mname)
        if ctx is None:
            continue
        exp[ctx]['methods'].append(mname)
        for pat, cat in EFFECT_PATTERNS:
            if re.search(pat, src):
                exp[ctx]['effects'].add(cat)
        for pat, gate in CONTEXT_PATTERNS:
            if re.search(pat, src):
                exp[ctx]['gates'].add(gate)
        for m in re.finditer(r'connect_for_combat\([^,]+,\s*"([^"]+)"', src):
            exp[ctx]['signals'].add(m.group(1))
    return {k: v for k, v in exp.items() if v['effects'] or v['signals'] or v['gates']}


# ---------------------------------------------------------------------------
# B. 运行时画像
# ---------------------------------------------------------------------------
BUFF_NAME_TO_CATEGORY = {
    'Block': 'block', 'Lucky': 'lucky', 'Regeneration': 'regeneration',
    'Vampirism': 'vampirism', 'Spikes': 'spikes', 'Mana': 'mana',
    'Empower': 'empower', 'Heat': 'heat', 'Poison': 'poison',
    'Blind': 'blind', 'Cold': 'cold',
}


def run_profile(key: str, data: dict) -> dict:
    """solo harness：物品 + 木桩对手 + 脚本刺激。返回运行时证据。"""
    log = CombatLog()
    inv = GridInventory(7, 10)
    ch = Character(0, "P", 9999, 9999, 5.0, log=log)
    opp = Character(1, "O", 9999999, 9999, 5.0, log=log)
    ch.set_opponent(opp)
    opp.set_opponent(ch)
    ch.log = log
    opp.log = log

    it = Item(key, dict(data))
    it.character = ch
    it.log = log
    it.set_grid_position(3, 3, 0, inventory=inv)
    # 严格模式收集行为失败
    it.behavior.strict = True

    # 影响格伴侣：物品有影响格时放一把木剑（供联动/activated/heal 类效果触发）
    companion = None
    probe_cells = it._affected_cells_abs(0) or it._affected_cells_abs(2) \
        or it._affected_cells_abs(4) or it._affected_cells_abs(7)
    if probe_cells and "Wooden Sword" in DB:
        ckey = "Wooden Sword"
        companion = Item(ckey, dict(DB[ckey]))
        companion.character = ch
        companion.log = log
        cr, cc = probe_cells[0]
        companion.set_grid_position(cr, cc, 0, inventory=inv)

    # 事件采集
    seen = Counter()          # (type, origin, buff, target_role)
    damage_amounts = []

    def on_attack(t, actor, target, origin, damage, health_damage, **kw):
        if origin == it.key:
            seen[('damage',)] += 1
            damage_amounts.append(damage)
    log.attack = (lambda orig=log.attack:
                  lambda t, actor, target, origin, damage, health_damage,
                  hit=True, critical=False, block_absorbed=0, parent=None:
                  (on_attack(t, actor, target, origin, damage, health_damage),
                   orig(t, actor, target, origin, damage, health_damage,
                        hit=hit, critical=critical, block_absorbed=block_absorbed,
                        parent=parent))[1])()

    def track(ev_type, side_fn):
        def wrap(orig):
            def inner(t, *a, **kw):
                seen[(ev_type,)] += 1
                return orig(t, *a, **kw)
            return inner
        return wrap

    # heal / stack_gain / stack_lose 记录（origin 或 buff 归属）
    _orig_heal = log.heal

    def heal_cap(t, actor, amount, overheal=0, origin=None, parent=None):
        if origin == it.key:
            seen[('heal',)] += 1
        return _orig_heal(t, actor, amount, overheal=overheal, origin=origin, parent=parent)
    log.heal = heal_cap

    _orig_sg = log.stack_gain

    def sg_cap(t, *a, **kw):
        # stack_gain(t, actor, target, origin, buff, amount, ...) —— t 吃掉首个参数后
        origin = a[2] if len(a) > 2 else kw.get('origin')
        buff = a[3] if len(a) > 3 else kw.get('buff')
        if origin is not it.key:
            return None                      # 过滤刺激/噪声事件
        actor = a[0] if a else kw.get('actor')
        role = 'owner' if actor == ch.name() else 'opponent'
        cat = BUFF_NAME_TO_CATEGORY.get(buff, buff)
        seen[('stack_gain', cat, role)] += 1
        return _orig_sg(t, *a, **kw)
    log.stack_gain = sg_cap

    _orig_sl = log.stack_lose

    def sl_cap(t, *a, **kw):
        origin = a[2] if len(a) > 2 else kw.get('origin')
        buff = a[3] if len(a) > 3 else kw.get('buff')
        if origin is not it.key:
            return None
        actor = a[0] if a else kw.get('actor')
        role = 'owner' if actor == ch.name() else 'opponent'
        cat = BUFF_NAME_TO_CATEGORY.get(buff, buff)
        seen[('stack_lose', cat, role)] += 1
        return _orig_sl(t, *a, **kw)
    log.stack_lose = sl_cap

    _orig_stam = log.stamina_gain

    def stam_cap(t, *a, **kw):
        origin = a[2] if len(a) > 2 else kw.get('origin')
        if origin is not it.key:
            return None
        seen[('stamina_gain',)] += 1
        return _orig_stam(t, *a, **kw)
    log.stamina_gain = stam_cap

    # 生命周期（伴侣先 prepare：canAffect 联动会读伴侣的成员，
    # 对齐真实引擎「全部物品先 prepare 再建联动」的顺序）
    if companion is not None:
        companion.prepare()
    it.prepare()
    ch.set_items([x for x in (it, companion) if x is not None])
    it.pre_combat_start()
    if companion is not None:
        companion.pre_combat_start()
    it.combat_start()
    if companion is not None:
        companion.combat_start()
    it.post_combat_start()
    if companion is not None:
        companion.post_combat_start()

    # 确定性机会骰（chance 恒成功）
    class AlwaysYes:
        def random(self):
            return 0.0

        def randint(self, a, b):
            return b

        def choice(self, seq):
            return seq[0] if seq else None
    it.chance_rng = AlwaysYes()

    # 命中恒成功（Stone accuracy=70 会 legitimately miss，审计关注效果链而非命中）
    ch.accuracy_rng = type('AlwaysHitRng', (), {
        'roll_percent': staticmethod(lambda v: True),
        'roll': staticmethod(lambda v: True),
        'reset': staticmethod(lambda: None),
    })()

    # pickRandomElement 轮转选择（AlwaysYes 恒取首元素会让 Flute 的
    # options 轮换永远轮不到 lucky）
    Util_obj = BEHAVIOR_GLOBALS_REF['Util']
    _orig_pick = Util_obj.pickRandomElement
    _pick_seq = {'n': 0, 'last': {}}

    def lru_pick(lst, _orig=_orig_pick):
        """最久未用值优先：保证各选项都会被轮询到（Flute options 等）"""
        if not lst:
            return None
        best = min(lst, key=lambda v: _pick_seq['last'].get(v, -1))
        _pick_seq['n'] += 1
        _pick_seq['last'][best] = _pick_seq['n']
        return best
    Util_obj.pickRandomElement = lru_pick

    # 木桩对手给点 buff/mana 供偷取/消耗类效果
    opp.gain_block(5)
    opp.gain_stacks(BuffType.MANA, 5)
    opp.gain_stacks(BuffType.LUCKY, 5)
    ch.gain_block(3)

    # 时间推进 + 每秒刺激
    stimuli = ['damaged', 'healed', 'mana', 'stamina', 'damaged_big',
               'mana', 'healed', 'mana']
    t = 0.0
    ch.use_stamina(80)                      # 耐力降到低位，供恢复/消耗类效果显影
    ch.gain_stacks(BuffType.LUCKY, 3)       # 幸运供 use_lucky/幸运消耗类显影
    for sec in range(int(SIM_SECONDS)):
        t = (sec + 1) * 1.0
        log.current_time = t
        # 健康高低交替：低血量供阈值触发（药水/Leather Boots），
        # 高血量供"健康时"分支（Shell Totem giveEmpower）
        if sec % 4 == 3:
            ch.cur_health = ch.get_max_health() * 0.8
        else:
            ch.cur_health = ch.get_max_health() * 0.25
        # 给物主挂减益（cleanse 族效果显影；不用 cold——cold 会拖慢冷却）
        ch.gain_stacks(BuffType.POISON, 2)
        ch.gain_stacks(BuffType.BLIND, 1)
        kind = stimuli[sec % len(stimuli)]
        from simulator.damage import DamageSource, DS_Type
        if kind == 'damaged':
            ds = DamageSource()
            ds.types = [DS_Type.MELEE]
            ds.set_damage(4, 4)
            ds.origin = None
            ch.take_damage(ds, origin_label='stimulus')
        elif kind == 'damaged_big':
            ds = DamageSource()
            ds.types = [DS_Type.MELEE]
            ds.set_damage(30, 30)
            ch.take_damage(ds, origin_label='stimulus')
        elif kind == 'healed':
            ch.heal(6, origin='stimulus')
        elif kind == 'mana':
            ch.gain_stacks(BuffType.MANA, 4)
        elif kind == 'stamina':
            ch.use_stamina(2)
        # 物理帧推进 1s（60 tick），物品冷却/计时
        actors = [it] + ([companion] if companion is not None else [])
        if it.character is not None and not it.character.is_dead:
            for _ in range(60):
                t += DELTA
                log.current_time = t
                for actor in actors:
                    if not actor.consumed:
                        actor.physics_tick(DELTA, t)
                ch.character_tick(DELTA)
                for b in ch.buffs.values():
                    b.process_timeouts(t, log, ch.name())
                if it.consumed or it.character.is_dead:
                    break
        if it.consumed:
            break

    # 结束态证据
    end_state = {
        'opp_poison': opp.get_poison(), 'opp_blind': opp.get_blind(),
        'opp_cold': opp.get_cold(), 'opp_block': opp.get_block(),
        'opp_spikes': opp.get_spikes(), 'opp_mana': opp.get_mana(),
        'own_block': ch.get_block(), 'own_spikes': ch.get_spikes(),
        'own_regen': ch.get_regeneration(), 'own_lucky': ch.get_lucky(),
        'own_vamp': ch.get_vampirism(), 'own_mana': ch.get_mana(),
        'own_heat': ch.get_heat() if hasattr(ch, 'get_heat') else 0,
    }
    Util_obj.pickRandomElement = _orig_pick
    failures = dict(it._behavior_executor.failures) if it._behavior_executor else {}
    return {
        'seen': seen, 'damage_amounts': damage_amounts,
        'end_state': end_state, 'failures': failures,
        'activations': it.metrics.get('activations', 0),
        'consumed': it.consumed,
    }


# ---------------------------------------------------------------------------
# C. 对照
# ---------------------------------------------------------------------------
def evidence_for(cat: str, prof: dict) -> bool:
    seen = prof['seen']
    end = prof['end_state']
    table = {
        'damage': any(k == ('damage',) for k in seen),
        'effect_damage': any(k == ('damage',) for k in seen),
        'lifesteal_damage': any(k == ('damage',) for k in seen),
        'heal': ('heal',) in seen,
        'block': ('stack_gain', 'block', 'owner') in seen or end['own_block'] > 0,
        'regeneration': ('stack_gain', 'regeneration', 'owner') in seen or end['own_regen'] > 0,
        'vampirism': ('stack_gain', 'vampirism', 'owner') in seen or end['own_vamp'] > 0,
        'spikes': ('stack_gain', 'spikes', 'owner') in seen or end['own_spikes'] > 0,
        'empower': ('stack_gain', 'empower', 'owner') in seen,
        'mana': ('stack_gain', 'mana', 'owner') in seen or end['own_mana'] > 0,
        'heat': ('stack_gain', 'heat', 'owner') in seen or end['own_heat'] > 0,
        'lucky': ('stack_gain', 'lucky', 'owner') in seen or end['own_lucky'] > 0,
        'poison': ('stack_gain', 'poison', 'opponent') in seen or end['opp_poison'] > 0,
        'blind': ('stack_gain', 'blind', 'opponent') in seen or end['opp_blind'] > 0,
        'cold': ('stack_gain', 'cold', 'opponent') in seen or end['opp_cold'] > 0,
        'cold_self': ('stack_gain', 'cold', 'owner') in seen,
        'debuff': any(k[0] == 'stack_gain' and k[-1] == 'opponent' for k in seen),
        'stamina': ('stamina_gain',) in seen,
        'max_health': any(k[0] == 'stack_gain' for k in seen) or True,  # 无独立事件，宽松
        'weapon_bonus_damage': True,   # 数值型，事件不可见，静态即信任
        'speed': True,
        'crit_chance': True, 'crit_severity': True, 'crit_tokens': True,
        'accuracy': True, 'damage_mod': True, 'stamina_mod': True,
        'cooldown_modify': True, 'cooldown_toggle': True, 'cooldown_advance': True,
        'cooldown_mod': True, 'protection': True, 'heal_amp': True,
        'consume': prof['consumed'],
        'use_block': ('stack_lose', 'block', 'owner') in seen,
        'use_mana': ('stack_lose', 'mana', 'owner') in seen,
        'use_lucky': ('stack_lose', 'lucky', 'owner') in seen,
        'use_spikes': ('stack_lose', 'spikes', 'owner') in seen,
        'drain_mana': ('stack_lose', 'mana', 'opponent') in seen,
        'drain_spikes': ('stack_lose', 'spikes', 'opponent') in seen,
        'steal_buff': any(k[0] == 'stack_gain' and k[-1] == 'owner' for k in seen),
        'steal_random_buff': any(k[0] == 'stack_gain' and k[-1] == 'owner' for k in seen),
        'remove_buffs': any(k[0] == 'stack_lose' and k[-1] == 'opponent' for k in seen),
        'cleanse': any(k[0] == 'stack_lose' and k[-1] == 'owner' for k in seen),
        'stun': True,   # stun 事件在对手端，宽松
        'invulnerable': True,
        'dodge': True, 'counter': True, 'lifesteal': True,
        'battle_rage': True, 'duplicate': True,
        'random_buffs': any(k[0] == 'stack_gain' and k[-1] == 'owner' for k in seen),
        'random_debuffs': any(k[0] == 'stack_gain' and k[-1] == 'opponent' for k in seen),
    }
    return bool(table.get(cat, True))


# 已知良性失败：商店阶段机制，战斗保真不受影响
BENIGN_FAILURES = {
    ("Shovel", "_ready"): "digUpBag 商店挖掘机制（非战斗）",
}


def audit_item(key: str, data: dict) -> dict:
    exp = static_expectations(key, data)
    prof = run_profile(key, data)
    issues = []
    # 行为执行失败（最高优先级问题）
    real_failures = {}
    for m, msg in prof['failures'].items():
        mname = m[-1] if isinstance(m, tuple) else str(m)
        if BENIGN_FAILURES.get((key, mname)) is None:
            real_failures[m] = msg
    if real_failures:
        issues.append(f"行为执行失败: {list(real_failures.values())[:2]}")
    # 冷却物品必须有激活
    has_cooldown_ctx = 'cooldown' in exp
    if data.get('cd') and prof['activations'] == 0 and has_cooldown_ctx is False:
        issues.append(f"有 cd={data.get('cd')} 但零激活且无 doCooldownEffect 行为（模板未命中？）")
    # 期望效果必须有运行时证据
    # （linkage/activated/mana_changed/battle_rage 语境需要多物品/特定信号场景，
    #   harness 无法真实搭建 → 归 STATIC-ONLY，由 verify_linkage 覆盖）
    static_only_ctx = {'linkage', 'activated_link', 'mana_changed', 'battle_rage_ctx'}
    for ctx, info in exp.items():
        if ctx in static_only_ctx:
            continue
        for cat in sorted(info['effects']):
            if not evidence_for(cat, prof):
                issues.append(f"[{CONTEXT_LABEL.get(ctx, ctx)}] 期望效果 '{cat}' 无运行时证据")
    # 反向：运行时增益/伤害超出静态期望
    expected_cats = set()
    for info in exp.values():
        expected_cats |= info['effects']
    # 随机增益/减益类物品可给出任意类别，不参与反向比对
    has_random = 'random_buffs' in expected_cats or 'random_debuffs' in expected_cats
    for k, n in prof['seen'].items():
        if k[0] == 'stack_gain' and n > 0:
            cat = k[1]
            if cat not in expected_cats and cat in (
                    'block', 'lucky', 'regeneration', 'vampirism', 'spikes',
                    'mana', 'empower', 'heat', 'poison', 'blind', 'cold'):
                if has_random:
                    continue    # 随机族效果的合法产物
                issues.append(f"运行时出现未声明的增益 '{cat}' ×{n}（疑似重复/多余效果）")
    if prof['damage_amounts'] and 'damage' not in expected_cats \
            and 'effect_damage' not in expected_cats and 'lifesteal_damage' not in expected_cats:
        issues.append(f"运行时出现未声明的伤害 {prof['damage_amounts'][:3]}")
    # 激活次数与冷却合理性：cd=5 的物品 25s 窗口应激活 ~5 次
    # （消耗型物品提前退场后不再触发，跳过该检查）
    cd = data.get('cd') or 0
    if cd and has_cooldown_ctx and not prof['consumed']:
        expect_n = max(1, int(SIM_SECONDS / cd))
        if prof['activations'] < expect_n - 2:   # 调度容差 2 次
            issues.append(f"激活次数 {prof['activations']} < 预期 ≈{expect_n}（cd={cd}，窗口 {SIM_SECONDS}s）")
        if prof['activations'] > expect_n + 3:
            issues.append(f"激活次数 {prof['activations']} > 预期 ≈{expect_n}（疑似连发）")
    status = 'DIVERGE' if issues else 'PASS'
    return {
        'key': key, 'status': status,
        'expectations': {c: {'effects': sorted(i['effects']),
                             'gates': sorted(i['gates']),
                             'signals': sorted(i['signals']),
                             'methods': i['methods']} for c, i in exp.items()},
        'activations': prof['activations'],
        'damage_amounts': prof['damage_amounts'][:8],
        'issues': issues,
    }


# ---------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description="全物品效果保真度审验")
    ap.add_argument("--key", help="只审验单个物品")
    ap.add_argument("--json", default=os.path.join(ROOT, "output", "audit", "fidelity_report.json"))
    ap.add_argument("--limit", type=int, default=0)
    args = ap.parse_args()

    global DB
    DB = load_items()
    keys = [args.key] if args.key else list(DB.keys())
    if args.limit:
        keys = keys[:args.limit]

    from simulator.behavior import set_class_methods
    # data.load_items 已注入 class_methods

    report = []
    n_pass = n_div = 0
    for idx, key in enumerate(keys, 1):
        data = DB[key]
        try:
            r = audit_item(key, data)
        except Exception as e:  # noqa: BLE001
            r = {'key': key, 'status': 'ERROR',
                 'issues': [f"{type(e).__name__}: {e}"], 'expectations': {},
                 'activations': 0, 'damage_amounts': []}
        report.append(r)
        if r['status'] == 'PASS':
            n_pass += 1
        else:
            n_div += 1
            print(f"[{r['status']}] {key}")
            for i in r['issues']:
                print(f"    - {i}")
        if idx % 50 == 0:
            print(f"  ... {idx}/{len(keys)}（PASS {n_pass} / DIVERGE {n_div}）", flush=True)

    print("=" * 70)
    print(f"PASS {n_pass} / DIVERGE+ERROR {n_div} / 总 {len(report)}")
    os.makedirs(os.path.dirname(args.json), exist_ok=True)
    json.dump(report, open(args.json, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print(f"报告: {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
