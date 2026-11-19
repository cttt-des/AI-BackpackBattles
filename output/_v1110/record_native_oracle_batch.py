"""Run the source Oracle with per-case native initial inputs and compare events.

Reuse the proven single-case generator, but load boundary inputs by case ID.
Native recordings remain read-only; this is an independent Oracle leg.
"""
from pathlib import Path
import argparse
import contextlib
import hashlib
import io
import json
import os
import re
import subprocess
import sys
import time

repo = Path(__file__).resolve().parents[2]
stage = repo / "output/_v1110"
ap = argparse.ArgumentParser()
ap.add_argument("--source", default="native_corpus/expand")
ap.add_argument("--project", default="full_corpus/expand/project", help="Isolated Oracle project under the stage directory")
ap.add_argument("--cases", default="native_kernel_baseline/cases.json")
ap.add_argument("--out", default="native_oracle_timer_batch")
ap.add_argument("--chunk", type=int, default=8)
ap.add_argument("--limit", type=int, default=0)
ap.add_argument("--prepare-only", action="store_true")
ap.add_argument("--track-charge-tweens", action="store_true")
ap.add_argument("--critical-shake", action="store_true")
args = ap.parse_args()
os.chdir(repo)
reference = stage / args.source
project = (stage / args.project).resolve()
assert project.is_relative_to(stage) and (project / "project.godot").is_file(), project
out = stage / args.out
out.mkdir(parents=True, exist_ok=True)
cases = json.loads((stage / args.cases).read_text("utf8"))["cases"]
if args.limit:
    cases = cases[:args.limit]
