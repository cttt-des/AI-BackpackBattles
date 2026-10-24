extends Bag

func canApplyEffect(toItem):
	return toItem.gainsBuffs()

func onPrepare():
	for item in getAffectedItemsInside():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
