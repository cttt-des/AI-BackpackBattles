extends "res://Items/LeatherHelm.gd"

onready var mana: = int(getP("mana"))

func canAffect(item):
	return item.gainsStack(Stack.Mana)

func onPrepare():
	.onPrepare()
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent(Game.EventType.Mana, getChance2())

func onCombatStart():
	giveMana(mana)
	.onCombatStart()
