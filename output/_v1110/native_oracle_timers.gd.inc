var _native_plain_timer_script
var _native_multi_timer_script

func _native_install_timers(node):
	if _native_plain_timer_script == null:
		_native_plain_timer_script = load("D:/文件资料/学习/自动背包AI/output/_v1110/native_oracle_timer.gd")
		var file = File.new()
		assert(file.open("D:/文件资料/学习/自动背包AI/output/_v1110/decompiled/Utility/MultiTimer.gd", File.READ) == OK)
		var original_multi = file.get_as_text()
		file.close()
		_native_multi_timer_script = GDScript.new()
		_native_multi_timer_script.source_code = original_multi.replace("extends Timer", "extends \"D:/文件资料/学习/自动背包AI/output/_v1110/native_oracle_timer.gd\"")
		assert(_native_multi_timer_script.reload() == OK)
	if node is Timer and not ("native_running" in node):
		var timestamps = null
		if node.get_script() == null:
			node.set_script(_native_plain_timer_script)
		elif node.get_script().resource_path.ends_with("/MultiTimer.gd"):
			timestamps = node.timestamps.duplicate()
			node.set_script(_native_multi_timer_script)
			node.timestamps = timestamps
		else:
			assert(false, "Unsupported Timer script: " + node.get_script().resource_path)
		node.native_bind_current()
	for child in node.get_children():
		_native_install_timers(child)

func _native_collect_active_timers(node, physics_pass, found):
	if node is Timer and node.native_running and not node.paused:
		if (node.process_mode == Timer.TIMER_PROCESS_PHYSICS) == physics_pass:
			found.append(node)
	for child in node.get_children():
		_native_collect_active_timers(child, physics_pass, found)

func drive_timers(physics_pass: bool, dt: float) -> void:
	_native_install_timers(root)
	var active := []
	_native_collect_active_timers(root, physics_pass, active)
	for timer in active:
		if is_instance_valid(timer) and timer.is_inside_tree():
			timer.native_step(dt)
