extends Item
var mana

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func canAffect(item):
	return item.gainsStack(CoreConst.Stack.Mana)


func onCombatStart():
	giveMana(mana)
	activate()


func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent(CoreConst.EventType.Mana, getChance())
		

func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 4

func _readyInit():
	._readyInit()
	mana = getP("mana")
