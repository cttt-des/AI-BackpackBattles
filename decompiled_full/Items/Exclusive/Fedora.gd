extends Item

onready var luckPerNature: = int(getP("luck"))
onready var luckPerTreasure: = int(getP("luck2"))
onready var luckNeeded: = int(getP("luckt"))
onready var numBuffs: = int(getP("buffs"))
onready var bonusChance: = getP("chance")

func canAffect(item):
	return item.isTreasure() or item.hasType(Type.Nature)

func canAffect_secondary(item):
	return item.canModifyChance()

func onPrepare():
	for item in getAffectedItems(Affected.Secondary):
		item.addBonusChance(bonusChance)

func onCombatStart():
	var numNature = 0
	var numTreasure = 0
	for item in getAffectedItems():
		if item.isTreasure():
			numTreasure += 1
		if item.hasType(Type.Nature):
			numNature += 1
	
	giveLucky(numNature * luckPerNature + numTreasure * luckPerTreasure)
	activate()

func doCooldownEffect():
	if character().getLucky() >= luckNeeded:
		var event = useLucky(luckNeeded)
		var buffs = Game.getBuffs()
		buffs.erase(Game.EventType.Lucky)
		stealRandomBuff(numBuffs, event, buffs)
	activate()

func getTriggerPriority() -> int:
	return Priority.High + 5
