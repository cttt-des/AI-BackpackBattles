"""CPU baseline for the native-aligned candidate; not a before/after speed claim."""
from pathlib import Path
import ctypes
import json
import statistics
import sys
import time

repo = Path(__file__).resolve().parents[2]
stage = repo / "output/_v1110"
sim_root = stage / "sim_native"
sys.path[:0] = [str(sim_root), str(sim_root / "native_sim_cpp")]
from native_sim.sim import NativeSimulator

out = stage / "native_core_check"
case = json.loads((out / "fixtures.json").read_text("utf8"))["cases"][0]
cid = case["case_id"]
gd = out / "align/lineups"
print("Benchmark case", cid, flush=True)
sim = NativeSimulator()
sim.lib.gd_sim_set_dbg_events.argtypes = [ctypes.c_int32]
sim.lib.gd_sim_set_dbg_events.restype = None
order = case["native_activation_order"]
lineups = {side: json.loads((gd / ("oracle_" + cid + "_" + side + ".json")).read_text("utf8")) for side in ("player", "opponent")}
for side, lineup in lineups.items():
    for field in ("stamina", "health", "regen"):
        if case[side].get(field) is not None:
            lineup[field] = case[side][field]

def pack():
    return [sim.pack_side(lineups[side], gem_lens=[len(item.get("gems") or []) for item in case[side]["items"]],
                          activation_order=order[side]) for side in ("player", "opponent")]

handles = pack()
state = next(int(line[6:]) for line in (out / "fights" / cid / "rng_state.txt").read_text().splitlines() if line.startswith("state="))
options = dict(seed=case["seed"], round_id=case["round_id"], below_master=case["below_master"],
               native_activation_order=False, rng_state=state, formal_ev_gate=500000, max_time=90.0,
               custom_health_multiplier=case["custom_health_multiplier"], replay_initial=case["replay_initial"])
iterations, rounds = 100, 3
result = {"case_id": cid, "iterations_per_round": iterations, "rounds": rounds,
          "timing": "single process CPU seconds, ctypes overhead included; no file logging or event serialization",
          "scope": "one previously five-way-verified round-1 case; no comparative speedup claim",
          "modes": {}}
start = time.process_time()
for _ in range(iterations):
    pack()
result["packing_us_per_pair"] = (time.process_time() - start) / iterations * 1e6
for debug in (False, True):
    sim.lib.gd_sim_set_dbg_events(int(debug))
    for _ in range(5):
        sim.run_one(*handles, **options)
    elapsed = []
    signatures = set()
    for _ in range(rounds):
        start = time.process_time()
        for _ in range(iterations):
            battle = sim.run_one(*handles, **options)
            assert not battle.timed_out and not battle.formal_ev_capped
            signatures.add((battle.player_wins, battle.ticks, battle.event_count, battle.player_hp, battle.opponent_hp))
        elapsed.append(time.process_time() - start)
    assert len(signatures) == 1, signatures
    seconds = statistics.median(elapsed) / iterations
    result["modes"]["debug_events_on" if debug else "debug_events_off"] = {
        "cpu_round_seconds": elapsed, "median_cpu_ms_per_battle": seconds * 1000,
        "battles_per_cpu_second": 1 / seconds, "result_signature": list(signatures.pop())}
sim.lib.gd_sim_set_dbg_events(0)
(out / "performance.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf8")
print(json.dumps(result, indent=2), flush=True)
