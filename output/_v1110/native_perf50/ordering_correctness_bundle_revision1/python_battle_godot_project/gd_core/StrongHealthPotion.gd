extends "res://gd_core_items/HealthPotion.gd"

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	giveRegeneration(getP4(), triggerEvent)


func getTriggerPriority() -> int:
	return CoreConst.Priority.High + 1

func _readyInit():
	._readyInit()
	pass
