# -*- coding: utf-8 -*-
"""build_data.py — 从解密后的权威 CSV (ItemData_e.csv) 生成战斗数据
输出: assets/battle_items.json, assets/characters.json

权威数值来源（decompiled 后解密的导出表）:
  name/id/rarity/type/extraTypes/shop/price/staminaCost
  minDam/maxDam/cd/accuracy/chance/chance2/block
  p1..p10  -> 物品参数（getP(N) / getP("name")），修复旧版 params 全为 0 的问题
  gain     -> 被动授予（仅用于“无脚本”的物品，避免与脚本 onCombatStart 重复）
  textEffect -> 展示用

效果 DSL 仍从 decompiled_full/Items/*.gd 解析:
  doCooldownEffect / onTriggerPotion / onCombatStart（新增）
"""
import csv
import json
import os
import re

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASSETS = os.path.join(BASE, 'assets')
DECOMP = os.path.join(BASE, 'decompiled_full', 'Items')
CSV_PATH = os.path.join(BASE, 'extracted', 'Sheets', 'CSV', 'ItemData_e.csv')

# ---------------- 脚本效果解析 ----------------
_OPT_ARGS = r'[^)]*\)'
_CALL_TO_EFFECT = [
    (r'giveCritTokens\s*\(\s*getP_m\("crit_tokens"\)\s*\)', {'type': 'give_crit_tokens', 'amount': 'p:crit_tokens'}),
    (r'giveCritTokens\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'give_crit_tokens', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveBlock\s*\(\s*getP_m\("block"\)\s*\)', {'type': 'gain_stacks', 'buff': 'block', 'amount': 'p:block'}),
    (r'giveBlock\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'block', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveBlock\s*\(\s*\)', {'type': 'gain_stacks', 'buff': 'block', 'amount': 'p:block'}),
    (r'giveSpikes\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'spikes', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveVampirism\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'vampirism', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveRegeneration\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'regen', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveLucky\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'lucky', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveMana\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'mana', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveEmpower\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'empower', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveHeat\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'heat', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveCold\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'cold', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveStamina\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stamina', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'giveStamina\s*\(\s*\)', {'type': 'gain_stamina', 'amount': 1}),
    (r'giveMaxHealth\s*\(\s*getP_m\("maxhealth"\)\s*\)', {'type': 'gain_max_health', 'amount': 'p:maxhealth'}),
    (r'giveMaxHealth\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_max_health', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'inflictPoison\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'poison', 'amount': f'p:{int(m.group(1))-1}', 'target': 'opponent'}),
    (r'selfInflictPoison\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'poison', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'inflictBlind\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'gain_stacks', 'buff': 'blind', 'amount': f'p:{int(m.group(1))-1}', 'target': 'opponent'}),
    (r'cleansePoison\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'cleanse_debuff', 'buff': 'poison', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'heal\s*\(\s*getP_m\("heal"\)' + _OPT_ARGS, {'type': 'heal', 'amount': 'p:heal'}),
    (r'heal\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'heal', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'heal\s*\(\s*\)', {'type': 'heal', 'amount': 'p:heal'}),
    (r'dealEffectDamage\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'deal_effect_damage', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'drainStamina\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'drain_stamina', 'amount': f'p:{int(m.group(1))-1}'}),
    (r'stun\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'stun', 'duration': f'p:{int(m.group(1))-1}'}),
    (r'useMana\s*\(\s*getP(\d)' + _OPT_ARGS, lambda m: {'type': 'use_mana', 'mana': f'p:{int(m.group(1))-1}'}),
]

_TRIGGER_MAP = {
    'character_damaged': 'character_damaged',
    'character_healed': 'character_healed',
    'character_stunned': 'character_stunned',
    'character_pre_use_stamina': 'character_pre_use_stamina',
    'pre_take_damage': 'pre_take_damage',
    'character_attacked': 'character_attacked',
}


def _to_float(v, default=0.0):
    try:
        return float(str(v).strip())
    except (ValueError, TypeError):
        return default


def _parse_body(func_name: str, script_text: str) -> str:
    """提取 GDScript 函数体（缩进驱动）"""
    m = re.search(r'func\s+' + re.escape(func_name) + r'\s*\([^)]*\)\s*:', script_text)
    if not m:
        return ''
    lines = script_text[m.end():].splitlines()
    body_lines = []
    for line in lines[1:]:
        if line.strip() and not line.startswith(('\t', ' ')):
            break
        body_lines.append(line)
    return '\n'.join(body_lines)


def _parse_calls(body: str) -> list:
    effects = []
    for pattern, effect in _CALL_TO_EFFECT:
        for m in re.finditer(pattern, body):
            e = effect(m) if callable(effect) else dict(effect)
            if e not in effects:
                effects.append(e)
    return effects


def _parse_effects(script_text: str) -> list:
    """doCooldownEffect + onTriggerPotion 效果"""
    body = _parse_body('doCooldownEffect', script_text) + '\n' + \
           _parse_body('onTriggerPotion', script_text)
    return _parse_calls(body)


def _parse_on_combat_start(script_text: str) -> list:
    """onCombatStart 效果（食物/消耗品/被动授予）"""
    return _parse_calls(_parse_body('onCombatStart', script_text))


def _parse_triggers(script_text: str, item_name: str) -> list:
    triggers = []
    if re.search(r'character_damaged', script_text) and 'getRelativeHealth' in script_text:
        m = re.search(r'healthThreshold\s*=\s*getP(\d)\s*/\s*100\.0', script_text)
        threshold = f'p:{int(m.group(1))-1}/100' if m else 0.5
        triggers.append({
            'on': 'character_damaged', 'source': 'self',
            'if': {'relative_health_lt': threshold},
            'action': {'type': 'consume_and_effect'},
        })
    if re.search(r'character_pre_use_stamina', script_text) and 'getCurrentStamina' in script_text:
        triggers.append({
            'on': 'character_pre_use_stamina', 'source': 'self',
            'if': {'stamina_lt': 'event.amount'},
            'action': {'type': 'consume_and_effect'},
        })
    if re.search(r'character_healed', script_text):
        triggers.append({
            'on': 'character_healed', 'source': 'opponent',
            'if': {},
            'action': {'type': 'consume_and_effect'},
        })
    return triggers


def _resolve_params(item: dict, effects: list) -> list:
    out = []
    named = item.get('named_params', {})
    params = item.get('params', [])
    for e in effects:
        e = dict(e)
        for k, v in list(e.items()):
            if isinstance(v, str) and v.startswith('p:'):
                ref = v[2:]
                if '/' in ref:
                    base, div = ref.split('/')
                    val = named.get(base, params[int(base)] if base.isdigit() and int(base) < len(params) else 0)
                    e[k] = round(float(val) / float(div), 3)
                elif ref.isdigit():
                    idx = int(ref)
                    e[k] = params[idx] if idx < len(params) else 0
                else:
                    e[k] = named.get(ref, 0)
        out.append(e)
    return out


# 被动授予映射（gain 字段 -> BuffType 名）
_GAIN_BUFF_MAP = {
    'spikes': 'spikes', 'spike': 'spikes',
    'regeneration': 'regen', 'regen': 'regen',
    'vampirism': 'vampirism',
    'empower': 'empower',
    'lucky': 'lucky', 'luck': 'lucky',
    'mana': 'mana',
    'heat': 'heat',
    'cold': 'cold',
    'blind': 'blind',
    'poison': 'poison',
    'block': 'block', 'blockt': 'block',
    'resist': 'resist',
    'maxhealth': 'maxhealth',
}
_DEFENSIVE_CATS = {'accessory', 'armor', 'shield', 'helmet', 'gloves', 'shoes'}


def _match_gain_amount(buff_name: str, named_params: dict) -> float:
    key = buff_name.lower().rstrip('t')
    for nk, nv in named_params.items():
        if nk.lower().rstrip('t') == key:
            return nv
    return 1.0


def category_from_type(t: str):
    t = (t or '').strip()
    if t == 'Melee Weapon':
        return 'weapon', 'melee'
    if t == 'Ranged Weapon':
        return 'weapon', 'ranged'
    if t == 'Weapon':
        return 'weapon', 'melee'
    if t == 'Food':
        return 'food', 'effect'
    if t == 'Potion':
        return 'potion', 'effect'
    if t == 'Shield':
        return 'shield', 'effect'
    if t == 'Bag':
        return 'bag', 'effect'
    if t == 'Armor':
        return 'armor', 'effect'
    if t == 'Accessory':
        return 'accessory', 'effect'
    if t == 'Gem':
        return 'gem', 'effect'
    if t == 'Helmet':
        return 'helmet', 'effect'
    if t == 'Shoes':
        return 'shoes', 'effect'
    if t == 'Gloves':
        return 'gloves', 'effect'
    if t == 'Book':
        return 'book', 'effect'
    if t == 'Card':
        return 'card', 'effect'
    if t == 'Pet':
        return 'pet', 'effect'
    if t == 'Spell':
        return 'spell', 'effect'
    if t == 'Skill':
        return 'skill', 'effect'
    if t == 'Chess Piece':
        return 'chess', 'effect'
    return 'utility', 'effect'


def _parse_crit(chance_str: str) -> float:
    m = re.search(r'(\d+(?:\.\d+)?)\s*:\s*crit', chance_str or '')
    if m:
        return float(m.group(1))
    return 0.0


def _types(cat: str, dmg_type: str, r: dict) -> list:
    types = []
    if cat == 'weapon':
        types.append('weapon')
        types.append('melee' if dmg_type == 'melee' else 'ranged')
    elif cat == 'food':
        types.append('food')
    elif cat == 'potion':
        types.append('potion')
    elif cat == 'shield':
        types.append('shield')
    elif cat == 'bag':
        types.append('bag')
    elif cat == 'armor':
        types.append('armor')
    for ex in (r.get('extraTypes') or '').split(','):
        ex = ex.strip().lower()
        if ex and ex not in types:
            types.append(ex)
    return types


def _find_script(name: str) -> str:
    """在 decompiled_full/Items 及其子目录中按文件名匹配 .gd（兼容大小写/空格/连字符/品质前缀/New后缀）。"""
    norm0 = name.lower().replace(' ', '').replace('-', '')
    candidates = [name, name.replace(' ', ''), name.replace(' ', '').lower(),
                  name.lower(), name.replace('-', ''), name.replace('-', '').lower(),
                  name.replace(' ', '').replace('-', ''),
                  name.replace(' ', '').replace('-', '').lower()]
    for cand in candidates:
        p = os.path.join(DECOMP, cand + '.gd')
        if os.path.exists(p):
            return p
    # 递归搜索子目录（Exclusive/、Exclusive/Chess/、Gems/ 等）
    for root, _, files in os.walk(DECOMP):
        for f in files:
            if not f.endswith('.gd'):
                continue
            fn = f[:-3]
            if fn.lower().replace(' ', '').replace('-', '') == norm0:
                return os.path.join(root, f)
    # 变体：去 Unstable/Stable 前缀、尾部 New
    k = name.replace('-', '')
    for q in ('Unstable ', 'Stable ', 'Chipped ', 'Flawed ', 'Regular ',
              'Flawless ', 'Perfect ', 'Strong ', 'Lesser ', 'Greater '):
        if k.startswith(q):
            k = k[len(q):]
            break
    if k.endswith(' New'):
        k = k[:-4]
    k = k.rstrip('0123456789 ').strip()
    if k and k != name:
        return _find_script(k)
    return ''


def convert_items():
    rows = {}
    if os.path.exists(CSV_PATH):
        with open(CSV_PATH, encoding='utf-8') as f:
            for r in csv.DictReader(f):
                rows[r['name']] = r
    else:
        raise FileNotFoundError(f"未找到解密 CSV: {CSV_PATH}")

    out = {}
    for name, r in rows.items():
        cat, dmg_type = category_from_type(r['type'])
        sp = _find_script(name)
        script_text = ''
        if sp:
            with open(sp, encoding='utf-8', errors='replace') as f:
                script_text = f.read()

        # p1..p10 参数
        params = []
        named_params = {}
        for i in range(1, 11):
            v = (r.get(f'p{i}') or '').strip()
            if not v:
                continue
            if ':' in v:
                val, nm = v.split(':', 1)
                named_params[nm.strip()] = _to_float(val)
                params.append(_to_float(val))
            else:
                params.append(_to_float(v))

        crit = _parse_crit(r.get('chance', '')) or _parse_crit(r.get('chance2', ''))

        script_effects = _parse_effects(script_text)
        script_effects = _resolve_params({'params': params, 'named_params': named_params}, script_effects)
        on_start = _parse_on_combat_start(script_text)
        on_start = _resolve_params({'params': params, 'named_params': named_params}, on_start)
        triggers = _parse_triggers(script_text, name)

        # ★ gain 列 = Item.gd gainedStacks（“物品会获得哪些 buff”的联动判定标志，
        # 如 DeathScythe.canAffect 检查 gainsStack(Stack.Poison)），不是“prepare 时给角色 buff”。
        # 脚本物品的 buff 给予在 doCooldownEffect/onCombatStart 行为中实现；
        # 此前把 gain 提取为 passive 并在 prepare 阶段给角色加 heat/cold/mana/spikes，
        # 导致与行为重复叠加、冷却被错误速度修正（Pot/Cauldron/Book of Ice 等）——已移除。
        passive = None

        item_data = {
            'key': name,
            'zh': name,
            'size': [1, 1],
            'category': cat,
            'damage_type': dmg_type,
            'min_dam': int(_to_float(r.get('minDam', '') or 0)),
            'max_dam': int(_to_float(r.get('maxDam', '') or 0)),
            'cd': _to_float(r.get('cd', '') or 0),
            'accuracy': _to_float(r.get('accuracy', '') or 100),
            'crit': crit,
            'stamina_cost': _to_float(r.get('staminaCost', '') or 0),
            'block': int(_to_float(r.get('block', '') or 0)),
            'price': int(_to_float(r.get('price', '') or 0)),
            'rarity': r.get('rarity', ''),
            'material': r.get('material', ''),
            'can_activate': (r.get('canActivate', '') or '') != 'no',
            'params': params,
            'named_params': named_params,
            'types': _types(cat, dmg_type, r),
            'effects': script_effects,
            'triggers': triggers,
            'on_start': on_start or None,
            'passive': passive,
            'csv_chance': r.get('chance', ''),
            'csv_chance2': r.get('chance2', ''),
            'text_effect': r.get('textEffect', ''),
            'source': 'csv',
            'script': os.path.basename(sp) if sp else '',
        }
        if cat == 'weapon':
            item_data['effect'] = {'type': 'attack'}
        elif script_effects:
            item_data['effect'] = {'effects': script_effects}
        else:
            item_data['effect'] = {'type': 'none', 'note': '无脚本效果'}
        out[name] = item_data
    return out


def convert_characters():
    """从 extracted/CharacterClasses/*.tres 提取角色真实数值（权威来源）"""
    EXTRACTED = os.path.join(BASE, 'extracted', 'CharacterClasses')
    names = ['Adventurer', 'Ranger', 'Berserker', 'Pyromancer', 'Mage', 'Reaper', 'Engineer']
    out = {}
    for name in names:
        path = os.path.join(EXTRACTED, name, name + '.tres')
        health, stamina, gold = 25.0, 5.0, 13
        if os.path.exists(path):
            with open(path, encoding='utf-8') as f:
                text = f.read()
            m = re.search(r'health\s*=\s*([\d.]+)', text)
            if m:
                health = float(m.group(1))
            m = re.search(r'stamina\s*=\s*([\d.]+)', text)
            if m:
                stamina = float(m.group(1))
            m = re.search(r'gold\s*=\s*([\d.]+)', text)
            if m:
                gold = int(float(m.group(1)))
        out[name] = {
            'key': name,
            'health': health,
            'stamina': stamina,
            'regen': 1.0,
            'gold': gold,
            'source': 'tres',
        }
    return out


def main():
    items = convert_items()
    chars = convert_characters()
    with open(os.path.join(ASSETS, 'battle_items.json'), 'w', encoding='utf-8') as f:
        json.dump({'items': items}, f, ensure_ascii=False, indent=1)
    with open(os.path.join(ASSETS, 'characters.json'), 'w', encoding='utf-8') as f:
        json.dump({'characters': chars}, f, ensure_ascii=False, indent=1)
    print(f"battle_items.json: {len(items)} 物品（来源: 解密 CSV）")
    print(f"characters.json: {len(chars)} 角色")
    w = sum(1 for v in items.values() if v['category'] == 'weapon')
    food = sum(1 for v in items.values() if v['category'] == 'food')
    potion = sum(1 for v in items.values() if v['category'] == 'potion')
    with_params = sum(1 for v in items.values() if v.get('params'))
    with_passive = sum(1 for v in items.values() if v.get('passive'))
    with_onstart = sum(1 for v in items.values() if v.get('on_start'))
    with_crit = sum(1 for v in items.values() if v.get('crit'))
    print(f"武器: {w}, 食物: {food}, 药水: {potion}")
    print(f"含参数(params): {with_params}, 含被动: {with_passive}, 含on_start: {with_onstart}, 含暴击: {with_crit}")


if __name__ == '__main__':
    main()
