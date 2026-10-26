extends Item
var bonusSpeed

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func canAffect(item):
	return item.isCrafted() and (item.hasCooldown() or item.gainsBuffs())


func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(bonusSpeed)
		item.changeAmplificiationChancePercent_allBuffs(getChance())


func getRelatedItems():
	pass

func _readyInit():
	._readyInit()
	bonusSpeed = getP("speed") / 100.0
