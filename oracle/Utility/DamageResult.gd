extends Reference
class_name DamageResult

var event
var damageSource
var damage: int
var healthDamage: int
var hit: bool
var critical: bool
var damageReduction: int = 0

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
	if damageSource.origin is Item:
		damage *= damageSource.origin.getCritSeverity()
	else:
		damage *= Item.BASE_CRIT_SEVERITY
	critical = true

func applyDamageReduction(amount, item):
	
	var leftOverDmg = max(0, damage - damageReduction)
	var actualReduction = min(amount, leftOverDmg)
	item.addMetric(Game.ItemMetrics.DamageBlocked, actualReduction)
	
	damageReduction += amount

func triggerOnHit():
	return hasHit() and canTriggerItems()

func triggerOnDamaged():
	return getDamage() > 0 and canTriggerItems()

func triggerOnMeleeAttacked():
	return (hasHit() and 
			canTriggerItems() and 
			damageSource.hasType(DamageSource.Type.Melee))

func triggerOnAttacked():
	return (hasHit() and 
			canTriggerItems() and 
			damageSource.isAttack())

func canTriggerItems():
	return damageSource.flags & DamageSource.Flags.CanTriggerItems

func canTriggerSpikes():
	return hasHit() and getDamage() > 0 and damageSource.canTriggerSpikes()

func canTriggerVampirism():
	return hasHit() and getDamage() > 0 and damageSource.canTriggerVampirism()


func willBeLethal(character) -> bool:
	return damage >= (character.getCurrentHealth() + character.getBlock())
