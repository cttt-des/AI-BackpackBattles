extends Item

onready var maxHealthAmp: = getP("healthamp") / 100.0

func canAffect(item):
	return item.hasType(Type.Dark)

func canAffect_global(item):
	return item.descriptor.hasParam("maxhealth")

func onPrepare():
	character().changeMaxHealthGain(maxHealthAmp)
	connectForCombat(character(), "character_overhealed", "onOverheal")

func doCooldownEffect():
	var healAmount = getP_m("heal") + getP_m("heal_dark") * getNumAffectedItems()
	heal(healAmount)
	activate()

func onOverheal(overheal, healEvent):
	giveMaxHealth(overheal, healEvent)
