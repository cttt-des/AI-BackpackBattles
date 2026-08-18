extends Item

func onCombatStart():
	inflictBlind(getP1())
	consume()
