extends "res://gd_core_items/StoneSkinPotion.gd"
var spikes

func onTriggerPotion(triggerEvent = null):
	.onTriggerPotion(triggerEvent)
	giveStacksTemporary(character(), CoreConst.EventType.Spikes, 
		spikes, getP_m("dur"), triggerEvent)

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
