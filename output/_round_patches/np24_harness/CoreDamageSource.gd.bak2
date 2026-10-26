# =============================================================================
# CoreDamageSource.gd — 无头战斗内核：伤害源
# =============================================================================
# 对齐源码：Utility/DamageSource.gd（全文 171 行）
#
# 剥离内容：
#   · `Util.rng.randi_range(...)` → 注入的 CoreRng（同一套语义，仅换随机源持有者）
#   · `origin is Item` → `origin is CoreItem`（类型改名，判定不变）
#   · `item.hasType(Item.Type.X)` → `item.hasType(CoreConst.Type.X)`
#     （原版 Item.gd:34-67 的 Type 枚举已整体收拢到 CoreConst.Type，取值逐项相同，
#       hasType 只按整数值判成员，判定不变）
#   · 无其他改动；枚举值、flags 常量、函数体逐字保留。
# =============================================================================
extends Reference
class_name CoreDamageSource


enum Type{
	Melee, 
	Ranged, 
	Effect, 
	SelfDamage, 
	Unhealing = 98, 
	Spikes = 104, 
	Poison = 108, 
	Fatigue = 99
}

const damTypeNames = {
	Type.Melee: "melee", 
	Type.Ranged: "ranged", 
	Type.Effect: "effect"
}

enum Flags{
	None = 0, 
	CanBeBlocked = 1, 
	CanTriggerSpikes = 2, 
	CanTriggerVampirism = 4, 
	CanTriggerItems = 8, 
	CanMiss = 16, 
	CanCrit = 32, 
	All = 63
}


const chipDamageFlags = Flags.CanBeBlocked
const meleeFlags = Flags.All
const rangedFlags = Flags.All
const effectFlags = Flags.CanBeBlocked + Flags.CanTriggerItems + Flags.CanCrit
const unhealingFlags = Flags.CanBeBlocked + Flags.CanTriggerItems
const selfDamageFlags = Flags.CanBeBlocked + Flags.CanTriggerItems

var minDamage: int
var maxDamage: int
var types: Array
var accuracy: float = 100
var critChancePercent: float = 0
var origin
var flags = Flags.All


func fromDamageSource(otherDamSource):
	minDamage = otherDamSource.minDamage
	maxDamage = otherDamSource.maxDamage
	types = otherDamSource.types.duplicate()
	accuracy = otherDamSource.accuracy
	critChancePercent = otherDamSource.critChancePercent
	flags = otherDamSource.flags
	origin = otherDamSource.origin
	return self


func setItem(item, _type = null):
	if _type != null:
		types = [_type]
	else:
		if item.hasType(CoreConst.Type.Ranged):
			types.push_back(Type.Ranged)
		
		if item.hasType(CoreConst.Type.Melee):
			types.push_back(Type.Melee)
		
		if item.hasType(CoreConst.Type.Effect):
			types.push_back(Type.Effect)
		
		if types.empty():
			types.push_back(Type.Effect)
	
	if hasType(Type.Melee):
		flags = meleeFlags
	elif hasType(Type.Ranged):
		flags = rangedFlags
	elif hasType(Type.SelfDamage):
		flags = selfDamageFlags
	else:
		flags = effectFlags
	
	return init(item, types, item.getMinDamage(), item.getMaxDamage(), item.getAccuracy())


func init(_origin = null, _type = Type.Effect, _minDamage = 0, 
	_maxDamage = null, _accuracy = 100):
	
	origin = _origin
	if _type is Array:
		types = _type
	else:
		types = [_type]
	setDamage(_minDamage, _maxDamage)
	accuracy = _accuracy
	return self


func hasType(_type: int):
	return _type in types


func setDamage(_minDamage, _maxDamage = null):
	minDamage = _minDamage
	if _maxDamage:
		maxDamage = _maxDamage
	else:
		maxDamage = minDamage


func addDamage(_damage):
	minDamage += _damage
	maxDamage += _damage


func getCritChancePercent():
	return clamp(critChancePercent, 0.0, 100.0)


func updateItem(item):
	accuracy = item.getAccuracy()


func updateEffect(item, damage):
	origin = item
	setDamage(item.getModifiedEffectDamage(damage))
	critChancePercent = item.getCritChancePercent()


func addCritChancePercent(_critChance):
	critChancePercent += _critChance


func setFlag(flag):
	flags |= flag


func unsetFlag(flag):
	flags = flags & ~ flag


func canMiss() -> bool:
	return flags & Flags.CanMiss


func canTriggerSpikes() -> bool:
	return flags & Flags.CanTriggerSpikes


func canTriggerVampirism() -> bool:
	return flags & Flags.CanTriggerVampirism


func canBeBlocked() -> bool:
	return flags & Flags.CanBeBlocked


func canCrit() -> bool:
	return flags & Flags.CanCrit


func isAttack() -> bool:
	return hasType(Type.Melee) or hasType(Type.Ranged)


func isEffectDamage() -> bool:
	return hasType(Type.Effect) or hasType(Type.Unhealing)


func isAttackOrEffect() -> bool:
	return isAttack() or isEffectDamage()


func canApplyLifesteal() -> bool:
	return isAttack() or hasType(Type.Effect)


func makeSpectral():
	unsetFlag(Flags.CanBeBlocked)


# ── 唯一改动点：随机源注入（原为 Util.rng） ──
var _rng


func randDamage():
	# 原版 `origin is Item`；此处改用类型标记 isCoreItem()（鸭子类型），
	# 因为 CoreDamageSource ↔ CoreItem 的 class_name 互相引用会构成
	# GDScript 3 禁止的循环依赖。判定语义完全一致（CoreItem 恒返回 true）。
	if origin != null and origin.has_method("isCoreItem"):
		critChancePercent = origin.getCritChancePercent()
		if isAttack():
			setDamage(origin.getMinDamage(self), origin.getMaxDamage(self))
		return origin.damageRangeRng.randIntRange(minDamage, maxDamage)
	else:
		return _rng.randi_range(minDamage, maxDamage)
