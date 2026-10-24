extends Item

onready var speedBonus: = getP("speed") / 100.0
onready var darkSpeed: = getP("speed_dark") / 100.0
onready var maxActivations: = int(getP("max"))

var numActivations: int

func canAffect(item):
	return item.hasCooldown()

func canAffect_secondary(item):
	return item.hasType(Type.Dark)

func onPrepare():
	numActivations = 0
	addSpeed(getNumAffectedItems(Affected.Secondary) * darkSpeed)

func doCooldownEffect():
	numActivations += 1
	for item in getAffectedItems():
		item.addSpeed(speedBonus)
	giveStacks(character(), Game.EventType.Blind, 1)
	
	if numActivations == maxActivations:
		onAfterEffectFinished()
	else:
		activate()
