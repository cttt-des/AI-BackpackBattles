extends SceneTree

const STEPS := 300
var frame := 0
var model: Node
var native_events := []
var model_events := []
var native_pending := {}


func _initialize() -> void:
	call_deferred("start")


func start() -> void:
	var path := OS.get_environment("NATIVE_SCENE_DELAY_MODEL")
	var source := File.new()
	if source.open(path, File.READ) != OK:
		quit(1)
		return
	var script := GDScript.new()
	script.source_code = """extends Node
var _timed := []
var fight_ended := false
func _nativeF32(value: float) -> float:
	return PoolRealArray([value])[0]
""" + source.get_as_text()
	source.close()
	if script.reload() != OK:
		quit(1)
		return
	model = script.new()
	root.add_child(model)
	connect("idle_frame", self, "run_frame")


func register_timer(id: int, delay: float, native: bool) -> void:
	if native:
		var timer := create_timer(delay)
		native_pending[id] = timer
		timer.connect("timeout", self, "on_timeout", [id, true])
	else:
		model._timed.append([self, "on_timeout", model._nativeF32(delay), [id, false]])


func on_timeout(id: int, native: bool) -> void:
	if native:
		native_pending.erase(id)
		native_events.append([frame, id])
	else:
		model_events.append([frame, id])
	if id >= 1000:
		register_timer(id - 1000, 0.0, native)


func run_frame() -> void:
	if native_events != model_events or model._timed.size() != native_pending.size():
		printerr("SceneTreeTimer callback mismatch at frame ", frame, ": ", native_events, " vs ", model_events)
		quit(1)
		return
	for pending in model._timed:
		var id: int = pending[3][0]
		if not native_pending.has(id) or native_pending[id].time_left != pending[2]:
			printerr("SceneTreeTimer countdown mismatch at frame ", frame, " timer ", id)
			quit(1)
			return
	if frame == STEPS:
		print("SceneTreeTimer contract: ", frame, " frames, ", native_events.size(), " callbacks, exact countdown and order")
		quit(0)
		return
	frame += 1
	var delta := root.get_process_delta_time()
	if frame < 220:
		var delays := [0.0, delta, 2.0 * delta, 0.2, 0.5, 0.998]
		for offset in 3:
			var id: int = frame * 3 + offset
			if offset == 1:
				id += 1000
			var delay: float = delays[(frame + offset) % delays.size()]
			register_timer(id, delay, true)
			register_timer(id, delay, false)
	model._step_native_delays(delta)
