"""Diagnostic: compare real frame replay using its observed battle inputs.

This imports two observed PCG states and the actual activation permutation.
It does not claim that a seed alone reproduces UI and animation RNG draws.
The underlying native recording is read-only; all candidate output is isolated.
"""
import argparse
import json
from pathlib import Path
import sys
import subprocess
import hashlib
import re

repo = Path.cwd()
sys.path.insert(0, str(repo))
sys.path.insert(0, str(repo / "tools"))
from tools import godot_headless as gh
from verify_oracle import canonical_stream, _tuple_of, _et_names
from _cpp_verify_events import recorded_gem_identity

parser = argparse.ArgumentParser()
parser.add_argument("case_id")
parser.add_argument("--reference", default="native_observed_clean")
parser.add_argument("--physics-first", action="store_true")
parser.add_argument("--rng-probe", action="store_true")
parser.add_argument("--restore-ambient-timers", action="store_true")
parser.add_argument("--restore-flickers", action="store_true")
parser.add_argument("--advance-character-tweens", action="store_true")
parser.add_argument("--advance-charge-tweens", action="store_true")
parser.add_argument("--opening-tween-pass", action="store_true")
parser.add_argument("--native-delta", action="store_true")
parser.add_argument("--source-fatigue-mode", action="store_true")
parser.add_argument("--snapshot-active-timers", action="store_true")
parser.add_argument("--compare-only", action="store_true")
args = parser.parse_args()
stage = repo / "output/_v1110"
reference = stage / args.reference / args.case_id
data = json.loads((reference / "boundaries.json").read_text("utf8"))
variant = ("physics_first" if args.physics_first else "current") + ("_ambient" if args.restore_ambient_timers else "")
variant += "_flickers" if args.restore_flickers else ""
variant += "_tweens" if args.advance_character_tweens else ""
variant += "_f32dt" if args.native_delta else ""
variant += "_fatigue" if args.source_fatigue_mode else ""
variant += "_active" if args.snapshot_active_timers else ""
variant += "_charges" if args.advance_charge_tweens else ""
variant += "_opening" if args.opening_tween_pass else ""
out = stage / "native_boundary_comparison" / args.reference / variant
out.mkdir(parents=True, exist_ok=True)
source = (repo / "oracle/oracle_fight.gd").read_text("utf8")
if args.native_delta:
    assert source.count("const DT := 1.0 / 60.0") == 1
    source = source.replace("const DT := 1.0 / 60.0", "const DT := 0.01666666753590107")
if args.source_fatigue_mode:
    anchor = "\tCT.initialize()\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, anchor + "\tCT.fatigueStartTimer.process_mode = Timer.TIMER_PROCESS_PHYSICS\n\tCT.fatigueTickTimer.process_mode = Timer.TIMER_PROCESS_PHYSICS\n")
if args.snapshot_active_timers:
    anchor = "\tvar reg: Dictionary = U.oracleTimerLefts\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, anchor + '''\tvar active_timers := {}
	for timer in reg:
		if is_instance_valid(timer) and timer.is_inside_tree() and not timer.is_stopped() and (timer.process_mode == Timer.TIMER_PROCESS_PHYSICS) == physics_pass:
			active_timers[timer] = true
''')
    anchor = "\t\tvar eng = timer.get_time_left()\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, "\t\tif not active_timers.has(timer):\n\t\t\tcontinue\n" + anchor)
if args.physics_first:
    assert source.count("\tdrive_timers(true, dt)\n") == 1
    source = source.replace("\tdrive_timers(true, dt)\n", "")
    source = source.replace("func tick_battle(dt: float, n := 0) -> void :\n",
                            "func tick_battle(dt: float, n := 0) -> void :\n\tdrive_timers(true, dt)\n")
    assert source.count("\t\t\te[0] = eng            #") == 1
    source = source.replace("\t\t\te[0] = eng            #", "\t\t\te[0] = eng - dt if physics_pass else eng  #")
assert source.count("\tG.prepareItems(playerItems + opponentItems)\n") == 1
before_prepare = '''
	if not warmup:
		var native_order = %s
		var ordered_player := []
		var ordered_opponent := []
		var available = playerItems + opponentItems
		for descriptor in native_order:
			var found = null
			for item in available:
				var cell = item.getTopLeftCell()
				if item.getName() == descriptor["name"] and item.ownerType == int(descriptor["owner"]) and cell == Vector2(descriptor["top_left"][0], descriptor["top_left"][1]):
					found = item
					break
			assert(found != null)
			available.erase(found)
			if found.ownerType == 1:
				ordered_player.append(found)
			else:
				ordered_opponent.append(found)
		assert(available.empty())
		playerItems = ordered_player
		opponentItems = ordered_opponent
		U.rng.set_state(%s)
