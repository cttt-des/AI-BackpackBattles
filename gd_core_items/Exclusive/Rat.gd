extends "res://gd_core_items/Exclusive/ForestFriend.gd"
var poison: int
var blind: int

func initRat():
	damageSource = CoreDamageSource.new().setItem(self)
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
	var pitch = ctx.rng.randf_range(0.9, 1.1)


func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = ctx.rng.randf_range(0.9, 1.1)

func _readyInit():
	._readyInit()
	initRat()

