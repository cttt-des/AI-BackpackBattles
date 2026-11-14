extends Item
var cold
var maxHealthReduction

func onPrepare():
	opponent().changeMaxHealthGain(maxHealthReduction)


func onCombatStart():
	inflictCold(cold)
	consume()

func _readyInit():
	._readyInit()
	cold = int(getP("cold"))
	maxHealthReduction = - getP("healthreduction") / 100.0
