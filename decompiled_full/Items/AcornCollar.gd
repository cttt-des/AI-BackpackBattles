extends RangerCollar

func canAffect(item):
	return item.canDamage()

func onPrepare():
	if not affectedItems.empty():
		connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")

func onLuckyChanged(amount, _event):
	for item in affectedItems:
		item.changeCritChancePercent(amount * getChance())
