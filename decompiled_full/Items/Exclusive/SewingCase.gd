extends Bag

onready var bonusSpeed: = getP("speed") / 100.0

func canApplyEffect(toItem):
	return toItem.isCrafted() and (toItem.hasCooldown() or toItem.gainsBuffs())

func onPrepare():
	for item in getAffectedItemsInside():
		item.addSpeed(bonusSpeed)
		item.changeAmplificiationChancePercent_allBuffs(getChance())
