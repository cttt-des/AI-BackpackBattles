extends Weapon
var manaNeeded: int
var damBonus: int

func canAffect(item):
	return item.canBeEmpowered()


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var event = tryUseMana(manaNeeded)
		if event != null:
			addBonusDamage(damBonus)
			for item in getAffectedItems():
				item.addBonusDamage(damBonus)
			

func _readyInit():
	._readyInit()
	manaNeeded = getP1()
	damBonus = getP2()
