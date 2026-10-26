extends Item
const amuletColor = Color(0.980469, 0.214478, 0.214478)

func onPrepare():
	character().addHealingEfficiency(getP("healamp") / 100.0)


func onCombatStart():
	giveMaxHealth()
	activate()

func _readyInit():
	._readyInit()
	pass

