"""Pin a no-Flicker diagnostic clone to a recorded activation boundary."""
import argparse
import hashlib
import json
from pathlib import Path

from stage_native_mega_clover_rng import replace_one


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("project", type=Path)
    ap.add_argument("recording", type=Path)
    ap.add_argument("--opening-only", action="store_true", help="Leave idle Flicker state untouched and inspect activation events")
    args = ap.parse_args()
    project, source = args.project, args.recording
    if not project.name.startswith("native_controlled_") or project.resolve() == source.resolve():
        raise ValueError("Use an isolated controlled project")
    data = json.loads((source / "boundaries.json").read_bytes())
    assert args.opening_only or not data["flicker_states"]
    assert data["combat_start"]["state"] == data["before_activate"]["state"]
    assert all(row[3] == 0 for side in data["before_activate"]["buff_state"] for row in side)
    reader = project / "native_battle_reader.gd"
    body = reader.read_text("utf8")
    body += """

var native_trajectory_boundary

func read_native_trajectory_boundary():
	if native_trajectory_boundary != null:
		return native_trajectory_boundary
	var f = File.new()
	var result = f.open("res://activation_probe.json", File.READ)
	assert(result == OK)
	native_trajectory_boundary = JSON.parse(f.get_as_text()).result
	f.close()
	return native_trajectory_boundary

func restore_native_trajectory_rng(boundary):
	U.rng.set_seed(int(boundary["seed"]))
	U.rng.set_state(int(boundary["state"]))
	seed(int(boundary["engine_seed"]))
	for _draw in range(int(boundary["engine_offset"])):
		randi()
"""
    prepare_anchor = "func on_prepare(items) -> void:\n"
    body = replace_one(body, prepare_anchor, prepare_anchor +
                       '\trestore_native_trajectory_rng(read_native_trajectory_boundary()["prepare"])\n')
    anchor = "func on_activate(_items) -> void:\n"
    restore = """\tvar reference = read_native_trajectory_boundary()
	var activation = reference["before_activate"]
	for character in [G.PLAYER, G.OPPONENT]:
		for buff in character.buffs.values():
			assert(buff.temporaryStacks.empty())
			buff.current = 0
			buff.permanentStacks = 0
		for row in activation["buff_state"][character.playerId]:
			var buff = character.buffs[int(row[0])]
			buff.current = int(row[1])
			buff.permanentStacks = int(row[2])
	restore_native_trajectory_rng(activation)
	U.time = float(reference["combat_start"]["util_time"])
	U.clockTime = float(reference["combat_start"]["clock_time"])
	for observed in reference["idle_animation_timers"]:
		var character = G.PLAYER if int(observed["owner"]) == 0 else G.OPPONENT
		var timer = character.idleAniSpeedTimer
		timer.start(float(observed["left_precise"]))
		timer.wait_time = float(observed["wait_time"])
"""
    updated = replace_one(body, anchor, anchor + restore)
    reader.write_text(updated, encoding="utf8")
    (project / "activation_probe.json").write_text(json.dumps(
        {key: data[key] for key in ("prepare", "combat_start", "before_activate", "idle_animation_timers")},
        indent=2), encoding="utf8")
    manifest_file = project / "reference_manifest.json"
    manifest = json.loads(manifest_file.read_bytes())
    manifest["reader_sha256"] = hashlib.sha256(reader.read_bytes()).hexdigest()
    manifest["scope"] = "Controlled activation diagnostic on recovered source"
    manifest["adaptations"].append("Restore RNG, process clocks, carried buff balances and idle timers from the recorded activation boundary")
    manifest["diagnostic_original_sha256"] = hashlib.sha256((source / "events.json").read_bytes()).hexdigest()
    if args.opening_only:
        manifest["scope"] += " restricted to activation events because Flicker state is unchanged"
    manifest_file.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")


if __name__ == "__main__":
    main()
