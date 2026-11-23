"""Run the existing strict replay checks with two independent cohorts at a time."""
import argparse
import psutil
psutil.Process().nice(psutil.BELOW_NORMAL_PRIORITY_CLASS)
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
    # This subprocess is opened only after the complete AB decision. Keep the
    # affected-path repeat ahead of any strict event cohorts, also for a parent
    # qualifier that was already waiting before this guard was added.
    directed = WORK / 'post_ab_directed_regressions.json'
    if not directed.exists():
        subprocess.run([*PYTHON, str(WORK / 'verify_factory_after_ab.py')], check=True)
    proof = json.loads(directed.read_bytes())
    import hashlib
    assert proof['passed'] and proof['dll_sha256'] == hashlib.sha256(dll.read_bytes()).hexdigest()
    gate = WORK / f"{args.name}_full_gate.json"
    prefix = f"native_event_factory_bundle_{args.name}_"
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
            command = [WORK / "audit_verify.py", "--case-ids", inputs / "cases.json",
                       "--fights-root", inputs / "fights", "--align-root", inputs / "align",
                       "--cases-json", inputs / "fixtures.json", "--strict-gem-origins", "--strict-item-origins",
                       "--original-dir", original, "--native-only", "--out", report, "--dll", dll]
            receipt = report
        log = Path(str(report) + ".log")
        print(f"Checking {name} ({job['total']} fights)", flush=True)
        with log.open("wb") as output:
            subprocess.run([*PYTHON, *map(str, command)], stdout=output, stderr=subprocess.STDOUT, check=True)
            if name == "native_host_phases_observed_base_current":
                # The fixture-preparing wrapper launches a child verifier; audit
                # the same 124 cases explicitly in this fresh DLL process too.
                audit_command=[WORK / "audit_verify.py", "--case-ids", report / "cases.json",
                    "--fights-root", report / "fights", "--align-root", report / "align",
                    "--cases-json", report / "fixtures.json", "--strict-gem-origins", "--strict-item-origins",
                    "--original-dir", original, "--native-only", "--out", receipt, "--dll", dll,
                    "--ring-placement-observations", PLACEMENT]
                subprocess.run([*PYTHON,*map(str,audit_command)],stdout=output,stderr=subprocess.STDOUT,check=True)
        audit=json.loads((receipt / "native_type_audit.json").read_bytes())
        assert audit['coverage']['type_mismatch']==0 and audit['verifier_exit_code']==0
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
