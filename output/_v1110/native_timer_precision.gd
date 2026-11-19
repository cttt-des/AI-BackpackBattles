extends SceneTree

class Observer extends Node:
	var frames := 0
	var rage: Timer
	var fatigue_start: Timer
	var fatigue_tick: Timer
	func make_timer() -> Timer:
		var timer = Timer.new()
		timer.process_mode = Timer.TIMER_PROCESS_PHYSICS
		timer.one_shot = true
		add_child(timer)
		return timer
	func _ready():
		rage = make_timer()
		fatigue_start = make_timer()
		fatigue_tick = make_timer()
		rage.connect("timeout", self, "on_rage_end")
		fatigue_start.connect("timeout", self, "on_fatigue_start")
		fatigue_tick.connect("timeout", self, "on_fatigue_tick")
		rage.start(5.5)
		fatigue_start.start(14.0)
	func _physics_process(delta):
		frames += 1
		if frames == 1:
			print("[PRECISION] physics_delta=%.17f" % delta)
		if frames > 1100:
			get_tree().quit(1)
	func on_rage_end():
		print("[PRECISION] rage ended before physics frame ", frames + 1)
	func on_fatigue_start():
		print("[PRECISION] fatigue start before physics frame ", frames + 1)
		fatigue_tick.start(3.0)
	func on_fatigue_tick():
		print("[PRECISION] fatigue damage before physics frame ", frames + 1)
		get_tree().quit()

func _initialize():
	root.add_child(Observer.new())
