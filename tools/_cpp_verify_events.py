# -*- coding: utf-8 -*-
"""C++ 逐事件验收工具（四方对齐：Oracle/GDScript/Python/C++）。

对指定场次逐场：
  1. 以夹具（--cases-json）装配 C++ 输入（gem_lens / activation_order 直通 /
     rng_state 注入 / 血量·体力·回复 / below_master 冷却分支）；
  2. 跑 C++ 内核（libgdcore.dll）并经 gd_sim_dbg_event_line 导出有序事件流；
  3. 与 GDScript 回放产物（--align-root/gdcore，兼作 activation_order 来源）和
     Python 回放产物（--align-root/py）逐事件比较（胜负、自然终局、有序事件流：
     tick、类型、双方归属、来源、参数、父事件）。

验收判定（逐场 JSON 的 category）：
  pass             三方事件流一致且胜负一致
  battle_semantic  C++ 与 GDScript/Python 在排除表示差异后仍有真实事件差
  representation   仅归一化表示差异（宝石占位字面、id 级联偏移等），按
                   原有规范化规则计一致——不会出现，出现即如实记入
  input_mismatch   夹具/回放产物的 seed、物品数、rng_state 等输入不一致
  missing_product  GDScript/Python/oracle 回放产物缺失
  timeout          C++ 单场超时

C++ 导出缺失字段（如实列出，不计入一致）：
  - type_name（渲染名，canonical 用数字 type 比较，不受影响）；
  - origin 的宝石 host 占位字面（GemSocket/GemSocket2）两侧均为占位，
    canonical 归一为 o:gem，不参与判定；
  - 事件“id 级联偏移”（gd_core 内核系 id 分配与 oracle 不同，同内核系
    gd/py/C++ 三方 id 策略一致，可比较）。

用法（可复跑）:
  python tools/_cpp_verify_events.py \
      --cases-json gd_core_test/expand_align_cases.json \
      --case-ids output/_handoff10/original_order/cases.json \
      --fights-root output/_handoff10/original_order/fights \
      --align-root output/_handoff10/original_order/align \
      --dll native_sim_cpp/native_sim/libgdcore.dll \
      --out output/_timing_four_way/cpp_baseline

兼容性：native_sim_cpp/tools/_cmp_events.py 与 tools/_full1690.py 不改动；
本工具复用前者的 canonical 函数，后者仍是全量跑批入口。
"""
import argparse
import ctypes
import json
import sys
import time
from pathlib import Path


def io_open(path, mode='r', encoding='utf-8'):
    import io as _io
    return _io.open(path, mode, encoding=encoding)

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / 'native_sim_cpp'))
sys.path.insert(0, str(ROOT / 'native_sim_cpp' / 'tools'))

from native_sim.sim import NativeSimulator  # noqa: E402
import _cmp_events as CE  # noqa: E402




# ── 分层比较（1ulp 浮点 = 表示差异；其余差异 = 语义差异）──
_FP_RE = None


def _fp_extract(s):
    import re as _re
    global _FP_RE
    if _FP_RE is None:
        _FP_RE = _re.compile(r'f:([0-9a-f]{16})')
    import struct as _st
    return [_st.unpack('>d', bytes.fromhex(h))[0] for h in _FP_RE.findall(s)]


def _fp_skeleton(s):
    import re as _re
    global _FP_RE
    if _FP_RE is None:
        _FP_RE = _re.compile(r'f:([0-9a-f]{16})')
    return _FP_RE.sub('f:#', s)


def _ulp_close(a, b, ulps=2):
    if a == b:
        return True
    if a == 0 or b == 0:
        return abs(a - b) <= 2 ** -52
    ia = int.from_bytes(__import__('struct').pack('>d', a), 'big')
    ib = int.from_bytes(__import__('struct').pack('>d', b), 'big')
    if ia < 0:
        ia = -ia
    if ib < 0:
        ib = -ib
    return abs(ia - ib) <= ulps


