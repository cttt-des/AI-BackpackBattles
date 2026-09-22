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
extends Reference
class_name CoreRng


# ────────────────────────── 全局随机源（对齐 Util.gd:6） ──────────────────────────
var rng: RandomNumberGenerator


func _init(_seed: int = 0) -> void :
	rng = RandomNumberGenerator.new()
	if _seed == 0:
		rng.randomize()
	else:
		rng.seed = _seed


# ────────────────────────── Util.gd:1007-1033 逐字对齐 ──────────────────────────

func roll(maximum: float = 100.0) -> float:
	return rng.randf_range(0, maximum)


func flip(chance: float = 0.5) -> bool:
	return rng.randf() <= chance


func flipPercent(chance: float) -> bool:
	return roll() <= chance


func flipRound(chance: float) -> int:
	return int(floor(chance) + int(flip(fmod(chance, 1.0))))


func flipWeighted(weights: Array) -> int:
	var sum = 0.0
	for weight in weights:
		sum += weight
	
	var val = rng.randf_range(0, sum)
	var subsum = 0.0
	for i in weights.size():
		subsum += weights[i]
		if subsum >= val:
			return i
	
	return weights.size()


# ────────────────────────── 直调转发（对应原版 Util.rng.xxx 调用点） ──────────────────────────

func randf_range(from: float, to: float) -> float:
	return rng.randf_range(from, to)


func randi_range(from: int, to: int) -> int:
	return rng.randi_range(from, to)


func pickRandomElement(array: Array):
	return array[rng.randi_range(0, array.size() - 1)]


# 洗牌（对齐 Godot 3 `Array.shuffle()` 的交换模式：i 与 [i, n) 内随机位置交换）
# 原版由 Godot 全局 RNG（Math::rand）驱动，跨实现无法位对齐；此处改用注入随机源，
# 仍然是零假设均匀洗牌。洗牌唯一的判定影响是「同 TriggerPriority 物品的同帧触发次序」。
func shuffle(array: Array) -> Array:
	var n: int = array.size()
	if n < 2:
		return array
	for i in range(n - 1):
		var j: int = int(abs(rng.randi())) % (n - i)
		var tmp = array[i]
		array[i] = array[i + j]
		array[i + j] = tmp
	return array


# =============================================================================
# BalancedRng — 对齐 Utility/BalancedRandom.gd
# 用于 accuracyRng / critRng / critResistanceRng / stunResistanceRng 与物品 chanceRng
# =============================================================================
class BalancedRng extends Reference:
	
	# 原版：`var expectedWins = Util.rng.randf_range(0.2, - 0.2)`
	# from > to 是原版写法，randf_range 仍返回 [to, from]；保持调用形态不变。
	var expectedWins: float
	var wins = 0
	var balancedness = 3.0
	var lastResult = false
	
	var extraLuck = 0.0
	var lastTarget = 0.0
	var accChance = 0.0
	const luckBalance = 0.2
	
	var _rng
	
	func _init(_rng_ref = null, startBias: float = 0.0) -> void :
		_rng = _rng_ref
		if _rng != null:
			expectedWins = _rng.rng.randf_range(0.2, - 0.2)
		else:
			expectedWins = 0.0
		expectedWins += startBias
	
	func setBias(bias: float) -> void :
		expectedWins += bias
	
	func rollPercent(target: float) -> bool:
		return roll(target / 100.0)
	
	func roll(target: float) -> bool:
		if target <= 0: return false
		elif target >= 1: return true
		
		var chance = target
		
		var dif = expectedWins - wins
		if dif > 0.3:
			chance *= balancedness * min(1.0, dif)
		elif dif < - 0.3:
			chance /= balancedness * min(1.0, - dif)
		
		expectedWins += target
		
		if lastResult and target < 0.4:
			chance *= 0.5
		elif not lastResult and target > 0.6:
			chance *= 2.0
		
		var result = _rng.flip(chance)
		
		lastResult = result
		
		if result:
			wins += 1
			return true
		else:
			return false
	
	# 原版保留、战斗路径未使用的两个变体，一并原样搬运以免遗漏。
	func roll2(target: float) -> bool:
		if target <= 0:
			return false
		elif target >= 1:
			return true
		
		var chance = target + extraLuck * 0.3
		
		if _rng.flip(chance):
			extraLuck -= 1.0 - target
			return true
		else:
			extraLuck += target
			return false
	
	func roll1(target: float) -> bool:
		if target <= 0:
			return false
		elif target >= 1:
			return true
		
		accChance += target - lastTarget
		extraLuck += clamp(accChance, 0, 1) - target
		
		lastTarget = target
		
		if _rng.flip(accChance):
			accChance = target - extraLuck
			return true
		else:
			accChance += luckBalance
			return false
	
	# 对齐 BalancedRandom.gd:104-111
	# 注意：原版 reset() 把 expectedWins 归零（而非重新随机）—— 保真保留。
	func reset() -> void :
		expectedWins = 0.0
		wins = 0
		lastResult = false
		
		extraLuck = 0.0
		accChance = 0.0
		lastTarget = 0.0


# =============================================================================
# BalancedRange — 对齐 Utility/BalancedRange.gd（物品 damageRangeRng）
# =============================================================================
class BalancedRange extends Reference:
	
	var acc = 0.0
	var _rng
	
	func _init(_rng_ref = null) -> void :
		_rng = _rng_ref
	
	func reset() -> void :
		acc = 0.0
	
	func randIntRange(from: int, to: int) -> int:
		var rng = _rng.randi_range(from, to)
		var expected: float = 0.5 * (from + to)
		
		var dif: float = rng - expected
		
		if acc >= 1:
			var malus = min(rng - from, int(acc))
			acc -= malus
			rng -= malus
			
		elif acc <= - 1:
			var bonus = min(to - rng, int(abs(acc)))
			acc += bonus
			rng += bonus
		
		acc += dif
		
		return rng
