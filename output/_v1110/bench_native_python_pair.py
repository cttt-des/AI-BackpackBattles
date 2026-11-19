"""Compare pure and Cython Py using the same verified fixtures and runtime data."""
from pathlib import Path
import argparse
import json
import statistics
import subprocess
import sys
import time


stage = Path(__file__).resolve().parent
parser = argparse.ArgumentParser()
parser.add_argument("--fixtures", default="native_kernel_holy")
parser.add_argument("--pure", default="sim_native_pure_holy")
parser.add_argument("--compiled", default="sim_native_cython")
parser.add_argument("--out", default="native_kernel_holy_cython/performance_pair.json")
parser.add_argument("--worker")
parser.add_argument("--rounds", type=int, default=5)
parser.add_argument("--iterations", type=int, default=3)
args = parser.parse_args()
assert args.rounds >= 3 and args.iterations >= 2
report_root = stage / args.fixtures
modes = (args.pure, args.compiled)
assert modes[0] != modes[1] and (args.worker is None or args.worker in modes)

fixtures = json.loads((report_root / "fixtures.json").read_text("utf8"))["cases"]
eligible = []
for case in fixtures:
    cid = case["case_id"]
    result = json.loads((report_root / "cpp" / (cid + ".json")).read_text("utf8"))
    if result["category"] == "pass":
        eligible.append((result["cpp"]["event_count"], cid, case))
eligible.sort()
assert eligible, "No cases passed strict native event verification"
cases = [eligible[i][2] for i in sorted({0, len(eligible) // 2, len(eligible) - 1})]

if args.worker:
    engine = stage / args.worker
    sys.path[:0] = [str(engine), str(engine / "tools")]
    from simulator.gd_core_engine import GDCoreEngine
    from simulator.lineup import load_lineup
    from verify_oracle import _FightEndGate

    results = {}
    for case in cases:
        cid = case["case_id"]
        rng_state = next(int(line[6:]) for line in (report_root / "fights" / cid / "rng_state.txt").read_text().splitlines()
                         if line.startswith("state="))
        side_names = ("player", "opponent")
        inputs = [load_lineup(str(report_root / "align/lineups" / f"oracle_{cid}_{side}.json")) for side in side_names]
        stats = [{key: case[side].get(key) for key in ("health", "regen", "stamina")} for side in side_names]
        gems = [[len(item.get("gems") or []) for item in case[side]["items"]] for side in side_names]
        order = case["native_activation_order"]
        initial = case["replay_initial"]
        extra_initial = {key: initial[key] for key in ("buff_state", "engine_rng") if key in initial}

        def battle():
            fight = GDCoreEngine(*inputs, seed=case["seed"], below_master=case["below_master"],
                                 custom_health_multiplier=case["custom_health_multiplier"],
                                 rng_state=rng_state, reseed_after_player_character=True,
                                 p_activation_order=order["player"], o_activation_order=order["opponent"],
                                 p_gem_lens=gems[0], o_gem_lens=gems[1], p_stats=stats[0], o_stats=stats[1],
                                 probe_bases=(_FightEndGate,), label_rng_enabled=bool(case.get("label_rng", True)),
                                 light_log=True)
            fight.ctx.setReplayInitial(initial["activation_rng_state"], initial["idle_left"], initial["flickers"], **extra_initial)
            fight.run()
            assert fight.fight_ended and not fight.timed_out, cid
            return [fight.player_wins(), fight._ticks, fight.player.get_current_health(), fight.opponent.get_current_health()]

        signature = battle()
        cpu = time.process_time()
        for _ in range(args.iterations):
            assert battle() == signature, cid
        results[cid] = {"ms_per_battle": (time.process_time() - cpu) * 1000 / args.iterations, "signature": signature}
    compiled = sorted(name for name, module in sys.modules.items()
                      if name.startswith("gd_core_py") and str(getattr(module, "__file__", "")).lower().endswith(".pyd"))
    assert bool(compiled) == (args.worker == args.compiled), compiled
    print("[BENCH-PY] " + json.dumps({"results": results, "compiled": compiled}), flush=True)
    raise SystemExit(0)

trials = {mode: [] for mode in modes}
for round_number in range(args.rounds):
    for mode in (modes if round_number % 2 == 0 else modes[::-1]):
        child = subprocess.run([sys.executable, "-u", "-X", "utf8", __file__, "--worker", mode,
                                "--fixtures", args.fixtures, "--pure", args.pure, "--compiled", args.compiled,
                                "--iterations", str(args.iterations)], cwd=stage / mode,
                               capture_output=True, encoding="utf8", errors="replace", check=True)
        rows = [line[len("[BENCH-PY] "):] for line in child.stdout.splitlines() if line.startswith("[BENCH-PY] ")]
        assert len(rows) == 1, child.stderr[-2000:]
        trials[mode].append(json.loads(rows[0]))
    print("Python pair block", round_number + 1, "of", args.rounds, flush=True)
report = {"scope": "Strict event-passing fixtures. CPU time includes assembly and battle, with event materialization off and warm imports.",
          "rounds": args.rounds, "iterations_per_block": args.iterations, "cases": {},
          "compiled_modules": trials[modes[1]][0]["compiled"]}
for case in cases:
    cid = case["case_id"]
    rows = [[block["results"][cid] for block in trials[mode]] for mode in modes]
    signature = rows[0][0]["signature"]
    assert all(row["signature"] == signature for lane in rows for row in lane), cid
    times = [[row["ms_per_battle"] for row in lane] for lane in rows]
    report["cases"][cid] = {"pure_ms": times[0], "cython_ms": times[1],
                            "median_ms": list(map(statistics.median, times)), "signature": signature}
(stage / args.out).write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
