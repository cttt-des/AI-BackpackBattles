extends Item
var counter = 0
var activationParticles
var heatThreshold: int
var spikeRemoval: int
var heatPerSpike: int

func onPrepare():
	counter = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")


func onHeatChanged(amount, event):
	if counter < heatThreshold:
		counter += amount
		
		if counter >= heatThreshold:
			giveCritTokens(getP2())


func doCooldownEffect():
	var oppoSpikes = opponent().getSpikes()
	if oppoSpikes > 0:
		var event = opponent().loseSpikes(spikeRemoval, self)
		giveHeat(min(oppoSpikes, spikeRemoval) * heatPerSpike, event)
	activate()

func _readyInit():
	._readyInit()
	heatThreshold = getP1()
	spikeRemoval = getP3()
	heatPerSpike = getP4()
