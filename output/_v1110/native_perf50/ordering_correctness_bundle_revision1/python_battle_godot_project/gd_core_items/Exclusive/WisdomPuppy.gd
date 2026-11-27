extends Item

func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume


func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func doCooldownEffect():
	giveBlock()
	cleanseCold(getP1())
	activate()


func onPrepare():
	addSpeed(getNumAffectedItems() * getP2() / 100.0)

func _readyInit():
	._readyInit()
	pass
