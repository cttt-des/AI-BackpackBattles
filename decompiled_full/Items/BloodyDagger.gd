extends Dagger

const activationParticles = preload("res://Items/Particles/BloodyDaggerActivationParticles.tscn")

var vampirismStacks: int

func canAffect(item):
	return item.hasType(Type.Vampiric)
	
func onPrepare():
	vampirismStacks = 0

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if vampirismStacks < getP2():
			giveVampirism(getP1())
			vampirismStacks += getP1()
			ObjectPool.particleOneShot(activationParticles, sprite)
	
		var numAffected = getNumAffectedItems()
		if numAffected > 0:
			heal(numAffected * getP_m("heal"))
