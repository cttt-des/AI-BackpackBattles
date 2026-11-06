# =============================================================================
# RngStepProbe.gd — np46 逐抽对位取证：同 state 下两侧 randf_range/pickRandom
# 的步数与值实测（oracle 引擎 Util.rng 路径 vs gd_core CoreRng 路径）
# 取证锚点：S0=6993495402720534647（oracle 行741 = gd 行893 之后的公共链态）
#   oracle 行742: randf_range(0.95,1.05) => 1.042976 st=-5162755745590424535
#   gd    行894: randf_range(0.95,1.05) => 1.020635 st= 6121502325669617635
# =============================================================================
extends SceneTree

const S0 := 6993495402720534647

func _initialize() -> void :
	print("[probe] S0=", S0)
	# ① 引擎原生 RandomNumberGenerator（oracle Util.rng 同类）
	var r := RandomNumberGenerator.new()
	r.state = S0
	print("[engine] state set -> get_state=", r.get_state())
	var v1 := r.randf_range(0.95, 1.05)
	print("[engine] randf_range(0.95,1.05) => ", v1, " st=", r.get_state())
	var v2 := r.randf_range(0.95, 1.05)
	print("[engine] again => ", v2, " st=", r.get_state())
	r.state = S0
	var a := []
	a.push_back(1)
	a.push_back(2)
	a.push_back(3)
	var idx := r.randi_range(0, 2)
	print("[engine] randi_range(0,2) => ", idx, " st=", r.get_state())
	# ② 反向：从 oracle 742 的 st 出发，看下一步是否 = gd 894 的 st 前身等
	r.state = -5162755745590424535
	var v3 := r.randf_range(0.95, 1.05)
	print("[engine] from A: randf_range => ", v3, " st=", r.get_state())
	quit(0)
