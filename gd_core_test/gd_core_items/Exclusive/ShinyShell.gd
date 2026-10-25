extends Item

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


func doCooldownEffect():
	var healAmount = getP_m("heal") + getNumAffectedItems() * getP_m("heal_bonus")
	heal(healAmount)
	onAfterEffectFinished()

func _readyInit():
	._readyInit()
	pass
