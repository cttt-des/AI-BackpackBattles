extends Item

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)
	
func doCooldownEffect():
	for buff in Game.getBuffs():
		giveStacks(character(), buff, 1)
	onAfterEffectFinished()

func getRelatedItems():
	var related = []
	for classI in Game.Classes_Full.values():
		if Game.isClassUnlocked(classI):
			related.append_array(ItemBook.getShopItemsForClass(classI))
	return related

func getRelatedItemColumns() -> int:
	return 6

func getRelatedItemHeight() -> int:
	return 100
