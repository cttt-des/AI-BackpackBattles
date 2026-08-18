extends Item

func onCombatStart():
	giveHeat(1)
	consume()
