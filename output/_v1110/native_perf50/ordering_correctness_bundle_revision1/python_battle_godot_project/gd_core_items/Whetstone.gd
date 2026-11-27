extends Item
var dam

func canAffect(item):
	return item.canBeEmpowered()


func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(dam)
	activate()


func _readyInit():
	._readyInit()
	dam = getP("dam")
