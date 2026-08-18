extends Item

onready var goldValue: = int(getP("goldvalue"))

var filters = (ItemBook.Filter.OtherClasses + 
					ItemBook.Filter.Gated + 
					ItemBook.Filter.Crafted + 
					ItemBook.Filter.AnyRarity)

func onAddToInventory():
	ItemBook.updateClass(self)

func onAddedToStorageBox():
	ItemBook.updateClass(self)




func discard(discardGems = true):
	.discard(discardGems)
	ItemBook.updateClass(self)

func doCooldownEffect():
	giveBlock()
	activate()

func onShopEntered():
	var goldToSpend = goldValue
	while goldToSpend > 0:
		var giftedDescriptor
		if Util.flip(0.4):
			giftedDescriptor = ItemBook.getDescriptor("Stone")
		else:
			giftedDescriptor = getItemsMaxCost(goldToSpend).pick_random()
		
		goldToSpend -= giftedDescriptor.price
		
		var item = ItemBook.generateItem(giftedDescriptor)
		Game.playerNode.add_child(item)
		item.global_position = global_position
		item.pushToStorage(Game.STORAGEBOX.center + Util.randInBox(100, 100))
	
	activate()
	Game.saveRunState()

func getItemsMaxCost(maxCost):
	var candidates = []
	for descr in ItemBook.descriptorList:
		if (descr.price <= maxCost and 
			ItemBook.canBeGenerated(descr, filters)):
			
			candidates.push_back(descr)
	
	return candidates

func getRelatedItems():
	return getItemsMaxCost(goldValue)

func getRelatedItemColumns() -> int:
	return 4
