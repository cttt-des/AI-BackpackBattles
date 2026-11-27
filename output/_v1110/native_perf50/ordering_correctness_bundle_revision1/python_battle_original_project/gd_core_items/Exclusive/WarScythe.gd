extends Weapon
var poisonNeeded
var critDamage

func canAffect(item):
	return item.gainsStack(CoreConst.Stack.Poison)


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Poison, 1)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if opponent().getPoison() >= poisonNeeded:
			opponent().losePoison(poisonNeeded, self)
			addCritChancePercent(getChance())
			addCritSeverity(critDamage)

func _readyInit():
	._readyInit()
	poisonNeeded = int(getP("poisont"))
	critDamage = getP("critdam") / 100.0
