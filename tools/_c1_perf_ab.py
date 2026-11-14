# -*- coding: utf-8 -*-
"""C.1 性能复测：py 内核（GDCoreEngine 神谕对齐口径）vs native_sim_cpp，
同 60 场逐场交错计时（A/B/A/B 消除频序偏差）。

用法: python -X utf8 tools/_c1_perf_ab.py [场数]
默认读 output/perf/core_cases.txt 前 60 场。
"""
import ctypes
import json
import os
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
sys.path.append(os.path.join(ROOT, 'native_sim_cpp'))

N = int(sys.argv[1]) if len(sys.argv) > 1 else 60
ids = open(os.path.join(ROOT, 'output/perf/core_cases.txt'), encoding='utf-8').read().strip().split(',')
ids = ids[:N]

# ── py 腿 ──
from simulator.data import load_items, load_characters
from simulator.lineup import load_lineup
from simulator.gd_core_engine import GDCoreEngine, kernel

item_db = load_items()
character_db = load_characters()
fixture = {c['case_id']: c for c in json.load(
    open(os.path.join(ROOT, 'gd_core_test/expand_align_cases.json'), encoding='utf-8'))['cases']}
ALIGN = os.path.join(ROOT, 'output/oracle/align_expand')

py_times = []
nat_times = []

import struct  # noqa
from native_sim import get_simulator  # noqa
sim = get_simulator()
lib = sim.lib

t0 = time.time()
for cid in ids:
    c = fixture[cid]
    player = load_lineup(os.path.join(ALIGN, 'lineups', 'oracle_%s_player.json' % cid))
    opponent = load_lineup(os.path.join(ALIGN, 'lineups', 'oracle_%s_opponent.json' % cid))
    order = json.load(open(os.path.join(ALIGN, 'gdcore', cid, 'events.json'), encoding='utf-8'))['activation_order']
    rng_state = None
    rp = os.path.join(ALIGN and ROOT, 'output/oracle/expand/fights', cid, 'rng_state.txt')
    if os.path.exists(rp):
        for ln in open(rp, encoding='utf-8'):
            if ln.startswith('state='):
                rng_state = int(ln.strip()[6:])
                break
    p_gem_lens = [len(e.get('gems') or []) for e in c['player']['items']]
    o_gem_lens = [len(e.get('gems') or []) for e in c['opponent']['items']]
    common_py = dict(seed=int(c['seed']),
                     below_master=True, reseed_after_player_character=True,
                     max_time=90.0, rng_state=rng_state,
                     custom_health_multiplier=float(c.get('custom_health_multiplier', 100.0)),
                     label_rng_enabled=bool(c.get('label_rng', True)))
    common_nat = dict(seed=int(c['seed']), round_id=int(c.get('round_id', 1)),
                      below_master=True, reseed_after_player_character=True,
                      formal_ev_gate=500000, max_time=90.0, rng_state=rng_state,
                      custom_health_multiplier=float(c.get('custom_health_multiplier', 100.0)),
                      label_rng_enabled=bool(c.get('label_rng', True)))

    # A：py
    ta = time.time()
    eng = GDCoreEngine(player, opponent, item_db, character_db,
                       p_gem_lens=p_gem_lens, o_gem_lens=o_gem_lens,
                       p_activation_order=[int(x) for x in order['player']],
                       o_activation_order=[int(x) for x in order['opponent']],
                       p_stats={'stamina': c['player'].get('stamina'), 'health': c['player'].get('health'),
                                'regen': c['player'].get('regen')},
                       o_stats={'stamina': c['opponent'].get('stamina'), 'health': c['opponent'].get('health'),
                                'regen': c['opponent'].get('regen')},
                       **common_py)
    eng.run()
    py_times.append(time.time() - ta)

    # B：native（同口径：preordered 终序直通 + rng_state 注入）
    pf = json.load(open(os.path.join(ALIGN, 'lineups', 'oracle_%s_player.json' % cid), encoding='utf-8'))
    of = json.load(open(os.path.join(ALIGN, 'lineups', 'oracle_%s_opponent.json' % cid), encoding='utf-8'))
    for _sd, _sc in ((pf, c['player']), (of, c['opponent'])):
        for _f in ('stamina', 'health', 'regen'):
            if _sc.get(_f) is not None:
                _sd[_f] = _sc[_f]
    tb = time.time()
    hp = sim.pack_side(pf, gem_lens=p_gem_lens, activation_order=[int(x) for x in order['player']])
    ho = sim.pack_side(of, gem_lens=o_gem_lens, activation_order=[int(x) for x in order['opponent']])
    r = sim.run_one(hp, ho, native_activation_order=False, **common_nat)
    nat_times.append(time.time() - tb)

dt = time.time() - t0
py_sum = sum(py_times)
nat_sum = sum(nat_times)
print('cases: %d  (interleaved A/B, wall %.1fs)' % (len(ids), dt))
print('py   engine: total %.2fs  mean %.1f ms/fight  max %.1f ms' % (
    py_sum, py_sum / len(ids) * 1000, max(py_times) * 1000))
print('native dll:  total %.2fs  mean %.1f ms/fight  max %.1f ms' % (
    nat_sum, nat_sum / len(ids) * 1000, max(nat_times) * 1000))
print('speedup (py/native): %.2fx' % (py_sum / nat_sum))