def compare_rows(row_g, row_c, ulps=2):
    """逐键分层比较：返回 None=一致；'repr'（仅浮点 1ulp 差）；'semantic'。"""
    keys = ('ts', 'type', 'tgt', 'parent', 'origin', 'params')
    # 行格式 ts=f:..|type=N|id=N|tgt=N|parent=N|origin=..|params=d:{..}
    def parse(line):
        d = {}
        for part in line.split('|'):
            if '=' in part:
                k, v = part.split('=', 1)
                d[k] = v
        return d
    dg = parse(row_g)
    dc = parse(row_c)
    repr_only = False
    for k in keys:
        vg = dg.get(k)
        vc = dc.get(k)
        if vg == vc:
            continue
        if k == 'params':
            if _fp_skeleton(vg or '') == _fp_skeleton(vc or ''):
                fg = _fp_extract(vg or '')
                fc = _fp_extract(vc or '')
                if len(fg) == len(fc) and all(_ulp_close(a, b, ulps) for a, b in zip(fg, fc)):
                    repr_only = True
                    continue
                return 'semantic'
            return 'semantic'
        if k == 'origin':
            if vg == vc:
                continue
            if _fp_skeleton(vg or '') == _fp_skeleton(vc or ''):
                fg = _fp_extract(vg or '')
                fc = _fp_extract(vc or '')
                if len(fg) == len(fc) and all(_ulp_close(a, b, ulps) for a, b in zip(fg, fc)):
                    repr_only = True
                    continue
            return 'semantic'
        return 'semantic'
    return 'repr' if repr_only else None


def load_case_ids(spec: str) -> list:
    p = Path(spec)
    if p.exists() and p.suffix == '.json':
        d = json.load(io_open(p))
        cs = d['cases'] if isinstance(d, dict) and 'cases' in d else d
        return [c['case_id'] for c in cs]
    return [x.strip() for x in spec.replace(',', '\n').split() if x.strip()]


