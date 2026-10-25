extends Item
var luckPerNature
var luckPerTreasure
var luckNeeded
var numBuffs
var bonusChance

func canAffect(item):
	return item.isTreasure() or item.hasType(CoreConst.Type.Nature)


func canAffect_secondary(item):
	return item.canModifyChance()


func onPrepare():
	for item in getAffectedItems(CoreConst.Affected.Secondary):
		item.addBonusChance(bonusChance)


func onCombatStart():
	var numNature = 0
	var numTreasure = 0
	for item in getAffectedItems():
		if item.isTreasure():
			numTreasure += 1
		if item.hasType(CoreConst.Type.Nature):
			numNature += 1
	
	giveLucky(numNature * luckPerNature + numTreasure * luckPerTreasure)
	activate()


func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		var buffs = CoreConst.getBuffs()
		buffs.erase(CoreConst.EventType.Lucky)
		stealRandomBuff(numBuffs, event, buffs)
	activate()


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 5

func _readyInit():
	._readyInit()
	luckPerNature = int(getP("luck"))
	luckPerTreasure = int(getP("luck2"))
	luckNeeded = int(getP("luckt"))
	numBuffs = int(getP("buffs"))
	bonusChance = getP("chance")
