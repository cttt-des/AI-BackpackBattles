extends Weapon
var permDamBonus

func onCombatStart():
	giveHeat(getP1())
	activate(null, false)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit() and rollChance():
		addBonusDamage(permDamBonus)

func _readyInit():
	._readyInit()
	permDamBonus = getP2()
