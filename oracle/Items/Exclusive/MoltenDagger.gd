extends Dagger

const activationParticles = preload("res://Items/Exclusive/Particles/MoltenDaggerActivationParticles.tscn")

onready var heatNeeded: = int(getP1())
onready var bonusDam: = int(getP2())

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and character().getHeat() >= heatNeeded:
		addBonusDamage(bonusDam)
		useHeat(heatNeeded)
		ObjectPool.particleOneShot(activationParticles, sprite)
