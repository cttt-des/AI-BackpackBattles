extends "res://gd_core_items/PestilenceFlask.gd"
var poisonTimer

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	poisonTimer.start(getP3())


func poisonTimerTimeout():
	inflictPoison(getP4())


func onCombatEnd():
	poisonTimer.stop()

func _readyInit():
	._readyInit()
	poisonTimer = newItemTimer("PoisonTimer", "poisonTimerTimeout", true)
