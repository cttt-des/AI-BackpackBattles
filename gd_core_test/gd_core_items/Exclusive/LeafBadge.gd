extends Item

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func canAffect(item):
	return item.canDamage()


func onPrepare():
	if not getAffectedItems().empty():
		connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")
	

func onLuckyChanged(amount, _event):
	for item in getAffectedItems():
		item.changeCritChancePercent(amount * getChance())


func doCooldownEffect():
	giveLucky(1)
	activate()


func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 3

func _readyInit():
	._readyInit()
	pass
