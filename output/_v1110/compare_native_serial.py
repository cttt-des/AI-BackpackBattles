"""Compare native DLLs on alternating AB/BA pairs of the same 200 replays."""
import argparse
import hashlib
import json
import math
from pathlib import Path
import statistics
import time

import psutil

from bench_native_corpus import load_simulator, measure, prepare, select_cases


def summarize(pairs, field):
    ratios = [row["candidate"][field] / row["baseline"][field] for row in pairs]
    return {
        "median_reduction_pct": 100 * (1 - statistics.median(ratios)),
        "candidate_wins": sum(ratio < 1 for ratio in ratios),
        "baseline_wins": sum(ratio > 1 for ratio in ratios),
        "range_reduction_pct": [100 * (1 - max(ratios)), 100 * (1 - min(ratios))],
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--pairs", type=int, default=8)
    parser.add_argument("--candidate-first", action="store_true")
    parser.add_argument("--warmup-seconds", type=float, default=0,
                        help="Continue alternating complete warmup batches for at least this long")
    args = parser.parse_args()
    if args.pairs < 2 or args.pairs % 2:
        parser.error("--pairs must be a positive even number")
    if not math.isfinite(args.warmup_seconds) or not 0 <= args.warmup_seconds <= 120:
        parser.error("--warmup-seconds must be between zero and 120")

    reference = json.loads(args.reference.read_bytes())
    cases = select_cases(200)
    arms = {}
    report = {
        "inputs_sha256": reference["inputs_sha256"],
        "results_sha256": reference["results_sha256"],
        "fights": len(cases),
        "workers": 1,
        "pairs": [],
    }
    for label, path in (("baseline", args.baseline), ("candidate", args.candidate)):
        sim = load_simulator(path)
        digest = hashlib.sha256()
        jobs = list(prepare(sim, cases, digest))
        if digest.hexdigest() != report["inputs_sha256"]:
            raise ValueError(f"Workload differs from the reference for {label}")
        arms[label] = sim, jobs
        report[label + "_dll_sha256"] = hashlib.sha256(path.read_bytes()).hexdigest()
        report[label + "_dll_bytes"] = path.stat().st_size

    load = psutil.cpu_percent(interval=0.3)

    def run(label):
        nonlocal load
        sim, jobs = arms[label]
        result = measure(sim, jobs, 1, load, continuous=True)
        load = result["load_pct_after"]
        if result.pop("results_sha256") != report["results_sha256"]:
            raise ValueError(f"Replay result differs from the reference for {label}")
        return result

    warmup_start = time.perf_counter()
    warmup_rounds = 0
    warmup_batches = []
    while not warmup_rounds or time.perf_counter() - warmup_start < args.warmup_seconds:
        order = list(arms) if warmup_rounds % 2 == 0 else list(reversed(arms))
        for label in order:
            sample = run(label)
            warmup_batches.append({"arm": label, **{key: sample[key] for key in
                                   ("wall_s", "main_thread_cpu_s", "background_load_pct")}})
        warmup_rounds += 1
    report["warmup"] = {"minimum_seconds": args.warmup_seconds, "rounds": warmup_rounds,
                        "elapsed_seconds": time.perf_counter() - warmup_start, "batches": warmup_batches}
    for index in range(args.pairs):
        candidate_first = bool(index % 2) != args.candidate_first
        order = ("candidate", "baseline") if candidate_first else ("baseline", "candidate")
        pair = {"order": "BA" if candidate_first else "AB"}
        for label in order:
            pair[label] = run(label)
        report["pairs"].append(pair)
        for field in ("main_thread_cpu_s", "wall_s"):
            report[field] = summarize(report["pairs"], field)
        args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")
        print(f"{args.candidate.name} {index + 1}/{args.pairs}: "
              f"CPU {pair['baseline']['main_thread_cpu_s']:.3f} / {pair['candidate']['main_thread_cpu_s']:.3f}s, "
              f"wall {pair['baseline']['wall_s']:.3f} / {pair['candidate']['wall_s']:.3f}s", flush=True)


if __name__ == "__main__":
    main()
