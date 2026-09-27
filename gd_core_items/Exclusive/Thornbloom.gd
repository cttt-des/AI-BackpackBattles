extends Weapon
var spikes: int
var empower: int
var damPerSpike

func onPrepare():
	connectForCombat(character(), "character_empower_changed", "onEmpowerChanged")
	connectForCombat(character(), "character_spikes_changed", "onSpikesChanged")


func onSpikesChanged(amount, _event):
	changeVaryingDamage(damPerSpike * amount)


func onEmpowerChanged(amount, event):
	if amount > 0:
		giveMaxHealth(getP_m("maxhealth") * amount, event)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveSpikes(spikes)
		
		if rollChance():
			giveEmpower(empower)
		else:
			pass

func _readyInit():
	._readyInit()
	spikes = getP("spikes")
	empower = getP("empower")
	damPerSpike = getP("damperspike")
