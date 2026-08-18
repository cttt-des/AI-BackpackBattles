extends "res://Items/Exclusive/DivinePotion.gd"

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	giveRandomBuffs(getP3())
	
