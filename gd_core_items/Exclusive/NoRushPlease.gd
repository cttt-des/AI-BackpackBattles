extends "res://gd_core_items/LeatherHelm.gd"
var cold

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

func _readyInit():
	._readyInit()
	cold = int(getP("cold"))
