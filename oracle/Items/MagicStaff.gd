extends Weapon

const activationParticleScene = preload("res://Items/Particles/MagicStaffActivationParticles.tscn")

onready var manaCost = getP1()
onready var tempDamBonus = getP2()
onready var permDamBonus = getP3()

func onPreDealDamage_early(damageRes: DamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		damageRes.damage += tempDamBonus
		addBonusDamage(permDamBonus)
		var activationParticles = ObjectPool.particleOneShot(activationParticleScene, self)
		activationParticles.global_position = specificDragParticles[0].global_position
