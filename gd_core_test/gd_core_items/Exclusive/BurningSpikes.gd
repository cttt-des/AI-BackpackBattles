extends Item
var spikesAcc: = 0
var affectedItemsDict: Dictionary
var spikes
var heat
var spikesNeeded
var heatForSpikes

func canAffect(item):
	return item.gainsStack(CoreConst.Stack.Spikes)


func onPrepare():
	spikesAcc = 0
	affectedItemsDict = ctx.util.arrayAsIndexDict(getAffectedItems())
	
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

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
	heat = int(getP("heat"))
	spikesNeeded = int(getP("spikest"))
	heatForSpikes = int(getP("heat2"))
