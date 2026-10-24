extends Weapon

func canAffect(item):
	return item.canBeEmpowered() and item.descriptor.isMeleeWeapon()

func onPreCombatStart():
	for item in getAffectedItems():
		item.reduceBonusDamage(getP1())
		addBonusDamage(getP2())
