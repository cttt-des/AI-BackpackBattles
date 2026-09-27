extends Item
var active: bool
var salesChance
var goldCost

func getData():
	return active


func setData(data):
	active = data


func onSwitchToCombat():
	active = false


func onShopEntered():
	pass

func onSaleRoll(_item):
	pass

func onSaleRoll_storage(_item):
	onSaleRoll(_item)


func getGatedDescriptor(rarity):
	pass

func onGateItemRoll():
	if active:
		.onGateItemRoll()


func onGateItemRoll_storage():
	onGateItemRoll()

func _readyInit():
	._readyInit()
	salesChance = getP("sales") / 100.0
	goldCost = int(getP("gold"))
