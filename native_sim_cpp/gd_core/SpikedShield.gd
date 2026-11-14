extends Shield
var spikesGiven: int
var spikes
var maxSpikes

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

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
	maxSpikes = int(getP("maxspikes"))
