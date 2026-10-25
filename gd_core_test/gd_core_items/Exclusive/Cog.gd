extends Item

func canAffect(item):
	return item.isCrafted()


func onCombatStart():
	var numAffected = getNumAffectedItems()
	if numAffected > 0:
		giveBlock(getBlock() * numAffected)
		activate()


func onSold():
	pass

func getSellPrice():
	return 0

func _readyInit():
	._readyInit()
	pass
