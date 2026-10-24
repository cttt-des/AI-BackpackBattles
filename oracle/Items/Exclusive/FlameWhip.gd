extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/FlameWhipActivationParticles.tscn")

onready var spikesNeeded: int = getP("spikes")
onready var heatGain: int = getP("heat")
onready var bonusDamage: float = getP("bonusdam")





func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if character().getSpikes() >= spikesNeeded:
			useSpikes(spikesNeeded)
			damageRes.damage += bonusDamage
			giveHeat(heatGain)
			ObjectPool.particleOneShot(activationParticles, sprite)
