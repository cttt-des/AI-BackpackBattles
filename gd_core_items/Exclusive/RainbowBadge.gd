extends Item

func onAddToInventory():
	pass

func onRemoveFromInventory():
	pass

func doCooldownEffect():
	for buff in CoreConst.getBuffs():
		giveStacks(character(), buff, 1)
	onAfterEffectFinished()


func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 6


func getRelatedItemHeight() -> int:
	return 100

func _readyInit():
	._readyInit()
	pass
