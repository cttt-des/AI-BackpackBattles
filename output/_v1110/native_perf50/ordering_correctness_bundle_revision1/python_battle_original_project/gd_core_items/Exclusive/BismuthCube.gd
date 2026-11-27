extends Cube
var numActivations: = 0
var buffCounter: = 0
var nonOxidated
var buffsNeeded
var maxUses

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	setState(0)
	buffCounter = 0
	affectedItem = getFirstAffectedItem()
	connectToCharacterBuffs("onBuffsChanged")


func onBuffsChanged(amount, event):
	var remainingUses = maxUses - numActivations
	if remainingUses == 0: return
	
	if amount > 0:
		var numProccs: = 0
		buffCounter += amount
		while buffCounter > buffsNeeded:
			numProccs += 1
			buffCounter -= buffsNeeded
		
		numProccs = min(remainingUses, numProccs)
		
		if numProccs > 0:
			if affectedItem != null:
				if ctx.cube_advanced.get(affectedItem, self) == self:
					ctx.cube_advanced[affectedItem] = self
					affectedItem.advanceCooldownSeconds(cdAdvance * numProccs)
				else:
					affectedItem.advanceCooldownSeconds(cdAdvance * numProccs * penaltyFactor)
				
			giveRandomBuffs(numProccs)
			setState(numActivations + numProccs)
			miniActivate()


func onShopEntered():
	onStateChanged(maxUses)


func onStateChanged(_numActivations):
	numActivations = _numActivations

func _readyInit():
	._readyInit()
	buffsNeeded = getP("buffs")
	maxUses = int(getP("max"))
	onStateChanged(maxUses)

