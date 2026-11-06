extends SceneTree

const S0 := 6993495402720534647
const A := -5162755745590424535
const B := -2788569748657586988
const X := 6121502325669617635
const Y := -600874497684407674

func _initialize() -> void :
	var r := RandomNumberGenerator.new()
	# ① 从 S0 连续 randf_range(0.95,1.05)×8，找 1.042976 与 A
	r.state = S0
	print("[p1] S0 chain of randf_range(0.95,1.05):")
	for i in range(8):
		var v := r.randf_range(0.95, 1.05)
		print("  step", i + 1, " v=", v, " st=", r.get_state())
	# ② 从 A 起 randi_range(0,2)（模拟 pickRandomElement 单步）
	r.state = A
	var i1 := r.randi_range(0, 2)
	print("[p2] A randi_range(0,2) => ", i1, " st=", r.get_state())
	r.state = A
	var i2 := r.randi_range(0, 1)
	print("[p2] A randi_range(0,1) => ", i2, " st=", r.get_state())
	# ③ 从 B 起 randi_range(0,1)
	r.state = B
	var i3 := r.randi_range(0, 1)
	print("[p3] B randi_range(0,1) => ", i3, " st=", r.get_state())
	# ④ 从 B 起 randi_range(0,0)
	r.state = B
	var i4 := r.randi_range(0, 0)
	print("[p4] B randi_range(0,0) => ", i4, " st=", r.get_state())
	# ⑤ 从 X 起 randi_range(0,0)
	r.state = X
	var i5 := r.randi_range(0, 0)
	print("[p5] X randi_range(0,0) => ", i5, " st=", r.get_state())
	quit(0)
