extends Item
var luckNeeded
var numBuffs
var activationParticles

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		giveMostBuffs(numBuffs, event)
	
	activate()
		

func _readyInit():
	._readyInit()
	luckNeeded = getP("luck")
	numBuffs = getP("buffs")