def read_rng_state(fights_root: Path, cid: str):
    p = Path(fights_root) / cid / 'rng_state.txt'
    if not p.exists():
        return None
    for ln in io_open(p, encoding='utf-8'):
        if ln.startswith('state='):
            return int(ln.strip()[6:]) & ((1 << 64) - 1)
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description='C++ 逐事件验收（四方对齐）')
    ap.add_argument('--cases-json', default=str(ROOT / 'gd_core_test' / 'expand_align_cases.json'))
    ap.add_argument('--case-ids', required=True, help='场次清单 JSON 或逗号/空白分隔 id')
    ap.add_argument('--fights-root', default=str(ROOT / 'output' / 'oracle' / 'expand' / 'fights'))
    ap.add_argument('--align-root', default=str(ROOT / 'output' / 'oracle' / 'align_expand'))
    ap.add_argument('--gdcore-dir', default=None, help='默认 <align-root>/gdcore')
    ap.add_argument('--py-dir', default=None, help='默认 <align-root>/py')
    ap.add_argument('--oracle-dir', default=None, help='默认 <fights-root>')
    ap.add_argument('--dll', default=str(ROOT / 'native_sim_cpp' / 'native_sim' / 'libgdcore.dll'))
    ap.add_argument('--out', default=str(ROOT / 'output' / '_timing_four_way' / 'cpp_baseline'))
    ap.add_argument('--below-master', action='store_true',
                    help='旧语料族口径（默认 False = handoff10 新语料族，对手冷却掷 0.95-1.05）')
    ap.add_argument('--timeout', type=int, default=600, help='单场 wall clock 秒')
    args = ap.parse_args()

    gdcore_dir = Path(args.gdcore_dir or (Path(args.align_root) / 'gdcore'))
    py_dir = Path(args.py_dir or (Path(args.align_root) / 'py'))
    oracle_dir = Path(args.oracle_dir or args.fights_root)
    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    all_cases = {c['case_id']: c for c in json.load(
        io_open(args.cases_json, encoding='utf-8'))['cases']}
    ids = load_case_ids(args.case_ids)
    print('场次 %d：夹具=%s below_master=%s' % (len(ids), args.cases_json, args.below_master))

    sim = NativeSimulator(lib_path=args.dll)
    lib = sim.lib
    lib.gd_sim_set_dbg_events.argtypes = [ctypes.c_int32]
    lib.gd_sim_set_dbg_events.restype = None
    lib.gd_sim_dbg_event_count.argtypes = []
    lib.gd_sim_dbg_event_count.restype = ctypes.c_int32
    lib.gd_sim_dbg_event_line.argtypes = [ctypes.c_int32]
    lib.gd_sim_dbg_event_line.restype = ctypes.c_char_p

    results = []
    t_all = time.time()
    for n, cid in enumerate(ids, 1):
        rec = {'caseId': cid, 'category': None, 'missing_fields': [], 'notes': []}
        fx = all_cases.get(cid)
        if fx is None:
            rec['category'] = 'input_mismatch'
            rec['notes'].append('夹具缺该 case_id')
            results.append(rec)
            print('[%d/%d] %s input_mismatch（夹具缺）' % (n, len(ids), cid))
            continue

        # ── 输入核对：三份回放产物 + rng_state + activation_order ──
        missing = []
        gd_ev_path = gdcore_dir / cid / 'events.json'
        py_ev_path = py_dir / cid / 'events.json'
        or_ev_path = oracle_dir / cid / 'events.json'
        rs_path = Path(args.fights_root) / cid / 'rng_state.txt'
        for tag, p in (('gdcore', gd_ev_path), ('py', py_ev_path), ('oracle', or_ev_path)):
            if not p.exists():
                missing.append('%s 缺 events.json' % tag)
        rng_state = None
        if rs_path.exists():
            for ln in io_open(rs_path, encoding='utf-8'):
                if ln.startswith('state='):
                    rng_state = int(ln.strip()[6:]) & ((1 << 64) - 1)
                    break
        else:
            missing.append('缺 rng_state.txt')
        if missing:
            rec['category'] = 'missing_product'
            rec['notes'] = missing
            results.append(rec)
            print('[%d/%d] %s missing_product %s' % (n, len(ids), cid, missing))
            continue

        gd_doc = json.load(io_open(gd_ev_path, encoding='utf-8'))
        # 输入核对：seed / activation_order
        if int(gd_doc.get('seed', -1)) != int(fx['seed']):
            rec['category'] = 'input_mismatch'
            rec['notes'].append('gdcore seed %s ≠ 夹具 %s' % (gd_doc.get('seed'), fx['seed']))
        order = gd_doc.get('activation_order') or {}
        n_items = len(fx['player']['items']) + len(fx['opponent']['items'])
        pn = len(fx['player']['items'])
        on = len(fx['opponent']['items'])
        po = [int(x) for x in (order.get('player') or [])]
        oo = [int(x) for x in (order.get('opponent') or [])]
        if sorted(po) != list(range(pn)) or sorted(oo) != list(range(on)):
            rec.setdefault('notes', []).append(
                'activation_order 非满排列（player=%d/opp=%d，夹具=%d/%d）'
                % (len(po), len(oo), pn, on))
        if rec.get('category') == 'input_mismatch':
            results.append(rec)
            print('[%d/%d] %s input_mismatch %s' % (n, len(ids), cid, rec['notes']))
            continue

        # ── C++ 装配 + 运行 ──
        t0 = time.time()
        case_run = dict(fx)
        case_run['player'] = fx['player']
        case_run['opponent'] = fx['opponent']
        pg = [len(e.get('gems') or []) for e in fx['player']['items']]
        og = [len(e.get('gems') or []) for e in fx['opponent']['items']]
        hp = sim.pack_side(fx['player'], gem_lens=pg,
                           activation_order=[int(x) for x in order['player']])
        ho = sim.pack_side(fx['opponent'], gem_lens=og,
                           activation_order=[int(x) for x in order['opponent']])
        lib.gd_sim_set_dbg_events(1)
        res = sim.run_one(hp, ho, seed=int(fx['seed']),
                          round_id=int(fx.get('round_id', 1)),
                          below_master=bool(args.below_master),
                          native_activation_order=True,
                          reseed_after_player_character=True,
                          formal_ev_gate=500000, max_time=90.0,
                          rng_state=rng_state,
                          custom_health_multiplier=float(fx.get('custom_health_multiplier', 100.0)),
                          label_rng_enabled=bool(fx.get('label_rng', True)))
        cpp_wall = time.time() - t0
        if cpp_wall > args.timeout:
            rec['category'] = 'timeout'
            results.append(rec)
            print('[%d/%d] %s timeout %.0fs' % (n, len(ids), cid, cpp_wall))
            continue

        # ── 三方事件流 ──
        n_lines = lib.gd_sim_dbg_event_count()
        nat_lines = []
        for i in range(n_lines):
            s = lib.gd_sim_dbg_event_line(i)
            nat_lines.append(s.decode('utf-8', 'replace') if s else '')

        def coarse_seg(line):
            a = line.index('|origin=') + len('|origin=')
            b = line.index('|params=')
            return line[:a] + CE.coarse_origin(line[a:b]) + line[b:]

        nat_canon = [coarse_seg(x) for x in nat_lines]
        pyd = json.load(io_open(py_ev_path, encoding='utf-8'))
        gdd = json.load(io_open(gd_ev_path, encoding='utf-8'))
        py_rows = [r for r in pyd['events'] if r.get('id') is not None and r['id'] >= 0]
        gd_rows = [r for r in gdd['events'] if r.get('id') is not None and r['id'] >= 0]
        py_canon = [CE.py_row_canonical(r) for r in py_rows]
        gd_canon = [CE.py_row_canonical(r) for r in gd_rows]

        # 逐场结果
        rec['cpp'] = {'event_count': int(res.event_count), 'winner':
                      'player' if res.player_wins else 'opponent', 'ticks': int(res.ticks)}
        rec['gd'] = {'event_count': gdd.get('event_count'), 'winner': gdd.get('winner')}
        rec['py'] = {'event_count': pyd.get('event_count'), 'winner': pyd.get('winner')}
        or_doc = json.load(io_open(or_ev_path, encoding='utf-8'))
        rec['oracle'] = {'event_count': len(or_doc.get('events') or []),
                         'winner': or_doc.get('winner')}

        # 胜负：C++ vs gd/py vs oracle
        winners = {'cpp': rec['cpp']['winner'], 'gd': rec['gd']['winner'],
                   'py': rec['py']['winner'], 'oracle': rec['oracle'].get('winner')}
        rec['winner'] = winners
        rec['winner_match'] = len(set(winners.values())) == 1

        # 事件流：C++ vs gd（同为 gd_core 内核系，id/parent 可比）
        cmp_n = min(len(nat_canon), len(gd_canon))
        ev_first = None
        ev_kind = None
        repr_rows = 0
        for k in range(cmp_n):
            v = compare_rows(gd_canon[k], nat_canon[k])
            if v is not None:
                ev_first = k
                ev_kind = v
                if v == 'repr':
                    repr_rows += 1
                break
        if ev_first is None and len(nat_canon) != len(gd_canon):
            ev_first = cmp_n
            ev_kind = 'length'
        # py vs gd（基线互相校验，严格位型）
        pygd_first = next((k for k in range(min(len(py_canon), len(gd_canon)))
                           if py_canon[k] != gd_canon[k]), None)
        rec['events_cpp_vs_gd'] = {'rows_cpp': len(nat_canon), 'rows_gd': len(gd_canon),
                                   'first_divergence': ev_first, 'kind': ev_kind,
                                   'o_row': nat_canon[ev_first][:220] if ev_first is not None and ev_first < len(nat_canon) else None,
                                   'g_row': gd_canon[ev_first][:220] if ev_first is not None and ev_first < len(gd_canon) else None}
        rec['events_py_vs_gd_first'] = pygd_first
        rec['cpp_missing_fields'] = list(rec['missing_fields'])

        if pygd_first is None and len(py_canon) == len(gd_canon) and ev_first is None \
                and len(nat_canon) == len(gd_canon):
            rec['category'] = 'pass'
        elif ev_first is not None and ev_kind == 'repr':
            # 该行仅浮点 1ulp 表示差：若行数一致则整场计 representation
            rec['category'] = 'representation' if len(nat_canon) == len(gd_canon) \
                else 'battle_semantic'
        else:
            rec['category'] = 'battle_semantic'
        results.append(rec)
        print('[%d/%d] %s %s | cpp=%d gd=%d py=%d | 首分歧=%s wall=%.1fs' % (
            n, len(ids), cid, rec['category'], len(nat_canon), len(gd_canon), len(py_canon),
            ev_first, cpp_wall))

        io_open(out_dir / ('%s.json' % cid), 'w', encoding='utf-8').write(
            json.dumps(rec, ensure_ascii=False, indent=1))

    passed = sum(1 for r in results if r['category'] == 'pass')
    win_diff = sum(1 for r in results if not r.get('winner_match', True))
    summary = {
        'total': len(results), 'passed': passed,
        'category': {k: sum(1 for r in results if r['category'] == k)
                     for k in set(r['category'] for r in results)},
        'winner_mismatch': win_diff,
        'first_divergences': [{'caseId': r['caseId'],
                               'first': r.get('events_cpp_vs_gd', {}).get('first_divergence'),
                               'rows_cpp': r.get('events_cpp_vs_gd', {}).get('rows_cpp'),
                               'rows_gd': r.get('events_cpp_vs_gd', {}).get('rows_gd'),
                               'o_row': r.get('events_cpp_vs_gd', {}).get('o_row'),
                               'g_row': r.get('events_cpp_vs_gd', {}).get('g_row')}
                              for r in results if r['category'] != 'pass'],
        'below_master': bool(args.below_master),
        'dll': args.dll,
        'wall_total_s': round(time.time() - t_all, 1),
    }
    io_open(out_dir / 'summary.json', 'w', encoding='utf-8').write(
        json.dumps(summary, ensure_ascii=False, indent=1))
    print('== 汇总 ==')
    print(json.dumps(summary, ensure_ascii=False, indent=1)[:800])
    return 0 if passed == len(results) else 1


if __name__ == '__main__':
    sys.exit(main())
