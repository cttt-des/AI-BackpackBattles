# -*- coding: utf-8 -*-
"""B.2 取证：native(_full1690 参数) vs py 腿留档 逐行对位，定位首个分叉事件。

用法: python -X utf8 tools/_b2_probe_native.py <case_id> [case_id ...]
"""
import ctypes, json, sys
from pathlib import Path

ROOT = Path(r"D:\文件资料\学习\自动背包AI")
sys.path.insert(0, str(ROOT))
sys.path.append(str(ROOT / 'native_sim_cpp'))
sys.path.insert(0, str(ROOT / 'native_sim_cpp' / 'tools'))
from native_sim import get_simulator  # noqa: E402
import _cmp_events as CE  # noqa: E402

sim = get_simulator()
lib = sim.lib
lib.gd_sim_set_dbg_events.argtypes = [ctypes.c_int32]
lib.gd_sim_dbg_event_count.restype = ctypes.c_int32
lib.gd_sim_dbg_event_line.restype = ctypes.c_char_p

CASES = {c["case_id"]: c for c in json.load(
    open(ROOT / "gd_core_test/expand_align_cases.json", encoding="utf-8"))["cases"]}


def probe(cid):
    c = CASES[cid]
    L = ROOT / 'output/oracle/align_expand/lineups'
    GD = ROOT / 'output/oracle/align_expand/gdcore'
    FY = ROOT / 'output/oracle/expand/fights'
    pf = json.load(open(L / f'oracle_{cid}_player.json', encoding='utf-8'))
    of = json.load(open(L / f'oracle_{cid}_opponent.json', encoding='utf-8'))
    order = json.load(open(GD / cid / 'events.json', encoding='utf-8'))['activation_order']
    rs = None
    rp = FY / cid / 'rng_state.txt'
    if rp.exists():
        for ln in open(rp, encoding='utf-8'):
            if ln.startswith('state='):
                rs = int(ln.strip()[6:])
                break
    pg = [len(e.get('gems') or []) for e in c['player']['items']]
    og = [len(e.get('gems') or []) for e in c['opponent']['items']]
    # 体力/血量/回复夹具真值注入（与 tools/_full1690.py 同步；见 sim.py pack_side 注）
    for _sd, _sc in ((pf, c['player']), (of, c['opponent'])):
        for _f in ('stamina', 'health', 'regen'):
            if _sc.get(_f) is not None:
                _sd[_f] = _sc[_f]
    hp = sim.pack_side(pf, gem_lens=pg, activation_order=[int(x) for x in order['player']])
    ho = sim.pack_side(of, gem_lens=og, activation_order=[int(x) for x in order['opponent']])
    lib.gd_sim_set_dbg_events(1)
    r = sim.run_one(hp, ho, seed=int(c['seed']), round_id=int(c.get('round_id', 1)),
                    below_master=True, native_activation_order=False,
                    reseed_after_player_character=True, formal_ev_gate=500000,
                    max_time=90.0, rng_state=rs,
                    custom_health_multiplier=float(c.get('custom_health_multiplier', 100.0)),
                    label_rng_enabled=bool(c.get('label_rng', True)))
    n = lib.gd_sim_dbg_event_count()
    nat = [lib.gd_sim_dbg_event_line(i).decode('utf-8', 'replace') for i in range(n)]

    def coarse_seg(line):
        a = line.index('|origin=') + len('|origin=')
        b = line.index('|params=')
        return line[:a] + CE.coarse_origin(line[a:b]) + line[b:]
    nat = [coarse_seg(x) for x in nat]
    pyd = json.load(open(ROOT / 'output/oracle/align_expand/py' / cid / 'events.json', encoding='utf-8'))
    pye = [r2 for r2 in pyd['events'] if r2.get('id') is not None and r2['id'] >= 0]
    py_canon = [CE.py_row_canonical(r2) for r2 in pye]
    m = min(len(py_canon), len(nat))
    first = None
    for i in range(m):
        if py_canon[i] != nat[i]:
            first = i
            break
    print(f'== {cid}: py={len(py_canon)} nat={len(nat)} first_diff={first}')
    if first is not None:
        for k in range(max(0, first - 1), min(m, first + 4)):
            mark = '>>' if k == first else '  '
            print(f'  {mark} py {py_canon[k][:120]}')
            print(f'  {mark} nt {nat[k][:120]}')
    else:
        print('   前缀全一致；py 尾段:')
        for k in range(m, min(len(py_canon), m + 6)):
            print('   P+', py_canon[k][:120])
        print('   nat 尾段:')
        for k in range(m, min(len(nat), m + 6)):
            print('   N+', nat[k][:120])


for cid in sys.argv[1:]:
    probe(cid)
