extends Item
var typesDict
var speedPerSpell

func canAffect(item):
	return (item.hasType(CoreConst.Type.Nature) or 
			item.hasType(CoreConst.Type.Ice) or 
			item.hasType(CoreConst.Type.Holy) or 
			item.hasType(CoreConst.Type.Dark) or 
			item.hasType(CoreConst.Type.Spell))


func onPrepare():
	typesDict = countTypes(getAffectedItems())
	
	if typesDict[CoreConst.Type.Spell] > 0:
		addSpeed(speedPerSpell * typesDict[CoreConst.Type.Spell])


func doCooldownEffect():
	
	if typesDict[CoreConst.Type.Nature] > 0:
		giveLucky(typesDict[CoreConst.Type.Nature] * getP("luck"))
		giveSpikes(typesDict[CoreConst.Type.Nature] * getP("spikes"))
	
	if typesDict[CoreConst.Type.Ice] > 0:
		giveBlock(typesDict[CoreConst.Type.Ice] * getBlock())
		inflictCold(typesDict[CoreConst.Type.Ice] * getP("cold"))
	
	if typesDict[CoreConst.Type.Holy] > 0:
		giveRegeneration(typesDict[CoreConst.Type.Holy] * getP("regen"))
	
	if typesDict[CoreConst.Type.Dark] > 0:
		stealRandomBuff(typesDict[CoreConst.Type.Dark])
	
	onAfterEffectFinished()


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	if not placed:
		descr = descr.replace("$n_nature", "")
		descr = descr.replace("$n_ice", "")
		descr = descr.replace("$n_holy", "")
		descr = descr.replace("$n_dark", "")
		
		return descr
	
	typesDict = countTypes(getAffectedItems())
	
	descr = insertCounter(descr, "n_nature", typesDict[CoreConst.Type.Nature])
	descr = insertCounter(descr, "n_ice", typesDict[CoreConst.Type.Ice])
	descr = insertCounter(descr, "n_holy", typesDict[CoreConst.Type.Holy])
	descr = insertCounter(descr, "n_dark", typesDict[CoreConst.Type.Dark])
	
	
	return descr

func _readyInit():
	._readyInit()
	speedPerSpell = getP("speed") / 100.0
