"""Alternate fixed-200 batches between processes that each load one native DLL."""
import argparse
from contextlib import ExitStack
import hashlib
import json
import math
import os
from pathlib import Path
import subprocess
import sys
import time

import psutil

from bench_native_corpus import load_simulator, measure, prepare, select_cases
from compare_native_serial import summarize


def worker(dll, reference_path, logical_cpu=None):
    process = psutil.Process()
    if logical_cpu is not None:
        process.cpu_affinity([int(logical_cpu)])
    dll = Path(dll)
    reference = json.loads(Path(reference_path).read_bytes())
    sim = load_simulator(dll)
    signature = hashlib.sha256()
    jobs = list(prepare(sim, select_cases(200), signature))
    if signature.hexdigest() != reference["inputs_sha256"]:
        raise ValueError("Worker inputs differ from the fixed reference")
    print(json.dumps({"ready": True, "pid": os.getpid(), "fights": len(jobs),
                      "priority_class": int(process.nice()), "cpu_affinity": process.cpu_affinity(),
                      "inputs_sha256": signature.hexdigest(), "dll_bytes": dll.stat().st_size,
                      "dll_sha256": hashlib.sha256(dll.read_bytes()).hexdigest()}), flush=True)
    load = psutil.cpu_percent(interval=0.3)
    for command in sys.stdin:
        if command.strip() == "quit":
            return
        if command.strip() != "run":
            raise ValueError("Unknown benchmark worker command")
        result = measure(sim, jobs, 1, load, continuous=True)
        load = result["load_pct_after"]
        if result["results_sha256"] != reference["results_sha256"]:
            raise ValueError("Worker results differ from the fixed reference")
        print(json.dumps(result), flush=True)


