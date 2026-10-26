extends Item
var options: Array

func canAffect(item):
	return true


func onPrepare():
	addSpeed(getP3() / 100.0 * getNumAffectedItems())
	options = [0, 1, 2]


func doCooldownEffect():
	var rng = ctx.util.pickRandomElement(options)
	if rng == 0:
		giveBlock()
	elif rng == 1:
		giveStamina(getP1())
	else:
		giveLucky(getP2())
	
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)

func _readyInit():
	._readyInit()
	pass
