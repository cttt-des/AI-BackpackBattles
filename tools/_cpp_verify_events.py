# -*- coding: utf-8 -*-
"""Compare a C++ replay with existing Oracle, GDScript, and Python events.

Example:
  python tools/_cpp_verify_events.py --case-ids output/_handoff10/original_order/cases.json
      --fights-root output/_handoff10/original_order/fights
      --align-root output/_handoff10/original_order/align
      --dll native_sim_cpp/native_sim/libgdcore.dll
      --out output/_timing_four_way/cpp_baseline_checked

C++ omits the synthetic combat-end row. Compare its natural terminal result
and tick with the three terminal rows. C++ debug gem origins are coarse in the
legacy event-line format. For the complete identities, use --strict-gem-origins
with updated recordings and the supplemental DLL export.
"""
import argparse
import ctypes
import json
import re
import struct
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
from tools.verify_oracle import _canon_num, _et_names, _tuple_of, canonical_stream  # noqa: E402




_DEBUG_FLOAT = re.compile(r"(?<=[=,\[])f:([0-9a-f]{16})(?![0-9a-f])")


def canonical_fields(row):
    fields = dict(part.split("=", 1) for part in row.split("|", 6))
    fields.pop("id")
    fields["origin"] = CE.coarse_origin(fields["origin"])
    timestamp = struct.unpack(">d", bytes.fromhex(fields["ts"][2:]))[0]
    fields["ts"] = int(round(timestamp * 60))

    def normalize_number(match):
        value = struct.unpack(">d", bytes.fromhex(match.group(1)))[0]
        return CE.canon_val(_canon_num(value))

    fields["params"] = _DEBUG_FLOAT.sub(normalize_number, fields["params"])
    return fields


def event_rows(doc):
    rows = doc["events"]
    if rows and rows[-1]["type"] in (111, 112):
        return rows[:-1], rows[-1]
    return rows, None


def recorded_gem_identity(row):
    origin = row.get("origin")
    if not isinstance(origin, dict) or origin.get("kind") != "gem":
        return None
    identity = origin.get("identity")
    if (isinstance(identity, list) and len(identity) == 6
            and all(isinstance(value, str) and value for value in identity[:2])
            and all(type(value) is int for value in identity[2:]) and identity[5] >= 0):
        return tuple(identity)
    return ()


def native_gem_identity(getter, index, event_line):
    gem = ctypes.c_char_p()
    host = ctypes.c_char_p()
    coordinates = (ctypes.c_int32 * 4)()
    state = getter(index, ctypes.byref(gem), ctypes.byref(host), coordinates)
    if state == 1:
        return (gem.value.decode("utf8"), host.value.decode("utf8"), *coordinates)
    if state < 0 or "|origin=o:gem|" in event_line:
        return ()
    return None


def compare_gem_origins(getter, native_rows, recordings):
    inputs = {leg: list(map(recorded_gem_identity, rows)) for leg, rows in recordings.items()}
    inputs["cpp"] = [native_gem_identity(getter, i, row) for i, row in enumerate(native_rows)]
    missing = [leg for leg, identities in inputs.items() if () in identities]
    for index, identities in enumerate(zip(*inputs.values())):
        if () not in identities and len(set(identities)) > 1:
            return missing, {"index": index, **dict(zip(inputs, identities))}
    return missing, None


def first_difference(left, right):
    first = next((i for i, (a, b) in enumerate(zip(left, right))
                  if canonical_fields(a) != canonical_fields(b)), None)
    if first is None and len(left) != len(right):
        return min(len(left), len(right))
    return first


def first_tuple_difference(left, right):
    first = next((i for i, (a, b) in enumerate(zip(left, right)) if a != b), None)
    return min(len(left), len(right)) if first is None and len(left) != len(right) else first


