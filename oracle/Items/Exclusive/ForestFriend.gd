extends Item

func canAffect(item):
	return item.hasType(Type.Pet) or item.hasType(Type.Food)

func combatStart():
	.combatStart()
	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		addSpeed(numAffected * getP1() / 100.0)

