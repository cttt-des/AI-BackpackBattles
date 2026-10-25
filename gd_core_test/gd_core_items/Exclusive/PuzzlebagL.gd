extends Bag
var healamp

func canApplyEffect(toItem):
	return toItem.canHealOrLifesteal()


func onPrepare():
	for item in getAffectedItemsInside():
		item.changeHealAmp(healamp)


func onCombatStart():
	giveMaxHealth()
	activate()


func getBagEffect(number):
	var descr = ctx.util.tra(getName() + "_BAGEFFECT")
	descr = insertParameter(descr, "p_healamp", getP("healamp") * number)
	return descr

func _readyInit():
	._readyInit()
	healamp = getP("healamp") / 100.0
