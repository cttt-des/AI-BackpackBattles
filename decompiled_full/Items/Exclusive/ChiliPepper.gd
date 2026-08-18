extends Food

func doCooldownEffect():
	giveHeat(getP1())
	heal()
	if character().getHeat() >= getP3():
		cleanseRandomDebuffs(1)
	
	activate()
