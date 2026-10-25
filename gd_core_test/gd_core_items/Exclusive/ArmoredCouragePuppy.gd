extends "res://gd_core_items/Exclusive/CouragePuppy.gd"

func _readyInit():
	._readyInit()
	damageSource.unsetFlag(CoreDamageSource.Flags.CanTriggerItems)
	damageSource.unsetFlag(CoreDamageSource.Flags.CanTriggerSpikes)
