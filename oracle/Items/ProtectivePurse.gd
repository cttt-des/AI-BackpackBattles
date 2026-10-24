extends Bag

func onCombatStart():
	var totalBlock = getBlock()
	if isTypeInInventory(ItemBook.bagtacularDescriptor):
		totalBlock += ItemBook.bagtacularDescriptor.getP("block")
	
	giveBlock(totalBlock)
	activate()
