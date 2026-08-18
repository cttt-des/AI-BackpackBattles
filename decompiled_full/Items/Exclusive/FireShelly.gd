extends "res://Items/Exclusive/Shelly.gd"

onready var heat: = int(getP("heat"))

func doCooldownEffect():
	giveHeat(heat)
	.doCooldownEffect()
