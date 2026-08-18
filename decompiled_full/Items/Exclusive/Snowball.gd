extends Item

onready var cold: = int(getP("cold"))
onready var maxHealthReduction: = - getP("healthreduction") / 100.0

func onPrepare():
	opponent().changeMaxHealthGain(maxHealthReduction)

func onCombatStart():
	inflictCold(cold)
	consume()
