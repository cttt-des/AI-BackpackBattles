extends Bag
var usedStacks: Dictionary
var affectedInside: Array
var refund

func canApplyEffect(toItem):
	return toItem.usesBuffs()


func onPrepare():
	affectedInside = getAffectedItemsInside()
	if not affectedInside.empty():
		connectToCharacterBuffs("onBuffChanged")
		for buff in CoreConst.getBuffs():
			usedStacks[buff] = 0.0


func onBuffChanged(amount, event):
	if (amount < 0 and event.getParam("used", false) and 
		event.origin in affectedInside):
		var used = - amount
		var buffType = event.getType()
		usedStacks[buffType] += used * refund
		var toRefund = int(round(usedStacks[buffType]))
		
		if toRefund > 0:
			usedStacks[buffType] -= toRefund
			giveStacks(character(), buffType, toRefund, event)
			miniActivate()


func getBagEffect(number):
	var descr = ctx.util.tra(getName() + "_BAGEFFECT")
	descr = insertParameter(descr, "p_buff", getP("buff") * number)
	return descr

func _readyInit():
	._readyInit()
	refund = getP("buff") / 100.0
