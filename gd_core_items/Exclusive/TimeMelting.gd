extends Item
var heat
var bonusdur

func canAffect(item):
	return item.hasInventoryDuration()


func onPrepare():
	for item in getAffectedItems():
		item.modifyParam("dur", bonusdur)


func onCombatStart():
	giveHeat(heat)
	activate()


func getTriggerPriority():
	return CoreConst.Priority.High + 100

func _readyInit():
	._readyInit()
	heat = int(getP("heat"))
	bonusdur = getP("bonusdur") / 100.0
