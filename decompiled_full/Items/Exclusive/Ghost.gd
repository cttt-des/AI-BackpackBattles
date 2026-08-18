extends Item

const pickupSound = preload("res://Assets/Sound/Ghost1.ogg")
const dropSound = preload("res://Assets/Sound/Ghost2.ogg")

onready var unhealing: = getP("unhealing") / 100.0
onready var activationParticles = $Icon / ActivationParticles

func onPrepare():
	character().giveUnhealing(unhealing)

func doCooldownEffect():
	var useEvents = useRandomBuffs(1)
	if useEvents != null:
		heal(getP_m("heal"), useEvents[0])
		activationParticles.activate()
	activate()

func playPickupSound():
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.3) - 0.1)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.3) - 0.1)
