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
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume
	# ★ kernel_r2c 移植补抽：原版 Sound.playSound(..., Util.randPitch(0.3) - 0.1)——
	#   randPitch(0.3)=randf_range(0.7, 1.3)（Util.gd:685-686）1 抽，-0.1 为纯音效
	#   后处理。转译期随音效行被剥，链消耗丢失。
	ctx.rng.randf_range(0.7, 1.3)

func _readyInit():
	._readyInit()
	unhealing = getP("unhealing") / 100.0
