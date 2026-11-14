extends "res://gd_core_items/Exclusive/Hedgehog.gd"
var damagePerEmpower
var empower

func onHPLow(event):
	.onHPLow(event)
	giveEmpower(empower, event)


func doCooldownEffect():
	var dam = descriptor.minDam
	dam += character().getSpikes() * damagePerSpike
	dam += character().getEmpower() * damagePerEmpower
	var res = dealEffectDamage(dam)
	activate(res)


func playPickupSound():
	# decomp Items/Exclusive/HyperHedgehog.gd:23 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume


	# decomp Items/Exclusive/HyperHedgehog.gd:27 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func spawnSpikeParticles():
	pass

func _readyInit():
	._readyInit()
	damagePerEmpower = getP("dam_empower")
	empower = int(getP("empower"))
