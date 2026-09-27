extends Item
var goldValue

func onAddToInventory():
	pass

func onAddedToStorageBox():
	pass

func discard(discardGems = true):
	.discard(discardGems)

func doCooldownEffect():
	giveBlock()
	activate()


func onShopEntered():
	pass

func getItemsMaxCost(maxCost):
	pass

func getRelatedItems():
	return getItemsMaxCost(goldValue)


func getRelatedItemColumns() -> int:
	return 4

func _readyInit():
	._readyInit()
	goldValue = int(getP("goldvalue"))
