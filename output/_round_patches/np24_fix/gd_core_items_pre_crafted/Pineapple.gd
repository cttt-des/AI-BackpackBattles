extends Food

func doCooldownEffect():
	heal()
	giveSpikes(1)
	activate()

func _readyInit():
	._readyInit()
	pass
