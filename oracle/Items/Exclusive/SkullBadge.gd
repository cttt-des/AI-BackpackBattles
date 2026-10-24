extends Item

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)
	
func doCooldownEffect():
	inflictRandomDebuffs(1)
	activate()

func getRelatedItems():
	return ItemBook.getShopItemsForClass(Game.Classes_Full.Reaper)

func getRelatedItemColumns() -> int:
	return 3
