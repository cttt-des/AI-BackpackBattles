extends Food
var poison
var healingDebuff

func doCooldownEffect():
	inflictPoison(poison)
	opponent().reduceHealingEfficiency(healingDebuff)
	activate()

func _readyInit():
	._readyInit()
	poison = int(getP("poison"))
	healingDebuff = getP("healreduction") / 100.0
