extends "res://Items/HealthPotion.gd"

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	giveRegeneration(getP4(), triggerEvent)

func getTriggerPriority() -> int:
	return Priority.High + 1
