extends Shield

var spikesGiven: int
onready var spikes: = int(getP("spikes"))
onready var maxSpikes: = int(getP("maxspikes"))

func onPrepare():
	spikesGiven = 0

func beforeBlock():
	.beforeBlock()
	var spikesLeft = maxSpikes - spikesGiven
	if spikesLeft > 0:
		var spikesToGive = min(spikesLeft, spikes)
		spikesGiven += spikesToGive
		giveSpikes(spikesToGive)

func afterBlock():
	drainStamina(getP2(), blockedDamageRes.event)
	activate()
