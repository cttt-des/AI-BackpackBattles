extends Item

func onCombatStart():
	giveLucky(getP1())
	consume()
