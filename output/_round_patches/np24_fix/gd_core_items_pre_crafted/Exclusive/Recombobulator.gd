extends Item
export var stable = true
var idleAnimation

func canAffect(item):
	return not item.isBag() and (item.canStartNewRecipe() or item.bondedBaseItem == self)


func cacheAffectedItemsForCombat():
	.cacheAffectedItemsForCombat()
	var arr = getItemsInAffectedCells_cached()
	cachedAffectedItems[CoreConst.Affected.Primary] = arr




func readyToFuse() -> bool:
	if stable:
		return not bondedIngredients.empty()
	else:
		return bondedBaseItem == null


func onFusingFinished(validBonds):
	.onFusingFinished(validBonds)

func reactToDropResult(dropResult):
	.reactToDropResult(dropResult)
	if wasAddedToInventory(dropResult):
		pass


func doCooldownEffect():
	giveRandomBuffs(1)
	cleanseRandomDebuffs(1)
	activate()


func getCounterValue() -> int:
	return getAffectedGoldValue()

func _readyInit():
	._readyInit()
	pass
