extends Item

onready var spikes: = int(getP("spikes"))
onready var heat: = int(getP("heat"))
onready var spikesNeeded: = int(getP("spikest"))
onready var heatForSpikes: = int(getP("heat2"))

var spikesAcc: = 0
var affectedItemsDict: Dictionary

func canAffect(item):
	return item.gainsStack(Stack.Spikes)

func onPrepare():
	spikesAcc = 0
	affectedItemsDict = Util.arrayAsIndexDict(getAffectedItems())
	
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")

func onSpikesChanged(amount, event):
	if amount > 0 and event.origin in affectedItemsDict:
		spikesAcc += amount
		var numProccs = spikesAcc / spikesNeeded
		if numProccs > 0:
			giveHeat(heatForSpikes * numProccs)
			spikesAcc %= spikesNeeded
			miniActivate()

func onCombatStart():
	giveSpikes(spikes)
	giveHeat(heat)
	activate()

