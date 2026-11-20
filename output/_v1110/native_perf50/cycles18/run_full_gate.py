"""Run the existing strict replay checks with two independent cohorts at a time."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import subprocess
import sys

WORK = Path(__file__).resolve().parent
STAGE = WORK.parents[1]
PLACEMENT = STAGE / "native_controlled_prismatic_run948_placement"
PYTHON = [sys.executable, "-u", "-X", "utf8"]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name")
    args = parser.parse_args()
    dll = WORK / f"{args.name}.dll"
    gate = WORK / f"{args.name}_full_gate.json"
    prefix = f"native_cycle18_{args.name}_"
    plan = json.loads((STAGE / "native_host_phases_reuse_plan.json").read_bytes())
    plan.extend((
        {"source": "native_host_observed_expand/expand", "name": "native_host_rng_phases_new_expand", "total": 19},
        {"source": "native_host_observed_base/base", "name": "native_host_phases_observed_base_current", "total": 124},
        {"source": "native_host_observed_base/base", "name": "native_host_phases_observed_base_last", "total": 8},
    ))

    def check(job):
        name = job["name"]
        report = STAGE / (prefix + name.removeprefix("native_"))
        inputs = STAGE / (name + "_cpp")
        original = STAGE / job["source"]
        if name == "native_host_phases_observed_base_current":
            ids = WORK / f"{args.name}_base_current_ids.json"
            cases = json.loads((inputs / "cases.json").read_bytes())["cases"]
            ids.write_text(json.dumps([case["case_id"] for case in cases]), encoding="utf8")
            command = [STAGE / "check_native_kernel_batch.py", "--source", original, "--out", report.name,
                       "--limit", "0", "--direct-cpp", "--strict-item-origins", "--native-util-clock",
                       "--dll", dll, "--case-ids", ids, "--ring-placement-observations", PLACEMENT]
            receipt = report / "cpp"
        else:
            command = [STAGE / "sim_native/tools/_cpp_verify_events.py", "--case-ids", inputs / "cases.json",
                       "--fights-root", inputs / "fights", "--align-root", inputs / "align",
                       "--cases-json", inputs / "fixtures.json", "--strict-gem-origins", "--strict-item-origins",
                       "--original-dir", original, "--native-only", "--out", report, "--dll", dll]
            receipt = report
        log = Path(str(report) + ".log")
        print(f"Checking {name} ({job['total']} fights)", flush=True)
        with log.open("wb") as output:
            subprocess.run([*PYTHON, *map(str, command)], stdout=output, stderr=subprocess.STDOUT, check=True)
        summary = json.loads((receipt / "summary.json").read_bytes())
        if summary["total"] != job["total"] or summary["passed"] != job["total"]:
            raise ValueError(f"A replay did not match in {name}. See {log}")
        print(f"{name}: {summary['passed']}/{summary['total']} strict passes", flush=True)
        return str(receipt)

    # Start the long cohorts first so a small reference batch cannot delay them.
    priority = {"native_host_phases_reuse_2": 1}
    plan.sort(key=lambda job: (priority.get(job["name"], 0), job["total"]), reverse=True)
    with ThreadPoolExecutor(max_workers=2) as pool:
        reports = list(pool.map(check, plan))
    subprocess.run([*PYTHON, str(STAGE / "check_native_corpus_gate.py"), "--dll", str(dll), "--report", *reports,
                    "--host-observed-plan", str(STAGE / "native_host_observed_reference_plan.json"),
                    "--ring-placement-observations", str(PLACEMENT), "--out", str(gate)], check=True)
    subprocess.run([*PYTHON, str(STAGE / "compare_native_event_receipts.py"),
                    "--baseline", str(STAGE / "native_perf50/cycles11/inline_timers_full_gate.json"), "--candidate", str(gate),
                    "--baseline-prefix", "native_cycle11_inline_timers_", "--candidate-prefix", prefix,
                    "--out", str(WORK / f"{args.name}_event_hashes.json")], check=True)


if __name__ == "__main__":
    main()
