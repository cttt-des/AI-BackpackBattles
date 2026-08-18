extends "res://Items/LeatherHelm.gd"

onready var cold: = int(getP("cold"))

func onPrepare():
	pass

func onPreCombatStart():
	.onPreCombatStart()
	opponent().changeDamageResistance(damReduction)

func buffEnded():
	.buffEnded()
	opponent().changeDamageResistance( - damReduction)

func onCombatStart():
	inflictCold(cold)
	.onCombatStart()
