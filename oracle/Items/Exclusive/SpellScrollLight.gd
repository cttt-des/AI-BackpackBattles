extends Item

onready var speedBonus: = getP("speed") / 100.0

func canAffect(item):
	return item.hasType(Type.Holy)

func onPrepare():
	addSpeed(speedBonus * getNumAffectedItems())

func doCooldownEffect():
	cleanseRandomDebuffs(1)
	if character().getDebuffStacks() == 0:
		heal()
	activate()

