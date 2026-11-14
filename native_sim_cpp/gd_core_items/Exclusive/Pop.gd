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
	# decomp Items/Exclusive/Pop.gd:21 Sound.playSound_process(popSound, 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

	# decomp Items/Exclusive/Pop.gd:25 Sound.playSound(popSound, volume - 0, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
	ctx.rng.randf_range(0.9, 1.1)
func _readyInit():
	._readyInit()
	speedPerMana = getP("speed") / 100.0
	maxSpeedBonus = getP("max") / 100.0
