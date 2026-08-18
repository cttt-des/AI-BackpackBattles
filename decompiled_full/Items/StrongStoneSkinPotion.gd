extends "res://Items/StoneSkinPotion.gd"

onready var spikes: = int(getP("spikes"))

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	giveStacksTemporary(character(), Game.EventType.Spikes, 
		spikes, getP_m("dur"), triggerEvent)
