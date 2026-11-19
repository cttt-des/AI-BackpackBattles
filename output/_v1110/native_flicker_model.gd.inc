# FlickerAnimation's only combat-relevant effect is its shared RNG consumption.
# Each source has a position/speed and optional delayed play; no animation tracks.
var flicker_initial = null
var _flickers: Array = []

static func _nativeF32(value: float) -> float:
	var packed := PoolRealArray()
	packed.append(value)
	return packed[0]

class NativeFlicker:
	var ctx
	var limits: Array
	var position := 0.0
	var speed := 1.0
	var length := 0.3
	var playing := false
	var inside_tree := true
	var loop := false

	func playAni() -> void:
		speed = ctx._nativeF32(ctx.rng.bare_randf_range(limits[2], limits[3]))
		position = 0.0
		playing = true

	func tick(delta: float) -> void:
		if not inside_tree or not playing:
			return
		position = ctx._nativeF32(position + ctx._nativeF32(delta * speed))
		if position >= length:
			if loop:
				position = fmod(position, length)
			else:
				position = length
				playing = false
				ctx.callDelayed(self, "playAni", ctx.rng.bare_randf_range(limits[0], limits[1]))

func restoreFlickers() -> void:
	var keep := []
	for pending in _timed:
		if pending[1] != "flickerPlayAni":
			keep.append(pending)
	_timed = keep
	lib_fires = []
	_flickers = []
	for snapshot in flicker_initial:
		var flicker = NativeFlicker.new()
		flicker.ctx = self
		flicker.limits = snapshot["limits"]
		flicker.position = _nativeF32(float(snapshot.get("position_precise", snapshot["position"])))
		flicker.speed = _nativeF32(float(snapshot.get("speed_precise", snapshot["speed"])))
		flicker.length = _nativeF32(float(snapshot["length"]))
		flicker.playing = bool(snapshot["playing"])
		flicker.inside_tree = bool(snapshot["inside_tree"])
		flicker.loop = bool(snapshot["loop"])
		_flickers.append(flicker)
		for pending in snapshot["pending"]:
			assert(pending["method"] == "playAni")
			callDelayed(flicker, "playAni", float(pending["left"]))

func tickFlickers(delta: float) -> void:
	for flicker in _flickers:
		flicker.tick(delta)
