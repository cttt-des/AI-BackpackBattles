"""Paired real-case replay: change only the formerly missing rage metadata."""
from pathlib import Path
import argparse
import json
import subprocess
import sys

stage = Path(__file__).resolve().parent
sim = stage / "sim_native"
cid = "run101621_r3_o705060_r3"
case_root = stage / "native_metadata_check" / cid
out = stage / "auto_rage_metadata_effect"
ap = argparse.ArgumentParser()
ap.add_argument("--mode", choices=("missing_flags", "observed"))
args = ap.parse_args()
if args.mode:
    sys.path[:0] = [str(sim)]
    from simulator.gd_core_engine import runtime_data
    from tools import verify_oracle as verifier
    data = runtime_data()
    if args.mode == "missing_flags":
        for item in data["items"].values():
            item["descr"]["hasBattleRageEffect"] = False
    verifier.FIGHTS_DIR = str(case_root / "fights")
    verifier.GD_OUT = str(case_root / "align/gdcore")
    verifier.LINEUP_OUT = str(case_root / "align/lineups")
    verifier.CASES_JSON = str(case_root / "fixtures.json")
    verifier.PY_OUT = str(out / args.mode)
    assert verifier.run_py(json.loads((case_root / "cases.json").read_text("utf8"))["cases"]) == 0
else:
    for mode in ("missing_flags", "observed"):
        subprocess.run([sys.executable, "-u", "-X", "utf8", str(Path(__file__)), "--mode", mode], cwd=sim, check=True)
    reports = {}
    for mode in ("missing_flags", "observed"):
        doc = json.loads((out / mode / cid / "events.json").read_text("utf8"))
        reports[mode] = {key: doc[key] for key in ("winner", "combat_time", "event_count", "player_hp", "opponent_hp")}
        reports[mode]["rage_events"] = [{"type": row["type"], "timestamp": row["timestamp"], "origin": row["origin"]}
                                        for row in doc["events"] if row["type"] in (21, 22)]
    assert not reports["missing_flags"]["rage_events"]
    assert reports["observed"]["rage_events"]
    summary = {"case_id": cid, "scope": "Paired pure Python replay, identical observed inputs; only hasBattleRageEffect flags disabled in the control; files and DLL unchanged",
               "modes": reports, "winner_changed": reports["missing_flags"]["winner"] != reports["observed"]["winner"]}
    (out / "summary.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    print(json.dumps(summary, ensure_ascii=False, indent=2))
