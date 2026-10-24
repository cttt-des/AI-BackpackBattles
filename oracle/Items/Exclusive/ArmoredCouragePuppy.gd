extends "res://Items/Exclusive/CouragePuppy.gd"

func _ready() -> void :
	damageSource.unsetFlag(DamageSource.Flags.CanTriggerItems)
	damageSource.unsetFlag(DamageSource.Flags.CanTriggerSpikes)
