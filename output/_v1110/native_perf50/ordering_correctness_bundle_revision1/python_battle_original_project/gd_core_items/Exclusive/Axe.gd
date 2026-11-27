extends Weapon
var permDamBonus

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		addBonusDamage(permDamBonus)

func _readyInit():
	._readyInit()
	permDamBonus = int(getP1())
