"""Measure one native DLL on the fixed 200-fight workload."""
import argparse
import ctypes
import hashlib
import importlib.util
import json
from pathlib import Path
import statistics
import sys
import time

import psutil


STAGE = Path(__file__).resolve().parent
ROOT = STAGE.parents[1]
SIM = STAGE / "sim_native"
sys.path.insert(0, str(ROOT))
from trainer.evaluator import OpponentPool


def load_simulator(dll):
    binding = SIM / "native_sim_cpp/native_sim/sim.py"
    spec = importlib.util.spec_from_file_location("_bench_native_binding", binding)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.NativeSimulator(lib_path=dll.resolve(), runtime_path=SIM / "assets/gd_core_runtime.json")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dll", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--workers", type=int, default=1)
    args = parser.parse_args()
    if args.workers < 1:
        parser.error("--workers must be positive")
    opponents = OpponentPool().sample((450, 650), 50, seed=42)[:25]
    assert len(opponents) == 25
    demand = hashlib.sha256(json.dumps(opponents, sort_keys=True).encode()).hexdigest()
    before_load = psutil.cpu_percent(interval=0.3)
    battery_before = psutil.sensors_battery()
    wall_start = time.perf_counter()
    cpu_start = time.process_time()
    sim = load_simulator(args.dll)
    packed = [sim.pack_side(opponent, strict=True) for opponent in opponents]
    player = packed[0]
    pairs = [(player, opponent, sim.make_options(round_id=player.round_id, seed=2026_11_11 + index * 10000 + seed,
                                                  formal_ev_gate=500000, max_time=90.0))
             for index, opponent in enumerate(packed) for seed in range(8)]
    native_start = time.perf_counter()
    native_cpu_start = time.process_time()
    outcomes = sim.run_batch(pairs, n_threads=args.workers, training=True)
    kernel_cpu = time.process_time() - native_cpu_start
    kernel_wall = time.perf_counter() - native_start
    cpu = time.process_time() - cpu_start
    wall = time.perf_counter() - wall_start
    memory = psutil.Process().memory_info()
    after_load = psutil.cpu_percent(interval=0.3)
    battery_after = psutil.sensors_battery()
    assert len(outcomes) == len(pairs)
    signature = hashlib.sha256()
    for result in outcomes:
        signature.update(ctypes.string_at(ctypes.addressof(result), ctypes.sizeof(result)))
    durations = [result.combat_time for result in outcomes]
    report = {
        "dll_sha256": hashlib.sha256(args.dll.read_bytes()).hexdigest(), "inputs_sha256": demand,
        "results_sha256": signature.hexdigest(), "fights": len(outcomes), "workers": args.workers,
        "event_gate_hits": sum(result.formal_ev_capped for result in outcomes),
        "timed_out": sum(result.timed_out for result in outcomes),
        "combat_seconds": {
            "minimum": min(durations), "median": statistics.median(durations),
            "mean": statistics.mean(durations), "maximum": max(durations),
        },
        "wall_s": wall, "fights_per_second": len(outcomes) / wall, "cpu_s": cpu,
        "kernel_wall_s": kernel_wall, "kernel_cpu_s": kernel_cpu,
        "peak_working_set_bytes": memory.peak_wset, "private_commit_bytes": memory.private,
        "load_pct_before": before_load, "load_pct_after": after_load,
        "on_ac_before": battery_before.power_plugged if battery_before else None,
        "on_ac_after": battery_after.power_plugged if battery_after else None,
    }
    args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(f"{args.dll.name}: {report['fights_per_second']:.2f} fights/s; {cpu:.2f} CPU s; "
          f"{memory.peak_wset / (1024**2):.1f} MiB peak; {report['results_sha256'][:12]}")


if __name__ == "__main__":
    main()
