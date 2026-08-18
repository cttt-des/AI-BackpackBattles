extends Item

onready var activationParticles = $Icon / ActivationParticles
onready var heatThreshold: int = getP1()
onready var spikeRemoval: int = getP3()
onready var heatPerSpike: int = getP4()

var counter = 0

func onPrepare():
	counter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")

func onHeatChanged(amount, event):
	if counter < heatThreshold:
		counter += amount
		
		if counter >= heatThreshold:
			giveCritTokens(getP2())
			activationParticles.activate()

func doCooldownEffect():
	var oppoSpikes = opponent().getSpikes()
	if oppoSpikes > 0:
		var event = opponent().loseSpikes(spikeRemoval, self)
		giveHeat(min(oppoSpikes, spikeRemoval) * heatPerSpike, event)
	activate()

