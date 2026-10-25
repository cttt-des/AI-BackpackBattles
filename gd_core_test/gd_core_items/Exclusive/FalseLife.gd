extends Item
var maxHealthAmp

func canAffect(item):
	return item.hasType(CoreConst.Type.Dark)


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

func _readyInit():
	._readyInit()
	maxHealthAmp = getP("healthamp") / 100.0
