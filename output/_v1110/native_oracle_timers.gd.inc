var _native_plain_timer_script
var _native_multi_timer_script
var _native_timer_cache := []
var _native_timer_cache_dirty := true
var _native_timer_cache_connected := false

func _native_timer_tree_changed():
	_native_timer_cache_dirty = true

func _native_install_timers(node, collect := false):
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
	if collect and node is Timer:
		_native_timer_cache.append(node)
	for child in node.get_children():
		_native_install_timers(child, collect)

func drive_timers(physics_pass: bool, dt: float) -> void:
	if not _native_timer_cache_connected:
		assert(has_signal("tree_changed"))
		assert(connect("tree_changed", self, "_native_timer_tree_changed") == OK)
		_native_timer_cache_connected = true
	if _native_timer_cache_dirty:
		_native_timer_cache.clear()
		_native_install_timers(root, true)
		_native_timer_cache_dirty = false
	var active := []
	for timer in _native_timer_cache:
		if is_instance_valid(timer) and timer.is_inside_tree() and timer.native_running and not timer.paused:
			if (timer.process_mode == Timer.TIMER_PROCESS_PHYSICS) == physics_pass:
				active.append(timer)
	for timer in active:
		if is_instance_valid(timer) and timer.is_inside_tree():
			timer.native_step(dt)
