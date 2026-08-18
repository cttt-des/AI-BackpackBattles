extends Item

var affectedItemsDict: Dictionary

var healthAcc: float

func onShopEntered():
	giveGold(getP1())

func canAffect(item):
	return item.usesBuffs()
	
func onPrepare():
	healthAcc = 0
	affectedItemsDict.clear()
	for item in getAffectedItems():
		affectedItemsDict[item] = true
	connectToCharacterBuffs("onBuffChanged")

func onBuffChanged(amount, event):
	if event.getOrigin() in affectedItemsDict:
		if amount < 0 and event.getParam("used", false):
			healthAcc += abs(amount) * getP_m("maxhealth")
			var health = round(healthAcc)
			healthAcc -= health
			giveMaxHealth(health, event)
			miniActivate()

func getShopPriority() -> int:
	return Priority.Lowest
