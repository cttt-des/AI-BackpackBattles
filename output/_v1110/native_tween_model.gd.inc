# State needed by the RNG gates in Character.playAttack/ActivateAnimation.
# The renderer's Tween is reduced to a linear two-stage motion and one latch.
var attack_moving_forward := false
var attack_sound_ready_time := -1.0
var _tick_timer_left := 0.0
var _tick_timer_active := false
var damage_anim_current := ""
var _visual_x := 0.0
var _visual_y := 0.0
var _visual_from_x := 0.0
var _visual_from_y := 0.0
var _visual_to_x := 0.0
var _visual_to_y := 0.0
var _visual_forward := 0.0
var _visual_back := 0.0
var _visual_elapsed := 0.0
var _visual_kind := 0
var _visual_stage := 0
var _visual_generation := 0
var _idle_animation_left := 1.0

func _beginVisualMotion(kind: int, to_x: float, to_y: float, forward: float, back: float) -> void:
	_visual_generation += 1
	ctx.registerMotion(0, self, _visual_generation)
	_visual_from_x = _visual_x
	_visual_from_y = _visual_y
	_visual_to_x = to_x
	_visual_to_y = to_y
	_visual_forward = _f32eng(forward)
	_visual_back = _f32eng(back)
	_visual_elapsed = 0.0
	_visual_kind = kind
	_visual_stage = 0
	attack_moving_forward = true

static func _visualLerp(a: float, b: float, elapsed: float, duration: float) -> float:
	return _f32eng(a + _f32eng(_f32eng(_f32eng(b - a) * elapsed) / duration))

func tickVisualMotion(delta: float) -> void:
	if _visual_kind == 0:
		return
	var remaining = delta
	if _visual_stage == 0:
		_visual_elapsed = _f32eng(_visual_elapsed + remaining)
		if _visual_elapsed < _visual_forward:
			_visual_x = _visualLerp(_visual_from_x, _visual_to_x, _visual_elapsed, _visual_forward)
			_visual_y = _visualLerp(_visual_from_y, _visual_to_y, _visual_elapsed, _visual_forward)
			return
		_visual_x = _visual_to_x
		_visual_y = _visual_to_y
		remaining = min(delta, _f32eng(_visual_elapsed - _visual_forward))
		_visual_elapsed = 0.0
		_visual_stage = 1
	if _visual_stage == 1:
		if remaining <= 0.0:
			return
		attack_moving_forward = false
		_visual_stage = 2
	_visual_elapsed = _f32eng(_visual_elapsed + remaining)
	var back_x = 0.0 if _visual_kind == 1 else _visual_from_x
	if _visual_elapsed < _visual_back:
		_visual_x = _visualLerp(_visual_to_x, back_x, _visual_elapsed, _visual_back)
		_visual_y = _visualLerp(_visual_to_y, 0.0, _visual_elapsed, _visual_back)
	else:
		_visual_x = back_x
		_visual_y = 0.0
		_visual_kind = 0

func tickIdleAnimation(delta: float) -> void:
	_idle_animation_left -= delta
	if _idle_animation_left < 0.0:
		ctx.rng.randf_range(0.8, 1.2)
		_idle_animation_left = _f32eng(ctx.rng.randf_range(2.0, 5.0))

func playAttackAnimation() -> void:
	var distance = ctx.rng.randf_range(100.0, 160.0)
	if attack_moving_forward:
		return
	var forward = _f32eng(distance - _visual_x) / 2600.0 * ctx.rng.randf_range(0.9, 1.1)
	var back = distance / 1000.0 * ctx.rng.randf_range(0.9, 1.1)
	_beginVisualMotion(1, distance, 0.0, forward, back)
	ctx.rng.randi_range(0, 2)
	ctx.rng.randf_range(0.8, 1.2)
	if ctx.time > attack_sound_ready_time:
		ctx.rng.randi_range(0, classAttackSoundCount() - 1)
		attack_sound_ready_time = ctx.time + 0.1
