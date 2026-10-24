extends "res://Items/WoodenBuckler.gd"

onready var flatDam: = getP("dam")
onready var damFactor: = getP("damfactor") / 100.0

func canAffect(item):
	return item.canBeEmpowered()

func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(flatDam)
		item.addBonusDamageFactor(damFactor)
	activate()
	
