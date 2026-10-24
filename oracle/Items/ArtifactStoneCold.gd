extends "res://Items/Stone.gd"

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	for weapon in getAffectedItems():
		connectForCombat(weapon, "attacked", "onAffectedWeaponAttacked")

func onAffectedWeaponAttacked(damageRes):
	if damageRes.hasHit():
		inflictCold(getP2())
		miniActivate()

func preHit():
	inflictCold(getP1())
