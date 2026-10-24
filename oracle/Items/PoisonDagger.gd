extends Dagger

const activationParticles = preload("res://Items/Particles/PoisonDaggerActivationParticles.tscn")

onready var poison: = int(getP1())

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		inflictPoison(poison)
		ObjectPool.particleOneShot(activationParticles, sprite)
