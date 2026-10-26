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
	# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.1)（=randf_range(0.9, 1.1)，
	#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
	#   后此覆写生效，抽面必须与原版一致）。
	ctx.rng.randf_range(0.9, 1.1)


func spawnSpikeParticles():
	pass

func _readyInit():
	._readyInit()
	damagePerEmpower = getP("dam_empower")
	empower = int(getP("empower"))
