extends Weapon

func canAffect(item):
	return item.gainsBuffs()


func canAffect_secondary(item):
	return item.canDamage()


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var item1 = getFirstAffectedItem(CoreConst.Affected.Primary)
		if item1 != null:
			item1.changeAmplificiationChancePercent_allBuffs(getChance())
		
		var item2 = getFirstAffectedItem(CoreConst.Affected.Secondary)
		if item2 != null:
			item2.changeCritChancePercent(getChance2())

func _readyInit():
	._readyInit()
	pass
