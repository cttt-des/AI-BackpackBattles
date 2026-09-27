extends Weapon
var regenNeeded
var vampirism
var spikes

func onPrepare():
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")


func onVampirismChanged(amount, _event):
	changeVaryingDamage(amount)


func onSpikesChanged(amount, _event):
	changeVaryingDamage(amount)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		var numRegen = character().getRegeneration()
		if numRegen >= regenNeeded:
			var event = useRegeneration(regenNeeded)
			giveVampirism(vampirism, event)
			giveSpikes(spikes, event)

func _readyInit():
	._readyInit()
	regenNeeded = int(getP1())
	vampirism = int(getP2())
	spikes = int(getP3())
