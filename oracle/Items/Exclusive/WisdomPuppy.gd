extends Item

const pickupSound = preload("res://Assets/Sound/Wolf1.mp3")

func playPickupSound():
	Sound.playSound_process(pickupSound, - 4)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(pickupSound, volume - 8)

func canAffect(item):
	return item.hasType(Type.Pet)

func doCooldownEffect():
	giveBlock()
	cleanseCold(getP1())
	activate()

func onPrepare():
	addSpeed(getNumAffectedItems() * getP2() / 100.0)
