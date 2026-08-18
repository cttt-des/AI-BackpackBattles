extends Food

onready var poison: = int(getP("poison"))
onready var healingDebuff = getP("healreduction") / 100.0

func doCooldownEffect():
	inflictPoison(poison)
	opponent().reduceHealingEfficiency(healingDebuff)
	activate()
