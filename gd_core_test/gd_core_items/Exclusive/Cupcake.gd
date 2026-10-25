extends Food
var numBuffs

func doCooldownEffect():
	heal()
	giveMostBuffs(numBuffs)







	activate()

func _readyInit():
	._readyInit()
	numBuffs = int(getP("buffs"))
