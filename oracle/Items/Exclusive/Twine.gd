extends Item

onready var maxHealth: = int(getP("health"))

func canAffect(item):
	return item.canActivate()

func canAffect_secondary(item):
	return item.isNeutral()

func onPrepare():
	for triggerItem in getAffectedItems():
		connectForCombat(triggerItem, "activated", "onTriggerItemActivated")

func onTriggerItemActivated(event):
	var totalChance = getBaseChance()
	totalChance += getNumAffectedItems(Affected.Secondary) * getBaseChance2()
	if rollChance(totalChance):
		giveMaxHealth(maxHealth, event)
		activate()
