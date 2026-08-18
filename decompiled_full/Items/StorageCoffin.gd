extends Bag

func onPrepare():
	for item in getItemsInside():
		connectForCombat(item, "activated", "onItemActivated")

func onItemActivated(event):
	if rollChance():
		inflictPoison(1)
		activate()

func canApplyEffect(toItem):
	return toItem.canActivate() and not toItem.isBag()
