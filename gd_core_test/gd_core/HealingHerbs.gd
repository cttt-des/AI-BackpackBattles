extends Item

func onCombatStart():
	giveRegeneration(getP1())
	consume()

func _readyInit():
	._readyInit()
	pass
