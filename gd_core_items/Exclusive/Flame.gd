extends Item

func onCombatStart():
	giveHeat(1)
	consume()

func _readyInit():
	._readyInit()
	pass
