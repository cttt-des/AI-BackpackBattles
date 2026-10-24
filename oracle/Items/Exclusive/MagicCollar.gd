extends RangerCollar

onready var mana: = int(getP("mana"))

func canAffect(item):
	return item.canBeEmpowered()

func onPrepare():
	for item in affectedItems:
		connectForCombat(item, "attacked", "onWeaponAttacked")

func onWeaponAttacked(damageRes: DamageResult):
	if damageRes.triggerOnHit():
		var totalChance = getChance() * character().getLucky()
		if rollChance(totalChance):
			giveMana(mana, damageRes.event)
			miniActivate()
