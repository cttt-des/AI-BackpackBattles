extends Item

func onCombatStart():
	giveVampirism(getP1())
	giveMaxHealth()
	activate()
