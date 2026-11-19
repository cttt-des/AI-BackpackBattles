"""Compare one-fight and batch outcomes from the seeded 1.1.10 entry points."""
import argparse
import ctypes
import hashlib
import json
from pathlib import Path
import sys


STAGE = Path(__file__).resolve().parent
SIM = STAGE / "sim_native"
sys.path[:0] = [str(SIM), str(SIM / "native_sim_cpp")]
from native_sim.sim import NativeSimulator


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dll", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--threads", type=int, default=1)
    args = parser.parse_args()
    simulator = NativeSimulator(args.dll.resolve())
    cases = {
        "native_ring_placement_target3": ("run1143_r13", "run1492_r18", "run948_r18"),
        "native_host_phases_observed_base_current_cpp": ("run989_r18",),
    }
    seeds = (0, 1, 42, (1 << 64) - 1)
    jobs = []
    for directory, ids in cases.items():
        lineups = STAGE / directory / "align/lineups"
        for cid in ids:
            sides = []
            for side in ("player", "opponent"):
                lineup = json.loads((lineups / f"oracle_{cid}_{side}.json").read_bytes())
                sides.append(simulator.pack_side(lineup))
            jobs.extend((cid, seed, *sides) for seed in seeds)
    jobs.append(jobs[0])
    pairs = []
    singles = []
    for cid, seed, player, opponent in jobs:
        options = {"seed": seed, "round_id": player.round_id, "below_master": True,
                   "formal_ev_gate": 500000, "max_time": 90.0}
        pairs.append((player, opponent, simulator.make_options(**options)))
        result = simulator.run_one(player, opponent, training=True, **options)
        if result.timed_out or result.formal_ev_capped or result.event_count == 0:
            raise RuntimeError(f"No natural seeded terminal for {cid} seed {seed}")
        singles.append(result)

    def signature(structure):
        return ctypes.string_at(ctypes.addressof(structure), ctypes.sizeof(structure))

    reference = list(map(signature, singles))
    assert reference[0] == reference[-1], "A reused seed changed after earlier battles"
    for threads in dict.fromkeys((1, args.threads)):
        for order in (pairs, pairs[::-1]):
            results = simulator.run_batch(order, n_threads=threads, training=True)
            actual = list(map(signature, results))
            expected = reference if order is pairs else reference[::-1]
            if actual != expected:
                raise RuntimeError(f"Seeded results changed in the {threads}-thread batch")
    report = {"verified_fights": len(jobs), "threads": args.threads,
              "dll_sha256": hashlib.sha256(args.dll.read_bytes()).hexdigest(),
              "cases": [{"id": cid, "seed": seed, "player_wins": bool(result.player_wins),
                         "events": result.event_count, "ticks": result.ticks}
                        for (cid, seed, *_), result in zip(jobs, singles, strict=True)]}
    args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    print(f"{len(jobs)} seeded fights match across single and {args.threads}-thread batch calls")


if __name__ == "__main__":
    main()
