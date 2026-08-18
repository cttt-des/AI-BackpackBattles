extends DragonEgg

func onCombatStart():
	doCooldownEffect()

func doCooldownEffect():
	giveMana(getP1())
	activate()
