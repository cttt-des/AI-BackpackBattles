extends Item

func onCombatStart():
	giveBlock()
	inflictCold(getP1())
	activate()
	
func doCooldownEffect():
	if character().getHeat() >= getP2():
		useHeat(getP2())
		inflictCold(getP3())
		giveBlock(getP4())
	activate()
