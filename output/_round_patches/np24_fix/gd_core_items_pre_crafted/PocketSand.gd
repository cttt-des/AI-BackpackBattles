extends Item

func onCombatStart():
	inflictBlind(getP1())
	consume()

func _readyInit():
	._readyInit()
	pass
