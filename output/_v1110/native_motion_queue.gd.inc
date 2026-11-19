# Creation order of battle-relevant Tween effects, with no visual objects.
# An entry is [kind, subject, generation-or-charge]. New entries wait until the
# next pass, just as SceneTree::process_tweens snapshots its last list element.
var _motion_queue: Array = []

func registerMotion(kind: int, subject, token) -> void:
	_motion_queue.push_back([kind, subject, token])

func tickMotion(delta: float) -> void:
	if _motion_queue.empty():
		return
	var snapshot = _motion_queue
	_motion_queue = []
	var survivors := []
	for entry in snapshot:
		if entry[0] == 0:
			var character = entry[1]
			if character._visual_generation != entry[2] or character._visual_kind == 0:
				continue
			character.tickVisualMotion(delta)
			if character._visual_kind != 0:
				survivors.append(entry)
		else:
			var charge = entry[2]
			entry[1]._tickChargePath(charge, delta)
			if charge.active:
				survivors.append(entry)
	survivors.append_array(_motion_queue)
	_motion_queue = survivors
