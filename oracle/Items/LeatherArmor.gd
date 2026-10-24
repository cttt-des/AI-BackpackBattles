extends Item

func onPreCombatStart():
	character().changeDebuffResistStacks(getP1())

func onCombatStart():
	giveBlock()
	activate()
