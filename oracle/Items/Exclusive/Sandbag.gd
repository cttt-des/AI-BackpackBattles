extends "res://Items/LeatherHelm.gd"

onready var blind: = int(getP("blind"))

func onPrepare():
	pass

func onPreCombatStart():
	if not Game.sandbagActive:
		Game.sandbagActive = true
		.onPreCombatStart()
		opponent().changeDamageResistance(damReduction)
	elif buffsActive > 0:
		Util.changeTimer(buffTimer, getBuffDur())

func onCombatStart():
	inflictBlind(blind)
	giveStacks(character(), Game.EventType.Blind, blind)
	activate()

func buffEnded():
	if buffsActive > 0:
		.buffEnded()
		opponent().changeDamageResistance( - damReduction)
		Game.sandbagActive = false



