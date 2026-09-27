extends Item
var typesDict
var manaNeeded
var numDebuffs
var bonusPoison
var bonusBlind
var bonusCold

func canAffect(item):
	return (item.hasType(CoreConst.Type.Nature) or 
			item.hasType(CoreConst.Type.Dark) or 
			item.hasType(CoreConst.Type.Ice))


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
	
	descr = insertCounter(descr, "n_nature", typesDict[CoreConst.Type.Nature])
	descr = insertCounter(descr, "n_dark", typesDict[CoreConst.Type.Dark])
	descr = insertCounter(descr, "n_ice", typesDict[CoreConst.Type.Ice])
	
	return descr


func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		var event = useMana(manaNeeded)
		
		var leastStacks = getLeastStacks(numDebuffs, opponent(), 
			CoreConst.getDebuffs())
		
		if rollChance(getChance() * typesDict[CoreConst.Type.Nature]):
			ctx.util.dictAdd(leastStacks, CoreConst.EventType.Poison, bonusPoison)
		
		if rollChance(getChance() * typesDict[CoreConst.Type.Dark]):
			ctx.util.dictAdd(leastStacks, CoreConst.EventType.Blind, bonusBlind)
		
		if rollChance(getChance() * typesDict[CoreConst.Type.Ice]):
			ctx.util.dictAdd(leastStacks, CoreConst.EventType.Cold, bonusCold)
		
		for debuffType in leastStacks:
			giveStacks(opponent(), debuffType, leastStacks[debuffType], event)
	
	activate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	numDebuffs = int(getP("debuffs"))
	bonusPoison = int(getP("poison"))
	bonusBlind = int(getP("blind"))
	bonusCold = int(getP("cold"))
