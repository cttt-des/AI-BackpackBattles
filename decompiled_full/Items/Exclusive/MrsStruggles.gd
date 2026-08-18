extends Item

onready var activationParticles = $ActivationParticles

func canAffect(item):
	return item.hasType(Type.Dark)

func onPrepare():
	addSpeed(getNumAffectedItems() * getP1() / 100.0)

func doCooldownEffect():
	for buff in Game.getBuffs():
		opponent().loseStacks(buff, 1, self)
	activate()
	activationParticles.activate()
