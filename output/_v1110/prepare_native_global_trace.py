"""Locate global RNG advances in a separate controlled source experiment."""
from pathlib import Path
import argparse
import hashlib
import json
import shutil


stage = Path(__file__).resolve().parent
source = stage / "native_controlled_chess_trace_project"
parser = argparse.ArgumentParser()
parser.add_argument("--project-name", default="native_controlled_global_trace_project")
args = parser.parse_args()
target = (stage / args.project_name).resolve()
assert target.parent == stage and target.name.startswith("native_controlled_global_")
assert source.is_dir() and not target.exists()
shutil.copytree(source, target)

game = target / "Core/Game.gd"
text = game.read_text("utf8")
start = text.index("func activateItems(items):\n")
end = text.index("\nfunc endCombat():", start)
activation = text[start:end]
activation = activation.replace('\temit_signal("combat_start")\n', '''\tvar global_reader = get_node("/root/NativeBattleReader")
\tglobal_reader.global_rng_checkpoint("activate_enter")
\temit_signal("combat_start")
\tglobal_reader.global_rng_checkpoint("combat_start signal")
''')
for line in ("combatTimer.start()", "PLAYER.combatStart()", "OPPONENT.combatStart()",
             "item.preCombatStart()", "item.combatStart()", "item.postCombatStart()"):
    anchor = "\t\t" + line + "\n" if line.startswith("item.") else "\t" + line + "\n"
    assert activation.count(anchor) == 1, line
    label = json.dumps(line) + ' + " " + item.getName()' if line.startswith("item.") else json.dumps(line)
    depth = "\t\t" if line.startswith("item.") else "\t"
    activation = activation.replace(anchor, anchor + depth + f"global_reader.global_rng_checkpoint({label})\n")
game.write_text(text[:start] + activation + text[end:], encoding="utf8", newline="\n")

reader = target / "native_battle_reader.gd"
text = reader.read_text("utf8")
anchor = '\t\tobservations["before_activate"]["engine_seed"] = str(activation_seed)\n'
assert text.count(anchor) == 1
text = text.replace(anchor, anchor + "\t\t_global_probe_begin(activation_seed)\n")
text += '''

var _global_probe_seed := 0
var _global_probe_index := 0
var _global_probe_values := []
var _global_probe_offsets := {}
var _global_probe_enabled := false

func _global_probe_begin(value: int):
	_global_probe_seed = value
	_global_probe_index = 0
	var replay_rng := RandomNumberGenerator.new()
	replay_rng.seed = value
	for i in range(4098):
		_global_probe_values.append(replay_rng.randi())
	for i in range(4096):
		var mark = [_global_probe_values[i], _global_probe_values[i + 1]]
		assert(not _global_probe_offsets.has(mark))
		_global_probe_offsets[mark] = i
	_global_probe_enabled = true
	get_tree().connect("physics_frame", self, "global_rng_checkpoint", ["physics boundary"])
	get_tree().connect("idle_frame", self, "global_rng_checkpoint", ["idle boundary"])

func global_rng_checkpoint(label: String):
	if not _global_probe_enabled:
		return
	if ended or G.combatTimer.combatTime > 1.0:
		_global_probe_enabled = false
		return
	# Identify the next draw, then restore the original cursor on the seeded stream.
	var pair = [randi(), randi()]
	var offset = _global_probe_offsets.get(pair, -1)
	if offset < _global_probe_index:
		fail("Global RNG position outside the controlled trace sequence")
		return
	seed(_global_probe_seed)
	for i in range(offset):
		randi()
	if offset != _global_probe_index:
		print("[GLOBAL-RNG] ", JSON.print([G.combatTimer.combatTime, label, _global_probe_index, offset]))
	_global_probe_index = offset
	if OS.get_environment("NATIVE_TRACE_DISABLE_PARTICLES") == "1" and not label.ends_with("CombatStart()"):
		_global_probe_suppress_particles(get_tree().root)

func _global_probe_suppress_particles(node):
	if node is CPUParticles2D or node is Particles2D:
		node.emitting = false
		node.set_process_internal(false)
		node.set_physics_process_internal(false)
	for child in node.get_children():
		_global_probe_suppress_particles(child)
'''
reader.write_text(text, encoding="utf8", newline="\n")
manifest_path = target / "reference_manifest.json"
manifest = json.loads(manifest_path.read_text("utf8"))
manifest["reader_sha256"] = hashlib.sha256(reader.read_bytes()).hexdigest()
manifest["global_rng_trace_game_sha256"] = hashlib.sha256(game.read_bytes()).hexdigest()
manifest["adaptations"].append("Controlled global RNG cursor probe restores the seed and offset after each observation")
manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf8")
