extends Goobert

func doCooldownEffect():
	giveBlock()
	heal()
	giveVampirism(getP3())
	giveHeat(getP4())
	inflictBlind(getP("blind"))
	
	for item in getAffectedItems():
		if item.canBeEmpowered():
			item.addBonusDamage(getP5())
