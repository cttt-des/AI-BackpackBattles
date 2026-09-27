extends Weapon
var permDamBonus

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		addBonusDamage(permDamBonus)

func _readyInit():
	._readyInit()
	permDamBonus = getP1()
