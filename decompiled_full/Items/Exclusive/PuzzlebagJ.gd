extends Bag

onready var bonusdur: = getP("bonusdur") / 100.0

func canApplyEffect(toItem):
	return toItem.hasInventoryDuration()

func onPrepare():
	for item in getAffectedItemsInside():
		item.modifyParam("dur", bonusdur)

func getTriggerPriority():
	return Priority.High + 100

func getBagEffect(number):
	var descr = Util.tra(getName() + "_BAGEFFECT")
	descr = insertParameter(descr, "p_bonusdur", getP("bonusdur") * number)
	return descr
