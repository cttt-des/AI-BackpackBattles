extends Item

onready var bonusSpeed: = getP("speed") / 100.0

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)

func canAffect(item):
	return item.isCrafted() and (item.hasCooldown() or item.gainsBuffs())

func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(bonusSpeed)
		item.changeAmplificiationChancePercent_allBuffs(getChance())

func getRelatedItems():
	return ItemBook.getShopItemsForClass(Game.Classes_Full.Adventurer)
