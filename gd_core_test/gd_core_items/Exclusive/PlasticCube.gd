extends Cube
var spikes

func canAffect(item):
	return item.hasCooldown()


func doCooldownEffect():
	deactivateCooldown()
	
	var affectedItem = getFirstAffectedItem()
	if affectedItem != null:
		if not affectedItem in ctx.cube_advanced:
			ctx.cube_advanced[affectedItem] = self
			affectedItem.advanceCooldownPercent(cdAdvance)
		else:
			affectedItem.advanceCooldownPercent(cdAdvance * penaltyFactor)
	
	giveSpikes(spikes)
	onAfterEffectFinished()

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
