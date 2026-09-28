extends Item
var snowballDescriptor

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		ctx.defer(self, "replaceWithSnowballs", [dropRes])


func replaceWithSnowballs(dropResult):
	pass

func getRecipeDescriptor():
	return snowballDescriptor

func _readyInit():
	._readyInit()
	snowballDescriptor = ctx.item_book.getDescriptor("Snowball")
	connect("dropped", self, "onDropped")

