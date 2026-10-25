extends Bag
var bonusdur

func canApplyEffect(toItem):
	return toItem.hasInventoryDuration()


func onPrepare():
	for item in getAffectedItemsInside():
		item.modifyParam("dur", bonusdur)


func getTriggerPriority():
	return CoreConst.Priority.High + 100


func getBagEffect(number):
	var descr = ctx.util.tra(getName() + "_BAGEFFECT")
	descr = insertParameter(descr, "p_bonusdur", getP("bonusdur") * number)
	return descr

func _readyInit():
	._readyInit()
	bonusdur = getP("bonusdur") / 100.0
