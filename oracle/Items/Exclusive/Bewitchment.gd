extends Item

onready var manaNeeded: = int(getP("manat"))
onready var numDebuffs: = int(getP("debuffs"))
onready var bonusPoison: = int(getP("poison"))
onready var bonusBlind: = int(getP("blind"))
onready var bonusCold: = int(getP("cold"))

var typesDict

func canAffect(item):
	return (item.hasType(Type.Nature) or 
			item.hasType(Type.Dark) or 
			item.hasType(Type.Ice))

func onPrepare():
	typesDict = countTypes(getAffectedItems())

func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	if not placed:
		descr = descr.replace("$n_nature", "")
		descr = descr.replace("$n_dark", "")
		descr = descr.replace("$n_ice", "")
		return descr
	
	typesDict = countTypes(getAffectedItems())
	
	descr = insertCounter(descr, "n_nature", typesDict[Type.Nature])
	descr = insertCounter(descr, "n_dark", typesDict[Type.Dark])
	descr = insertCounter(descr, "n_ice", typesDict[Type.Ice])
	
	return descr

func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		
		var leastStacks = getLeastStacks(numDebuffs, opponent(), 
			Game.getDebuffs())
		
		if rollChance(getChance() * typesDict[Type.Nature]):
			Util.dictAdd(leastStacks, Game.EventType.Poison, bonusPoison)
		
		if rollChance(getChance() * typesDict[Type.Dark]):
			Util.dictAdd(leastStacks, Game.EventType.Blind, bonusBlind)
		
		if rollChance(getChance() * typesDict[Type.Ice]):
			Util.dictAdd(leastStacks, Game.EventType.Cold, bonusCold)
		
		for debuffType in leastStacks:
			giveStacks(opponent(), debuffType, leastStacks[debuffType], event)
	
	activate()
