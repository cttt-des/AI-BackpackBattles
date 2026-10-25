extends Item
var speedReduction
var damBonusFactor

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


func onWeaponAttacked(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveBlock(getBlock(), true, damageRes.event)
		miniActivate()

func _readyInit():
	._readyInit()
	speedReduction = getP("speedreduction") / 100.0
	damBonusFactor = getP("dambonus") / 100.0
