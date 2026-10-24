extends SceneTree
# 探针：验证 --fixed-fps 60 无头下游戏时间与真实时间的解耦程度。
# 判据：600 个物理帧（=10s 游戏时间）的墙钟耗时。
#   实时耦合 → ≈10s；解耦 → 远小于 1s。
# 运行：Godot --headless --path oracle --script oracle_probe.gd [--fixed-fps 60]

var start_ticks := 0
var util_node = null
var done := false
var last_report := - 1


func _initialize() -> void :
	start_ticks = OS.get_ticks_usec()
	print("PROBE: begin cmdline=", OS.get_cmdline_args())
	# 命令行末位参数可指定 time_scale（0=不改）
	var args = OS.get_cmdline_args()
	if args.size() >= 3:
		var ts := float(args[args.size() - 1])
		if ts > 0:
			Engine.time_scale = ts
			print("PROBE: Engine.time_scale=", ts)


func _idle(_delta: float) -> bool :
	if done:
		return true
	if util_node == null:
		util_node = root.get_node_or_null("/root/Util")
	var f := int(Engine.get_physics_frames())
	var decile := f / 60
	if decile > last_report:
		last_report = decile
		print("PROBE: f=%d wall_ms=%.1f util_time=%.4f" %
				[f, float(OS.get_ticks_usec() - start_ticks) / 1000.0,
				util_node.time if util_node != null else - 1.0])
	if f >= 600:
		done = true
		print("PROBE: FINAL f=%d wall_ms=%.1f util_time=%.4f" %
				[f, float(OS.get_ticks_usec() - start_ticks) / 1000.0, util_node.time])
		quit(0)
		return true
	return false
