extends Item

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func onCombatStart():
	giveHeat(getP1())
	consume()


func onShopEntered():
	pass

func getRelatedItems():
	pass

func _readyInit():
	._readyInit()
	pass
