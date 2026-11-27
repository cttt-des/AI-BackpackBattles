extends Item
var numBuffs
var speedPerGold

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
	pass

func _readyInit():
	._readyInit()
	numBuffs = int(getP("buffs"))
	speedPerGold = getP("speed") / 100.0
