extends Item

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)
	
func onCombatStart():
	giveHeat(getP1())
	consume()

func onShopEntered():
	if Game.getGold() >= 1 and rollShopChance():
		var flame = ItemBook.generateItem("Flame")
		placeGeneratedItem(flame, occupiedCells)
		Game.spendGold(1)
		activate()
		Game.saveRunState()

func getRelatedItems():
	return ItemBook.getShopItemsForClass(Game.Classes_Full.Pyromancer)
