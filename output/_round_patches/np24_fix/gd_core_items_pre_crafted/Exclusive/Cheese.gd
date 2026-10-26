extends Food

func doCooldownEffect():
	giveMaxHealth()
	giveRandomBuffs(getP2())
	activate()

func _readyInit():
	._readyInit()
	pass
