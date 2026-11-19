extends Timer

# Blocking Oracle adapter: preserve Timer's native float API and double internal
# countdown while observing every start(), including restarts with equal values.
var native_running := false
var native_left := -1.0
var _native_bound := false

static func native_f32(value: float) -> float:
	var packed := PoolRealArray()
	packed.append(value)
	return packed[0]

func native_bind_current() -> void:
	native_left = .get_time_left()
	native_running = is_processing_internal() or is_physics_processing_internal()
	_native_bound = true
	_native_sync_registry()

func _native_sync_registry() -> void:
	var utility = get_node("/root/Util")
	utility.oracleTimerLefts[self] = [native_f32(max(0.0, native_left)), 0.0]

func start(duration: float = -1.0) -> void:
	.start(duration)
	native_left = get_wait_time()
	native_running = true
	_native_bound = true
	_native_sync_registry()

func stop() -> void:
	.stop()
	native_left = -1.0
	native_running = false
	_native_bound = true
	_native_sync_registry()

func stopCountdownForTimeout() -> void:
	# Engine one-shot expiry calls Timer.stop(), not MultiTimer.stop().
	stop()

func get_time_left() -> float:
	if not _native_bound:
		native_bind_current()
	return native_f32(max(0.0, native_left))

func is_stopped() -> bool:
	return get_time_left() <= 0.0

func native_step(delta: float) -> void:
	if not native_running:
		return
	native_left -= delta
	if native_left < 0.0:
		if one_shot:
			# Direct engine stop leaves the subclass timestamp queue intact.
			.stop()
			native_left = -1.0
			native_running = false
		else:
			native_left += get_wait_time()
		_native_sync_registry()
		emit_signal("timeout")
	else:
		_native_sync_registry()
