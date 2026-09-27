extends Item

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("identifyAmulet", dropRes)


func identifyAmulet(dropResult):
	pass

func getRelatedItemColumns() -> int:
	return 4


func getRelatedItemHeight() -> int:
	return 100

func _readyInit():
	._readyInit()
	connect("dropped", self, "onDropped")

