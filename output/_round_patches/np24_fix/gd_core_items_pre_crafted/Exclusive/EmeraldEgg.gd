extends DragonEgg

func onCombatStart():
	doCooldownEffect()


func doCooldownEffect():
	giveLucky(getP1())
	activate()

func _readyInit():
	._readyInit()
	pass
