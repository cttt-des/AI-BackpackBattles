extends "res://Items/LeatherHelm.gd"

func getStunProtectChance():
	return getChance2()

func onCombatStart():
	giveBlock()
	.onCombatStart()
