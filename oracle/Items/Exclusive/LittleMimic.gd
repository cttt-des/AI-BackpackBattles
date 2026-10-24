extends Item

onready var numBuffs: = int(getP("buffs"))
onready var speedPerGold: = getP("speed") / 100.0

func canAffect(item):
	return true

func getCounterValue() -> int:
	var gold = 0
	if placed:
		for item in getAffectedItems():
			gold += item.getPrice()
	else:
		for item in getAffectedItems_nocache():
			gold += item.getPrice()
	return gold

func onPrepare():
	addSpeed(getCounterValue() * speedPerGold)

func doCooldownEffect():
	giveMostBuffs(numBuffs)
	activate()

func onCalcTradeChance():
	Game.SELLBOX.tradeChance += getShopChance() / 100.0
