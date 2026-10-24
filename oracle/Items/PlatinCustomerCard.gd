extends Item

func canAffect(item):
	return item.getRarity() >= Rarity.Legendary

func onPreCombatStart():
	giveReflectStacks(getNumAffectedItems() * getP2())
	activate()

func onCombatStart():
	
	pass

func onCalcTradeChance():
	Game.SELLBOX.tradeChance += getShopChance() / 100.0
