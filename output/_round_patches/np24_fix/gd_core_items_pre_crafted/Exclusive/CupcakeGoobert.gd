extends Goobert
var numBuffs

func doCooldownEffect():
	heal()
	giveMostBuffs(numBuffs)





















func _readyInit():
	._readyInit()
	numBuffs = int(getP("buffs"))
