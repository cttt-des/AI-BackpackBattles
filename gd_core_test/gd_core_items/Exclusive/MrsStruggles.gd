extends Item
var activationParticles

func canAffect(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	addSpeed(getNumAffectedItems() * getP1() / 100.0)


func doCooldownEffect():
	for buff in CoreConst.getBuffs():
		opponent().loseStacks(buff, 1, self)
	activate()

func _readyInit():
	._readyInit()
	pass
