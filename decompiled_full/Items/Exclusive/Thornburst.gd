extends Item

onready var spikes: = int(getP("spikes"))
onready var uses: = int(getP("max"))
onready var spikeSpeed: = getP("speed") / 100.0

var activationsLeft: int

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
