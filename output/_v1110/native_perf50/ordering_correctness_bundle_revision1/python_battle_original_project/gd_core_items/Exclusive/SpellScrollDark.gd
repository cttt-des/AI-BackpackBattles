extends Item
var numActivations: int
var speedBonus
var darkSpeed
var maxActivations

func canAffect(item):
	return item.hasCooldown()


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Dark)


func onPrepare():
	numActivations = 0
	addSpeed(getNumAffectedItems(CoreConst.Affected.Secondary) * darkSpeed)


func doCooldownEffect():
	numActivations += 1
	for item in getAffectedItems():
		item.addSpeed(speedBonus)
	giveStacks(character(), CoreConst.EventType.Blind, 1)
	
	if numActivations == maxActivations:
		onAfterEffectFinished()
	else:
		activate()

func _readyInit():
	._readyInit()
	speedBonus = getP("speed") / 100.0
	darkSpeed = getP("speed_dark") / 100.0
	maxActivations = int(getP("max"))
