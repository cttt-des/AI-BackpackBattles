extends Item

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func doCooldownEffect():
	inflictRandomDebuffs(1)
	activate()


func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 3

func _readyInit():
	._readyInit()
	pass
