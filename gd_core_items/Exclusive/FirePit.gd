extends Bag

func canApplyEffect(toItem):
	return toItem.hasType(CoreConst.Type.Fire)


func onPreCombatStart():
	giveMaxHealth(getP_m("maxhealth") * getNumAffectedInside_type(CoreConst.Type.Fire))
	activate()


func onShopEntered():
	pass

func getBagMultiplicity(forItem) -> int:
	return forItem.getTypeMultiplicity(CoreConst.Type.Fire)

func _readyInit():
	._readyInit()
	pass
