extends Item
var options: Array

func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume


func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func onPrepare():
	addSpeed(getNumAffectedItems() * getP4() / 100.0)
	options = [0, 1, 2]


func doCooldownEffect():
	var rng = ctx.util.pickRandomElement(options)
	if rng == 0:
		giveLucky(getP1())
	elif rng == 1:
		giveRegeneration(getP2())
	else:
		giveEmpower(getP3())
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)

func _readyInit():
	._readyInit()
	pass
