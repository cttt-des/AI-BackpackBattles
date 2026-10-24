extends Item

func onCombatStart():
	giveSpikes(getP1())
	consume()
