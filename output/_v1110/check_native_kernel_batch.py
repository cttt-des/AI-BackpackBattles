"""Compare the three compact kernels directly with accepted native recordings.

The legacy verifier's reference slot contains native events in this audit.
This does not count as an independent Oracle replay or a five-way acceptance.
"""
from pathlib import Path
import argparse
import hashlib
import json
import shutil
import subprocess
import sys

repo = Path(__file__).resolve().parents[2]
stage = repo / "output/_v1110"
ap = argparse.ArgumentParser()
ap.add_argument("--source", default="native_corpus/expand")
ap.add_argument("--out", default="native_kernel_baseline")
ap.add_argument("--limit", type=int, default=100)
ap.add_argument("--prepare-only", action="store_true")
ap.add_argument("--reuse-inputs", action="store_true")
legs = ap.add_mutually_exclusive_group()
legs.add_argument("--cpp-only", action="store_true", help="Reuse GD/Py results only when their recorded source hashes still match")
legs.add_argument("--core-only", action="store_true", help="Run GD/Py and leave C++ pending while the DLL builds")
args = ap.parse_args()
assert not args.cpp_only or args.reuse_inputs
reference = stage / args.source
out = stage / args.out
sim = stage / "sim_native"
out.mkdir(parents=True, exist_ok=True)

if not args.reuse_inputs:
    source_cases = json.loads((reference / "cases.json").read_text("utf8"))["cases"]
    runtime = json.loads((sim / "assets/gd_core_runtime.json").read_text("utf8"))["items"]
    selected = []
    for case in source_cases:
        cid = case["case_id"]
        source = reference / cid
        if not (source / "reference_manifest.json").is_file():
            continue
        manifest = json.loads((source / "reference_manifest.json").read_text("utf8"))
        assert manifest["version"] == "1.1.10", cid
        events = json.loads((source / "events.json").read_text("utf8"))
        rows = events["events"]
        assert len(rows) == events["event_count"] and rows[-1]["type"] == {"player": 111, "opponent": 112}[events["winner"]], cid
        assert round(rows[-1]["timestamp"] * 60) == round(events["combat_time"] * 60), cid
        lineups = json.loads((source / "lineups.json").read_text("utf8"))
        assert all(events[key] == lineups[key] for key in ("seed", "run_id", "round_id", "opp_run_id", "opp_round_id")), cid
        boundaries = json.loads((source / "boundaries.json").read_text("utf8"))
        order = {"player": [], "opponent": []}
        for entry in boundaries["prepare"]["order"]:
            side = "player" if entry["owner"] == 1 else "opponent"
            matches = [i for i, item in enumerate(lineups[side]["items"])
                       if item["identifier"] == entry["name"]
                       and [item["top_left"][axis] for axis in ("x", "y")] == entry["top_left"]]
            assert len(matches) == 1, (cid, entry)
            order[side].append(matches[0])
        assert all(sorted(order[side]) == list(range(len(lineups[side]["items"]))) for side in order), cid
        idle = [None, None]
        for timer in boundaries["idle_animation_timers"]:
            idle[timer["owner"]] = timer.get("left_precise", timer["left"])
        assert all(value is not None for value in idle), cid
        flickers = boundaries["flicker_states"]
        for flicker in flickers:
            if "limits" not in flicker:
                descriptor = runtime[flicker["identity"]["name"]]["descr"]
                flicker["limits"] = [descriptor["flicker" + key] for key in ("MinDist", "MaxDist", "MinSpeed", "MaxSpeed")]
        lineups["replay_controls"]["replay_initial"] = {
            "activation_rng_state": boundaries["before_activate"]["state"], "idle_left": idle, "flickers": flickers}
        if "buff_state" in boundaries["before_activate"]:
            buff_state = boundaries["before_activate"]["buff_state"]
            assert len(buff_state) == 2 and all(row[3] == 0 for side in buff_state for row in side), cid
            lineups["replay_controls"]["replay_initial"]["buff_state"] = buff_state
        lineups["replay_controls"]["native_activation_order"] = order
        target = out / "fights" / cid
        target.mkdir(parents=True, exist_ok=True)
        (target / "lineups.json").write_text(json.dumps(lineups, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
        (target / "rng_state.txt").write_text("seed=%s\nstate=%s\n" % (boundaries["prepare"]["seed"], boundaries["prepare"]["state"]), encoding="utf8")
        shutil.copyfile(source / "events.json", target / "events.json")
        selected.append(case)
        if args.limit and len(selected) >= args.limit:
            break
    assert selected
    (out / "cases.json").write_text(json.dumps({"cases": selected}, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
else:
    selected = json.loads((out / "cases.json").read_text("utf8"))["cases"]

status = {"scope": "Native-frame reference versus GD/pure Python/C++; Oracle leg NOT run", "cases": len(selected),
          "reference": str(reference), "kernel_sha256": {}}
for folder in ("gd_core", "gd_core_items"):
    for path in sorted((sim / folder).rglob("*.gd")):
        status["kernel_sha256"][path.relative_to(sim).as_posix()] = hashlib.sha256(path.read_bytes()).hexdigest()
status["runtime_data_sha256"] = hashlib.sha256((sim / "assets/gd_core_runtime.json").read_bytes()).hexdigest()
if args.prepare_only:
    (out / "status.json").write_text(json.dumps(status, indent=2) + "\n", encoding="utf8")
    print("Prepared native inputs", len(selected), out)
    raise SystemExit(0)
common = ["--fights-root", str(out / "fights"), "--align-root", str(out / "align"), "--cases-json", str(out / "fixtures.json")]
if args.cpp_only:
    previous = json.loads((out / "status.json").read_text("utf8"))
    for key in ("kernel_sha256", "runtime_data_sha256", "cases", "reference"):
        assert previous[key] == status[key], ("GD/Py source or case provenance changed", key)
    alignment = json.loads((out / "alignment.json").read_text("utf8"))
    assert {row["caseId"] for row in alignment["perCase"]} == {row["case_id"] for row in selected}
    status["three_core_exit"] = previous["three_core_exit"]
else:
    with (out / "three_core.log").open("wb") as log:
        status["three_core_exit"] = subprocess.run([
            sys.executable, "-u", "-X", "utf8", "tools/verify_oracle.py", *common,
            "--alignment-out", str(out / "alignment.json"), "--gd-jobs", "1", "--py-jobs", "1", "--compare-jobs", "1", "--force"],
            cwd=sim, stdout=log, stderr=subprocess.STDOUT).returncode
if args.core_only:
    (out / "status.json").write_text(json.dumps(status, indent=2) + "\n", encoding="utf8")
    raise SystemExit(status["three_core_exit"])
status["dll_sha256"] = hashlib.sha256((sim / "native_sim_cpp/native_sim/libgdcore.dll").read_bytes()).hexdigest()
with (out / "cpp.log").open("wb") as log:
    status["cpp_exit"] = subprocess.run([
        sys.executable, "-u", "-X", "utf8", "tools/_cpp_verify_events.py", *common,
        "--case-ids", str(out / "cases.json"), "--strict-gem-origins", "--original-dir", str(reference),
        "--out", str(out / "cpp")], cwd=sim, stdout=log, stderr=subprocess.STDOUT).returncode
(out / "status.json").write_text(json.dumps(status, indent=2) + "\n", encoding="utf8")
print(json.dumps({key: value for key, value in status.items() if key != "kernel_sha256"}, indent=2))
raise SystemExit(0 if not status["three_core_exit"] and not status["cpp_exit"] else 1)
