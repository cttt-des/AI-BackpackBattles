extends "res://gd_core_items/LeatherHelm.gd"
var blind

func onPrepare():
	pass


func onPreCombatStart():
	if not ctx.sandbag_active:
		ctx.sandbag_active = true
		.onPreCombatStart()
		opponent().changeDamageResistance(damReduction)
	elif buffsActive > 0:
		ctx.util.changeTimer(buffTimer, getBuffDur())


func onCombatStart():
	inflictBlind(blind)
	giveStacks(character(), CoreConst.EventType.Blind, blind)
	activate()


func buffEnded():
	if buffsActive > 0:
		.buffEnded()
		opponent().changeDamageResistance( - damReduction)
		ctx.sandbag_active = false



func _readyInit():
	._readyInit()
	blind = int(getP("blind"))
