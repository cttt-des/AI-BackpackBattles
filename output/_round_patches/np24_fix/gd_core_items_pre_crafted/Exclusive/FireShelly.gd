extends "res://gd_core_items/Exclusive/Shelly.gd"
var heat

func doCooldownEffect():
	giveHeat(heat)
	.doCooldownEffect()

func _readyInit():
	._readyInit()
	heat = int(getP("heat"))
