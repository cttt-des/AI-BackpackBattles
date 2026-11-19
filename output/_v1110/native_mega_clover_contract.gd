extends SceneTree

# The emitting properties of Interface/MegaCloverParticles.tscn. The texture,
# color and particle geometry do not affect the number of calls to Math::rand.
const DRAW_COUNTS := [20, 10, 10, 10, 10, 10, 0, 10, 10, 0, 0, 0]
const IDLE_END_DRAW_COUNTS := [10, 10, 10, 10, 10, 10, 10, 0, 10, 10, 0, 0]
const SEED := 669606417
var frames := 0
var expected := RandomNumberGenerator.new()
var idle_spawn := false
var total_draws := 0


func _initialize():
	call_deferred("prepare")


func prepare():
	idle_spawn = OS.get_environment("NATIVE_PARTICLE_SPAWN") == "idle_end"
	if idle_spawn:
		create_timer(0.0).connect("timeout", self, "start_particles", [], CONNECT_ONESHOT)
	else:
		connect("physics_frame", self, "start_particles", [], CONNECT_ONESHOT)


func start_particles():
	var particles := CPUParticles2D.new()
	particles.emitting = false
	particles.amount = 9
	particles.one_shot = true
	particles.speed_scale = 1.66
	particles.explosiveness = 0.71
	particles.emission_shape = CPUParticles2D.EMISSION_SHAPE_RECTANGLE
	root.add_child(particles)
	expected.seed = SEED
	seed(SEED)
	particles.restart()
	connect("physics_frame", self, "check_draws")


func check_draws():
	var count: int = IDLE_END_DRAW_COUNTS[frames] if idle_spawn else DRAW_COUNTS[frames]
	for _i in count:
		expected.randi()
	total_draws += count
	var actual := randi()
	var wanted := expected.randi()
	if actual != wanted:
		printerr("Mega Clover draw mismatch at frame ", frames + 1, " got ", actual, " wanted ", wanted)
		quit(1)
		return
	frames += 1
	if frames == DRAW_COUNTS.size():
		print("Mega Clover particle contract: ", frames, " frames, ", total_draws, " draws")
		quit(0 if total_draws == 90 else 1)
