extends "res://Items/Exclusive/Hedgehog.gd"

const hyperActivationParticles = preload("res://Items/Exclusive/Particles/HyperHedgehogActivationParticles.tscn")

const pickupSound = preload("res://Assets/Sound/Charge1.ogg")
const dropSound = preload("res://Assets/Sound/Charge2.ogg")

onready var damagePerEmpower = getP("dam_empower")
onready var empower: = int(getP("empower"))

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
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))

func spawnSpikeParticles():
	ObjectPool.particleOneShot(hyperActivationParticles, sprite)