''' % (json.dumps(data["prepare"]["order"], ensure_ascii=False), data["prepare"]["state"])
if args.rng_probe:
    before_prepare = before_prepare.replace("\tif not warmup:\n", '\tif not warmup:\n\t\tU.rng = load("%s").new()\n' % (stage / "native_rng_observer.gd").as_posix(), 1)
source = source.replace("\tG.prepareItems(playerItems + opponentItems)\n",
                        before_prepare + "\tG.prepareItems(playerItems + opponentItems)\n")
source = source.replace("\tG.activateItems(playerItems + opponentItems)\n",
                        "\tif not warmup:\n\t\tU.rng.set_state(%s)\n" % data["before_activate"]["state"]
                        + ("\t\tU.rng.recording = true\n" if args.rng_probe else "")
                        + "\tG.activateItems(playerItems + opponentItems)\n")
if args.restore_flickers:
    source = source.replace("extends SceneTree\n", "extends SceneTree\n\nvar _native_visual_players := []\nvar _native_visual_orphans := []\n", 1)
    source = source.replace("\t\tU.rng.set_state(%s)\n" % data["before_activate"]["state"],
                            "\t\t_restore_native_visuals(%s)\n" % json.dumps(data["flicker_states"], ensure_ascii=False)
                            + "\t\tU.rng.set_state(%s)\n" % data["before_activate"]["state"])
    anchor = "\tdrive_delayed(dt)\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, '''\tfor animation in _native_visual_players:
		if is_instance_valid(animation) and animation.is_inside_tree() and animation.is_playing():
			animation.advance(dt)
''' + anchor)
    source += '''

func _native_find_host(node, identity):
	if "descriptor" in node and "ownerType" in node and node.descriptor != null:
		if node.descriptor.identifier == identity["name"] and node.ownerType == int(identity["owner"]):
			var cell = node.getTopLeftCell() if not node.occupiedCells.empty() else Vector2(-999, -999)
			if cell == Vector2(identity["top_left"][0], identity["top_left"][1]):
				return node
	for child in node.get_children():
		var found = _native_find_host(child, identity)
		if found != null:
			return found
	return null

func _restore_native_visuals(snapshots):
	var keep := []
	for entry in U.oracleDelayedTimers:
		var visual := false
		for connection in entry[0].get_signal_connection_list("timeout"):
			var target = connection["target"]
			if is_instance_valid(target) and target.get_script() != null and target.get_script().resource_path.ends_with("/FlickerAnimation.gd"):
				visual = true
		if not visual:
			keep.append(entry)
	U.oracleDelayedTimers = keep
	_native_visual_players = []
	for orphan in _native_visual_orphans:
		orphan.free()
	_native_visual_orphans = []
	for snapshot in snapshots:
		var animation = null
		if snapshot["identity"] != null:
			var host = _native_find_host(root, snapshot["identity"])
			if host != null:
				animation = host.get_node_or_null(snapshot["identity"]["relative_path"])
		else:
			animation = root.get_node_or_null(snapshot["path"])
		if animation == null and not snapshot["inside_tree"] and snapshot["identity"] != null:
			# Preserve the original scene's exported flicker limits without entering the tree.
			var orphan = IB.getDescriptor(snapshot["identity"]["name"]).instantiate()
			_native_visual_orphans.append(orphan)
			animation = orphan.get_node_or_null(snapshot["identity"]["relative_path"])
		assert(animation != null, "Missing native visual source " + str(snapshot))
		_native_visual_players.append(animation)
		animation.stop()
		animation.playback_speed = float(snapshot["speed"])
		if snapshot["playing"]:
			animation.play(snapshot["animation"])
			animation.seek(float(snapshot["position"]), true)
		for pending in snapshot["pending"]:
			U.callDelayed(animation, pending["method"], float(pending["left"]))
