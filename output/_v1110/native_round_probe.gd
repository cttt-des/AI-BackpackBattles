extends SceneTree

func _initialize():
	var just_below = float("0.49999999999999994")
	var stack_remainder = float("0.7") - float("0.2")
	var values = [just_below, 0.5, -just_below, -0.5, stack_remainder]
	for value in values:
		print("[ROUND] ", "%.17f" % value, " -> ", round(value))
	quit()
