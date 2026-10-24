extends Weapon

const thornParticlesScene = preload("res://Items/Exclusive/Particles/ThornShortbowParticles.tscn")

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		giveSpikes(1, damageRes.event)
		ObjectPool.particleOneShot(thornParticlesScene, self)
