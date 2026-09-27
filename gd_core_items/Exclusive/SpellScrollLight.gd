extends Item
var speedBonus

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


func onPrepare():
	addSpeed(speedBonus * getNumAffectedItems())


func doCooldownEffect():
	cleanseRandomDebuffs(1)
	if character().getDebuffStacks() == 0:
		heal()
	activate()

func _readyInit():
	._readyInit()
	speedBonus = getP("speed") / 100.0
