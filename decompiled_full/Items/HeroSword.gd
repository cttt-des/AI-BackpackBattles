extends Weapon

func canAffect(item):
	return item.canBeEmpowered()

func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(getP1())
	activate(null, false, false, ActivationAni.Jump)
