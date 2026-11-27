extends "res://gd_core_items/LeatherHelm.gd"

func getStunProtectChance():
	return getChance2()


func onCombatStart():
	giveBlock()
	.onCombatStart()

func _readyInit():
	._readyInit()
	pass
