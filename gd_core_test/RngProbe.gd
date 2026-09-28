extends SceneTree

# =============================================================================
# RngProbe.gd — 实测 Godot 3.6 `RandomNumberGenerator` 的原始输出序列
# =============================================================================
# 用法: godot --no-window --audio-driver Dummy --path gd_core_test --script RngProbe.gd
#
# ★ 为什么要现场实测：gd_core_py（Python 移植版）要与 gd_core（GDScript 版）做
#   逐事件对照。判定链里 `randf_range` / `randi_range` 会级联影响冷却、命中、暴击，
#   RNG 一旦错位，事件序列必然分叉，对照就失去意义。故 Python 侧的 PCG32 必须
#   与 Godot 逐位一致 —— 与其凭记忆写实现，不如把 Godot 的真实输出当基准来对齐。
#
# 输出协议（rng_probe.bin，全部 little-endian）：
#   uint32 magic = 0x524E4731 ('RNG1')
#   uint32 nSeeds, uint32 nPerSeg, uint32 nSegs
#   [nSeeds 个] int64 seed
#   然后按「seed 外层、段内层」顺序写 nSeeds * nSegs * nPerSeg 个 double：
#     段 0: randi()
#     段 1: randf()
#     段 2: randf_range(0.975, 1.05)
#     段 3: randf_range(0.2, -0.2)    ← from > to 是原版写法
#     段 4: randf_range(0, 100.0)
#     段 5: randi_range(0, 99)
#     段 6: randi_range(5, 5)         ← min == max 边界
#
# ★ 用二进制而非文本：Godot 的 str(float) 有效位数不足，文本会掩盖低位的
#   逐位差异 —— 而「逐位一致」正是本探针唯一要证明的东西。

const SEEDS := [0, 1, 42, 12345, 2147483647]
const N_PER_SEG := 24
const N_SEGS := 7

const OUT_PATH := "res://rng_probe.bin"


func _init() -> void:
	var fh = File.new()
	var err = fh.open(OUT_PATH, File.WRITE)
	if err != OK:
		print("RNGPROBE: FAIL 无法写入 ", OUT_PATH, " err=", err)
		quit(1)
		return

	fh.store_32(0x524E4731)
	fh.store_32(SEEDS.size())
	fh.store_32(N_PER_SEG)
	fh.store_32(N_SEGS)
	for s in SEEDS:
		fh.store_64(s)

	for s in SEEDS:
		# 每段都从同一个 seed 重新开始，便于独立对齐每一段
		var r = RandomNumberGenerator.new()

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(float(r.randi()))

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(r.randf())

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(r.randf_range(0.975, 1.05))

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(r.randf_range(0.2, -0.2))

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(r.randf_range(0.0, 100.0))

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(float(r.randi_range(0, 99)))

		r.seed = s
		for _i in range(N_PER_SEG):
			fh.store_double(float(r.randi_range(5, 5)))

	fh.close()
	print("RNGPROBE: ok  seeds=", SEEDS.size(), " nPerSeg=", N_PER_SEG,
		" nSegs=", N_SEGS, " -> ", OUT_PATH)
	quit(0)
