extends "res://gd_core_items/Stone.gd"

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

func _readyInit():
	._readyInit()
	pass
