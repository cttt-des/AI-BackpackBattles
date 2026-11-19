# Fixed 60 Hz idle passes. Each visible rate-20 shake draws once every third
# pass starting on pass three. A physics animation added during physics first
# runs on the following pass. An item label therefore gets one extra shake
# when born before the idle pass, compared with a callback born after idle.
const CRITICAL_SHAKE_WINDOW := 72
var _critical_shake_delta := []
var _critical_shake_active := [0, 0, 0]
var _critical_shake_frame := 0
var _critical_shake_after_idle := true

func resetCriticalShake() -> void:
	_critical_shake_delta.clear()
	_critical_shake_active = [0, 0, 0]
	_critical_shake_frame = 0
	_critical_shake_after_idle = true

func beginCriticalShakeFrame() -> void:
	_critical_shake_after_idle = false

func collectCriticalShake(on_item: bool) -> void:
	if _critical_shake_delta.empty():
		_critical_shake_delta.resize(CRITICAL_SHAKE_WINDOW)
		for i in range(CRITICAL_SHAKE_WINDOW):
			_critical_shake_delta[i] = 0
	var first := _critical_shake_frame + 2
	var end_offset := 66
	if on_item:
		end_offset = 39 if _critical_shake_after_idle else 42
	_critical_shake_delta[first % CRITICAL_SHAKE_WINDOW] += 1
	_critical_shake_delta[(first + end_offset) % CRITICAL_SHAKE_WINDOW] -= 1

func stepCriticalShake() -> void:
	_critical_shake_after_idle = true
	if _critical_shake_delta.empty():
		return
	var phase := _critical_shake_frame % 3
	_critical_shake_active[phase] += _critical_shake_delta[_critical_shake_frame]
	_critical_shake_delta[_critical_shake_frame] = 0
	var remaining := int(_critical_shake_active[phase])
	while remaining > 0:
		randi()
		remaining -= 1
	_critical_shake_frame = (_critical_shake_frame + 1) % CRITICAL_SHAKE_WINDOW
