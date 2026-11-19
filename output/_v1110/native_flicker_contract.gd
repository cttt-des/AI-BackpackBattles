extends SceneTree

func _initialize():
	call_deferred("check_flickers")

func check_flickers():
	var file = File.new()
	assert(file.open("D:/文件资料/学习/自动背包AI/output/_v1110/decompiled/Items/Animations/FlickerAnimation.gd", File.READ) == OK)
	var original = file.get_as_text()
	file.close()
	# Keep the original script's methods. Only route its autoload access to an
	# independent test context so the GD kernel project can load it.
	var script = GDScript.new()
	script.source_code = original.replace("extends AnimationPlayer", "extends AnimationPlayer\nvar context").replace("Util.rng", "context.rng").replace("Util.callDelayed", "context.callDelayed")
	assert(script.reload() == OK)
	for variant in 4:
		var native_context = CoreContext.new(771 + variant)
		var model_context = CoreContext.new(771 + variant)
		var native = script.new()
		native.context = native_context
		native.minDist = 4.0 if variant == 1 else 0.1
		native.maxDist = 16.0 if variant == 1 else 3.0
		var animation = Animation.new()
		animation.length = 0.3
		animation.loop = variant == 2
		native.add_animation("Flicker", animation)
		native.connect("animation_finished", native, "onAnimationEnded")
		native.playback_speed = 0.7
		native.play("Flicker")
		native.seek(0.1)
		model_context.flicker_initial = [{"limits": [native.minDist, native.maxDist, native.minSpeed, native.maxSpeed],
			"position": 0.1, "speed": 0.7, "length": 0.3, "playing": true,
			"inside_tree": variant != 3, "loop": variant == 2, "pending": []}]
		model_context.restoreFlickers()
		var model = model_context._flickers[0]
		for frame in 5000:
			if variant != 3:
				native.advance(CoreContext.PHYSICS_DELTA)
			model_context.tickFlickers(CoreContext.PHYSICS_DELTA)
			native_context._flushTimed()
			model_context._flushTimed()
			if native.current_animation_position != model.position or native.playback_speed != model.speed or native.is_playing() != model.playing or native_context.rng.rng.get_state() != model_context.rng.rng.get_state():
				print("[FLICKER-FAIL] variant=", variant, " frame=", frame,
					" native_pos=", native.current_animation_position, " model_pos=", model.position,
					" native_playing=", native.is_playing(), " model_playing=", model.playing)
				quit(1)
				return
		native.free()
	print("[FLICKER-PASS] 4 variants x 5000 frames: exact positions, speed, play state and RNG")
	quit()
