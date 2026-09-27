extends Card
var spadesParticles
var luck
var spikes

func cardSecondaryEffectActive():
	return chainPosition % 2 == 1


func doRevealEffect():
	giveCritTokens(1)
	
	if cardSecondaryEffectActive():
		giveLucky(luck)
		giveSpikes(spikes)
	
	activate()

func _readyInit():
	._readyInit()
	luck = int(getP("luck"))
	spikes = int(getP("spikes"))
