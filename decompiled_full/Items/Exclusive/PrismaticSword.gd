extends Weapon

onready var holyDam = getP("dam")
onready var debuffs = getP("debuffs")

var affectedTypes: Dictionary

func onPrepare():
	affectedTypes = countTypes(getAffectedItems())
	
	if affectedTypes[Type.Magic] > 0:
		addSpeed(affectedTypes[Type.Magic] * getP("speed") / 100.0)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		addBonusDamage(holyDam * affectedTypes[Type.Holy])
		if rollChance(getBaseChance2() * affectedTypes[Type.Dark]):
			inflictRandomDebuffs(debuffs)

func onPreDealDamage_late(damageRes: DamageResult):
	heal(ceil(damageRes.damage * getP_m("lifesteal") / 100.0 * affectedTypes[Type.Vampiric]))

func canAffect(item):
	return (item.hasType(Type.Vampiric) or 
			item.hasType(Type.Magic) or 
			item.hasType(Type.Holy) or 
			item.hasType(Type.Dark))

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


