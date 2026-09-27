extends Item
const amuletColor = Color(0.470588, 0.952941, 0.2)

func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func onPrepare():
	var spikesLimit = getP("spikedam") / 100.0
	character().changeRangedSpikesLimit(spikesLimit)
	character().changeMeleeSpikesLimit(spikesLimit)


func doCooldownEffect():
	giveSpikes(getP("spikes"))
	for item in getAffectedItems():
		item.doCooldownEffect()
	onAfterEffectFinished()
	
	

func _readyInit():
	._readyInit()
	pass

