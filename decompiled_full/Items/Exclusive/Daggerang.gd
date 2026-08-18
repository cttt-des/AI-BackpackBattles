extends Dagger

const stealParticles = preload("res://Items/Exclusive/Particles/StealParticles.tscn")

onready var staminaReduction: = getP("stamina")

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		changeStaminaFactor( - staminaReduction)
		if rollChance():
			stealRandomBuff(1)
			var particles = ObjectPool.particleOneShot(stealParticles, sprite)
			particles.position = Vector2(60, 60)
