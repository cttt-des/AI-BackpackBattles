extends Item
var speedPerHolyItem

func canAffect(item):
	return item.gainsBuffs()


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Holy)


func doCooldownEffect():
	giveRandomBuffs(1)
	activate()


func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
	
	addSpeed(getNumAffectedItems(CoreConst.Affected.Secondary) * speedPerHolyItem)

func _readyInit():
	._readyInit()
	speedPerHolyItem = getP("speed") / 100.0
