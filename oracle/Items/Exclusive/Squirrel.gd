extends "res://Items/Exclusive/ForestFriend.gd"

const pickupSound = preload("res://Assets/Sound/Squirrel.wav")
const dropSound = preload("res://Assets/Sound/Squirrel2.wav")

func doCooldownEffect():
	stealRandomBuff(1)
	activate()

func playPickupSound():
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound_process(pickupSound, - 6, pitch)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = Util.rng.randf_range(0.9, 1.1)
	
	Sound.playSound(pickupSound, volume - 6, pitch)
