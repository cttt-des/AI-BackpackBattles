extends Item

onready var mana: = int(getP("mana"))
onready var damReduction: = getP("damreduction") / 100.0

func canAffect(item):
	return item.getRarity() == Rarity.Common

func canAffect_secondary(item):
	return item.getRarity() == Rarity.Rare

func canAffect_tertiary(item):
	return item.getRarity() == Rarity.Epic

func onCombatStart():
	var numCommon = getNumAffectedItems(Affected.Primary)
	var numRare = getNumAffectedItems(Affected.Secondary)
	var numEpic = getNumAffectedItems(Affected.Tertiary)
	if numCommon > 0:
		giveBlock(getBlock() * numCommon)
	if numRare > 0:
		giveMana(mana * numRare)
	if numEpic > 0:
		opponent().changeEffectDamageFactor( - damReduction * numEpic)
	
	activate()
