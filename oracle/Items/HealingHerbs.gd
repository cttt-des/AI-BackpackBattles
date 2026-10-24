extends Item

func onCombatStart():
	giveRegeneration(getP1())
	consume()
