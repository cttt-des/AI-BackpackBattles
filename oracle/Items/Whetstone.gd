extends Item

onready var dam: = getP("dam")

func canAffect(item):
	return item.canBeEmpowered()

func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(dam)
	activate()


