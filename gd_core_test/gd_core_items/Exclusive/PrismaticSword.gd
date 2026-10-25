extends Weapon
var affectedTypes: Dictionary
var holyDam
var debuffs

func onPrepare():
	affectedTypes = countTypes(getAffectedItems())
	
	if affectedTypes[CoreConst.Type.Magic] > 0:
		addSpeed(affectedTypes[CoreConst.Type.Magic] * getP("speed") / 100.0)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		addBonusDamage(holyDam * affectedTypes[CoreConst.Type.Holy])
		if rollChance(getBaseChance2() * affectedTypes[CoreConst.Type.Dark]):
			inflictRandomDebuffs(debuffs)


func onPreDealDamage_late(damageRes: CoreDamageResult):
	heal(ceil(damageRes.damage * getP_m("lifesteal") / 100.0 * affectedTypes[CoreConst.Type.Vampiric]))


func canAffect(item):
	return (item.hasType(CoreConst.Type.Vampiric) or 
			item.hasType(CoreConst.Type.Magic) or 
			item.hasType(CoreConst.Type.Holy) or 
			item.hasType(CoreConst.Type.Dark))


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
	holyDam = getP("dam")
	debuffs = getP("debuffs")