def load_case_ids(spec: str) -> list:
    p = Path(spec)
    if p.exists() and p.suffix == '.json':
        d = json.load(io_open(p))
        cs = d['cases'] if isinstance(d, dict) and 'cases' in d else d
        return [c if isinstance(c, str) else c['case_id'] for c in cs]
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
    ap.add_argument('--original-dir', type=Path,
                    help='Require an independent original native-frame events.json for each case')
    ap.add_argument('--dll', default=str(ROOT / 'native_sim_cpp' / 'native_sim' / 'libgdcore.dll'))
    ap.add_argument('--out', default=str(ROOT / 'output' / '_timing_four_way' / 'cpp_baseline'))
    ap.add_argument("--below-master", action=argparse.BooleanOptionalAction, default=None,
                    help="Check that the recorded GDScript replay uses this setting")
    ap.add_argument('--timeout', type=int, default=600, help='单场 wall clock 秒')
    ap.add_argument('--strict-gem-origins', action='store_true',
                    help='Require gem type, host item, owner, cell and socket index in all four streams')
    args = ap.parse_args()

    gdcore_dir = Path(args.gdcore_dir or (Path(args.align_root) / 'gdcore'))
    py_dir = Path(args.py_dir or (Path(args.align_root) / 'py'))
    oracle_dir = Path(args.oracle_dir or args.fights_root)
    if args.original_dir and args.original_dir.resolve() == oracle_dir.resolve():
        ap.error("--original-dir must point to a separate recording root")
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
    if args.strict_gem_origins:
        try:
            gem_origin = lib.gd_sim_dbg_event_gem_origin
        except AttributeError:
            ap.error("--strict-gem-origins requires a DLL with gd_sim_dbg_event_gem_origin")
        gem_origin.argtypes = [ctypes.c_int32, ctypes.POINTER(ctypes.c_char_p),
                               ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_int32)]
        gem_origin.restype = ctypes.c_int32

    results = []
    event_names = _et_names()
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
        original_path = args.original_dir / cid / 'events.json' if args.original_dir else None
        player_path = Path(args.align_root) / "lineups" / f"oracle_{cid}_player.json"
        opponent_path = Path(args.align_root) / "lineups" / f"oracle_{cid}_opponent.json"
        for tag, path in (("gdcore", gd_ev_path), ("py", py_ev_path), ("oracle", or_ev_path),
                          ("player lineup", player_path), ("opponent lineup", opponent_path)):
            if not path.is_file():
                missing.append(f"{tag}: {path}")
        if original_path is not None and not original_path.is_file():
            missing.append(f"original: {original_path}")
        rng_state = read_rng_state(Path(args.fights_root), cid)
        if rng_state is None:
            missing.append("Missing RNG state")
        if missing:
            rec['category'] = 'missing_product'
            rec['notes'] = missing
            results.append(rec)
            print('[%d/%d] %s missing_product %s' % (n, len(ids), cid, missing))
            continue

        gd_doc = json.load(io_open(gd_ev_path))
        pyd = json.load(io_open(py_ev_path))
        or_doc = json.load(io_open(or_ev_path))
        original_doc = json.load(io_open(original_path)) if original_path is not None else None
        if any(int(doc.get("seed", -1)) != int(fx["seed"]) for doc in (gd_doc, pyd, or_doc)):
            rec["category"] = "input_mismatch"
            rec["notes"].append("Replay seed differs from fixture")
        if original_doc is not None:
            identity_fields = ("seed", "run_id", "round_id", "opp_run_id", "opp_round_id")
            if any(k not in original_doc or original_doc[k] != or_doc.get(k) for k in identity_fields):
                rec["category"] = "input_mismatch"
                rec["notes"].append("Original replay seed or history case differs from Oracle")
        below_master = gd_doc.get("below_master")
        if not isinstance(below_master, bool) or (
            args.below_master is not None and below_master != args.below_master
        ):
            rec["category"] = "input_mismatch"
            rec["notes"].append("Missing or conflicting recorded below_master")
        if fx.get("below_master", below_master) != below_master or pyd.get("below_master", below_master) != below_master:
            rec["category"] = "input_mismatch"
            rec["notes"].append("Replay cooldown league differs from fixture or between simulators")
        health_multiplier = float(fx.get("custom_health_multiplier", 100.0))
        if any(doc.get("custom_health_multiplier", 100.0) != health_multiplier for doc in (gd_doc, pyd)):
            rec["category"] = "input_mismatch"
            rec["notes"].append("Recorded replay health multiplier differs from fixture")
        order = gd_doc.get("activation_order") or {}
        if any(sorted(order.get(side) or []) != list(range(len(fx[side]["items"])))
               for side in ("player", "opponent")):
            rec["category"] = "input_mismatch"
            rec["notes"].append("Recorded activation order is not a full permutation")
        rec["below_master"] = below_master
        if rec.get('category') == 'input_mismatch':
            results.append(rec)
            print('[%d/%d] %s input_mismatch %s' % (n, len(ids), cid, rec['notes']))
            continue

        # ── C++ 装配 + 运行 ──
        t0 = time.time()
        player = json.load(io_open(player_path))
        opponent = json.load(io_open(opponent_path))
        for side, lineup in (("player", player), ("opponent", opponent)):
            for field in ("stamina", "health", "regen"):
                if fx[side].get(field) is not None:
                    lineup[field] = fx[side][field]
        pg = [len(item.get("gems") or []) for item in fx["player"]["items"]]
        og = [len(item.get("gems") or []) for item in fx["opponent"]["items"]]
        hp = sim.pack_side(player, gem_lens=pg, activation_order=order["player"])
        ho = sim.pack_side(opponent, gem_lens=og, activation_order=order["opponent"])
        lib.gd_sim_set_dbg_events(1)
        res = sim.run_one(hp, ho, seed=int(fx['seed']),
                          round_id=int(fx.get('round_id', 1)),
                          below_master=below_master,
                          native_activation_order=False,
                          reseed_after_player_character=True,
                          formal_ev_gate=500000, max_time=90.0,
                          rng_state=rng_state,
                          custom_health_multiplier=health_multiplier,
                          label_rng_enabled=bool(fx.get('label_rng', True)))
        cpp_wall = time.time() - t0
        if res.timed_out or cpp_wall > args.timeout:
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
        py_rows, py_end = event_rows(pyd)
        gd_rows, gd_end = event_rows(gd_doc)
        oracle_events, oracle_end = event_rows(or_doc)
        recorded_streams = {"oracle": oracle_events, "gd": gd_rows, "py": py_rows}
        endings = [oracle_end, gd_end, py_end]
        if original_doc is not None:
            original_events, original_end = event_rows(original_doc)
            recorded_streams["original"] = original_events
            endings.append(original_end)
        py_canon = [CE.py_row_canonical(r) for r in py_rows]
        gd_canon = [CE.py_row_canonical(r) for r in gd_rows]

        # 逐场结果
        rec['cpp'] = {'event_count': int(res.event_count), 'winner':
                      'player' if res.player_wins else 'opponent', 'ticks': int(res.ticks)}
        rec['gd'] = {'event_count': gd_doc.get('event_count'), 'winner': gd_doc.get('winner')}
        rec['py'] = {'event_count': pyd.get('event_count'), 'winner': pyd.get('winner')}
        rec['oracle'] = {'event_count': len(or_doc.get('events') or []),
                         'winner': or_doc.get('winner')}

        # 胜负：C++ vs gd/py vs oracle
        winners = {'cpp': rec['cpp']['winner'], 'gd': rec['gd']['winner'],
                   'py': rec['py']['winner'], 'oracle': rec['oracle'].get('winner')}
        if original_doc is not None:
            winners["original"] = original_doc.get("winner")
        rec['winner'] = winners
        rec['winner_match'] = len(set(winners.values())) == 1

        # 事件流：C++ vs gd（同为 gd_core 内核系，id/parent 可比）
        ev_first = first_difference(nat_canon, gd_canon)
        pygd_first = first_difference(py_canon, gd_canon)
        expected_end = 111 if res.player_wins else 112
        final_tick = round(float(res.combat_time) * 60)
        endings_match = all(
            row is not None and row["type"] == expected_end
            and round(float(row["timestamp"]) * 60) == final_tick
            for row in endings
        )
        rec["natural_ending_match"] = endings_match
        rec["events_cpp_vs_gd"] = {
            "rows_cpp": len(nat_canon), "rows_gd": len(gd_canon),
            "first_divergence": ev_first,
            "o_row": nat_canon[ev_first] if ev_first is not None and ev_first < len(nat_canon) else None,
            "g_row": gd_canon[ev_first] if ev_first is not None and ev_first < len(gd_canon) else None,
        }
        oracle_rows = list(map(_tuple_of, canonical_stream(str(or_ev_path), event_names)))
        gd_reference_rows = list(map(_tuple_of, canonical_stream(str(gd_ev_path), event_names)))
        oracle_first = first_tuple_difference(oracle_rows, gd_reference_rows)
        original_first = None
        if original_path is not None:
            original_rows = list(map(_tuple_of, canonical_stream(str(original_path), event_names)))
            original_first = first_tuple_difference(original_rows, oracle_rows)
            rec["events_original_vs_oracle_first"] = original_first
        rec["events_oracle_vs_gd_first"] = oracle_first
        rec["events_py_vs_gd_first"] = pygd_first
        gem_first = None
        if args.strict_gem_origins:
            missing_gems, gem_first = compare_gem_origins(gem_origin, nat_canon, recorded_streams)
            rec["missing_fields"].extend(f"{leg} gem identity" for leg in missing_gems)
            rec["strict_gem_first"] = gem_first
        elif any("|origin=o:gem|" in row for row in nat_canon):
            rec["missing_fields"].append("C++ debug gem host and socket index")
        if args.strict_gem_origins and rec["missing_fields"]:
            rec["category"] = "missing_event_metadata"
        elif (oracle_first is None and pygd_first is None and ev_first is None and gem_first is None
                and original_first is None and rec["winner_match"] and endings_match):
            rec["category"] = "pass"
        else:
            rec["category"] = "battle_semantic"
        results.append(rec)
        print('[%d/%d] %s %s | cpp=%d gd=%d py=%d | 首分歧=%s wall=%.1fs' % (
            n, len(ids), cid, rec['category'], len(nat_canon), len(gd_canon), len(py_canon),
            ev_first, cpp_wall))

    for rec in results:
        (out_dir / (rec["caseId"] + ".json")).write_text(
            json.dumps(rec, ensure_ascii=False, indent=1), encoding="utf-8")

    passed = sum(1 for r in results if r['category'] == 'pass')
    win_diff = sum(1 for r in results if r.get("winner_match") is False)
    summary = {
        'total': len(results), 'passed': passed,
        'category': {k: sum(1 for r in results if r['category'] == k)
                     for k in set(r['category'] for r in results)},
        'winner_mismatch': win_diff,
        'winner_unavailable': sum(1 for r in results if "winner_match" not in r),
        'cases_with_coarse_gem_origin': sum(1 for r in results if r["missing_fields"]),
        'strict_gem_origins': args.strict_gem_origins,
        'original_dir': str(args.original_dir) if args.original_dir else None,
        'first_divergences': [{'caseId': r['caseId'],
                               'first': r.get('events_cpp_vs_gd', {}).get('first_divergence'),
                               'rows_cpp': r.get('events_cpp_vs_gd', {}).get('rows_cpp'),
                               'rows_gd': r.get('events_cpp_vs_gd', {}).get('rows_gd'),
                               'o_row': r.get('events_cpp_vs_gd', {}).get('o_row'),
                               'g_row': r.get('events_cpp_vs_gd', {}).get('g_row'),
                               'first_gem': r.get('strict_gem_first'),
                               'first_original': r.get('events_original_vs_oracle_first')}
                              for r in results if r['category'] != 'pass'],
        'below_master_override': args.below_master,
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
