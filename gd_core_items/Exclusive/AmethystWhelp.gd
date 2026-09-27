extends Weapon

func onCombatStart():
	inflictRandomDebuffs(getP1())
	activate(null, false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		removeRandomBuffs(1)

func _readyInit():
	._readyInit()
	pass
