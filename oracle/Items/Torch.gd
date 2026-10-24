extends Weapon

const activationParticles = preload("res://Items/Particles/TorchActivationParticles.tscn")

onready var permDamBonus = getP1()

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		addBonusDamage(permDamBonus)
		var particles = ObjectPool.particleOneShot(activationParticles, sprite)
		particles.scale = Vector2.ONE
