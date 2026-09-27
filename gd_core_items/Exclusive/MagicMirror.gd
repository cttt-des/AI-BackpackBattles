extends Item
var buffFactor
var buffLimit

func canAffect(item):
	return item.hasType(CoreConst.Type.Holy)


func onPrepare():
	var totalChance = getChance() + getNumAffectedItems() * getChance2()
	character().changeAllDebuffsReflectChance(totalChance)


func doCooldownEffect():
	multiplyBuffsLimit(buffFactor, buffLimit)
	onAfterEffectFinished()

func _readyInit():
	._readyInit()
	buffFactor = getP("buffs") / 100.0
	buffLimit = int(getP("max"))
