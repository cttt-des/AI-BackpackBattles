extends Food

func doCooldownEffect():
	cleanseRandomDebuffs(1)
	
	if character().getLucky() >= getP2():
		if rollChance():
			giveEmpower(1)
	activate()

func _readyInit():
	._readyInit()
	pass
