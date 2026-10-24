extends Weapon

const luckyParticlesScene = preload("res://Items/Exclusive/Particles/LuckyShortbowParticles.tscn")

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		giveLucky(1)
		ObjectPool.particleOneShot(luckyParticlesScene, self)
