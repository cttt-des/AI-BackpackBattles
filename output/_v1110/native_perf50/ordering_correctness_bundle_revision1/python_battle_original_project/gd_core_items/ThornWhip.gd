extends Weapon

func onPrepare():
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveSpikes(1)


func onSpikesChanged(amount, _event):
	changeVaryingDamage(getP1() * amount)

func _readyInit():
	._readyInit()
	pass
