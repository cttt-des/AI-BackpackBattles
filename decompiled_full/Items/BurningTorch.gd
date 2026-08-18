extends Weapon

const activationParticles = preload("res://Items/Particles/TorchActivationParticles.tscn")
onready var permDamBonus = getP2()

func onCombatStart():
	giveHeat(getP1())
	activate(null, false)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		addBonusDamage(permDamBonus)
		var particles = ObjectPool.particleOneShot(activationParticles, sprite)
		particles.scale = Vector2(1.2, 1.2)
