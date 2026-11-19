extends SceneTree

var frame := 0
var native_context
var model_context
var native_timers := []
var model_timers := []
var native_events := []
var model_events := []
var model_script

class Receiver:
	extends Reference
	var driver
	var index
	func timeout():
		driver.model_timeout(index)

func read_text(path):
	var file = File.new()
	assert(file.open(path, File.READ) == OK)
	var text = file.get_as_text()
	file.close()
	return text

func _initialize():
	call_deferred("start_contract")

func start_contract():
	var base = "D:/文件资料/学习/自动背包AI/output/_v1110/"
	model_script = GDScript.new()
	model_script.source_code = read_text(base + "native_timer_model.gd.inc")
	assert(model_script.reload() == OK)
	var multi_script = GDScript.new()
	multi_script.source_code = read_text(base + "decompiled/Utility/MultiTimer.gd").replace("extends Timer", "extends Timer\nvar context").replace("Util.time", "context.time")
	assert(multi_script.reload() == OK)
	native_context = CoreContext.new(19)
	model_context = CoreContext.new(19)
	for index in 5:
		var native = multi_script.new() if index == 3 else Timer.new()
		if index == 3:
			native.context = native_context
		native.process_mode = Timer.TIMER_PROCESS_PHYSICS
		native.one_shot = index != 4
		root.add_child(native)
		native.connect("multi_timeout" if index == 3 else "timeout", self, "native_timeout", [index])
		native_timers.append(native)
		var receiver = Receiver.new()
		receiver.driver = self
		receiver.index = index
		var model = model_script.new(model_context, receiver, str(index))
		model.one_shot = index != 4
		model.multi = index == 3
		model.callback_method = "timeout"
		model_timers.append(model)
	var control_script = GDScript.new()
	control_script.source_code = "extends Node\nvar driver\nfunc _physics_process(delta):\n\tdriver.check_frame(delta)\n"
	assert(control_script.reload() == OK)
	var controller = control_script.new()
	controller.driver = self
	root.add_child(controller)
	for timers in [native_timers, model_timers]:
		timers[0].start(0.1)
		timers[1].start(0.2)
		timers[3].start(0.1)
		timers[3].start(0.2)
		timers[3].start(0.25)
		timers[4].start(0.08)

func on_timeout(timers, index):
	if index == 0 and frame < 50:
		timers[1].start(0.05)
		timers[2].start(0.05)
		if frame < 20:
			timers[0].start(0.1)

func native_timeout(index):
	native_events.append([frame, index])
	on_timeout(native_timers, index)

func model_timeout(index):
	model_events.append([frame, index])
	on_timeout(model_timers, index)

func check_frame(delta):
	model_context.timer_pass_epoch += 1
	model_context.in_physics_timer_pass = true
	for model in model_timers:
		model.tick(delta)
	model_context.in_physics_timer_pass = false
	if native_events != model_events:
		print("[TIMER-FAIL] frame=", frame, " native=", native_events, " model=", model_events)
		quit(1)
		return
	for index in native_timers.size():
		if native_timers[index].get_time_left() != model_timers[index].get_time_left():
			print("[TIMER-FAIL] countdown frame=", frame, " index=", index, " native=", native_timers[index].get_time_left(), " model=", model_timers[index].get_time_left())
			quit(1)
			return
	native_context.time += delta
	model_context.time += delta
	for timers in [native_timers, model_timers]:
		if frame == 9:
			timers[4].start(0.08)
		if frame == 11:
			timers[4].stop()
			timers[4].start(0.08)
		if frame == 18:
			timers[3].stop()
			timers[3].start(0.1)
			timers[3].start(0.1)
		if frame == 45:
			timers[0].start(0.05)
			timers[1].start(0.2)
		if frame == 60:
			timers[0].start(-1)
		if frame == 75:
			timers[0].start(0)
	frame += 1
	if frame == 1000:
		print("[TIMER-PASS] 1000 native physics frames, ", native_events.size(), " callbacks; exact countdowns and event order")
		quit()
