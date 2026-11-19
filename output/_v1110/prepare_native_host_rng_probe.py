"""Record shared RNG draws caused by the Windows focus and process timer callbacks."""
import hashlib
import json
from pathlib import Path
import sys

from stage_native_mega_clover_rng import replace_one


def main():
    project = Path(sys.argv[1])
    if not project.name.startswith("native_host_rng_"):
        raise ValueError("Use a separate recovered project for the host RNG probe")
    game = project / "Core/Game.gd"
    source = game.read_text("utf8")
    rng_call = "processTimer.start(Util.rng.randf_range(10, 30))"
    assert source.count(rng_call) == 2
    for kind in ("focus_out", "process_timer"):
        source = source.replace(rng_call, f'processTimer.start(_nativeObserveHostDelay("{kind}"))', 1)
    source += """

func _nativeObserveHostDelay(kind: String) -> float:
	var before = str(Util.rng.get_state())
	var delay = Util.rng.randf_range(10, 30)
	var reader = get_node_or_null("/root/NativeBattleReader")
	if reader != null:
		reader.on_host_rng(kind, before, str(Util.rng.get_state()))
	return delay
"""

    reader = project / "native_battle_reader.gd"
    body = reader.read_text("utf8")
    anchor = '\tobservations = {"startup": startup, "batch_index": index}\n'
    body = replace_one(body, anchor, anchor + '\tobservations["host_rng_draws"] = []\n')
    body += """

func on_host_rng(kind: String, before: String, after: String) -> void:
	if activated and not ended:
		observations["host_rng_draws"].append({"kind": kind, "before": before, "after": after,
			"combat_time": "%.17f" % G.combatTimer.combatTime, "physics_frame": Engine.get_physics_frames()})
"""

    game.write_text(source, encoding="utf8", newline="\n")
    reader.write_text(body, encoding="utf8", newline="\n")
    path = project / "reference_manifest.json"
    manifest = json.loads(path.read_bytes())
    manifest["reader_sha256"] = hashlib.sha256(reader.read_bytes()).hexdigest()
    manifest["host_rng_game_sha256"] = hashlib.sha256(game.read_bytes()).hexdigest()
    manifest["adaptations"].append("Observe Util RNG at window-focus and process timer callbacks")
    path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")


if __name__ == "__main__":
    main()
