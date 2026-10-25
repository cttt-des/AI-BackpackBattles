extends Item

func onCombatStart():
	giveVampirism(getP1())
	giveMaxHealth()
	activate()

func _readyInit():
	._readyInit()
	pass
