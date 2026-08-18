extends Item

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)

func canAffect(item):
	return item.canDamage()

func onPrepare():
	if not getAffectedItems().empty():
		connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")
	
func onLuckyChanged(amount, _event):
	for item in getAffectedItems():
		item.changeCritChancePercent(amount * getChance())

func doCooldownEffect():
	giveLucky(1)
	activate()

func getRelatedItems():
	return ItemBook.getShopItemsForClass(Game.Classes_Full.Ranger)

func getRelatedItemColumns() -> int:
	return 3
