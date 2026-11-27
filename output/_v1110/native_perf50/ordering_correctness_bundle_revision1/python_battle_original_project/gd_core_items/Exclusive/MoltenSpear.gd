extends Weapon
var totalBlockRemoval: int
var blockRemoval
var missDamage
var heatNeeded

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
			damageRes.damage += missDamage
			damageRes.hit = true
			useHeat(heatNeeded)


func onPreDealDamage_late(damageRes: CoreDamageResult):
	removeBlock(totalBlockRemoval)

func _readyInit():
	._readyInit()
	blockRemoval = getP("blockremoval")
	missDamage = int(getP("missdam"))
	heatNeeded = int(getP("heatt"))
