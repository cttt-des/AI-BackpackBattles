extends Item
var bonusDam
var bonusAcc

func canAffect(item):
	return item.canBeEmpowered()


func onCombatStart():
	giveHeat(getP("heat"))
	activate()


func doCooldownEffect():
	for item in getAffectedItems():
		item.addBonusDamage(bonusDam)
		item.addAccuracy(bonusAcc)
	activate()

func _readyInit():
	._readyInit()
	bonusDam = getP("dam")
	bonusAcc = getP("accuracy")
