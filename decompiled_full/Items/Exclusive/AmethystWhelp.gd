extends Weapon

func onCombatStart():
	inflictRandomDebuffs(getP1())
	activate(null, false)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		removeRandomBuffs(1)
