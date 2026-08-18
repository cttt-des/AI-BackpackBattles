extends Dagger

const activationParticles = preload("res://Items/Particles/CursedDaggerActivationParticles.tscn")

func canAffect(item):
	return item.canDamage()

func onPrepare():
	connectToOpponentDebuffs("onOpponentDebuffsChanged")

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		inflictRandomDebuffs(getP1())
		ObjectPool.particleOneShot(activationParticles, sprite)

func onOpponentDebuffsChanged(amount, _event):
	var extraCritChance = amount * getChance()
	var extraAccuracy = amount * getP2()
	addCritChancePercent(extraCritChance)
	addAccuracy(extraAccuracy)
	
	for item in getAffectedItems():
		item.addCritChancePercent(extraCritChance)
		if item.isWeapon():
			item.addAccuracy(extraAccuracy)
