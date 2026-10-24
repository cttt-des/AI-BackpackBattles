extends Bag

func canApplyEffect(toItem):
	return toItem.inflictsDebuffs()

func onPrepare():
	for item in getAffectedItemsInside():
		item.changeAmplificiationChancePercent_allDebuffs(getChance())
