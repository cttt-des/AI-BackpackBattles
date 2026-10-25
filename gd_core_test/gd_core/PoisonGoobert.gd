extends Goobert

func doCooldownEffect():
	heal()
	inflictPoison(getP3())

func _readyInit():
	._readyInit()
	pass
