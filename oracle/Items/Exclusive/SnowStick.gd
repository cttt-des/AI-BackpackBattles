extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/SnowStickActivationParticles.tscn")

onready var cold: = int(getP("cold"))
onready var selfCold: = int(getP("cold2"))

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		inflictCold(cold)
		giveStacks(character(), Game.EventType.Cold, selfCold)
		ObjectPool.particleOneShot(activationParticles, sprite)
