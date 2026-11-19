"""Interleaved CPU comparison, restricted to per-event-verified unchanged cases."""
from pathlib import Path
import argparse
import ctypes
import hashlib
import json
import statistics
import sys
import time

stage = Path(__file__).resolve().parent
sim_root = stage / "sim_native"
sys.path[:0] = [str(sim_root), str(sim_root / "native_sim_cpp")]
from native_sim.sim import NativeSimulator

ap = argparse.ArgumentParser()
ap.add_argument("--before", default="native_kernel_baseline")
ap.add_argument("--after", default="native_kernel_timers")
ap.add_argument("--before-dll", type=Path, help="Override the baseline DLL path")
ap.add_argument("--after-dll", type=Path, help="Override the candidate DLL path")
ap.add_argument("--after-results", type=Path, help="Candidate verification directory with the same inputs")
ap.add_argument("--report", type=Path)
ap.add_argument("--rounds", type=int, default=5)
ap.add_argument("--iterations", type=int, default=5)
ap.add_argument("--samples", type=int, default=3)
args = ap.parse_args()
roots = [stage / name for name in (args.before, args.after)]
verified = [roots[0] / "cpp", args.after_results or roots[1] / "cpp"]
summaries = [json.loads((root / "summary.json").read_text("utf8")) for root in verified]
# Read the per-case files; the summary only includes a prefix of failures.
reports = [[json.loads(path.read_text("utf8")) for path in root.glob("run*.json")] for root in verified]
assert all(len(rows) == summary["total"] for rows, summary in zip(reports, summaries))
maps = [{row["caseId"]: row for row in report} for report in reports]
eligible = [cid for cid, row in maps[0].items()
            if row["category"] == "pass" and maps[1][cid]["category"] == "pass"]
assert eligible and args.rounds >= 3 and args.iterations > 0 and args.samples >= 2
ranked = sorted(eligible, key=lambda cid: len(json.loads((roots[1] / "fights" / cid / "events.json").read_text("utf8"))["events"]))
selected = list(dict.fromkeys(ranked[round(i * (len(ranked) - 1) / (args.samples - 1))] for i in range(args.samples)))
dlls = [args.before_dll or roots[0] / "bin/libgdcore.dll", args.after_dll or sim_root / "native_sim_cpp/native_sim/libgdcore.dll"]
dlls = [path.resolve() for path in dlls]
if args.after_results is not None:
    assert Path(summaries[1]["dll"]).resolve() == dlls[1], "Verification used a different candidate DLL"
dll_hashes = [hashlib.sha256(path.read_bytes()).hexdigest() for path in dlls]
for summary, digest in zip(summaries, dll_hashes):
    if "dll_sha256" in summary:
        assert summary["dll_sha256"] == digest, "Verification used a different DLL"
if all(row.get("reference_mode") == "native-only" for row in summaries):
    fixture_digest = hashlib.sha256((roots[1] / "fixtures.json").read_bytes()).hexdigest()
    assert all(row["fixtures_sha256"] == fixture_digest for row in summaries), "Verification used different inputs"
    assert all(maps[0][cid]["original_events_sha256"] == maps[1][cid]["original_events_sha256"] for cid in selected)
engines = [NativeSimulator(path) for path in dlls]
for engine in engines:
    engine.lib.gd_sim_set_dbg_events.argtypes = [ctypes.c_int32]
    engine.lib.gd_sim_set_dbg_events.restype = None
fixtures = {row["case_id"]: row for row in json.loads((roots[1] / "fixtures.json").read_text("utf8"))["cases"]}
result = {"scope": "Event-count quantiles among cases passing the recorded strict replay checks in both builds",
          "timing": "interleaved single-process CPU time, setup/combat/teardown and ctypes included; packing, JSON and file I/O excluded",
          "dll_sha256": dll_hashes,
          "rounds": args.rounds, "iterations_per_block": args.iterations, "cases": []}
for cid in selected:
    case = fixtures[cid]
    lines = roots[1] / "align/lineups"
    lineups = {side: json.loads((lines / ("oracle_" + cid + "_" + side + ".json")).read_text("utf8"))
               for side in ("player", "opponent")}
    for side, lineup in lineups.items():
        for field in ("stamina", "health", "regen"):
            if case[side].get(field) is not None:
                lineup[field] = case[side][field]
    packed = [[engine.pack_side(lineups[side], gem_lens=[len(item.get("gems") or []) for item in case[side]["items"]],
                               activation_order=case["native_activation_order"][side])
               for side in ("player", "opponent")] for engine in engines]
    rng_state = next(int(line[6:]) for line in (roots[1] / "fights" / cid / "rng_state.txt").read_text().splitlines()
                     if line.startswith("state="))
    options = dict(seed=case["seed"], round_id=case["round_id"], below_master=case["below_master"],
                   native_activation_order=False, rng_state=rng_state, formal_ev_gate=500000, max_time=90.0,
                   custom_health_multiplier=case["custom_health_multiplier"], replay_initial=case["replay_initial"])
    row = {"case_id": cid, "modes": {}}
    for debug in (False, True):
        for engine, handles in zip(engines, packed):
            engine.lib.gd_sim_set_dbg_events(int(debug))
            for _ in range(3):
                engine.run_one(*handles, **options)
        times = [[], []]
        signatures = [set(), set()]
        for block in range(args.rounds):
            for index in ((0, 1) if block % 2 == 0 else (1, 0)):
                started = time.process_time()
                for _ in range(args.iterations):
                    battle = engines[index].run_one(*packed[index], **options)
                    assert not battle.timed_out and not battle.formal_ev_capped
                    signatures[index].add((battle.player_wins, battle.ticks, battle.event_count, battle.player_hp, battle.opponent_hp))
                times[index].append((time.process_time() - started) / args.iterations * 1000)
        assert len(signatures[0]) == len(signatures[1]) == 1 and signatures[0] == signatures[1], (cid, signatures)
        medians = list(map(statistics.median, times))
        row["modes"]["debug_on" if debug else "debug_off"] = {
            "before_ms": times[0], "after_ms": times[1], "median_ms": medians,
            "after_over_before": medians[1] / medians[0], "signature": list(signatures[0].pop())}
    result["cases"].append(row)
    print(cid, row["modes"], flush=True)
report = args.report or roots[1] / "performance_pair.json"
report.write_text(json.dumps(result, indent=2) + "\n", encoding="utf8")
