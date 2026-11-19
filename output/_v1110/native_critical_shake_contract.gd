extends SceneTree

# Compare scalar lifetime/period scheduling with real RichTextLabel and
# physics AnimationPlayer callbacks on a 60 Hz Godot 3.6 SceneTree.
const STREAM_SEED := 11602
const TYPES := [0.7, 1.1]
const BIRTHS := {4: [0], 76: [1], 151: [0, 1], 201: [1, 1]}
const LATE_BIRTHS := {140: [0], 162: [0], 202: [1]}
const MAX_FRAME := 300
var frame := 0
var draws := 0
var tape := []
var offsets := {}
var observed := [[], []]
var terminals := []
var mismatches := []
var expected := 0


class NativeLabel extends Node2D:
	var death_callback: FuncRef
	var birthday: int
	var kind: int

	func retire() -> void:
		get_parent().remove_child(self)
		death_callback.call_func(birthday, kind)
		queue_free()

class PhysicsSpawner extends Node:
	var callback: FuncRef

	func _physics_process(_delta: float) -> void:
		callback.call_func()


func _initialize() -> void:
	call_deferred("start")


func start() -> void:
	var rng := RandomNumberGenerator.new()
	rng.seed = STREAM_SEED
	for i in range(1026):
		tape.append(rng.randi())
	for i in range(1024):
		var key := [tape[i], tape[i + 1]]
		assert(not offsets.has(key))
		offsets[key] = i
	seed(STREAM_SEED)
	var spawner := PhysicsSpawner.new()
	spawner.callback = funcref(self, "spawn_on_physics_pass")
	root.add_child(spawner)
	connect("physics_frame", self, "on_physics_frame")
	connect("idle_frame", self, "on_idle_frame")


func on_physics_frame() -> void:
	var offset: int = offsets.get([randi(), randi()], -1)
	if offset != expected:
		mismatches.append([frame, expected, offset])
		if offset < 0:
			quit(1)
			return
	if frame >= 4 and frame < 46 and offset > draws:
		observed[0].append(frame - 4)
	if frame >= 76 and frame < 143 and offset > draws:
		observed[1].append(frame - 76)
	draws = offset
	seed(STREAM_SEED)
	for i in range(draws):
		randi()
	frame += 1
	if frame > MAX_FRAME:
		print("[CRITICAL-SHAKE] ", JSON.print({"frames": MAX_FRAME, "draws": draws,
			"item_idle_passes": observed[0], "character_idle_passes": observed[1],
			"animation_end_frames_after_spawn": terminals, "mismatches": mismatches.slice(0, 8)}))
		quit(0 if mismatches.empty() else 1)
		return
	beginCriticalShakeFrame()


func spawn_on_physics_pass() -> void:
	for kind in BIRTHS.get(frame, []):
		spawn(kind)
	for kind in LATE_BIRTHS.get(frame, []):
		create_timer(0.0).connect("timeout", self, "spawn", [kind], CONNECT_ONESHOT)


func on_idle_frame() -> void:
	var physics_delta := root.get_physics_process_delta_time()
	var idle_delta := root.get_process_delta_time()
	if not is_equal_approx(physics_delta, 1.0 / 60.0) or not is_equal_approx(idle_delta, physics_delta):
		printerr("[CRITICAL-SHAKE-FAIL] unexpected dt ", physics_delta, " ", idle_delta)
		quit(1)
		return
	stepCriticalShake()


func spawn(kind: int) -> void:
	var number := NativeLabel.new()
	number.birthday = frame
	number.kind = kind
	number.death_callback = funcref(self, "on_retire")
	var label := RichTextLabel.new()
	label.bbcode_enabled = true
	label.bbcode_text = "[center][shake rate=20 level=50]42[/shake]"
	number.add_child(label)
	var anim := Animation.new()
	anim.length = TYPES[kind]
	var track := anim.add_track(Animation.TYPE_METHOD)
	anim.track_set_path(track, NodePath("."))
	anim.track_insert_key(track, TYPES[kind], {"method": "retire", "args": []})
	var animation := AnimationPlayer.new()
	animation.playback_process_mode = AnimationPlayer.ANIMATION_PROCESS_PHYSICS
	animation.add_animation("LabelLifetime", anim)
	number.add_child(animation)
	root.add_child(number)
	animation.play("LabelLifetime")
	collectCriticalShake(kind == 0)


func on_retire(birthday: int, kind: int) -> void:
	terminals.append([kind, frame - birthday])
