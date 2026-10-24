extends Goobert

func doCooldownEffect():
	giveBlock()
	giveMaxHealth()
	giveVampirism(getP3())
	giveRandomBuffs(getP4())
	inflictBlind(getP("blind"))
	
	for item in getAffectedItems():
		if item.canBeEmpowered():
			item.addBonusDamage(getP5())
