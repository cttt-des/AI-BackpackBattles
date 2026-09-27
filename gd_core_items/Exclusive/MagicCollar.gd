extends RangerCollar
var mana

func canAffect(item):
	return item.canBeEmpowered()


func onPrepare():
	for item in affectedItems:
		connectForCombat(item, "attacked", "onWeaponAttacked")


func onWeaponAttacked(damageRes: CoreDamageResult):
	if damageRes.triggerOnHit():
		var totalChance = getChance() * character().getLucky()
		if rollChance(totalChance):
			giveMana(mana, damageRes.event)
			miniActivate()

func _readyInit():
	._readyInit()
	mana = int(getP("mana"))
