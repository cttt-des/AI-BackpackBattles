extends Bag
var activeParticles
var activationParticles
var requiredItems

func canApplyEffect(toItem):
	return toItem.getRarity() >= CoreConst.Rarity.Godly


func onShopEntered():
	pass

func onAffectedItemInsideAdded(_item):
	if getNumAffectedInside() == requiredItems:
		pass



func onItemRemoved(item):
	.onItemRemoved(item)
	if not conditionFulfilled():
		pass


func conditionFulfilled() -> bool:
	return getNumAffectedInside() >= requiredItems





func onRemoveFromInventory():
	pass


func onAddToInventory():
	if conditionFulfilled():
		pass


func discard(withGems = true):
	.discard(withGems)
	

func _readyInit():
	._readyInit()
	requiredItems = getP("insideitems")
