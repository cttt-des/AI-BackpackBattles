"""Compare the three compact kernels directly with accepted native recordings.

The legacy verifier's reference slot contains native events in this audit.
This does not count as an independent Oracle replay or a five-way acceptance.
"""
from pathlib import Path
import argparse
import hashlib
import json
import math
import shutil
import subprocess
import sys

repo = Path(__file__).resolve().parents[2]
stage = repo / "output/_v1110"
ap = argparse.ArgumentParser()
ap.add_argument("--source", default="native_corpus/expand")
ap.add_argument("--out", default="native_kernel_baseline")
ap.add_argument("--limit", type=int, default=100)
ap.add_argument("--case-ids", type=Path, help="JSON list of recorded case IDs to check")
ap.add_argument("--prepare-only", action="store_true")
ap.add_argument("--reuse-inputs", action="store_true")
ap.add_argument("--dll", type=Path, help="Use a separate candidate DLL")
ap.add_argument("--strict-item-origins", action="store_true", help="Require ordinary item identifiers and board cells")
ap.add_argument("--native-util-clock", action="store_true", help="Use the original process clock recorded at combat activation")
legs = ap.add_mutually_exclusive_group()
legs.add_argument("--cpp-only", action="store_true", help="Reuse GD/Py results only when their recorded source hashes still match")
legs.add_argument("--direct-cpp", action="store_true", help="Check C++ against native events without running GD, Py or Oracle")
legs.add_argument("--core-only", action="store_true", help="Run GD/Py and leave C++ pending while the DLL builds")
args = ap.parse_args()
if args.case_ids and args.reuse_inputs:
    ap.error("--case-ids selects new inputs and cannot be used with --reuse-inputs")
assert not args.cpp_only or args.reuse_inputs
if args.strict_item_origins and not args.direct_cpp:
    ap.error("--strict-item-origins requires --direct-cpp")
reference = stage / args.source
out = stage / args.out
sim = stage / "sim_native"
out.mkdir(parents=True, exist_ok=True)

