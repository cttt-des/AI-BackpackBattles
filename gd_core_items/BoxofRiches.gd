extends Item
var numGems = 1
const gemOdds = [
	16, 
	8, 
	2, 
	1, 
	0.5
]

func onShopEntered():
	pass

func getGatedDescriptor(rarityOdds, numHighRolls = 0) -> CoreItemData:
	return null

func getRelatedItemHeight() -> int:
	return 50



func onGateItemRoll():
	pass

func _readyInit():
	._readyInit()
	pass
