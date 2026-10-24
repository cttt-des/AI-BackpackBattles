extends Item

onready var speedPerSpell: = getP("speed") / 100.0

var typesDict

func canAffect(item):
	return (item.hasType(Type.Nature) or 
			item.hasType(Type.Ice) or 
			item.hasType(Type.Holy) or 
			item.hasType(Type.Dark) or 
			item.hasType(Type.Spell))

func onPrepare():
	typesDict = countTypes(getAffectedItems())
	
	if typesDict[Type.Spell] > 0:
		addSpeed(speedPerSpell * typesDict[Type.Spell])

func doCooldownEffect():
	
	if typesDict[Type.Nature] > 0:
		giveLucky(typesDict[Type.Nature] * getP("luck"))
		giveSpikes(typesDict[Type.Nature] * getP("spikes"))
	
	if typesDict[Type.Ice] > 0:
		giveBlock(typesDict[Type.Ice] * getBlock())
		inflictCold(typesDict[Type.Ice] * getP("cold"))
	
	if typesDict[Type.Holy] > 0:
		giveRegeneration(typesDict[Type.Holy] * getP("regen"))
	
	if typesDict[Type.Dark] > 0:
		stealRandomBuff(typesDict[Type.Dark])
	
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
	
	descr = insertCounter(descr, "n_nature", typesDict[Type.Nature])
	descr = insertCounter(descr, "n_ice", typesDict[Type.Ice])
	descr = insertCounter(descr, "n_holy", typesDict[Type.Holy])
	descr = insertCounter(descr, "n_dark", typesDict[Type.Dark])
	
	
	return descr
