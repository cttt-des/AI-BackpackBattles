extends Item

onready var heat: = int(getP("heat"))
onready var bonusdur: = getP("bonusdur") / 100.0

func canAffect(item):
	return item.hasInventoryDuration()

func onPrepare():
	for item in getAffectedItems():
		item.modifyParam("dur", bonusdur)

func onCombatStart():
	giveHeat(heat)
	activate()

func getTriggerPriority():
	return Priority.High + 100
