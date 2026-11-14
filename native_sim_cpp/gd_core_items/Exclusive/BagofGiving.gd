extends Bag
var activationParticles
var maxStamina

func canApplyEffect(toItem):
	return toItem.isClassItem()


func onPrepare():
	for item in getAffectedItemsInside():
		connectForCombat(item, "activated", "onItemInsideActivated")


func onItemInsideActivated(event):
	giveMaxStaminaTemporary(maxStamina, event)
	miniActivate()


func onAddToInventory():
	pass

func onRemoveFromInventory():
	.onRemoveFromInventory()

func onShopEntered():
	pass

func getShopPriority() -> int:
	return CoreConst.Priority.Low


func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 6


func getRelatedItemHeight() -> int:
	return 110

func _readyInit():
	._readyInit()
	maxStamina = getP("stamina")
