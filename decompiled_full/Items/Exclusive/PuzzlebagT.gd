extends Bag

onready var refund = getP("buff") / 100.0

var usedStacks: Dictionary
var affectedInside: Array

func canApplyEffect(toItem):
	return toItem.usesBuffs()

func onPrepare():
	affectedInside = getAffectedItemsInside()
	if not affectedInside.empty():
		connectToCharacterBuffs("onBuffChanged")
		for buff in Game.getBuffs():
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
	var descr = Util.tra(getName() + "_BAGEFFECT")
	descr = insertParameter(descr, "p_buff", getP("buff") * number)
	return descr
