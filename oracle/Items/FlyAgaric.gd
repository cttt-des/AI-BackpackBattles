extends Food

func doCooldownEffect():
	inflictPoison(getP1())
	activate()
