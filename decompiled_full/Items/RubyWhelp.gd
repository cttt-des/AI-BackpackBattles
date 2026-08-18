extends Weapon

func onPreCombatStart():
	giveReflectStacks(getP2())

func onCombatStart():
	giveHeat(getP1())
	activate(null, false)
