# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class BalancedRng(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.expectedWins = 0.0
		self.wins = 0
		self.balancedness = 3.0
		self.lastResult = False
		self.extraLuck = 0.0
		self.lastTarget = 0.0
		self.accChance = 0.0
		self._rng = None


	# 原版：`var expectedWins = Util.rng.randf_range(0.2, - 0.2)`
	# from > to 是原版写法，randf_range 仍返回 [to, from]；保持调用形态不变。

	luckBalance = 0.2


	def _init(self, _rng_ref=None, startBias=0.0):
		self._rng = _rng_ref
		if self._rng != None:
			# 走 CoreRng.randf_range 追踪包装（神谕 BalancedRandom.gd:4 =
			# Util.rng_trace_range(0.2, -0.2)，同值同链位，仅补 trace 可见性）
			self.expectedWins = self._rng.randf_range(0.2, - 0.2)
		else:
			self.expectedWins = 0.0
		self.expectedWins += startBias

	def setBias(self, bias):
		self.expectedWins += bias

	def rollPercent(self, target):
		return self.roll(_div(target, 100.0))

	def roll(self, target):
		if target <= 0:
			return False
		elif target >= 1:
			return True

		chance = target

		dif = self.expectedWins - self.wins
		if dif > 0.3:
			chance *= self.balancedness * min(1.0, dif)
		elif dif < - 0.3:
			chance /= self.balancedness * min(1.0, - dif)

		self.expectedWins += target

		if self.lastResult and target < 0.4:
			chance *= 0.5
		elif not self.lastResult and target > 0.6:
			chance *= 2.0

		result = self._rng.flip(chance)

		self.lastResult = result

		if result:
			self.wins += 1
			return True
		else:
			return False

	# 原版保留、战斗路径未使用的两个变体，一并原样搬运以免遗漏。
	def roll2(self, target):
		if target <= 0:
			return False
		elif target >= 1:
			return True

		chance = target + self.extraLuck * 0.3

		if self._rng.flip(chance):
			self.extraLuck -= 1.0 - target
			return True
		else:
			self.extraLuck += target
			return False

	def roll1(self, target):
		if target <= 0:
			return False
		elif target >= 1:
			return True

		self.accChance += target - self.lastTarget
		self.extraLuck += clamp(self.accChance, 0, 1) - target

		self.lastTarget = target

		if self._rng.flip(self.accChance):
			self.accChance = target - self.extraLuck
			return True
		else:
			self.accChance += self.luckBalance
			return False

	# 对齐 BalancedRandom.gd:104-111
	# 注意：原版 reset() 把 expectedWins 归零（而非重新随机）—— 保真保留。
	def reset(self):
		self.expectedWins = 0.0
		self.wins = 0
		self.lastResult = False

		self.extraLuck = 0.0
		self.accChance = 0.0
		self.lastTarget = 0.0


# =============================================================================
# BalancedRange — 对齐 Utility/BalancedRange.gd（物品 damageRangeRng）
# =============================================================================

class BalancedRange(GodotObject):
	def _init_fields(self):
		super()._init_fields()
		self.acc = 0.0
		self._rng = None



	def _init(self, _rng_ref=None):
		self._rng = _rng_ref

	def reset(self):
		self.acc = 0.0

	def randIntRange(self, from_, to):
		# ★ kernel_r5：对齐 oracle Utility/BalancedRange.gd:14 `Util.rng.randi_range`
		#   ——**裸调不入账本**（oracle 伤害掷点在 rng_log 零痕迹）。此前走
		#   CoreRng.randi_range 追踪版，使 gd trace 多出伤害行、与语料账本
		#   不可直比（run862_r18 对位 walk 在 c99/c100 间虚位差 δ 实证）。
		#   消耗面不变（同一 PCG 同参数），仅账本可见性对齐。
		rng = self._rng.rng.randi_range(from_, to)
		expected = 0.5 * (from_ + to)

		dif = rng - expected

		if self.acc >= 1:
			malus = min(rng - from_, int(self.acc))
			self.acc -= malus
			rng -= malus

		elif self.acc <= - 1:
			bonus = min(to - rng, int(abs(self.acc)))
			self.acc += bonus
			rng += bonus

		self.acc += dif

		return rng


