extends "res://Items/LeatherArmor.gd"

func onCalcTradeChance():
	Game.SELLBOX.tradeChance += getShopChance() / 100.0
