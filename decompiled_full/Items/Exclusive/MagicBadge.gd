extends Item

onready var mana: = getP("mana")

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	ItemBook.updateClass(self)

func canAffect(item):
	return item.gainsStack(Stack.Mana)

func onCombatStart():
	giveMana(mana)
	activate()

func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent(Game.EventType.Mana, getChance())
		
func getRelatedItems():
	return ItemBook.getShopItemsForClass(Game.Classes_Full.Mage)

func getRelatedItemColumns() -> int:
	return 4
