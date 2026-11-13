# -*- coding: utf-8 -*-
"""三闸之一:seed 双态逐位(pyd 臂 + GD_PURE_PY 纯 py 臂)——可复现入口。

用法: python -X utf8 tools/seed_gate.py
基线四元组: output/perf/_seed_gate_baseline.json
  20260923 -> (907, opponent, 1548, 191079)
  42       -> (1042, opponent, 1991, 247251)
四元组 = (ticks, winner, n_events, events_bytes),口径同 bench_sim._evidence。
纯 py 臂在子进程内先 import tools._purepy_arm(置 GD_PURE_PY=1)再导入引擎。
"""
import io
import json
import os
import subprocess
import sys

ROOT = r'D:\文件资料\学习\自动背包AI'
os.chdir(ROOT)
sys.path.insert(0, ROOT)

BASE = json.load(io.open('output/perf/_seed_gate_baseline.json', encoding='utf-8'))
PL = io.open('lineups/truth_20261001_220653_R19_player.json', encoding='utf-8').read()
OP = io.open('lineups/truth_20261001_220653_R19_opponent.json', encoding='utf-8').read()

RUNNER = r'''
import io, json, sys
sys.path.insert(0, r'D:\文件资料\学习\自动背包AI')
if sys.argv[1] == 'pure':
    import tools._purepy_arm
import json as _j
from simulator.gd_core_engine import GDCoreEngine
pl = _j.load(open(r'D:\文件资料\学习\自动背包AI\lineups\truth_20261001_220653_R19_player.json', encoding='utf-8'))
op = _j.load(open(r'D:\文件资料\学习\自动背包AI\lineups\truth_20261001_220653_R19_opponent.json', encoding='utf-8'))
out = {}
for seed in ('20260923', '42'):
    eng = GDCoreEngine(pl, op, {}, {}, seed=int(seed), max_time=180.0)
    eng.run()
    out[seed] = {"ticks": int(eng._ticks),
                 "winner": "player" if eng.player_wins() else "opponent",
                 "n_events": eng.log.event_count,
                 "events_bytes": len(json.dumps(eng.log.to_dict(),
                                                ensure_ascii=False).encode("utf-8"))}
print(json.dumps(out))
'''

fails = 0
for arm in ('pyd', 'pure'):
    env = dict(os.environ, GD_PURE_PY='1') if arm == 'pure' else dict(os.environ)
    r = subprocess.run([sys.executable, '-X', 'utf8', '-c', RUNNER, arm],
                       capture_output=True, text=True, encoding='utf-8', env=env,
                       timeout=600)
    if r.returncode != 0:
        print(arm, 'CRASH'); print(r.stderr[-1500:]); fails += 1; continue
    got = json.loads(r.stdout.strip().splitlines()[-1])
    for seed, quad in BASE.items():
        g = got[seed]
        ok = (g['ticks'] == quad['ticks'] and g['winner'] == quad['winner']
              and g['n_events'] == quad['n_events']
              and g['events_bytes'] == quad['events_bytes'])
        print(f"{arm:4s} seed={seed}: ticks={g['ticks']}/{quad['ticks']} "
              f"ev={g['n_events']}/{quad['n_events']} "
              f"bytes={g['events_bytes']}/{quad['events_bytes']} "
              f"winner={g['winner']} -> {'OK' if ok else 'FAIL'}")
        if not ok:
            fails += 1
print('SEED GATE', 'GREEN' if fails == 0 else f'RED({fails})')
sys.exit(0 if fails == 0 else 1)
