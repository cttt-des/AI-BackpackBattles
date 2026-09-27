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

func _readyInit():
	._readyInit()
	speedPerMana = getP("speed") / 100.0
	maxSpeedBonus = getP("max") / 100.0
