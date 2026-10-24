extends "res://Items/Piggybank.gd"

func canAffect(item):
	return item.canModifyChance()

func onPrepare():
	for item in getAffectedItems():
		item.addBonusChance(getP3())

func onCombatStart():
	giveLucky(getP2())
	activate()

func getTriggerPriority() -> int:
	return Priority.High + 5

func explodeRandomly():
	pass
