extends Bag

var itemsInside

func onPrepare():
	itemsInside = getItemsInside()
	if not getItemsInside().empty():
		connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")
	for item in itemsInside:
		item.changeCritChancePercent(getChance())
	
func onLuckyChanged(amount, event):
	var change = amount * getChance2()
	for item in itemsInside:
		item.changeCritChancePercent(change)

func canApplyEffect(toItem):
	return toItem.canDamage()
