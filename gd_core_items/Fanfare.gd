extends Item
var options: Array

func canAffect(item):
	return true

















func onPrepare():
	addSpeed(getP5() / 100.0 * getNumAffectedItems())
	options = [0, 1, 2]


func doCooldownEffect():
	var rng = ctx.util.pickRandomElement(options)
	if rng == 0:
		giveEmpower(getP1())
	elif rng == 1:
		giveMana(getP2())
		removeMana(getP3())
	else:
		drainStamina(getP4())
	
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)

func _readyInit():
	._readyInit()
	pass
