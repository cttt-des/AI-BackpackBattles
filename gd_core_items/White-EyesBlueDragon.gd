extends Card
var snowflakes
var damReduction

func doRevealEffect():
	giveBlock(getBlock() + getP1() * chainPosition)
	inflictCold(getP2())
	opponent().changeEffectDamageFactor( - damReduction)
	activate()

func _readyInit():
	._readyInit()
	damReduction = getP("damfactor") / 100.0
