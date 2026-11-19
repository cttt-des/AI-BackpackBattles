# Godot 3.6 SceneTreeTimer uses real_t for both the initial delay and each
# subtraction. The initial tail fences off timers registered by callbacks.
func _step_native_delays(delta: float) -> void:
	var limit := _timed.size()
	var read := 0
	var write := 0
	while read < limit:
		var entry = _timed[read]
		entry[2] = _nativeF32(entry[2] - delta)
		if entry[2] < 0.0:
			if not fight_ended and is_instance_valid(entry[0]):
				entry[0].callv(entry[1], entry[3])
		else:
			if write != read:
				_timed[write] = entry
			write += 1
		read += 1
	if write != limit:
		var end := _timed.size()
		while read < end:
			_timed[write] = _timed[read]
			write += 1
			read += 1
		_timed.resize(write)
