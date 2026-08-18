extends Bag
















func canApplyEffect(toItem):
	return toItem.hasType(Type.Fire)

func onPreCombatStart():
	giveMaxHealth(getP_m("maxhealth") * getNumAffectedInside_type(Type.Fire))
	activate()

func onShopEntered():
	if Game.getGold() >= 1:
		var flame = ItemBook.generateItem(ItemBook.flameDescriptor)
		placeGeneratedItem(flame, occupiedCells)
		Game.spendGold(1)
		activate()
		Game.saveRunState()

func getBagMultiplicity(forItem) -> int:
	return forItem.getTypeMultiplicity(Type.Fire)
