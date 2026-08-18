extends Item

onready var speedReduction = getP("speedreduction") / 100.0
onready var damBonusFactor = getP("dambonus") / 100.0

func canAffect(item):
	return item.canBeEmpowered()
	
func onPrepare():
	for weapon in getAffectedItems():
		connectForCombat(weapon, "attacked", "onWeaponAttacked")

func onCombatStart():
	for item in getAffectedItems():
		item.reduceSpeed(speedReduction)
		item.addBonusDamageFactor(damBonusFactor)
	activate()

func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.hasHit():
		giveBlock(getBlock(), true, damageRes.event)
		miniActivate()
