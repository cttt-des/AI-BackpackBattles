extends SceneTree

# =============================================================================
# RngStateProbe.gd — 实测「state 直注入」：Godot 原生 vs gd_core 内核 rng
# =============================================================================
# 用法: godot --headless --path gd_core_test --script RngStateProbe.gd
#
# ★ 为什么需要它：确定性重放不只是「从头播种」—— 真实对局的 PCG state 是一条
#   64 位连续流，重放层要把**运行中途实测的 state** 原样灌进内核从中途续跑。
#   Godot 3.6 的 `state` setter（random_pcg.h:79 `RandomPCG::set_state`）语义是
#   直接赋值 `pcg.state = p_state`（不前进、不重播），与 `seed` setter
#   （pcg32_srandom_r：清零 → 推进两次 → 加 initstate）完全不同。
#   gd_core 侧 CoreRng.set_state / CoreContext.set_state 必须与引擎**逐位一致**，
#   与 RngProbe.gd（只测 seed 路径）互补 —— state 注入路径此前没有任何闸门覆盖。
#
# 被测对象（同一组 state 各灌一次）：
#   · 原生   RandomNumberGenerator.new() + .state = s          —— 基准
#   · 内核 A CoreRng.new(1) + set_state(s)                     —— CoreRng.set_state
#   · 内核 B CoreContext.new(1) + set_state(s)                 —— CoreContext.set_state 转发
#
# 段设计（每段都从同一 state 重新注入，段间独立；对齐 RngProbe.gd 的段口径）：
#   段 0: randi()                      内核走 kr.rng.randi()（注入后由成员直出）
#   段 1: randf()                      内核走 kr.rng.randf()
#   段 2: randf_range(0.975, 1.05)     内核走 kr.randf_range —— Util.gd 冷却带
#   段 3: randf_range(0.2, -0.2)       内核走 kr.randf_range —— from > to 是原版写法
#   段 4: randf_range(0, 100.0)        内核走 kr.roll()      —— Util.gd:1007 flipPercent 路径
#   段 5: randi_range(0, 99)           内核走 kr.randi_range
#
# 双产物：
#   · rng_state_probe.bin（全部 little-endian）—— **原生流**，是
#     tools/verify_godot_rng.py「state 注入」段的基准（与 rng_probe.bin 同角色）：
#       uint32 magic = 0x524E4732 ('RNG2')
#       uint32 nStates, uint32 nPerSeg, uint32 nSegs
#       [nStates 个] int64 state
#       然后按「state 外层、段内层」顺序写 nStates * nSegs * nPerSeg 个 double
#   · rng_state_probe_result.txt —— 人读报告：readback + 逐段比对结论。
#
# ★ 不一致 quit(1)；全一致 quit(0)。
# ★ 用二进制存原生流而非文本：Godot 的 str(float) 有效位数不足，文本会掩盖低位
#   的逐位差异 —— 「逐位一致」正是本探针唯一要证明的东西。

const OUT_BIN := "res://rng_state_probe.bin"
const OUT_TXT := "res://rng_state_probe_result.txt"

const N_PER_SEG := 24
const N_SEGS := 6
const SEG_NAMES := [
	"randi()",
	"randf()",
	"randf_range(0.975, 1.05)",
	"randf_range(0.2, -0.2)",
	"randf_range(0, 100.0)",
	"randi_range(0, 99)",
]

const MAGIC := 0x524E4732

# state 组：典型值（0 / 小整数 / 32 位边界 / INT64_MAX）+ 运行中途实测值
# （中途值才是重放的真实用法：从一条跑到一半的流里读 state 灌回来续跑）。
var states: Array = []


func _collectStates() -> void:
	for s in [0, 1, 42, 12345, 2147483647, 4294967296, 777777777777777777,
			9223372036854775807]:
		states.push_back(s)

	# 中途实测 state #1：seed 42 起步消费 37 个 randi 后的现场
	var r = RandomNumberGenerator.new()
	r.seed = 42
	for _i in range(37):
		r.randi()
	states.push_back(r.state)

	# 中途实测 state #2：混跑 randf / randf_range（randf 每次消费两个 rand()，
	# 留下的 state 落点与纯 randi 流不同）后的现场
	r.seed = 123456789
	for _i in range(5):
		r.randf()
	for _i in range(11):
		r.randf_range(0.975, 1.05)
	states.push_back(r.state)


