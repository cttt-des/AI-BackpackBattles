extends Item

func onCombatStart():
	giveSpikes(getP1())
	consume()

func _readyInit():
	._readyInit()
	pass
