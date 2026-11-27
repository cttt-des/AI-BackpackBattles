extends DragonEgg

func onCombatStart():
	doCooldownEffect()


func doCooldownEffect():
	inflictRandomDebuffs(getP1())
	activate()

func _readyInit():
	._readyInit()
	pass
