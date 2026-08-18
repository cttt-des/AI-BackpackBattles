extends Food

func doCooldownEffect():
	giveMaxHealth()
	giveRandomBuffs(getP2())
	activate()
