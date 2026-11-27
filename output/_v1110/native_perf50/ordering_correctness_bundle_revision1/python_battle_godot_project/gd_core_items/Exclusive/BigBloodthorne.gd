extends "res://gd_core_items/Greatsword.gd"
var damPerVampOrSpike
var regenNeeded
var vampirism
var spikes

func onPrepare():
	.onPrepare()
	connectForCombat(character(), "character_vampirism_changed", "onVampirismChanged")
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")


func onVampirismChanged(amount, _event):
	changeVaryingDamage(amount * damPerVampOrSpike)


func onSpikesChanged(amount, _event):
	changeVaryingDamage(amount * damPerVampOrSpike)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if character().getRegeneration() >= regenNeeded:
			useRegeneration(regenNeeded)
			giveVampirism(vampirism)
			giveSpikes(spikes)

func _readyInit():
	._readyInit()
	damPerVampOrSpike = getP("dam")
	regenNeeded = int(getP("regent"))
	vampirism = int(getP("vampirism"))
	spikes = int(getP("spikes"))