class Arm:
    def __init__(self, dll, reference, log_path, logical_cpu=None):
        self.log = log_path.open("w+b")
        affinity_args = [] if logical_cpu is None else [str(logical_cpu)]
        self.process = subprocess.Popen(
            [sys.executable, "-u", str(Path(__file__).resolve()), "--worker", str(dll.resolve()),
             str(reference.resolve()), *affinity_args], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=self.log,
            text=True, encoding="utf8", creationflags=subprocess.CREATE_NO_WINDOW | subprocess.NORMAL_PRIORITY_CLASS)
        try:
            self.ready = self.read()
            if self.ready.get("ready") is not True or self.ready["fights"] != 200:
                raise ValueError("Unexpected worker initialization response")
        except BaseException:
            self.close()
            raise

    def read(self):
        line = self.process.stdout.readline()
        if not line:
            self.log.seek(0)
            detail = self.log.read().decode("utf8", "replace")[-4000:]
            raise RuntimeError(f"Native benchmark worker exited: {detail}")
        return json.loads(line)

    def run(self):
        self.process.stdin.write("run\n")
        self.process.stdin.flush()
        return self.read()

    def close(self):
        try:
            if self.process.poll() is None:
                try:
                    self.process.stdin.write("quit\n")
                    self.process.stdin.flush()
                    self.process.wait(timeout=5)
                except (BrokenPipeError, OSError, subprocess.TimeoutExpired):
                    self.process.kill()
                    self.process.wait(timeout=5)
        finally:
            self.process.stdin.close()
            self.process.stdout.close()
            self.log.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--pairs", type=int, default=8)
    parser.add_argument("--candidate-first", action="store_true")
    parser.add_argument("--candidate-load-first", action="store_true")
    parser.add_argument("--warmup-seconds", type=float, default=60)
    parser.add_argument("--logical-cpu", type=int,
                        help="Pin both arms to the same allowed logical CPU for a controlled comparison")
    args = parser.parse_args()
    if args.logical_cpu is not None and args.logical_cpu not in psutil.Process().cpu_affinity():
        parser.error("--logical-cpu must be in the current process's allowed affinity mask")
    if args.pairs < 2 or args.pairs % 2:
        parser.error("--pairs must be a positive even number")
    if not math.isfinite(args.warmup_seconds) or not 0 <= args.warmup_seconds <= 120:
        parser.error("--warmup-seconds must be between zero and 120")
    if args.out.exists():
        parser.error("Use a new report path")
    args.out.parent.mkdir(parents=True, exist_ok=True)
    reference = json.loads(args.reference.read_bytes())
    report = {"inputs_sha256": reference["inputs_sha256"], "results_sha256": reference["results_sha256"],
              "fights": 200, "workers": 1, "pairs": [], "execution_mode": "separate_single_dll_processes",
              "worker_pids": {}, "worker_priority_class": {}, "worker_cpu_affinity": {}, "load_order": [],
              "report_writes_during_measurement": False, "requested_logical_cpu": args.logical_cpu}
    paths = {"baseline": args.baseline, "candidate": args.candidate}
    labels = ["candidate", "baseline"] if args.candidate_load_first else ["baseline", "candidate"]
    with ExitStack() as resources:
        arms = {}
        for label in labels:
            arm = Arm(paths[label], args.reference, args.out.with_name(args.out.stem + f"_{label}_worker.log"), args.logical_cpu)
            resources.callback(arm.close)
            arms[label] = arm
            if arm.ready["inputs_sha256"] != report["inputs_sha256"]:
                raise ValueError(f"Worker input mismatch for {label}")
            report[label + "_dll_sha256"] = arm.ready["dll_sha256"]
            report[label + "_dll_bytes"] = arm.ready["dll_bytes"]
            report["worker_pids"][label] = arm.ready["pid"]
            report["worker_priority_class"][label] = arm.ready["priority_class"]
            report["worker_cpu_affinity"][label] = arm.ready["cpu_affinity"]
            report["load_order"].append(label)
            if args.logical_cpu is not None and arm.ready["cpu_affinity"] != [args.logical_cpu]:
                raise ValueError(f"Worker affinity mismatch for {label}")
        if len(set(report["worker_pids"].values())) != 2:
            raise ValueError("Both arms must execute in separate processes")

        def run(label):
            result = arms[label].run()
            if result.pop("results_sha256") != report["results_sha256"]:
                raise ValueError(f"Result mismatch for {label}")
            return result

        start = time.perf_counter()
        rounds, batches = 0, []
        while not rounds or time.perf_counter() - start < args.warmup_seconds:
            for label in labels if rounds % 2 == 0 else list(reversed(labels)):
                result = run(label)
                batches.append({"arm": label, **{key: result[key] for key in
                               ("wall_s", "main_thread_cpu_s", "background_load_pct")}})
            rounds += 1
        report["warmup"] = {"minimum_seconds": args.warmup_seconds, "rounds": rounds,
                            "elapsed_seconds": time.perf_counter() - start, "batches": batches}
        try:
            for index in range(args.pairs):
                first = bool(index % 2) != args.candidate_first
                order = ("candidate", "baseline") if first else ("baseline", "candidate")
                pair = {"order": "BA" if first else "AB"}
                for label in order:
                    pair[label] = run(label)
                report["pairs"].append(pair)
                for key in ("main_thread_cpu_s", "wall_s"):
                    report[key] = summarize(report["pairs"], key)
                print(f"{args.candidate.name} {index + 1}/{args.pairs}: "
                      f"CPU {pair['baseline']['main_thread_cpu_s']:.3f} / {pair['candidate']['main_thread_cpu_s']:.3f}s, "
                      f"wall {pair['baseline']['wall_s']:.3f} / {pair['candidate']['wall_s']:.3f}s", flush=True)
        finally:
            args.out.write_text(json.dumps(report, indent=2) + "\n", encoding="utf8")


if __name__ == "__main__":
    if sys.argv[1:2] == ["--worker"]:
        worker(*sys.argv[2:])
    else:
        main()
