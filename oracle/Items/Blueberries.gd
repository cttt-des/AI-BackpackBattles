extends Food

func doCooldownEffect():
	var overflow = giveMana_capped(getP1(), getP2())
	if overflow > 0:
		giveLucky(getP3())
	activate()
