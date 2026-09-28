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
			self.expectedWins = self._rng.rng.randf_range(0.2, - 0.2)
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
		rng = self._rng.randi_range(from_, to)
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


	# ────────────────────────── Util.gd:1007-1033 逐字对齐 ──────────────────────────

	def roll(self, maximum=100.0):
		return self.rng.randf_range(0, maximum)


	def flip(self, chance=0.5):
		return self.rng.randf() <= chance


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

	def randf_range(self, from_, to):
		return self.rng.randf_range(from_, to)


	def randi_range(self, from_, to):
		return self.rng.randi_range(from_, to)


	def pickRandomElement(self, array):
		return array[self.rng.randi_range(0, len(array) - 1)]


	# 洗牌（对齐 Godot 3 `Array.shuffle()` 的交换模式：i 与 [i, n) 内随机位置交换）
	# 原版由 Godot 全局 RNG（Math::rand）驱动，跨实现无法位对齐；此处改用注入随机源，
	# 仍然是零假设均匀洗牌。洗牌唯一的判定影响是「同 TriggerPriority 物品的同帧触发次序」。
	def shuffle(self, array):
		n = len(array)
		if n < 2:
			return array
		for i in _iter(_gd_range(n - 1)):
			j = _mod(int(abs(self.rng.randi())), n - i)
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
