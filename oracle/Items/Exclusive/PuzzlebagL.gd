extends Bag

onready var healamp: = getP("healamp") / 100.0

func canApplyEffect(toItem):
	return toItem.canHealOrLifesteal()

func onPrepare():
	for item in getAffectedItemsInside():
		item.changeHealAmp(healamp)

func onCombatStart():
	giveMaxHealth()
	activate()

func getBagEffect(number):
	var descr = Util.tra(getName() + "_BAGEFFECT")
	descr = insertParameter(descr, "p_healamp", getP("healamp") * number)
	return descr
