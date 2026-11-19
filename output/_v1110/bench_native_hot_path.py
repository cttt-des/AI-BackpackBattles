"""Measure one native DLL on the fixed 200-fight, one-thread workload."""
import argparse
import ctypes
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import time

import psutil


STAGE = Path(__file__).resolve().parent
ROOT = STAGE.parents[1]
SIM = STAGE / "sim_native"
sys.path.insert(0, str(ROOT))
from trainer.evaluator import OpponentPool


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dll", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    opponents = OpponentPool().sample((450, 650), 50, seed=42)[:25]
    assert len(opponents) == 25
    demand = hashlib.sha256(json.dumps(opponents, sort_keys=True).encode()).hexdigest()
    before_load = psutil.cpu_percent(interval=0.3)
    wall_start = time.perf_counter()
    cpu_start = time.process_time()
    binding = SIM / "native_sim_cpp/native_sim/sim.py"
    spec = importlib.util.spec_from_file_location("_bench_native_binding", binding)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    sim = module.NativeSimulator(lib_path=args.dll.resolve(), runtime_path=SIM / "assets/gd_core_runtime.json")
    packed = [sim.pack_side(opponent, strict=True) for opponent in opponents]
    player = packed[0]
    pairs = [(player, opponent, sim.make_options(round_id=player.round_id, seed=2026_11_11 + index * 10000 + seed,
                                                  formal_ev_gate=500000, max_time=90.0))
             for index, opponent in enumerate(packed) for seed in range(8)]
    native_start = time.perf_counter()
    native_cpu_start = time.process_time()
    outcomes = sim.run_batch(pairs, n_threads=1, training=True)
    kernel_cpu = time.process_time() - native_cpu_start
    kernel_wall = time.perf_counter() - native_start
    cpu = time.process_time() - cpu_start
    wall = time.perf_counter() - wall_start
    memory = psutil.Process().memory_info()
    after_load = psutil.cpu_percent(interval=0.3)
    signature = hashlib.sha256()
    for result in outcomes:
        signature.update(ctypes.string_at(ctypes.addressof(result), ctypes.sizeof(result)))
    report = {
        "dll_sha256": hashlib.sha256(args.dll.read_bytes()).hexdigest(), "inputs_sha256": demand,
        "results_sha256": signature.hexdigest(), "fights": len(outcomes), "workers": 1,
        "event_gate_hits": sum(result.formal_ev_capped for result in outcomes),
        "timed_out": sum(result.timed_out for result in outcomes),
        "wall_s": wall, "fights_per_second": len(outcomes) / wall, "cpu_s": cpu,
        "kernel_wall_s": kernel_wall, "kernel_cpu_s": kernel_cpu,
        "peak_working_set_bytes": memory.peak_wset, "private_working_bytes": memory.private,
        "load_pct_before": before_load, "load_pct_after": after_load,
    }
    args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(f"{args.dll.name}: {report['fights_per_second']:.2f} fights/s; {cpu:.2f} CPU s; "
          f"{memory.peak_wset / (1024**2):.1f} MiB peak; {report['results_sha256'][:12]}")


if __name__ == "__main__":
    main()
