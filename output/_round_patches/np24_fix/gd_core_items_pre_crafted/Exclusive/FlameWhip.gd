extends Weapon
var spikesNeeded: int
var heatGain: int
var bonusDamage: float

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if character().getSpikes() >= spikesNeeded:
			useSpikes(spikesNeeded)
			damageRes.damage += bonusDamage
			giveHeat(heatGain)

func _readyInit():
	._readyInit()
	spikesNeeded = getP("spikes")
	heatGain = getP("heat")
	bonusDamage = getP("bonusdam")
