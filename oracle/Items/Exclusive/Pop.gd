extends Weapon

const popSound = preload("res://Assets/Sound/Pop1.wav")

onready var speedPerMana: = getP("speed") / 100.0
onready var maxSpeedBonus: = getP("max") / 100.0

var previousSpeedBonus: float

func onPrepare():
	previousSpeedBonus = 0
	connectForCombat(character(), "character_mana_changed", "onManaChanged")

func onManaChanged(_amount, _event):
	var speed = min(maxSpeedBonus, speedPerMana * character().getMana())
	if speed - previousSpeedBonus != 0:
		addSpeed(speed - previousSpeedBonus)
		previousSpeedBonus = speed

func playPickupSound():
	Sound.playSound_process(popSound, 4, Util.randPitch(0.15))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(popSound, volume - 0, Util.randPitch(0.15))
