extends Item

onready var critDam: = getP1() / 100.0
onready var blockRemoval: = int(getP2())

func canAffect(item):
	return item.canBeEmpowered()

func canAffect_secondary(item):
	return item.canActivate()
	
func onPrepare():
	for item in getAffectedItems():
		item.addCritSeverity(critDam)
		
		connectForCombat(item, "pre_deal_damage_late", "onItemAttacks")

	for item in getAffectedItems(Affected.Secondary):
		connectForCombat(item, "activated", "onItemActivated")

func onItemAttacks(damageRes: DamageResult):
	if damageRes.wasCriticalHit():
		damageRes.damageSource.origin.removeBlock(blockRemoval)

func onItemActivated(event):
	if rollChance():
		giveLucky(1)
		miniActivate()
