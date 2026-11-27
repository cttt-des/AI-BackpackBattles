extends Weapon
var manaCost
var empower
var spikes

func onPreDealDamage_early(damageRes: CoreDamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		giveEmpower(empower, event)
		if character().isBattleRaging():
			giveSpikes(spikes, event)

func _readyInit():
	._readyInit()
	manaCost = getP("mana")
	empower = getP("empower")
	spikes = getP("spikes")
