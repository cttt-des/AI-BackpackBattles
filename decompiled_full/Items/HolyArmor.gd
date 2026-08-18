extends Item




func canAffect(item):
	return item.hasType(Type.Holy)

func onCombatStart():
	giveBlock()





	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		giveRegeneration(numAffected * getP1())
	
	activate()


func doCooldownEffect():
	cleansePoison(getP2())
	activate()



