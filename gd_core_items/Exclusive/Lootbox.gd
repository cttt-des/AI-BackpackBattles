extends Item
const OFFSET = 50.0
var itemValue

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("generateItems", dropRes)


func generateItems(dropResult):
	pass

func _readyInit():
	._readyInit()
	itemValue = int(getP("gold"))
	connect("dropped", self, "onDropped")

