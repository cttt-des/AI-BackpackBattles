extends Bag
var bonusSpeed

func canApplyEffect(toItem):
	return toItem.isCrafted() and (toItem.hasCooldown() or toItem.gainsBuffs())


func onPrepare():
	for item in getAffectedItemsInside():
		item.addSpeed(bonusSpeed)
		item.changeAmplificiationChancePercent_allBuffs(getChance())

func _readyInit():
	._readyInit()
	bonusSpeed = getP("speed") / 100.0
