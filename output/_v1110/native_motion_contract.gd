extends SceneTree

var native_forward := false

func moving_back():
	native_forward = false

func _initialize():
	call_deferred("check_motion")

func check_motion():
	var body = Node2D.new()
	root.add_child(body)
	var context = CoreContext.new(771)
	var model = CoreCharacter.new(context, 0)
	var random = RandomNumberGenerator.new()
	random.seed = 19
	var tween = null
	var starts := 0
	var delta = CoreContext.PHYSICS_DELTA
	for frame in range(2000):
		if frame % 7 == 0 and not native_forward:
			var kind = 1 if frame % 3 else 2
			var forward = random.randf_range(-0.1, 0.15)
			var backward = random.randf_range(0.03, 0.4)
			var target = Vector2(random.randf_range(100, 160), 0) if kind == 1 else Vector2(body.position.x, -40)
			if is_instance_valid(tween):
				tween.kill()
			tween = body.create_tween()
			if kind == 1:
				tween.tween_property(body, "position", target, forward)
			else:
				tween.tween_property(body, "position:y", target.y, forward)
			tween.tween_callback(self, "moving_back")
			if kind == 1:
				tween.tween_property(body, "position", Vector2.ZERO, backward)
			else:
				tween.tween_property(body, "position:y", 0.0, backward)
			native_forward = true
			model._beginVisualMotion(kind, target.x, target.y, forward, backward)
			starts += 1
		if is_instance_valid(tween) and tween.is_valid():
			tween.custom_step(delta)
		model.tickVisualMotion(delta)
		if body.position.x != model._visual_x or body.position.y != model._visual_y or native_forward != model.attack_moving_forward:
			print("[MOTION-FAIL] frame=", frame, " native=", body.position, " model=", Vector2(model._visual_x, model._visual_y),
				" native_forward=", native_forward, " model_forward=", model.attack_moving_forward,
				" elapsed=", model._visual_elapsed, " forward=", model._visual_forward, " back=", model._visual_back)
			quit(1)
			return
	print("[MOTION-PASS] exact positions and latch at 2000 frames; transitions=", starts)
	quit()
