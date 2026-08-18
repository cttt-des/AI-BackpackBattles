extends Card

onready var snowflakes = $Snowflakes
onready var damReduction: = getP("damfactor") / 100.0

func doRevealEffect():
	giveBlock(getBlock() + getP1() * chainPosition)
	inflictCold(getP2())
	opponent().changeEffectDamageFactor( - damReduction)
	activate()
	snowflakes.activate()
