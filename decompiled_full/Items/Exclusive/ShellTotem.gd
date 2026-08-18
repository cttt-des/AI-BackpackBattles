extends Item

onready var healthThreshold = getP("healtht") / 100.0

func canAffect(item):
	return item.hasType(Type.Holy)

func onPrepare():
	changeStaminaFactor( - getP("stamina") * getNumAffectedItems())

func doCooldownEffect():
	if useStamina() == Character.StaminaResult.Sufficient:
		if character().getRelativeHealth() > healthThreshold:
			giveEmpower(1)
		else:
			heal()
		activate()
