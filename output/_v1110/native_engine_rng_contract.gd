extends SceneTree

func _initialize():
	var rng := RandomNumberGenerator.new()
	for value in [0, 1, 11601, 11602, 2147483648, -1]:
		seed(value)
		rng.seed = value
		for size in range(1, 64):
			var actual := range(size)
			var expected := actual.duplicate()
			actual.shuffle()
			for i in range(size - 1, 0, -1):
				var j = rng.randi() % (i + 1)
				var prev = expected[i]
				expected[i] = expected[j]
				expected[j] = prev
			if actual != expected or actual.pick_random() != expected[rng.randi() % size] or randi() != rng.randi():
				printerr("[ENGINE-RNG-FAIL] seed=", value, " size=", size)
				quit(1)
				return
	print("[ENGINE-RNG-PASS] Godot Array.shuffle, pick_random and randi agree with six independent seeded streams")
	quit()
