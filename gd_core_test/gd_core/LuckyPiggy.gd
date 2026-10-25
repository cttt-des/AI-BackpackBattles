extends "res://gd_core_items/Piggybank.gd"

func canAffect(item):
	return item.canModifyChance()


func onPrepare():
	for item in getAffectedItems():
		item.addBonusChance(getP3())


func onCombatStart():
	giveLucky(getP2())
	activate()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 5


func explodeRandomly():
	pass

func _readyInit():
	._readyInit()
	pass
