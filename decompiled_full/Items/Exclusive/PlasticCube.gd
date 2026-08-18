extends Cube

onready var spikes: = int(getP("spikes"))

func canAffect(item):
	return item.hasCooldown()

func doCooldownEffect():
	deactivateCooldown()
	
	var affectedItem = getFirstAffectedItem()
	if affectedItem != null:
		if not affectedItem in Game.cubeAdvanced:
			Game.cubeAdvanced[affectedItem] = self
			affectedItem.advanceCooldownPercent(cdAdvance)
		else:
			affectedItem.advanceCooldownPercent(cdAdvance * penaltyFactor)
	
	giveSpikes(spikes)
	onAfterEffectFinished()
