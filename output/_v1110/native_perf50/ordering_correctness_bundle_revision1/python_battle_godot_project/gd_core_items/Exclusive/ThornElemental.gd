extends Item
var spikesLimit
var spikes

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func onPrepare():
	character().changeEffectSpikesLimit(spikesLimit)
	character().changeRangedSpikesLimit(spikesLimit)
	character().changeSpikesCritChancePercent(getChance() * getNumAffectedItems())


func doCooldownEffect():
	giveSpikes(spikes)
	activate()

func _readyInit():
	._readyInit()
	spikesLimit = getP("spikedam") / 100.0
	spikes = int(getP("spikes"))