if not args.reuse_inputs:
    source_cases = json.loads((reference / "cases.json").read_text("utf8"))["cases"]
    if args.case_ids:
        requested = json.loads(args.case_ids.read_bytes())
        if (not isinstance(requested, list) or not requested
                or not all(isinstance(cid, str) for cid in requested)
                or len(set(requested)) != len(requested)):
            ap.error("--case-ids requires a nonempty, unique list of case IDs")
        by_id = {case["case_id"]: case for case in source_cases}
        missing = [cid for cid in requested if cid not in by_id
                   or not (reference / cid / "reference_manifest.json").is_file()]
        if missing:
            ap.error("Requested cases have no complete source recording: " + ", ".join(missing[:10]))
        source_cases = [by_id[cid] for cid in requested]
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
            if flicker["inside_tree"] and flicker.get("path", "").startswith("/root/Main/Combat/Opponent/"):
                flicker["native_opponent"] = True
            if "limits" not in flicker:
                descriptor = runtime[flicker["identity"]["name"]]["descr"]
                flicker["limits"] = [descriptor["flicker" + key] for key in ("MinDist", "MaxDist", "MinSpeed", "MaxSpeed")]
        lineups["replay_controls"]["replay_initial"] = {
            "activation_rng_state": boundaries["before_activate"]["state"], "idle_left": idle, "flickers": flickers}
        host_draws = boundaries.get("host_rng_draws")
        if args.native_util_clock or host_draws:
            util_time = boundaries["combat_start"]["util_time"]
            assert math.isfinite(float(util_time)) and float(util_time) >= 0, cid
            lineups["replay_controls"]["replay_initial"]["util_time"] = util_time
        if host_draws:
            schedule = []
            for draw in host_draws:
                assert draw["kind"] in ("focus_out", "process_timer"), (cid, draw)
                tick = round(float(draw["combat_time"]) * 60)
                assert 0 <= tick < (1 << 31) and (not schedule or tick >= schedule[-1][0]), (cid, draw)
                for state in ("before", "after"):
                    assert -(1 << 63) <= int(draw[state]) < (1 << 63), (cid, draw)
                schedule.append([tick, draw["before"], draw["after"]])
            lineups["replay_controls"]["replay_initial"]["host_rng_draws"] = schedule
        if "opening_idle_delta" in boundaries:
            lineups["replay_controls"]["replay_initial"]["native_scene_delays"] = True
        if "buff_state" in boundaries["before_activate"]:
            buff_state = boundaries["before_activate"]["buff_state"]
            assert len(buff_state) == 2 and all(row[3] == 0 for side in buff_state for row in side), cid
            lineups["replay_controls"]["replay_initial"]["buff_state"] = buff_state
        activation = boundaries["before_activate"]
        preparation = boundaries["prepare"]
        if "damage_number_mode" in activation and "engine_seed" in preparation and "engine_seed" in activation:
            assert activation["visible_combat_shakes"] == 0, (cid, "Live pre-activation critical label")
            lineups["replay_controls"]["replay_initial"]["engine_rng"] = [
                preparation["engine_seed"], preparation.get("engine_offset", 0),
                activation["engine_seed"], activation.get("engine_offset", 0), activation["damage_number_mode"]]
        lineups["replay_controls"]["native_activation_order"] = order
        target = out / "fights" / cid
        target.mkdir(parents=True, exist_ok=True)
        (target / "lineups.json").write_text(json.dumps(lineups, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
        (target / "rng_state.txt").write_text("seed=%s\nstate=%s\n" % (boundaries["prepare"]["seed"], boundaries["prepare"]["state"]), encoding="utf8")
        shutil.copyfile(source / "events.json", target / "events.json")
        selected.append(case)
        if not args.case_ids and args.limit and len(selected) >= args.limit:
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
if args.direct_cpp:
    status["scope"] = "Original native-frame recordings versus C++"
    # Use the shared lineup generator directly. Pass the case list through a
    # file so the Windows command line can also carry the full corpus.
    generate = '''
import json
from pathlib import Path
import sys
sys.path.insert(0, "tools")
from gen_fixture_from_lineup import oracle_mode
out = Path(sys.argv[1])
ids = [row["case_id"] for row in json.loads((out / "cases.json").read_text("utf8"))["cases"]]
raise SystemExit(oracle_mode([str(out / "fights" / cid) for cid in ids],
                            str(out / "align/lineups"), str(out / "fixtures.json")))
'''
    with (out / "fixture.log").open("wb") as log:
        status["fixture_exit"] = subprocess.run([sys.executable, "-u", "-X", "utf8", "-c", generate, str(out)],
                                               cwd=sim, stdout=log, stderr=subprocess.STDOUT).returncode
    if status["fixture_exit"]:
        (out / "status.json").write_text(json.dumps(status, indent=2) + "\n", encoding="utf8")
        raise SystemExit("Could not assemble every original replay fixture. See " + str(out / "fixture.log"))
elif args.cpp_only:
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
dll = args.dll.resolve() if args.dll else sim / "native_sim_cpp/native_sim/libgdcore.dll"
status["dll_sha256"] = hashlib.sha256(dll.read_bytes()).hexdigest()
with (out / "cpp.log").open("wb") as log:
    status["cpp_exit"] = subprocess.run([
        sys.executable, "-u", "-X", "utf8", "tools/_cpp_verify_events.py", *common,
        "--case-ids", str(out / "cases.json"), "--strict-gem-origins", "--original-dir", str(reference),
        "--out", str(out / "cpp"), "--dll", str(dll), *(["--native-only"] if args.direct_cpp else []),
        *(["--strict-item-origins"] if args.strict_item_origins else [])],
        cwd=sim, stdout=log, stderr=subprocess.STDOUT).returncode
(out / "status.json").write_text(json.dumps(status, indent=2) + "\n", encoding="utf8")
print(json.dumps({key: value for key, value in status.items() if key != "kernel_sha256"}, indent=2))
raise SystemExit(0 if not status.get("three_core_exit") and not status["cpp_exit"] else 1)
