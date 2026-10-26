extends Item

func onCombatStart():
	giveLucky(getP1())
	consume()

func _readyInit():
	._readyInit()
	pass
