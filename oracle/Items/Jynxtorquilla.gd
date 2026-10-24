extends Item

const activationParticles = preload("res://Items/Particles/JynxActivationParticles.tscn")

var numActivations: int

onready var speedBonus = getP("speed") / 100.0
onready var maxActivations: = int(getP("max"))

func canAffect(item):
	return item.hasCooldown()

func onPrepare():
	numActivations = 0

func doCooldownEffect():
	if numActivations < maxActivations:
		for item in getAffectedItems():
			
			item.addSpeed(speedBonus)
			
		numActivations += 1
		ObjectPool.particleOneShot(activationParticles, self)
	
	if opponent().getLucky() > 0:
		removeLucky(getP3())
	
	activate()
