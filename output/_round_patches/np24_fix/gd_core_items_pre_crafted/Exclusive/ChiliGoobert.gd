extends Goobert

func doCooldownEffect():
	heal()
	giveHeat(getP3())

func _readyInit():
	._readyInit()
	pass
