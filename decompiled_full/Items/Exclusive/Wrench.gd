extends Weapon

func canAffect(item):
	return item.gainsBuffs()

func canAffect_secondary(item):
	return item.canDamage()

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		var item1 = getFirstAffectedItem(Affected.Primary)
		if item1 != null:
			item1.changeAmplificiationChancePercent_allBuffs(getChance())
		
		var item2 = getFirstAffectedItem(Affected.Secondary)
		if item2 != null:
			item2.changeCritChancePercent(getChance2())
