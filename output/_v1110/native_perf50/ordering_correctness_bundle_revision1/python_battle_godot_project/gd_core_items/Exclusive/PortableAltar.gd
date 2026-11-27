extends Bag
const valueFactor = 1.0

func canLockBag():
	return true


func showBagBorderForItem(item):
	return not item.isBag()


func onCombatStart():
	giveEmpower(getP("empower"))
	activate()




func onRecipesUpdated():
	if ownerType != CoreConst.Owner.PlayerInventory: return
	if fusing: return
	
	if locked or not placed:
		for bonded in bondedIngredients:
			bonded.removeBondedBaseItem()
		removeAllIngredients()
		return
	
	for item in getItemsInside():
		if item.canStartNewRecipe():
			createBondVisual(item)
			updateBondVisuals()
			item.addToBaseItem(self)


func readyToFuse() -> bool:
	return not bondedIngredients.empty()


func onFusingFinished(validBonds):
	.onFusingFinished(validBonds)

func getCounterValue() -> int:
	var gold = 0
	for item in bondedIngredients:
		gold += item.getPrice()
	return gold

func _readyInit():
	._readyInit()
	pass
