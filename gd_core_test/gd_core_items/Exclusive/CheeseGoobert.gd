extends Goobert

func doCooldownEffect():
	giveMaxHealth()
	giveRandomBuffs(getP3())

func _readyInit():
	._readyInit()
	pass
