extends Item

func onCalcTradeChance():
	Game.SELLBOX.tradeChance += getShopChance() / 100.0
