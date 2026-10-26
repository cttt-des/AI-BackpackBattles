extends "res://gd_core_items/LeatherHelm.gd"
var mana

func canAffect(item):
	return item.gainsStack(CoreConst.Stack.Mana)


func onPrepare():
	.onPrepare()
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent(CoreConst.EventType.Mana, getChance2())


func onCombatStart():
	giveMana(mana)
	.onCombatStart()

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
