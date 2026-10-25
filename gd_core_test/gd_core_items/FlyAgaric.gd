extends Food

func doCooldownEffect():
	inflictPoison(getP1())
	activate()

func _readyInit():
	._readyInit()
	pass
