extends Item
var maxHealth

func canAffect(item):
	return item.canActivate()


func canAffect_secondary(item):
	return item.isNeutral()


func onPrepare():
	for triggerItem in getAffectedItems():
		connectForCombat(triggerItem, "activated", "onTriggerItemActivated")


func onTriggerItemActivated(event):
	var totalChance = getBaseChance()
	totalChance += getNumAffectedItems(CoreConst.Affected.Secondary) * getBaseChance2()
	if rollChance(totalChance):
		giveMaxHealth(maxHealth, event)
		activate()

func _readyInit():
	._readyInit()
	maxHealth = int(getP("health"))
