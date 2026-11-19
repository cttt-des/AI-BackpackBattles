extends RandomNumberGenerator

# Observe actual engine draws without changing their values or advancing PCG.
# Enabled only at the activation boundary, and bounded to a full natural fight.
var recording := false
var draws := []

func observe(kind, lower, upper, value) -> void:
	if not recording:
		return
	var game = Engine.get_main_loop().root.get_node("Game")
	var timestamp = game.combatTimer.combatTime
	if timestamp > 90.0 or draws.size() >= 200000:
		recording = false
		return
	draws.append({"kind": kind, "lower": lower, "upper": upper, "value": value,
		"state": str(get_state()), "time": timestamp,
		"physics_frame": Engine.get_physics_frames(), "stack": get_stack()})

func randf_range(lower, upper):
	var value = .randf_range(lower, upper)
	observe("randf_range", lower, upper, value)
	return value

func randf():
	var value = .randf()
	observe("randf", 0, 1, value)
	return value

func randi_range(lower, upper):
	var value = .randi_range(lower, upper)
	observe("randi_range", lower, upper, value)
	return value

func randi():
	var value = .randi()
	observe("randi", 0, 4294967295, value)
	return value
