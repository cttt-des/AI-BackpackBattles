extends Goobert

func doCooldownEffect():
	giveBlock()
	heal()
	giveVampirism(getP3())
	inflictBlind(getP4())
	inflictPoison(getP4())
	
	for item in getAffectedItems():
		if item.canBeEmpowered():
			item.addBonusDamage(getP5())
