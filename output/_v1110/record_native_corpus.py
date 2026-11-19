"""Record all expanded and base cases using frozen recovered-source Main projects.

One native process at a time; each process records several natural history
fights. No manual combat tick or event replay. Failed batches are not accepted.
"""
from pathlib import Path
import argparse
import ctypes
import datetime
import json
import os
import subprocess
import sys
from ctypes import wintypes

repo = Path(__file__).resolve().parents[2]
stage = repo / "output/_v1110"
ap = argparse.ArgumentParser()
ap.add_argument("--chunk", type=int, default=12)
ap.add_argument("--cohort", choices=("both", "expand", "base"), default="both")
ap.add_argument("--output-root", default="native_corpus", help="Separate output and status directory under the 1.1.10 stage")
args = ap.parse_args()
if args.chunk < 1:
    ap.error("chunk must be positive")
root = (stage / args.output_root).resolve()
if root.parent != stage:
    ap.error("output root must be a direct child of the version stage")
root.mkdir(exist_ok=True)
status_path = root / "status.json"

def write_status(status):
    status["updated_utc"] = datetime.datetime.now(datetime.timezone.utc).isoformat()
    temporary = status_path.with_suffix(".tmp")
    temporary.write_text(json.dumps(status, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    os.replace(temporary, status_path)

def live(pid):
    kernel = ctypes.windll.kernel32
    kernel.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
    kernel.OpenProcess.restype = wintypes.HANDLE
    kernel.GetExitCodeProcess.argtypes = [wintypes.HANDLE, ctypes.POINTER(wintypes.DWORD)]
    kernel.GetExitCodeProcess.restype = wintypes.BOOL
    kernel.CloseHandle.argtypes = [wintypes.HANDLE]
    kernel.CloseHandle.restype = wintypes.BOOL
    handle = kernel.OpenProcess(0x1000, False, int(pid))
    if not handle:
        return False
    try:
        code = wintypes.DWORD()
        return bool(kernel.GetExitCodeProcess(handle, ctypes.byref(code))) and code.value == 259
    finally:
        kernel.CloseHandle(handle)

if status_path.is_file():
    previous = json.loads(status_path.read_text("utf8"))
    if previous.get("phase") not in ("complete", "failed") and live(previous.get("pid", 0)):
        raise SystemExit("Another native recorder is still live: " + str(previous["pid"]))
status = {"pid": os.getpid(), "phase": "starting", "cohorts": {},
          "scope": "Recovered 1.1.10 source plus vanilla Godot 3.6; installation EXE cross-check pending"}
write_status(status)

def accepted(folder, cid, expected):
    case = folder / cid
    try:
        manifest = json.loads((case / "reference_manifest.json").read_text("utf8"))
        for key in ("version", "cohort", "battle_script_sha256", "reader_sha256", "case_list_sha256", "history_snapshot_sha256"):
            if manifest.get(key) != expected.get(key):
                return False
        doc = json.loads((case / "events.json").read_text("utf8"))
        boundaries = json.loads((case / "boundaries.json").read_text("utf8"))
        lineup = json.loads((case / "lineups.json").read_text("utf8"))
        events = doc.get("events", [])
        winner = {"player": 111, "opponent": 112}.get(doc.get("winner"))
        return (bool(events) and len(events) == doc["event_count"] and events[-1]["type"] == winner
                and round(float(events[-1]["timestamp"]) * 60) == round(float(doc["combat_time"]) * 60)
                and all(doc[key] == lineup[key] for key in ("seed", "run_id", "round_id", "opp_run_id", "opp_round_id"))
                and all(key in boundaries for key in ("prepare", "before_activate", "idle_animation_timers", "flicker_states")))
    except (OSError, ValueError, KeyError, TypeError):
        return False

cohorts = ("expand", "base") if args.cohort == "both" else (args.cohort,)
for cohort in cohorts:
    folder = root / cohort
    folder.mkdir(exist_ok=True)
    project_name = "native_corpus_project_" + cohort
    project = stage / project_name
    status["phase"] = "preparing"
    status["cohort"] = cohort
    write_status(status)
    if not (project / "reference_manifest.json").is_file():
        with (folder / "prepare.log").open("ab") as log:
            subprocess.run([sys.executable, "-u", "-X", "utf8", str(stage / "prepare_native_reference.py"),
                            str(stage), "--cohort", cohort, "--project-name", project_name],
                           cwd=repo, stdout=log, stderr=subprocess.STDOUT, check=True)
    expected = json.loads((project / "reference_manifest.json").read_text("utf8"))
    cases = json.loads((project / "fights.json").read_text("utf8"))["cases"]
    assert len(cases) == (1690 if cohort == "expand" else 914)
    ids = [case["case_id"] for case in cases]
    assert len(ids) == len(set(ids))
    # Front-load actual auto-rage cases missed by the old all-false metadata.
    priority = ["run101621_r3_o705060_r3", "run101697_r6_o400041_r6", "run400041_r7_o101102_r7", "run101098_r5_o101130_r5"]
    ids = [cid for cid in priority if cid in ids] + [cid for cid in ids if cid not in priority]
    (folder / "cases.json").write_text(json.dumps({"cases": cases}, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    batch_number = 0
    pending = [cid for cid in ids if not accepted(folder, cid, expected)]
    while True:
        status["cohorts"][cohort] = {"total": len(ids), "completed": len(ids) - len(pending), "remaining": len(pending)}
        if not pending:
            write_status(status)
            break
        batch_number += 1
        selected = pending[:min(args.chunk, 4 if batch_number == 1 else args.chunk)]
        batch_file = folder / "current_batch.json"
        batch_file.write_text(json.dumps(selected, indent=2) + "\n", encoding="utf8")
        status["phase"] = "recording"
        status["batch"] = selected
        with (folder / "driver.log").open("ab") as log:
            child = subprocess.Popen([sys.executable, "-u", "-X", "utf8", str(stage / "run_native_1110.py"),
                                      "--case-ids", str(batch_file), "--cohort", cohort,
                                      "--project-name", project_name, "--reuse-prepared", "--disable-render-loop",
                                      "--out", root.name + "/" + cohort, "--timeout", str(max(300, len(selected) * 120))],
                                     cwd=repo, stdout=log, stderr=subprocess.STDOUT)
            status["child_pid"] = child.pid
            write_status(status)
            print(cohort, "batch", batch_number, "cases", len(selected), "child", child.pid, flush=True)
            result = child.wait()
        if result or any(not accepted(folder, cid, expected) for cid in selected):
            status["phase"] = "failed"
            status["failure"] = {"exit": result, "cases": selected}
            write_status(status)
            raise SystemExit("Native batch rejected; inspect " + str(folder / "driver.log"))
        metadata = json.loads((folder / "descriptor_metadata.json").read_text("utf8"))
        if metadata["count"] != 519 or metadata["locale"] != "en":
            status["phase"] = "failed"
            status["failure"] = {"descriptor_count": metadata["count"], "locale": metadata["locale"]}
            write_status(status)
            raise SystemExit("Unexpected native descriptor table or locale")
        del pending[:len(selected)]
        print(cohort, "batch", batch_number, "accepted", len(selected), flush=True)
status["phase"] = "complete"
write_status(status)
print("Requested native cohorts recorded and checked", flush=True)
