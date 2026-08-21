# -*- coding: utf-8 -*-
"""全物品冷却验证 v2：固定冷却 + 速度修正对齐。

验证方法（每物品单独上场 vs 空手对手）：
1. 用 Item 状态链计算期望首触发 = pre_combat_start 的 trigger_time / combat_start 后的 get_speed()
   （对齐 Item.gd：preCombatStart 设 triggerTime=cd，combatStart 的 onCombatStart 可能加 heat/cold
    → getSpeed 修正；递减 triggerTime -= delta*getSpeed()）
2. 实战日志首触发时间必须落在 [expected-0.03, expected+0.03]（±2 tick 容差）

RNG 语义：冷却时长固定 = cd（无 ±5% 波动），同帧先后由 ordered_items 顺序决定。
"""
import sys, os, json, re, time
sys.path.insert(0, r'D:\文件资料\学习\自动背包AI')
from simulator.item import Item
from simulator.character import Character
from simulator.simulate import simulate_once, load_items, load_characters

db = json.load(open(r'D:\文件资料\学习\自动背包AI\assets\battle_items.json', encoding='utf-8'))['items']
items = load_items(); chars = load_characters()

def mk_lineup(name, it_ids):
    its = [{'id': x, 'row': 0, 'col': i, 'rotation': 0, 'quantity': 1,
            'container': False, 'contents': [], 'gems': []} for i, x in enumerate(it_ids)]
    return {'version': 3, 'meta': {'name': name}, 'character': 'Ranger', 'round': 3,
            'class_modifiers': {'health': 9999, 'stamina': 9999, 'stamina_regen': 99.0, 'gold': 13},
            'health_override': None,
            'backpack': {'grid': {'rows': 7, 'cols': 10}, 'items': its}, 'storage': []}

def expected_first_trigger(kid: str) -> float:
    """按状态链计算期望首触发时间（对齐原版 preCombatStart→combatStart→_physics_process）"""
    it = Item(kid, dict(db[kid]), seed=1)
    ch = Character(0, max_health=9999, seed=1); opp = Character(1, max_health=9999, seed=1)
    ch.set_opponent(opp); opp.set_opponent(ch)
    it.character = ch; it.log = None
    it.prepare()
    it.pre_combat_start()
    it.combat_start()
    if not it.has_cooldown():
        return None
    speed = it.get_speed()
    return it.trigger_time / speed if speed > 0 else None

tmp = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'output', 'bb_cd')
os.makedirs(tmp, exist_ok=True)
json.dump(mk_lineup('o', []), open(tmp + '/o.json', 'w'))

test_ids = [k for k, v in db.items()
            if v.get('cd') and v.get('behavior') and v.get('category') not in ('gem', 'chess')]
ok = bad = 0
bad_list = []
t0 = time.time()
for i, kid in enumerate(test_ids):
    exp = expected_first_trigger(kid)
    if exp is None:
        continue
    json.dump(mk_lineup('p', [kid]), open(tmp + '/p.json', 'w'))
    try:
        eng = simulate_once(tmp + '/p.json', tmp + '/o.json', items, chars, 42)
        txt = eng.log.to_text('en')
    except Exception as ex:
        bad += 1; bad_list.append((kid, 'CRASH', repr(ex)[:60])); continue
    first = None
    for l in txt.split('\n'):
        m = re.match(r'([\d.]+):\s+\[P\]\s+.*? activated', l)
        if m:
            first = float(m.group(1)); break
    if first is None:
        continue  # 被动物品（触发无激活日志）
    if exp - 0.03 <= first <= exp + 0.03:
        ok += 1
    else:
        bad += 1; bad_list.append((kid, 'exp=%.3f' % exp, 'act=%.3f' % first))
    if (i + 1) % 50 == 0:
        print(f'  {i+1}/{len(test_ids)} ok={ok} bad={bad} {time.time()-t0:.0f}s', flush=True)
print(f'== 完成 {len(test_ids)} 有cd物品 | ok={ok} bad={bad} | 用时 {time.time()-t0:.0f}s ==')
for b in bad_list[:25]:
    print('  BAD:', b)
