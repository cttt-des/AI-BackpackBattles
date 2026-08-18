extends Weapon

func onCombatStart():
	giveLucky(getP1())
	activate(null, false)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		inflictPoison(getP2())
