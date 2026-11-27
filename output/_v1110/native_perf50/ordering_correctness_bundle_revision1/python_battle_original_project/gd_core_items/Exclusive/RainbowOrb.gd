extends Item
var buffs

func canAffect(item):
	
	return (item.hasType(CoreConst.Type.Vampiric) or 
			item.hasType(CoreConst.Type.Magic) or 
			item.hasType(CoreConst.Type.Holy) or 
			item.hasType(CoreConst.Type.Dark))


func onCombatStart():
	var typesDict = countTypes(getAffectedItems())
	
	if typesDict[CoreConst.Type.Vampiric] > 0:
		giveVampirism(typesDict[CoreConst.Type.Vampiric] * getP("vampirism"))
	
	if typesDict[CoreConst.Type.Magic] > 0:
		giveMana(typesDict[CoreConst.Type.Magic] * getP("mana"))
	
	if typesDict[CoreConst.Type.Holy] > 0:
		character().addHealingEfficiency(typesDict[CoreConst.Type.Holy] * getP("healamp") / 100.0)
	
	if typesDict[CoreConst.Type.Dark] > 0:
		inflictRandomDebuffs(typesDict[CoreConst.Type.Dark] * getP("debuffs"))
	
	activate()


func doCooldownEffect():
	giveAllBuffs()
	activate()


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	if not placed:
		descr = descr.replace("$n_magic", "")
		descr = descr.replace("$n_vampiric", "")
		descr = descr.replace("$n_holy", "")
		descr = descr.replace("$n_dark", "")
		return descr
	
	var typesDict = countTypes(getAffectedItems())
	
	descr = insertCounter(descr, "n_magic", typesDict[CoreConst.Type.Magic])
	descr = insertCounter(descr, "n_vampiric", typesDict[CoreConst.Type.Vampiric])
	descr = insertCounter(descr, "n_holy", typesDict[CoreConst.Type.Holy])
	descr = insertCounter(descr, "n_dark", typesDict[CoreConst.Type.Dark])
	
	return descr


func _readyInit():
	._readyInit()
	buffs = getP("buffs")
