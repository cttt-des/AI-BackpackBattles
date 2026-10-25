extends Item

func canAffect(item):
	return item.hasType(CoreConst.Type.Pet) or item.hasType(CoreConst.Type.Food)


func combatStart():
	.combatStart()
	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		addSpeed(numAffected * getP1() / 100.0)

func _readyInit():
	._readyInit()
	pass