'''
if args.advance_character_tweens and not args.advance_charge_tweens:
    anchor = "\tdrive_delayed(dt)\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, anchor + '''\tfor character in [G.OPPONENT, G.PLAYER]:
		if is_instance_valid(character.attackTween) and character.attackTween.is_valid():
			character.attackTween.custom_step(dt)
''')
if args.advance_charge_tweens:
    anchor = "\tdrive_delayed(dt)\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, anchor + "\t_advance_native_tweens(dt)\n")
    source += '''

func _collect_charge_tweens(node, found):
	if node.get_script() != null and node.get_script().resource_path.ends_with("/ElectricalCharge.gd"):
		if is_instance_valid(node.tween) and node.tween.is_valid():
			found.append(node.tween)
	for child in node.get_children():
		_collect_charge_tweens(child, found)

func _native_tween_created_before(left, right):
	return left.get_instance_id() < right.get_instance_id()

func _advance_native_tweens(delta):
	var tweens := []
	_collect_charge_tweens(root, tweens)
'''
    if args.advance_character_tweens:
        source += '''	for character in [G.OPPONENT, G.PLAYER]:
		if is_instance_valid(character.attackTween) and character.attackTween.is_valid():
			tweens.append(character.attackTween)
'''
    source += '''	tweens.sort_custom(self, "_native_tween_created_before")
	for tween in tweens:
		if is_instance_valid(tween) and tween.is_valid():
			tween.custom_step(delta)
'''
    if args.opening_tween_pass:
        # Activation runs in a SceneTreeTimer callback. Its newly-created Tweens
        # therefore receive the native idle Tween pass before the next physics tick.
        anchor = "\trebuild_timer_registry()\n"
        assert source.count(anchor) == 1
        source = source.replace(anchor, anchor + "\t_advance_native_tweens(DT)\n")
elif args.opening_tween_pass:
    parser.error("--opening-tween-pass requires --advance-charge-tweens")
if args.rng_probe:
    source = source.replace("\tdump_events(events, dir, res)\n", '''\tdump_events(events, dir, res)
	if not warmup:
		var rng_dump = File.new()
		rng_dump.open(dir.plus_file("rng_draws.json"), File.WRITE)
		rng_dump.store_string(JSON.print(U.rng.draws, "  ") + "\\n")
		rng_dump.close()
''')
if args.restore_ambient_timers:
    timers = data["idle_animation_timers"]
    for timer in timers:
        if "left_precise" in timer:
            timer["left"] = float(timer["left_precise"])
    anchor = "\trebuild_timer_registry()\n"
    assert source.count(anchor) == 1
    source = source.replace(anchor, anchor + '''
	if not warmup:
		for snapshot in %s:
			var character = G.PLAYER if int(snapshot["owner"]) == 0 else G.OPPONENT
			var timer = character.idleAniSpeedTimer
			timer.process_mode = int(snapshot["process_mode"])
			if not snapshot["stopped"]:
				timer.start(float(snapshot["left"]))
				timer.wait_time = float(snapshot["wait_time"])
				U.oracleTimerLefts[timer] = [float(snapshot["left"]), timer.get_time_left()]
