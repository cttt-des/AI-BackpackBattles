extends Dagger

const activationParticleScene = preload("res://Items/Particles/MagicTorchActivationParticles.tscn")

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		var event = tryUseMana(getP1())
		if event:
			damageRes.damage += getP2()
			damageRes.damageSource.makeSpectral()
			var particles = ObjectPool.particleOneShot(activationParticleScene, sprite)
			particles.position = Vector2(30, - 20)
