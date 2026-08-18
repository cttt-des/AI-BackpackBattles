extends Weapon

const activationParticleScene = preload("res://Items/Particles/MagicTorchActivationParticles.tscn")

onready var manaNeeded: int = getP1()
onready var damBonus: int = getP2()

func canAffect(item):
	return item.canBeEmpowered()

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		var event = tryUseMana(manaNeeded)
		if event != null:
			addBonusDamage(damBonus)
			for item in getAffectedItems():
				item.addBonusDamage(damBonus)
			
			var particles = ObjectPool.particleOneShot(activationParticleScene, sprite)
			particles.position = Vector2(0, - 90)
