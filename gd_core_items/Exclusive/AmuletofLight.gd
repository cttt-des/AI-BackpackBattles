extends Item
const amuletColor = Color(1, 0.850098, 0.400391)
var regenOnActivate

func canAffect(item):
	return item.canActivate()


func onPrepare():
	connectForCombat(character(), "character_regeneration_changed", "onRegenChanged")
	
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")


func onItemActivated(event):
	if event.origin.hasType(CoreConst.Type.Holy):
		if rollChance2():
			giveRegeneration(regenOnActivate, event)
			miniActivate()
	else:
		if rollChance():
			giveRegeneration(regenOnActivate, event)
			miniActivate()


func onRegenChanged(amount, event):
	if amount > 0:
		giveMaxHealth(amount * getP_m("maxhealth"), event)

func _readyInit():
	._readyInit()
	regenOnActivate = int(getP("regen"))
	pass

