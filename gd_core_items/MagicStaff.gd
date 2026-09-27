extends Weapon
var manaCost
var tempDamBonus
var permDamBonus

func onPreDealDamage_early(damageRes: CoreDamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		damageRes.damage += tempDamBonus
		addBonusDamage(permDamBonus)

func _readyInit():
	._readyInit()
	manaCost = getP1()
	tempDamBonus = getP2()
	permDamBonus = getP3()
