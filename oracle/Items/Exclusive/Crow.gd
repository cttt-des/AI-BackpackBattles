extends Item

const activationParticles = preload("res://Items/Exclusive/Particles/CrowActivationParticles.tscn")
const pickupSound = preload("res://Assets/Sound/Crow1.wav")
const dropSound = preload("res://Assets/Sound/Crow2.wav")

var numActivations: int

onready var speedBonus = getP("speed") / 100.0
onready var maxActivations: = int(getP("max"))
onready var luck: = int(getP("luck"))

func canAffect(item):
	return item.hasCooldown() or item.inflictsDebuffs()

func onPrepare():
	numActivations = 0

func doCooldownEffect():
	if numActivations < maxActivations:
		for item in getAffectedItems():
			
			item.addSpeed(speedBonus)
			item.changeAmplificiationChancePercent_allDebuffs(getChance())
			
		numActivations += 1
		ObjectPool.particleOneShot(activationParticles, self)
	
	var luckToRemove = min(luck, opponent().getLucky())
	if luckToRemove > 0:
		stealStack(Game.EventType.Lucky, luckToRemove)
	
	activate()

func playPickupSound():
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))
