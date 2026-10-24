extends Weapon

const poisonParticlesScene = preload("res://Items/Exclusive/Particles/PoisonShortbowParticles.tscn")

onready var poison: int = getP1()

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance():
		var randomDebuff = Util.pickRandomElement(Game.getDebuffs())
		if randomDebuff == Game.EventType.Poison:
			inflictPoison(poison + 1)
		else:
			inflictPoison(poison)
			giveStacks(opponent(), randomDebuff, 1)
		ObjectPool.particleOneShot(poisonParticlesScene, self)