assert cases and args.chunk > 0
first = cases[0]["case_id"]
inputs = {case["case_id"]: json.loads((reference / case["case_id"] / "boundaries.json").read_text("utf8")) for case in cases}
(out / "cases.json").write_text(json.dumps({"cases": cases}, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
input_file = out / "native_inputs.json"
input_file.write_text(json.dumps(inputs, ensure_ascii=False, separators=(",", ":")) + "\n", encoding="utf8")

generator = stage / "compare_native_boundaries.py"
prefix = generator.read_text("utf8").split("oracle_diagnostics = None\n", 1)[0]
argv = sys.argv
namespace = {"__name__": "_native_batch_template", "__file__": str(generator)}
try:
    sys.argv = [str(generator), first, "--reference", args.source, "--case-subdir", "--physics-first",
                "--restore-ambient-timers", "--restore-flickers", "--advance-character-tweens",
                "--advance-charge-tweens", "--opening-tween-pass", "--native-delta",
                "--source-fatigue-mode", "--snapshot-active-timers", "--native-translations", "--native-timers",
                "--oracle-project", args.project]
    if args.track_charge_tweens:
        sys.argv.append("--track-charge-tweens")
    if args.critical_shake:
        sys.argv.append("--critical-shake")
    with contextlib.redirect_stdout(io.StringIO()):
        exec(compile(prefix, str(generator), "exec"), namespace)
finally:
    sys.argv = argv
source = namespace["source"]
data = inputs[first]

def replace_once(old, new):
    global source
    assert source.count(old) == 1, old[:140]
    source = source.replace(old, new, 1)

replace_once("func run_case(c: Dictionary, warmup := false) -> Dictionary :\n",
             "func run_case(c: Dictionary, warmup := false) -> Dictionary :\n\tvar native_input = _native_input_for(c[\"case_id\"])\n")
replace_once("var native_order = " + json.dumps(data["prepare"]["order"], ensure_ascii=False),
             'var native_order = native_input["prepare"]["order"]')
replace_once("U.rng.set_state(%s)" % data["prepare"]["state"], 'U.rng.set_state(int(native_input["prepare"]["state"]))')
replace_once("U.rng.set_state(%s)" % data["before_activate"]["state"], 'U.rng.set_state(int(native_input["before_activate"]["state"]))')
for boundary in ("prepare", "before_activate"):
    rng_set = 'U.rng.set_state(int(native_input["%s"]["state"]))' % boundary
    if "engine_seed" in data[boundary]:
        static = "\n\t\t_restore_native_engine(%d, %d)" % (int(data[boundary]["engine_seed"]), data[boundary].get("engine_offset", 0))
        replace_once(rng_set + static, rng_set)
    replace_once(rng_set, rng_set + '\n\t\tvar engine_boundary = native_input["%s"]\n\t\tif engine_boundary.has("engine_seed"):\n\t\t\t_restore_native_engine(int(engine_boundary["engine_seed"]), int(engine_boundary.get("engine_offset", 0)))' % boundary)
if "buff_state" in data["before_activate"]:
    replace_once('_native_restore_buff_state(%s)' % json.dumps(data["before_activate"]["buff_state"]),
                 '_native_restore_buff_state(native_input["before_activate"].get("buff_state"))')
else:
    anchor = "\tG.activateItems(playerItems + opponentItems)\n"
    replace_once(anchor, '\t\t_native_restore_buff_state(native_input["before_activate"].get("buff_state"))\n' + anchor)
replace_once("_restore_native_visuals(%s)" % json.dumps(data["flicker_states"], ensure_ascii=False),
             '_restore_native_visuals(native_input["flicker_states"])')
replace_once("for snapshot in %s:" % json.dumps(namespace["timers"], ensure_ascii=False),
             'for snapshot in native_input["idle_animation_timers"]:')
if args.critical_shake:
    assert all(boundaries["before_activate"].get("visible_combat_shakes", 0) == 0 for boundaries in inputs.values())
    replace_once('settings.settings[settings.Setting.damage_numbers] = %d' % data["before_activate"].get("damage_number_mode", 0),
                 'settings.settings[settings.Setting.damage_numbers] = int(native_input["before_activate"].get("damage_number_mode", 0))')
# The native getter is float, recorded precisely as a string alongside its JSON number.
source = source.replace('float(snapshot["left"])', 'float(snapshot.get("left_precise", snapshot["left"]))')
source += '''

var _native_input_table := {}

func _native_input_for(case_id):
	if _native_input_table.empty():
		var file = File.new()
		assert(file.open("%s", File.READ) == OK)
		_native_input_table = JSON.parse(file.get_as_text()).result
		file.close()
	assert(_native_input_table.has(case_id))
	return _native_input_table[case_id]
''' % input_file.as_posix()
script = out / "oracle_fight.gd"
script.write_text(source, encoding="utf8", newline="\n")
manifest = {"scope": "Independent source Oracle; native initial states and activation order only; no expected events passed to the engine",
            "script_sha256": hashlib.sha256(script.read_bytes()).hexdigest(),
            "inputs_sha256": hashlib.sha256(input_file.read_bytes()).hexdigest(), "cases": len(cases),
            "support_sha256": {name: hashlib.sha256((stage / name).read_bytes()).hexdigest()
                               for name in ("native_oracle_timer.gd", "native_oracle_timers.gd.inc")}}
manifest["support_sha256"].update({name: hashlib.sha256((project / name).read_bytes()).hexdigest() for name in
                                   ("project.godot", "Core/Game.gd", "Core/CombatLog.gd", "Utility/Util.gd", "Items/Exclusive/ChessBoard.gd")})
(out / "build_manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")
if args.prepare_only:
    print("Prepared independent Oracle batch", len(cases), out)
    raise SystemExit(0)

sys.path[:0] = [str(repo), str(repo / "tools")]
from tools import godot_headless as gh
from verify_oracle import canonical_stream, _tuple_of, _et_names
from _cpp_verify_events import recorded_gem_identity

def complete(cid):
    folder = out / "fights" / cid
    try:
        doc = json.loads((folder / "events.json").read_text("utf8"))
        row = doc["events"][-1]
        proof = json.loads((folder / "oracle_manifest.json").read_text("utf8"))
        return (len(doc["events"]) == doc["event_count"] and row["type"] == {"player": 111, "opponent": 112}[doc["winner"]]
                and round(row["timestamp"] * 60) == round(doc["combat_time"] * 60)
                and proof["script_sha256"] == manifest["script_sha256"]
                and proof["support_sha256"] == manifest["support_sha256"]
                and proof["native_boundary_sha256"] == hashlib.sha256((reference / cid / "boundaries.json").read_bytes()).hexdigest()
                and all(hashlib.sha256((folder / name).read_bytes()).hexdigest() == digest
                        for name, digest in proof["products_sha256"].items())
                and set(proof["products_sha256"]) == {"events.json", "lineups.json", "rng_state.txt"})
    except (OSError, ValueError, KeyError, IndexError):
        return False

logs = []
round_number = 0
while True:
    pending = [case["case_id"] for case in cases if not complete(case["case_id"])]
    if not pending:
        break
    round_number += 1
    selected = pending[:args.chunk]
    started = time.time()
    # The Godot script uses terminal events as its own resume check. Record to
    # a fresh attempt so it cannot skip an older result with different inputs.
    attempt = out / "_attempts" / f"{manifest['script_sha256'][:12]}_{time.time_ns()}"
    attempt.mkdir(parents=True)
    child, log, handle = gh.spawn(gh.cmd(project=str(project), script=str(script)),
                                  label="native_oracle_batch", tag="native_oracle_batch",
                                  env_extra={"ORACLE_ONLY_CASES": ",".join(selected), "ORACLE_FIGHTS_ROOT": str(attempt),
                                             "ORACLE_REQUIRE_TERMINAL": "1", "ORACLE_FIGHT_CHUNK": str(args.chunk)})
    print("Oracle batch", round_number, "cases", len(selected), "pid", child.pid, "log", log, flush=True)
    try:
        result = child.wait(timeout=max(900, len(selected) * 300))
    except subprocess.TimeoutExpired:
        child.kill()
        child.wait()
        raise
    finally:
        handle.close()
    text = gh.read_log(log)
    errors = re.findall(r"SCRIPT ERROR: ([^\r\n]+)\s+at: ([^\r\n]+)", text)
    fatal = [(message, site) for message, site in errors if "Parse Error" in message or any(
        item in site for item in ("oracle_fight.gd:", "_native_", "native_oracle_timer.gd:", "/ElectricalCharge.gd", "/FlickerAnimation.gd"))]
    logs.append({"log": str(log), "exit": result, "script_errors": len(errors), "fatal": fatal,
                 "cases": selected, "script_sha256": manifest["script_sha256"], "support_sha256": manifest["support_sha256"]})
    (out / "logs.json").write_text(json.dumps(logs, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
    if result or fatal:
        raise SystemExit("Source Oracle batch failed; inspect " + str(log))
    for cid in selected:
        observed = attempt / cid
        products = [observed / name for name in ("events.json", "lineups.json", "rng_state.txt")]
        if not all(path.is_file() and path.stat().st_mtime >= started for path in products):
            raise SystemExit("Missing current-run Oracle products: " + cid)
        doc = json.loads(products[0].read_text("utf8"))
        terminal = doc["events"][-1]
        if (len(doc["events"]) != doc["event_count"] or terminal["type"] != {"player": 111, "opponent": 112}.get(doc["winner"])
                or round(terminal["timestamp"] * 60) != round(doc["combat_time"] * 60)):
            raise SystemExit("Invalid current-run Oracle ending: " + cid)
        proof = {"script_sha256": manifest["script_sha256"], "support_sha256": manifest["support_sha256"],
                 "native_boundary_sha256": hashlib.sha256((reference / cid / "boundaries.json").read_bytes()).hexdigest(),
                 "products_sha256": {path.name: hashlib.sha256(path.read_bytes()).hexdigest() for path in products},
                 "log": str(log)}
        folder = out / "fights" / cid
        folder.mkdir(parents=True, exist_ok=True)
        for path in products:
            os.replace(path, folder / path.name)
        marker = observed / "oracle_manifest.json"
        marker.write_text(json.dumps(proof, indent=2) + "\n", encoding="utf8")
        os.replace(marker, folder / marker.name)
        if not complete(cid):
            raise SystemExit("Invalid Oracle terminal or provenance: " + cid)

reports = []
for case in cases:
    cid = case["case_id"]
    paths = [reference / cid / "events.json", out / "fights" / cid / "events.json"]
    docs = [json.loads(path.read_text("utf8")) for path in paths]
    streams = [list(map(_tuple_of, canonical_stream(str(path), _et_names()))) for path in paths]
    first_diff = next((i for i, (a, b) in enumerate(zip(*streams)) if a != b), None)
    if first_diff is None and len(streams[0]) != len(streams[1]):
        first_diff = min(map(len, streams))
    identities = [[recorded_gem_identity(row) for row in doc["events"]] for doc in docs]
    gems_match = identities[0] == identities[1] and all(() not in rows for rows in identities)
    inputs_match = all(docs[0][field] == docs[1][field] for field in ("seed", "run_id", "round_id", "opp_run_id", "opp_round_id"))
    endings = [doc["events"][-1] for doc in docs]
    ending_match = (docs[0]["winner"] == docs[1]["winner"] and endings[0]["type"] == endings[1]["type"]
                    and round(endings[0]["timestamp"] * 60) == round(endings[1]["timestamp"] * 60))
    reports.append({"case_id": cid, "match": first_diff is None and gems_match and inputs_match and ending_match,
                    "counts": list(map(len, streams)), "first": first_diff, "gems_match": gems_match,
                    "inputs_match": inputs_match, "ending_match": ending_match,
                    "native": streams[0][first_diff] if first_diff is not None and first_diff < len(streams[0]) else None,
                    "oracle": streams[1][first_diff] if first_diff is not None and first_diff < len(streams[1]) else None})
summary = {"total": len(reports), "passed": sum(row["match"] for row in reports), "cases": reports,
           "scope": manifest["scope"], "script_sha256": manifest["script_sha256"]}
(out / "comparison.json").write_text(json.dumps(summary, ensure_ascii=False, indent=2) + "\n", encoding="utf8")
print("Native versus independent Oracle:", summary["passed"], "/", summary["total"], flush=True)
raise SystemExit(0 if summary["passed"] == summary["total"] else 1)
