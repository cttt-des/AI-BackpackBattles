extends Item

const pickupSound = preload("res://Assets/Sound/Wolf2.mp3")

var options: Array

func playPickupSound():
	Sound.playSound_process(pickupSound, - 3)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(pickupSound, volume - 6)

func canAffect(item):
	return item.hasType(Type.Pet)

func onPrepare():
	addSpeed(getNumAffectedItems() * getP4() / 100.0)
	options = [0, 1, 2]

func doCooldownEffect():
	var rng = Util.pickRandomElement(options)
	if rng == 0:
		giveLucky(getP1())
	elif rng == 1:
		giveRegeneration(getP2())
	else:
		giveEmpower(getP3())
	activate()
	
	options = [0, 1, 2]
	options.erase(rng)
