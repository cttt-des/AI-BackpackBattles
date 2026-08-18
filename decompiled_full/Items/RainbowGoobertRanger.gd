extends Goobert

func doCooldownEffect():
	giveBlock()
	heal()
	giveVampirism(getP3())
	giveEmpower(getP4())
	inflictBlind(getP5())
	
	for item in getAffectedItems():
		if item.canBeEmpowered():
			item.addBonusDamage(getP6())
