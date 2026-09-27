extends Weapon
var totalBlockRemoval: int
var blockRemoval
var heatNeeded
var missDamage
var blind
var selfblind
var fireMultiplicity

func affectsEmpty(color):
	return true


func canAffect(item):
	return item.hasType(CoreConst.Type.Fire)


func onPrepare():
	totalBlockRemoval = blockRemoval * (getNumAffected_type(CoreConst.Type.Fire)
		+ getNumEmptyAffectedCells())


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if not damageRes.hasHit():
		if character().getHeat() >= heatNeeded:
			addBonusDamage(missDamage)
			damageRes.hit = true
			useHeat(heatNeeded)
	
	if damageRes.hasHit():
		inflictBlind(blind)
		selfInflictBlind(selfblind)


func onPreDealDamage_late(damageRes: CoreDamageResult):
	removeBlock(totalBlockRemoval)


func getTypeMultiplicity(type: int) -> int:
	if type == CoreConst.Type.Fire:
		return fireMultiplicity
	else:
		return .getTypeMultiplicity(type)

func _readyInit():
	._readyInit()
	blockRemoval = getP("blockremoval")
	heatNeeded = int(getP("heatt"))
	missDamage = int(getP("missdam"))
	blind = int(getP("blind"))
	selfblind = int(getP("blind_self"))
	fireMultiplicity = int(getP("fire"))
