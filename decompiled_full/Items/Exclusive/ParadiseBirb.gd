extends Item

const activationParticles = preload("res://Items/Exclusive/Particles/ParadiseBirbActivationParticles.tscn")
const pickupSound = preload("res://Assets/Sound/Birb1.ogg")
const dropSound = preload("res://Assets/Sound/Birb2.ogg")

var numActivations: int

onready var speedBonus = getP("speed") / 100.0
onready var maxActivations: = int(getP("max"))
onready var bonusHeal = getP("healamp") / 100.0

func canAffect(item):
	return (item.hasCooldown() or item.gainsBuffs() or item.canHealOrLifesteal())

func onPrepare():
	numActivations = 0

func doCooldownEffect():
	if numActivations < maxActivations:
	
		for item in getAffectedItems():
			item.addSpeed(speedBonus)
			item.changeAmplificiationChancePercent_allBuffs(getChance())
			item.changeHealAmp(bonusHeal)
		
		numActivations += 1
		ObjectPool.particleOneShot(activationParticles, self)
		
		if numActivations == maxActivations:
			onAfterEffectFinished()
		else:
			activate()

func playPickupSound():
	var pitch = Util.rng.randf_range(0.8, 1.0)
	Sound.playSound_process(pickupSound, - 7, pitch)

func playDropSound(volume = 0):
	volume += impactSoundVolume
	var pitch = Util.rng.randf_range(0.8, 1.0)
	Sound.playSound(dropSound, volume - 9, pitch)
