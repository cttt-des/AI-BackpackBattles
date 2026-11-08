extends RandomNumberGenerator
# =============================================================================
# BareRngLog — Util.rng 的日志壳（IS-A RandomNumberGenerator，行为全等）
# ORACLE_BARELOG=1 时逐抽打 [BARE] 行（kind from to => value st=）。
# 与 rng_log 的 rng_trace_* 包装行互补：这里连【裸调】（动画四连抽、flicker
# speed、Zap 等直调 Util.rng 的调用点）也逐笔可见。默认零输出零开销。
# =============================================================================
var _barelog := false


func _init():
	# RandomNumberGenerator extends Reference——无 _ready 生命周期，用 _init。
	_barelog = OS.get_environment("ORACLE_BARELOG") != ""


func randf_range(from, to):
	var r = .randf_range(from, to)
	if _barelog:
		print("[BARE] randf_range ", from, " ", to, " => ", r, " st=", get_state())
	return r


func randf():
	var r = .randf()
	if _barelog:
		print("[BARE] randf => ", r, " st=", get_state())
	return r


func randi_range(from, to):
	var r = .randi_range(from, to)
	if _barelog:
		print("[BARE] randi_range ", from, " ", to, " => ", r, " st=", get_state())
	return r


func randi():
	var r = .randi()
	if _barelog:
		print("[BARE] randi => ", r, " st=", get_state())
	return r
