extends Weapon

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		giveLucky(1)

func _readyInit():
	._readyInit()
	pass
