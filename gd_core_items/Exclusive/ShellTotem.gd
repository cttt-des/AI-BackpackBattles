extends Item
var healthThreshold

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


func onPrepare():
	changeStaminaFactor( - getP("stamina") * getNumAffectedItems())


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		if character().getRelativeHealth() > healthThreshold:
			giveEmpower(1)
		else:
			heal()
		activate()

func _readyInit():
	._readyInit()
	healthThreshold = getP("healtht") / 100.0
