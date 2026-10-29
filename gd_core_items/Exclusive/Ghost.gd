extends Item
var unhealing
var activationParticles

func onPrepare():
	character().giveUnhealing(unhealing)


func doCooldownEffect():
	var useEvents = useRandomBuffs(1)
	if useEvents != null:
		heal(getP_m("heal"), useEvents[0])
	activate()


func playPickupSound():
	# decomp Items/Exclusive/Ghost.gd:20 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.3) - 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

	# decomp Items/Exclusive/Ghost.gd:24 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.3) - 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func _readyInit():
	._readyInit()
	unhealing = getP("unhealing") / 100.0
