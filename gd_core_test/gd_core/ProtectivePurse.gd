extends Bag

func onCombatStart():
	var totalBlock = getBlock()
	if isTypeInInventory(ctx.item_book.getDescriptor("Bagtacular")):
		totalBlock += ctx.item_book.getDescriptor("Bagtacular").getP("block")
	
	giveBlock(totalBlock)
	activate()

func _readyInit():
	._readyInit()
	pass
