extends "res://Items/PestilenceFlask.gd"

onready var poisonTimer = $PoisonTimer

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	poisonTimer.start(getP3())

func poisonTimerTimeout():
	inflictPoison(getP4())

func onCombatEnd():
	poisonTimer.stop()
