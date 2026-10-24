extends Cube

onready var nonOxidated = $Icon / Nonoxidated
onready var buffsNeeded: = getP("buffs")
onready var maxUses: = int(getP("max"))
var numActivations: = 0
var buffCounter: = 0

func canAffect(item):
	return item.hasCooldown()

func _ready():
	onStateChanged(maxUses)

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
				if Game.cubeAdvanced.get(affectedItem, self) == self:
					Game.cubeAdvanced[affectedItem] = self
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
	nonOxidated.modulate.a = 1.0 - numActivations / float(maxUses)
