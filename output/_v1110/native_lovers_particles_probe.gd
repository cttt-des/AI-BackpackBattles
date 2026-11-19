extends SceneTree

const SEED := 669606417
var emitter
var emitter_script
var sequence := []
var cursor := 0
var counts := []
var restart_after := -1
var restart_visible = null
var profiles := {}
var pending := []
var profile := ""

func _initialize():
	call_deferred("prepare")

func prepare():
	var file := File.new()
	var source = OS.get_environment("NATIVE_CPU_PARTICLE_SCRIPT")
	if file.open(source, File.READ) != OK:
		quit(1)
		return
	emitter_script = GDScript.new()
	emitter_script.source_code = file.get_as_text()
	file.close()
	if emitter_script.reload() != OK:
		quit(1)
		return
	profiles = JSON.parse(OS.get_environment("NATIVE_PARTICLE_CASES")).result
	pending = profiles.keys()
	var expected := RandomNumberGenerator.new()
	expected.seed = SEED
	for _i in 900:
		sequence.append(expected.randi())
	run_next()

func run_next():
	if pending.empty():
		quit()
		return
	profile = pending.pop_front()
	var specification: Array = profiles[profile]
	restart_after = int(specification[1])
	restart_visible = null
	cursor = 0
	counts = []
	emitter = CPUParticles2D.new()
	emitter.set_script(emitter_script)
	emitter.emitting = false
	emitter.amount = 14
	emitter.one_shot = true
	emitter.speed_scale = 0.85
	emitter.explosiveness = 0.78
	emitter.lifetime_randomness = 0.24
	emitter.local_coords = false
	emitter.emission_shape = CPUParticles2D.EMISSION_SHAPE_RECTANGLE
	root.add_child(emitter)
	if specification[0] == "idle_end":
		create_timer(0.0).connect("timeout", self, "start_particles", [], CONNECT_ONESHOT)
	else:
		connect("physics_frame", self, "start_particles", [], CONNECT_ONESHOT)

func start_particles():
	seed(SEED)
	emitter.activate()
	if restart_after == 0:
		restart_visible = emitter.visible
		emitter.activate()
	connect("physics_frame", self, "count_draws")

func count_draws():
	var first := randi()
	var second := randi()
	for index in range(cursor, sequence.size() - 1):
		if sequence[index] == first and sequence[index + 1] == second:
			counts.append(index - cursor)
			cursor = index + 2
			if counts.size() == restart_after:
				restart_visible = emitter.visible
				emitter.activate()
			if counts.size() == max(30, restart_after + 17):
				print("[LOVERS-PARTICLES] ", JSON.print({"profile": profile, "draws": counts, "visible": restart_visible}))
				disconnect("physics_frame", self, "count_draws")
				emitter.queue_free()
				call_deferred("run_next")
			return
	printerr("Cannot locate the particle RNG state at frame ", counts.size() + 1)
	quit(1)
