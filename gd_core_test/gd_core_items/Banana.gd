extends Food

func doCooldownEffect():
	heal()
	giveStamina()
	activate()

func _readyInit():
	._readyInit()
	pass
