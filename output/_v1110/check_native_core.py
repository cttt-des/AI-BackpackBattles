"""Exercise the compact kernel with the independently observed initial context."""
import json
from pathlib import Path
import shutil
import subprocess
import sys

repo = Path.cwd()
stage = repo / "output/_v1110"
sim = stage / "sim_native"
cid = "run101207_r1_o604707_r1"
native = stage / "native_visual_state" / cid
proof = stage / "native_boundary_comparison/native_visual_state/physics_first_ambient_flickers_tweens_f32dt_fatigue_active/fights" / cid
out = stage / "native_core_check"
fight = out / "fights" / cid
fight.mkdir(parents=True, exist_ok=True)
boundaries = json.loads((native / "boundaries.json").read_text("utf8"))
lineups = json.loads((native / "lineups.json").read_text("utf8"))
case_table = json.loads((stage / "full_corpus/expand/cases.json").read_text("utf8"))
selected = [case for case in case_table["cases"] if case["case_id"] == cid]
assert len(selected) == 1
(out / "cases.json").write_text(json.dumps({"cases": selected}, ensure_ascii=False, indent=2), encoding="utf8")
order = {"player": [], "opponent": []}
for entry in boundaries["prepare"]["order"]:
    side = "player" if entry["owner"] == 1 else "opponent"
    matches = [i for i, item in enumerate(lineups[side]["items"])
               if item["identifier"] == entry["name"]
               and [item["top_left"][axis] for axis in ("x", "y")] == entry["top_left"]]
    assert len(matches) == 1, entry
    order[side].append(matches[0])
for side in order:
    assert sorted(order[side]) == list(range(len(lineups[side]["items"])))
idle = [None, None]
for timer in boundaries["idle_animation_timers"]:
    idle[timer["owner"]] = timer.get("left_precise", timer["left"])
lineups["replay_controls"]["replay_initial"] = {
    "activation_rng_state": boundaries["before_activate"]["state"], "idle_left": idle}
lineups["replay_controls"]["native_activation_order"] = order
(fight / "lineups.json").write_text(json.dumps(lineups, ensure_ascii=False, indent=2), encoding="utf8")
(fight / "rng_state.txt").write_text("seed=%s\nstate=%s\n" % (
    boundaries["prepare"]["seed"], boundaries["prepare"]["state"]), encoding="utf8")
shutil.copyfile(proof / "events.json", fight / "events.json")
shutil.copyfile(proof / "result.txt", fight / "result.txt")
with (out / "three_way.log").open("wb") as log:
    result = subprocess.run([sys.executable, "-u", "-X", "utf8", "tools/verify_oracle.py",
                             "--fights-root", str(out / "fights"), "--align-root", str(out / "align"),
                             "--cases-json", str(out / "fixtures.json"), "--alignment-out", str(out / "alignment.json"),
                             "--gd-jobs", "1", "--py-jobs", "1", "--compare-jobs", "1", "--force"],
                            cwd=sim, stdout=log, stderr=subprocess.STDOUT)
print("Compact native core verification exit", result.returncode, flush=True)
raise SystemExit(result.returncode)
