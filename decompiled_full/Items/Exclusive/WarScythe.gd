extends Weapon

onready var poisonNeeded: = int(getP("poisont"))
onready var critDamage: = getP("critdam") / 100.0

func canAffect(item):
	return item.gainsStack(Stack.Poison)

func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Poison, 1)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if opponent().getPoison() >= poisonNeeded:
			opponent().losePoison(poisonNeeded, self)
			addCritChancePercent(getChance())
			addCritSeverity(critDamage)
