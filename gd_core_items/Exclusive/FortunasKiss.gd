extends Item
var stackTypes: Array
var bonusChance
var luckNeeded

func canAffect(item):
	return item.canModifyChance()


func onPrepare():
	for item in getAffectedItems():
		item.addBonusChance(bonusChance)


func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		giveRandomBuffs(1, null, stackTypes)
	else:
		giveLucky(1)
	activate()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 5

func _readyInit():
	._readyInit()
	bonusChance = getP("chance")
	luckNeeded = int(getP("luckt"))
	stackTypes = CoreConst.getBuffs()
	stackTypes.erase(CoreConst.EventType.Lucky)
	
