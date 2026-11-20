"""Benchmark original replays sampled across the full duration distribution."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import ctypes
import hashlib
import json
from pathlib import Path
import statistics
import time

import psutil

from bench_native_hot_path import STAGE, load_simulator
from check_native_corpus_gate import reference_index


def read_header(path):
    with path.open("rb") as stream:
        prefix = stream.read(8192)
    header, marker, _ = prefix.partition(b'"events"')
    if not marker:
        raise ValueError(f"Missing original event header in {path}")
    return json.loads(header.rstrip().removesuffix(b",") + b"}")


def select_cases(count):
    references = reference_index(STAGE / "native_host_observed_reference_plan.json")
    cases = []
    for cohort in references.values():
        for case_id, ref in cohort.items():
            header = read_header(STAGE / ref["path"] / case_id / "events.json")
            cases.append((float(header["combat_time"]), case_id, header["winner"]))
    if not 0 < count <= len(cases):
        raise ValueError(f"Expected between 1 and {len(cases)} replays")
    cases.sort()
    return [cases[(2 * i + 1) * len(cases) // (2 * count)] for i in range(count)]


def prepare(sim, cases, inputs_digest):
    plan = json.loads((STAGE / "native_host_phases_reuse_plan.json").read_bytes())
    folders = [STAGE / (row["name"] + "_cpp") for row in plan]
    folders.extend(STAGE / name for name in (
        "native_host_rng_phases_new_expand_cpp", "native_host_phases_observed_base_last_cpp",
        "native_hot_verify_host_phases_observed_base_current",
    ))
    locations = {}
    for folder in folders:
        for case in json.loads((folder / "fixtures.json").read_bytes())["cases"]:
            case_id = case["case_id"]
            if case_id in locations:
                raise ValueError(f"Duplicate corpus fixture {case_id}")
            locations[case_id] = folder, case
    if len(locations) != 2604:
        raise ValueError(f"Expected 2604 distinct fixtures, found {len(locations)}")

    for duration, case_id, winner in cases:
        folder, case = locations[case_id]
        inputs_digest.update(json.dumps(case, sort_keys=True).encode())
        sides = []
        for side in ("player", "opponent"):
            data = (folder / "align/lineups" / f"oracle_{case_id}_{side}.json").read_bytes()
            inputs_digest.update(data)
            lineup = json.loads(data)
            fixture = case[side]
            for field in ("stamina", "health", "regen"):
                if fixture.get(field) is not None:
                    lineup[field] = fixture[field]
            sides.append(sim.pack_side(lineup, gem_lens=[len(item.get("gems") or []) for item in fixture["items"]],
                                       activation_order=case["native_activation_order"][side]))
        rng_file = (folder / "fights" / case_id / "rng_state.txt").read_text("utf8")
        rng_state = next(int(line[6:]) & ((1 << 64) - 1) for line in rng_file.splitlines() if line.startswith("state="))
        inputs_digest.update(str(rng_state).encode())
        options = {
            "seed": int(case["seed"]), "round_id": int(case["round_id"]), "below_master": case["below_master"],
            "native_activation_order": False, "reseed_after_player_character": True, "rng_state": rng_state,
            "formal_ev_gate": 500000, "max_time": 90.0, "replay_initial": case["replay_initial"],
            "custom_health_multiplier": float(case["custom_health_multiplier"]),
            "label_rng_enabled": bool(case.get("label_rng", True)),
        }
        yield case_id, sides, options, round(duration * 60), winner


def measure(sim, jobs, workers, load_before, *, continuous):
    before = psutil.sensors_battery()

    def replay(job):
        _, sides, options, _, _ = job
        return sim.run_one(*sides, **options)

    psutil.cpu_percent(interval=None)
    wall_start, cpu_start, thread_start = time.perf_counter(), time.process_time(), time.thread_time()
    if workers == 1:
        results = list(map(replay, jobs))
    else:
        with ThreadPoolExecutor(max_workers=workers) as executor:
            results = list(executor.map(replay, jobs))
    thread_cpu = time.thread_time() - thread_start
    cpu, wall = time.process_time() - cpu_start, time.perf_counter() - wall_start
    system_load = psutil.cpu_percent(interval=None)
    logical_cpus = psutil.cpu_count()
    background_load = max(0.0, system_load - 100 * cpu / (wall * logical_cpus)) if logical_cpus else None
    load_after = system_load if continuous else psutil.cpu_percent(interval=0.3)
    after = psutil.sensors_battery()
    signature, durations = hashlib.sha256(), []
    for (case_id, _, _, terminal_tick, winner), result in zip(jobs, results, strict=True):
        if (result.formal_ev_capped or result.timed_out
                or bool(result.player_wins) != (winner == "player")
                or round(result.combat_time * 60) != terminal_tick):
            raise ValueError(f"Replay terminal differs from the original in {case_id}")
        durations.append(result.combat_time)
        signature.update(ctypes.string_at(ctypes.addressof(result), ctypes.sizeof(result)))
    return {
        "results_sha256": signature.hexdigest(), "matched_original_terminal": len(results),
        "wall_s": wall, "cpu_s": cpu, "fights_per_second": len(results) / wall,
        "combat_seconds": {"minimum": min(durations), "median": statistics.median(durations),
                           "mean": statistics.mean(durations), "maximum": max(durations)},
        "on_ac_before": before.power_plugged if before else None,
        "on_ac_after": after.power_plugged if after else None,
        "load_pct_before": load_before, "load_pct_after": load_after,
        "system_load_pct": system_load, "background_load_pct": background_load,
        "main_thread_cpu_s": thread_cpu,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dll", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--size", type=int, default=200)
    parser.add_argument("--workers", type=int, default=1)
    parser.add_argument("--repeat", type=int, default=1, help="Run consecutive batches with the same packed inputs")
    args = parser.parse_args()
    if min(args.workers, args.repeat) < 1:
        parser.error("--workers and --repeat must be positive")
    cases = select_cases(args.size)
    sim = load_simulator(args.dll)
    inputs_digest = hashlib.sha256()
    jobs = list(prepare(sim, cases, inputs_digest))
    report = {
        "workload": "duration-stratified original replays with packed inputs and logging disabled",
        "dll_sha256": hashlib.sha256(args.dll.read_bytes()).hexdigest(),
        "inputs_sha256": inputs_digest.hexdigest(),
        "fights": len(jobs), "workers": args.workers,
        "case_ids": [job[0] for job in jobs],
    }
    load = psutil.cpu_percent(interval=0.3)
    samples = []
    for _ in range(args.repeat):
        sample = measure(sim, jobs, args.workers, load, continuous=args.repeat > 1)
        samples.append(sample)
        load = sample["load_pct_after"]
    if args.repeat == 1:
        report.update(samples[0])
    else:
        identity = {key: samples[0][key] for key in ("results_sha256", "combat_seconds")}
        for sample in samples:
            if any(sample.pop(key) != value for key, value in identity.items()):
                raise ValueError("Replay results changed across repeated batches")
        rates = [sample["fights_per_second"] for sample in samples]
        report.update(identity, repeat=len(samples), median_fights_per_second=statistics.median(rates),
                      minimum_fights_per_second=min(rates), samples=samples)
    args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
    if args.repeat == 1:
        print(f"{args.dll.name}: {report['fights_per_second']:.2f} replays/s; "
              f"{report['combat_seconds']['mean']:.2f} s of combat on average; {report['results_sha256'][:12]}")
    else:
        print(f"{args.dll.name}: {args.repeat} batches, median {report['median_fights_per_second']:.2f} replays/s, "
              f"minimum {report['minimum_fights_per_second']:.2f}; {report['results_sha256'][:12]}")


if __name__ == "__main__":
    main()