class CoreRng(GodotObject):

	resource_path = "res://gd_core/CoreRng.gd"

	def _init_fields(self):
		super()._init_fields()
		self.rng = None
		self.oracle_trace = False
		self.oracle_trace_log = []
		self._stacktrace = False      # ORACLE_ALIGN_STACKTRACE=1：逐抽附调用栈签名（诊断用）

	# =============================================================================
	# CoreRng.gd — 无头战斗内核：随机数层
	# =============================================================================
	# 对齐源码（decompiled_full/，v1.1.7）：
	#   Utility/Util.gd:1007-1033      roll / flip / flipPercent / flipRound / flipWeighted
	#   Utility/BalancedRandom.gd      BalancedRng（防连击/防连败/期望胜率平衡）
	#   Utility/BalancedRange.gd       BalancedRange（伤害区间累积修正）
	#
	# 剥离内容（与判定无关）：
	#   · 原版随机源 `Util.rng` 为全局 RandomNumberGenerator（每局 randomize）；
	#     此处改为由 CoreContext 注入的独立 RandomNumberGenerator，便于固定种子复现。
	#   · 其余数值比较、分支顺序、`<=`/`>=` 边界、乘除次序全部逐字保留。
	# =============================================================================


	# ────────────────────────── 全局随机源（对齐 Util.gd:6） ──────────────────────────


	def _init(self, _seed=0):
		self.rng = RandomNumberGenerator()
		if _seed == 0:
			self.rng.randomize()
		else:
			self.rng.seed = _seed
		self._stacktrace = _os_environ_get("ORACLE_ALIGN_STACKTRACE") != ""


	# ── state 直注入（确定性重放用） ──
	# 语义对齐 Godot 3.6 RandomNumberGenerator.state setter（源码存档
	# output/godot_src/random_pcg.h:79 `RandomPCG::set_state`）：
	#   `pcg.state = p_state` —— 直接赋值 PCG 状态，不前进、不重播，
	#   下一次 rand() 即从该状态出发。
	# ★ 与 `seed` setter 不同：seed 走 pcg32_srandom_r（先清零、推进两次、
	#   再加 initstate），且会改写 current_seed；state 只改 pcg 内部状态字。
	#   两者不可混为一谈 —— 重放「中途续跑」必须用 state 而非 seed。
	def set_state(self, state):
		self.rng.state = state


	# ────────────────────────── Util.gd:1007-1033 逐字对齐 ──────────────────────────

	def roll(self, maximum=100.0):
		# 走追踪版 randf_range（等价原版 Util.roll = rng.randf_range(0, maximum)）
		return self.randf_range(0, maximum)


	def flip(self, chance=0.5):
		r = self.rng.randf()
		if self.oracle_trace:
			self._trace("randf", 0, 0, r)
		return r <= chance


	def flipPercent(self, chance):
		return self.roll() <= chance


	def flipRound(self, chance):
		return int(floor(chance) + int(self.flip(fmod(chance, 1.0))))


	def flipWeighted(self, weights):
		sum = 0.0
		for weight in _iter(weights):
			sum += weight

		val = self.rng.randf_range(0, sum)
		subsum = 0.0
		for i in _iter(len(weights)):
			subsum += weights[i]
			if subsum >= val:
				return i

		return len(weights)


	# ────────────────────────── 直调转发（对应原版 Util.rng.xxx 调用点） ──────────────────────────

	# ── 逐抽诊断追踪（受控神谕对齐用；默认关，由宿主经 ctx.rng.oracle_trace 开启）──
	# 格式与神谕 rng_log.txt 逐列同构：[序号, "randf_range"/"randi_range"/"randf"/"randi",
	# from, to, 返回值]（oracle/Utility/Util.gd:757-781 的 trace 面同款）。


	def _trace(self, kind, from_, to, r):
		row = [len(self.oracle_trace_log), kind, from_, to, r]
		if self._stacktrace:
			frames = []
			st = get_stack()
			if st != None:
				# [0]=_trace [1]=包装器；自 [2] 起是真实调用方，取 3 层足定位
				for i in _iter(_gd_range(2, min(5, len(st)))):
					frames.append("%s:%d:%s" % [String(st[i]["source"]).get_file(),
							int(st[i]["line"]), String(st[i]["function"])])
			row.append(_join(PoolStringArray(frames), "<-"))
		self.oracle_trace_log.append(row)


	# ★ 事件标记（不消耗链）：CoreCombatLog.logEvent 在逐抽追踪开启时把事件类型
	#   写进 trace，与神谕 rng_log 的 EVENT 行同构，供逐抽↔逐事件精确对位。
	def trace_event(self, type):
		self.oracle_trace_log.append([len(self.oracle_trace_log), "EVENT", str(type), "", ""])


	def randf_range(self, from_, to, tag="randf_range"):
		# ★ kernel_r9 临时诊断注入（ORACLE_TEST_INJECT_AT/N，默认关闭零影响）
		if self.oracle_trace and _os_environ_get("ORACLE_TEST_INJECT_AT") != "":
			if len(self.oracle_trace_log) == int(_os_environ_get("ORACLE_TEST_INJECT_AT")):
				n_inj = int(_os_environ_get("ORACLE_TEST_INJECT_N"))
				for _i in _iter(n_inj):
					self.rng.randf_range(0.95, 1.05)
		r = self.rng.randf_range(from_, to)
		if self.oracle_trace:
			self._trace(tag, from_, to, r)
		return r


	def randi_range(self, from_, to, tag="randi_range"):
		r = self.rng.randi_range(from_, to)
		if self.oracle_trace:
			self._trace(tag, from_, to, r)
		return r


	# 对齐 Util.pickRandomElement（Util.gd:452-453 = array[rng.randi_range(0, size-1)]；
	# 神谕插桩 oracle/Utility/Util.gd:457 走 rng_trace_irange(…, "pickRandomElement")）。
	# ★ 此前走裸 rng.randi_range——链消耗正确但不进 oracle_trace，逐抽对位时呈现
	#   为「神谕多一抽」的假分歧（run1122_r11 逐抽对位 326 行后首见）。
	def pickRandomElement(self, array):
		return array[self.randi_range(0, len(array) - 1, "pickRandomElement")]


	# 洗牌（对齐 Godot 3 `Array.shuffle()` 的交换模式：i 与 [i, n) 内随机位置交换）
	# 原版由 Godot 全局 RNG（Math::rand）驱动，跨实现无法位对齐；此处改用注入随机源，
	# 仍然是零假设均匀洗牌。洗牌唯一的判定影响是「同 TriggerPriority 物品的同帧触发次序」。
	def shuffle(self, array):
		n = len(array)
		if n < 2:
			return array
		for i in _iter(_gd_range(n - 1)):
			r = self.rng.randi()
			if self.oracle_trace:
				self._trace("randi", 0, 0, r)
			j = _mod(int(abs(r)), n - i)
			tmp = array[i]
			array[i] = array[i + j]
			array[i + j] = tmp
		return array


	# =============================================================================
	# BalancedRng — 对齐 Utility/BalancedRandom.gd
	# 用于 accuracyRng / critRng / critResistanceRng / stunResistanceRng 与物品 chanceRng
	# =============================================================================
CoreRng.BalancedRng = BalancedRng
CoreRng.BalancedRange = BalancedRange


_R.reg("res://gd_core/CoreRng.gd", CoreRng)
_R.reg("CoreRng", CoreRng)
_R.reg("CoreRng", CoreRng)
