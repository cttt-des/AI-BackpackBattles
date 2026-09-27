extends Dagger
var heatNeeded
var bonusDam

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and character().getHeat() >= heatNeeded:
		addBonusDamage(bonusDam)
		useHeat(heatNeeded)

func _readyInit():
	._readyInit()
	heatNeeded = int(getP1())
	bonusDam = int(getP2())