''' % json.dumps(timers, ensure_ascii=False))
script = out / "oracle_fight.gd"
script.write_text(source, encoding="utf8")
oracle_diagnostics = None
if not args.compare_only:
    p, log, handle = gh.spawn(gh.cmd(project=str(stage / "full_corpus/expand/project"), script=str(script)),
                         label="native_boundary_compare", tag="native_boundary_compare",
                         env_extra={"ORACLE_ONLY_CASES": args.case_id,
                                    "ORACLE_FIGHTS_ROOT": str(out / "fights"),
                                    "ORACLE_REQUIRE_TERMINAL": "1", "ORACLE_FIGHT_CHUNK": "1"})
    print("pid", p.pid, "log", log, flush=True)
    try:
        rc = p.wait(timeout=240)
    except subprocess.TimeoutExpired:
        p.kill()
        p.wait()
        raise
    finally:
        handle.close()
    if rc:
        raise SystemExit(rc)
    log_text = Path(log).read_text("utf8", errors="replace")
    errors = re.findall(r"SCRIPT ERROR: ([^\r\n]+)\s+at: ([^\r\n]+)", log_text)
    oracle_diagnostics = {"log": str(log), "script_errors": len(errors),
                          "sites": sorted(set(site for _, site in errors)),
                          "scope": "Skeleton UI startup/teardown errors are retained; this is not a clean native-scene run"}
    (out / "oracle_diagnostics.json").write_text(json.dumps(oracle_diagnostics, indent=2) + "\n", encoding="utf8")
    fatal = [(message, site) for message, site in errors
             if any(location in site for location in (str(script), "_native_", "_restore_native_visuals", "/ElectricalCharge.gd", "/FlickerAnimation.gd"))]
    if fatal or "Debugger Break" in log_text:
        raise SystemExit("Oracle candidate has a scheduler/visual script error; inspect " + str(log))
paths = [reference / "events.json", out / "fights" / args.case_id / "events.json"]
documents = [json.loads(path.read_text("utf8")) for path in paths]
streams = [canonical_stream(str(path), _et_names()) for path in paths]
first = next((i for i, (a, b) in enumerate(zip(*streams)) if _tuple_of(a) != _tuple_of(b)), None)
identities = [[recorded_gem_identity(row) for row in doc["events"]] for doc in documents]
gem_missing = [label for label, rows in zip(("native", "oracle"), identities) if () in rows]
gem_first = next((i for i, (a, b) in enumerate(zip(*identities)) if a != b), None)
input_fields = ("seed", "run_id", "round_id", "opp_run_id", "opp_round_id")
inputs_match = all(key in documents[0] and documents[0][key] == documents[1].get(key) for key in input_fields)
natural_ending_match = all(
    doc["events"] and doc["event_count"] == len(doc["events"])
    and doc["events"][-1]["type"] == {"player": 111, "opponent": 112}.get(doc.get("winner"))
    and round(float(doc["events"][-1]["timestamp"]) * 60) == round(float(doc["combat_time"]) * 60)
    for doc in documents) and documents[0]["winner"] == documents[1]["winner"]
rng_comparison = None
if args.rng_probe:
    draws = [json.loads((path.parent / "rng_draws.json").read_text("utf8")) for path in paths]
    def draw_key(row):
        return row["kind"], row["lower"], row["upper"], row["state"], round(float(row["time"]) * 60)
    rng_first = next((i for i, (a, b) in enumerate(zip(*draws)) if draw_key(a) != draw_key(b)), None)
    rng_comparison = {"counts": list(map(len, draws)), "first": rng_first,
                      "match": rng_first is None and len(draws[0]) == len(draws[1])}
result = {"case_id": args.case_id, "counts": list(map(len, streams)), "first": first,
          "match": first is None and len(streams[0]) == len(streams[1]) and inputs_match
                   and natural_ending_match and not gem_missing and gem_first is None
                   and (rng_comparison is None or rng_comparison["match"]),
          "inputs_match": inputs_match, "natural_ending_match": natural_ending_match,
          "strict_gem_missing": gem_missing, "strict_gem_first": gem_first,
          "rng": rng_comparison, "controls": vars(args),
          "oracle_script_sha256": hashlib.sha256(script.read_bytes()).hexdigest(),
          "oracle_diagnostics": oracle_diagnostics,
          "native": streams[0][first] if first is not None else None,
          "oracle": streams[1][first] if first is not None else None,
          "scope": "Recovered-source native reference; imported initial states only; all listed events independently computed"}
(out / "comparison.json").write_text(json.dumps(result, indent=2, ensure_ascii=False), encoding="utf8")
print(json.dumps(result, indent=2, ensure_ascii=False))
raise SystemExit(0 if result["match"] else 1)
