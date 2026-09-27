extends Item
var activationsLeft: int
var spikes
var uses
var spikeSpeed

func onPrepare():
	activationsLeft = uses
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")


func doCooldownEffect():
	
	stun(getP_m("dur_stun"))
	giveSpikes(spikes)
	activationsLeft -= 1
	if activationsLeft == 0:
		onAfterEffectFinished()
	else:
		activate()


func onSpikesChanged(amount, event):
	addSpeed(spikeSpeed * amount)

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
	uses = int(getP("max"))
	spikeSpeed = getP("speed") / 100.0
