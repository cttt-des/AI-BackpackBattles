extends Item

const amuletColor = Color(0.470588, 0.952941, 0.2)

func _ready():
	specificDragParticles[0].self_modulate = amuletColor

func canAffect(item):
	return item.hasType(Type.Pet)

func onPrepare():
	var spikesLimit = getP("spikedam") / 100.0
	character().changeRangedSpikesLimit(spikesLimit)
	character().changeMeleeSpikesLimit(spikesLimit)

func doCooldownEffect():
	giveSpikes(getP("spikes"))
	for item in getAffectedItems():
		item.doCooldownEffect()
	onAfterEffectFinished()
	
	
