extends Item

onready var speedPerHolyItem: = getP("speed") / 100.0

func canAffect(item):
	return item.gainsBuffs()

func canAffect_secondary(item):
	return item.hasType(Type.Holy)

func doCooldownEffect():
	giveRandomBuffs(1)
	activate()

func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
	
	addSpeed(getNumAffectedItems(Affected.Secondary) * speedPerHolyItem)
