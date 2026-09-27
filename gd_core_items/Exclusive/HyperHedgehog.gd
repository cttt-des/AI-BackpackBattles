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
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume


func spawnSpikeParticles():
	pass

func _readyInit():
	._readyInit()
	damagePerEmpower = getP("dam_empower")
	empower = int(getP("empower"))
