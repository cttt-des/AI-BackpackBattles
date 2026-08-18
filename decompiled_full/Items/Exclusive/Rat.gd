extends "res://Items/Exclusive/ForestFriend.gd"

const pickupSound = preload("res://Assets/Sound/Rat1.wav")
const dropSound = preload("res://Assets/Sound/Rat2.wav")

var poison: int
var blind: int

func _ready() -> void :
	initRat()

func initRat():
	damageSource = DamageSource.new().setItem(self)
	poison = int(getP("poison"))
	blind = int(getP("blind"))

func doCooldownEffect():
	var dam = descriptor.minDam
	var res = dealEffectDamage(dam)
	if rollChance():
		inflictPoison(poison, res.event)
	if rollChance2():
		inflictBlind(blind, res.event)
		
	activate(res)

func playPickupSound():
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound_process(pickupSound, - 6, pitch)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = Util.rng.randf_range(0.9, 1.1)
	Sound.playSound(pickupSound, volume - 6, pitch)
