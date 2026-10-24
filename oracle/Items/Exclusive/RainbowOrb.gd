extends Item

onready var buffs = getP("buffs")

func canAffect(item):
	
	return (item.hasType(Type.Vampiric) or 
			item.hasType(Type.Magic) or 
			item.hasType(Type.Holy) or 
			item.hasType(Type.Dark))

func onCombatStart():
	var typesDict = countTypes(getAffectedItems())
	
	if typesDict[Type.Vampiric] > 0:
		giveVampirism(typesDict[Type.Vampiric] * getP("vampirism"))
	
	if typesDict[Type.Magic] > 0:
		giveMana(typesDict[Type.Magic] * getP("mana"))
	
	if typesDict[Type.Holy] > 0:
		character().addHealingEfficiency(typesDict[Type.Holy] * getP("healamp") / 100.0)
	
	if typesDict[Type.Dark] > 0:
		inflictRandomDebuffs(typesDict[Type.Dark] * getP("debuffs"))
	
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
	
	descr = insertCounter(descr, "n_magic", typesDict[Type.Magic])
	descr = insertCounter(descr, "n_vampiric", typesDict[Type.Vampiric])
	descr = insertCounter(descr, "n_holy", typesDict[Type.Holy])
	descr = insertCounter(descr, "n_dark", typesDict[Type.Dark])
	
	return descr


