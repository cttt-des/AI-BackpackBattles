extends Card

onready var spadesParticles = $SpadesParticles
onready var luck: = int(getP("luck"))
onready var spikes: = int(getP("spikes"))

func cardSecondaryEffectActive():
	return chainPosition % 2 == 1

func doRevealEffect():
	giveCritTokens(1)
	
	if cardSecondaryEffectActive():
		giveLucky(luck)
		giveSpikes(spikes)
		spadesParticles.activate()
	
	activate()
