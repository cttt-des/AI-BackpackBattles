extends Dagger

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var event = tryUseMana(getP1())
		if event:
			damageRes.damage += getP2()
			damageRes.damageSource.makeSpectral()

func _readyInit():
	._readyInit()
	pass
