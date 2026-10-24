extends Item

onready var spikesLimit = getP("spikedam") / 100.0
onready var spikes: = int(getP("spikes"))

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	character().changeEffectSpikesLimit(spikesLimit)
	character().changeRangedSpikesLimit(spikesLimit)
	character().changeSpikesCritChancePercent(getChance() * getNumAffectedItems())

func doCooldownEffect():
	giveSpikes(spikes)
	activate()
