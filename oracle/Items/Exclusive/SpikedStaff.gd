extends Weapon

onready var manaCost = getP("mana")
onready var empower = getP("empower")
onready var spikes = getP("spikes")

func onPreDealDamage_early(damageRes: DamageResult):
	var event = tryUseMana(manaCost)
	if event != null:
		giveEmpower(empower, event)
		if character().isBattleRaging():
			giveSpikes(spikes, event)