func _native(seg: int, r):
	match seg:
		0: return r.randi()
		1: return r.randf()
		2: return r.randf_range(0.975, 1.05)
		3: return r.randf_range(0.2, -0.2)
		4: return r.randf_range(0.0, 100.0)
		_: return r.randi_range(0, 99)


# 内核侧取值：kr 是 CoreRng。走 CoreRng 的公共转发面（roll / randf_range /
# randi_range）与成员直出（randi / randf），与段注释口径一一对应。
func _kernel(seg: int, kr):
	match seg:
		0: return kr.rng.randi()
		1: return kr.rng.randf()
		2: return kr.randf_range(0.975, 1.05)
		3: return kr.randf_range(0.2, -0.2)
		4: return kr.roll()
		_: return kr.randi_range(0, 99)


func _init() -> void:
	_collectStates()

	var fh = File.new()
	var err = fh.open(OUT_BIN, File.WRITE)
	if err != OK:
		print("RNGSTATEPROBE: FAIL 无法写入 ", OUT_BIN, " err=", err)
		quit(1)
		return

	var lines: Array = []
	lines.push_back("RNGSTATEPROBE: state 直注入探针（原生 vs CoreRng vs CoreContext）")
	lines.push_back("states=%d  nPerSeg=%d  nSegs=%d" % [
		states.size(), N_PER_SEG, N_SEGS])
	for s in states:
		lines.push_back("  state = %d" % s)

	# ── 原生流写盘（verify_godot_rng.py 的基准） ──
	fh.store_32(MAGIC)
	fh.store_32(states.size())
	fh.store_32(N_PER_SEG)
	fh.store_32(N_SEGS)
	for s in states:
		fh.store_64(s)

	var bad := 0
	var checked := 0

	for s in states:
		# ── readback：注入后 state 必须原样可读回（不前进、不重播的直接证据） ──
		var rn = RandomNumberGenerator.new()
		rn.state = s
		var ka = CoreRng.new(1)
		ka.set_state(s)
		var ctx = CoreContext.new(1)
		ctx.set_state(s)
		var rb_ok: bool = (rn.state == s) and (ka.rng.state == s) \
				and (ctx.rng.rng.state == s)
		if not rb_ok:
			bad += 1
			lines.push_back("[FAIL] readback  state=%d  native=%d coreRng=%d ctx=%d"
					% [s, rn.state, ka.rng.state, ctx.rng.rng.state])
		else:
			lines.push_back("[ok  ] readback  state=%d" % s)

		for seg in range(N_SEGS):
			# 每段都从同一 state 重新注入，段间独立（对齐 RngProbe.gd 的段隔离）
			rn.state = s
			ka.set_state(s)
			ctx.set_state(s)
			var seg_bad: Array = []
			for i in range(N_PER_SEG):
				var nv = _native(seg, rn)
				var va = _kernel(seg, ka)
				var vb = _kernel(seg, ctx.rng)
				checked += 2
				if va != nv or vb != nv:
					seg_bad.push_back([i, nv, va, vb])
				# 原生流写盘：整数段按 RngProbe.gd 的口径包成 double
				fh.store_double(float(nv))
			var name = SEG_NAMES[seg]
			if seg_bad.empty():
				lines.push_back("[ok  ] state=%d  段%d  %-26s 全等 %d/%d"
						% [s, seg, name, N_PER_SEG, N_PER_SEG])
			else:
				bad += seg_bad.size()
				lines.push_back("[FAIL] state=%d  段%d  %-26s 不一致 %d/%d"
						% [s, seg, name, seg_bad.size(), N_PER_SEG])
				for rec in seg_bad.slice(0, 3):
					lines.push_back("         idx=%d  native=%.17g  coreRng=%.17g  ctx=%.17g"
							% [rec[0], rec[1], rec[2], rec[3]])

	fh.close()

	var tf = File.new()
	err = tf.open(OUT_TXT, File.WRITE)
	if err != OK:
		print("RNGSTATEPROBE: FAIL 无法写入 ", OUT_TXT, " err=", err)
		quit(1)
		return
	lines.push_back("readback + 逐段比对共 %d 组（每值各对 CoreRng / CoreContext 两路），不一致 %d 组。"
			% [checked, bad])
	lines.push_back("RNGSTATEPROBE: " + ("FAIL" if bad > 0 else "ok") +
			"  原生基准 -> " + OUT_BIN)
	for line in lines:
		tf.store_line(line)
	tf.close()

	for line in lines:
		print(line)

	if bad > 0:
		quit(1)
	else:
		quit(0)
