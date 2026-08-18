extends Weapon

const activationParticles = preload("res://Items/Particles/ThornWhipActivationParticles.tscn")

func onPrepare():
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		giveSpikes(1)
		ObjectPool.particleOneShot(activationParticles, sprite)

func onSpikesChanged(amount, _event):
	changeVaryingDamage(getP1() * amount)
