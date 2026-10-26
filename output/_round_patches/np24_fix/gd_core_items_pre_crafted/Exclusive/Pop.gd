extends Weapon
var previousSpeedBonus: float
var speedPerMana
var maxSpeedBonus

func onPrepare():
	previousSpeedBonus = 0
	connectForCombat(character(), "character_mana_changed", "onManaChanged")


func onManaChanged(_amount, _event):
	var speed = min(maxSpeedBonus, speedPerMana * character().getMana())
	if speed - previousSpeedBonus != 0:
		addSpeed(speed - previousSpeedBonus)
		previousSpeedBonus = speed


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume
	# ★ kernel_r2c 移植补抽：原版此行含 Util.randPitch(0.15)（=randf_range(0.85, 1.15)，
	#   Util.gd:685-686），转译期随音效行被剥——链消耗丢失（activate() 虚分发
	#   后此覆写生效，抽面必须与原版一致）。
	ctx.rng.randf_range(0.85, 1.15)

func _readyInit():
	._readyInit()
	speedPerMana = getP("speed") / 100.0
	maxSpeedBonus = getP("max") / 100.0
