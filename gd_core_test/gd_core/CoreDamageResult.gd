# =============================================================================
# CoreDamageResult.gd — 无头战斗内核：伤害结算载体
# =============================================================================
# 对齐源码：Utility/DamageResult.gd（全文 71 行）
#
# 剥离内容：
#   · `damageSource.origin is Item` → `is CoreItem`
#   · `Item.BASE_CRIT_SEVERITY` → `CoreItem.BASE_CRIT_SEVERITY`（同为 2.0）
#   · `item.addMetric(...)` → `ctx.hooks.addMetric(...)`（统计埋点走空实现钩子）
#   · 判定条件、取整、max/min 包裹一律逐字保留。
# =============================================================================
extends Reference
class_name CoreDamageResult


var event
var damageSource
var damage: int
var healthDamage: int
var hit: bool
var critical: bool
var damageReduction: int = 0

var _ctx


func reset():
	hit = false
	damage = 0
	healthDamage = 0
	critical = false
	event = null


func getDamage():
	return damage


func hasHit():
	return hit


func wasCriticalHit():
	return hasHit() and critical


func makeCritical():
	if damageSource.origin is CoreItem:
		damage *= damageSource.origin.getCritSeverity()
	else:
		damage *= CoreItem.BASE_CRIT_SEVERITY
	critical = true


func applyDamageReduction(amount, item):
	var leftOverDmg = max(0, damage - damageReduction)
	var actualReduction = min(amount, leftOverDmg)
	item.addMetric(CoreConst.ItemMetrics.DamageBlocked, actualReduction)
	
	damageReduction += amount


func triggerOnHit():
	return hasHit() and canTriggerItems()


func triggerOnDamaged():
	return getDamage() > 0 and canTriggerItems()


func triggerOnMeleeAttacked():
	return (hasHit() and 
			canTriggerItems() and 
			damageSource.hasType(CoreDamageSource.Type.Melee))


func triggerOnAttacked():
	return (hasHit() and 
			canTriggerItems() and 
			damageSource.isAttack())


func canTriggerItems():
	return damageSource.flags & CoreDamageSource.Flags.CanTriggerItems


func canTriggerSpikes():
	return hasHit() and getDamage() > 0 and damageSource.canTriggerSpikes()


func canTriggerVampirism():
	return hasHit() and getDamage() > 0 and damageSource.canTriggerVampirism()


func willBeLethal(character) -> bool:
	return damage >= (character.getCurrentHealth() + character.getBlock())
