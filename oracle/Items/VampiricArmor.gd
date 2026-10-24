extends Item

func onCombatStart():
	healthToBlock(getP1(), getBlock())
	giveVampirism(getP2())
	activate()
	
func doCooldownEffect():
	healthToBlock(getP3(), getP4())
	activate()
