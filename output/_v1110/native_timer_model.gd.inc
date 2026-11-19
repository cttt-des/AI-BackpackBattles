extends Reference

# Timer's float wait_time, double countdown and active-list membership.
# MultiTimer adds only its original timestamp queue and callback sequence.
var _ctx = null
var _owner = null
var name := ""
var wait_time := 1.0 setget set_wait_time
var one_shot := true
var multi := false
var callback_method := ""
var timestamps: Array = []
var fire_count := 0
var _left := -1.0
var _stopped := true
var _first_pass := 0

func _init(ctx = null, owner = null, timerName: String = "") -> void:
	_ctx = ctx
	_owner = owner
	name = timerName

static func _f32eng(x: float) -> float:
	var pa = PoolRealArray()
	pa.append(x)
	return pa[0]

func set_wait_time(duration: float) -> void:
	if duration > 0.0:
		wait_time = _f32eng(duration)

func get_time_left() -> float:
	return _f32eng(max(0.0, _left))

func is_stopped() -> bool:
	return get_time_left() <= 0.0

func start(duration = -1.0) -> void:
	if multi and not is_stopped():
		timestamps.push_back(_utilTime() + duration)
		return
	if duration != null and duration > 0.0:
		set_wait_time(duration)
	_left = wait_time
	if _stopped:
		_first_pass = _ctx.timer_pass_epoch + 1 if _ctx != null else 0
	_stopped = false

func stop() -> void:
	timestamps.clear()
	stopCountdownForTimeout()

func stopCountdownForTimeout() -> void:
	_stopped = true
	_left = -1.0

func isFinished() -> bool:
	return timestamps.empty()

func tick(delta: float) -> void:
	if _stopped or (_ctx != null and _ctx.timer_pass_epoch < _first_pass):
		return
	_left -= delta
	if _left < 0.0:
		_onTimeout()

func _onTimeout() -> void:
	if one_shot:
		stopCountdownForTimeout()
	else:
		_left += wait_time
	_emitTimeout()
	if multi:
		while not timestamps.empty():
			var delay = timestamps.pop_front() - _utilTime()
			if delay > 0.05:
				start(delay)
				break
			_emitTimeout()

func _emitTimeout() -> void:
	fire_count += 1
	if _owner != null and callback_method != "":
		_owner.call(callback_method)

func _utilTime() -> float:
	return _ctx.time if _ctx != null else 0.0

func rebuildSeen() -> void:
	pass
