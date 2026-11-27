extends Weapon

func onCombatStart():
	giveLucky(getP1())
	activate(null, false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		inflictPoison(getP2())

func _readyInit():
	._readyInit()
	pass
