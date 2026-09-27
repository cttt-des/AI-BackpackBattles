extends "res://gd_core_items/WoodenBuckler.gd"
var flatDam
var damFactor

func canAffect(item):
	return item.canBeEmpowered()


func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(flatDam)
		item.addBonusDamageFactor(damFactor)
	activate()
	

func _readyInit():
	._readyInit()
	flatDam = getP("dam")
	damFactor = getP("damfactor") / 100.0
