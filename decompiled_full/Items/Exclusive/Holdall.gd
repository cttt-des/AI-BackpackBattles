extends Bag

func canApplyEffect(toItem):
	return toItem.isNeutral()

func onCombatStart():
	var block = getBlock() * getNumAffectedInside()
	if block > 0:
		giveBlock(block)
		activate()
