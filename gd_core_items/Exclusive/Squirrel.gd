extends "res://gd_core_items/Exclusive/ForestFriend.gd"

func doCooldownEffect():
	stealRandomBuff(1)
	activate()


func playPickupSound():
	var pitch = ctx.rng.randf_range(0.9, 1.1)


func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = ctx.rng.randf_range(0.9, 1.1)
	

func _readyInit():
	._readyInit()
	pass
