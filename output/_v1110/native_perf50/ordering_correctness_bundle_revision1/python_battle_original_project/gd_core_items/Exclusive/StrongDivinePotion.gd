extends "res://gd_core_items/Exclusive/DivinePotion.gd"

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	giveRandomBuffs(getP3())
	

func _readyInit():
	._readyInit()
	pass
