extends Item

onready var bonusDam = getP("dam")
onready var bonusAcc = getP("accuracy")

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
