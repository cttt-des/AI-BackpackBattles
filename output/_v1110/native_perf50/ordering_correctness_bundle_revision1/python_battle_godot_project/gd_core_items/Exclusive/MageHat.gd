extends Item
var mana
var damReduction

func canAffect(item):
	return item.getRarity() == CoreConst.Rarity.Common


func canAffect_secondary(item):
	return item.getRarity() == CoreConst.Rarity.Rare


func canAffect_tertiary(item):
	return item.getRarity() == CoreConst.Rarity.Epic


func onCombatStart():
	var numCommon = getNumAffectedItems(CoreConst.Affected.Primary)
	var numRare = getNumAffectedItems(CoreConst.Affected.Secondary)
	var numEpic = getNumAffectedItems(CoreConst.Affected.Tertiary)
	if numCommon > 0:
		giveBlock(getBlock() * numCommon)
	if numRare > 0:
		giveMana(mana * numRare)
	if numEpic > 0:
		opponent().changeEffectDamageFactor( - damReduction * numEpic)
	
	activate()

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
	damReduction = getP("damreduction") / 100.0
