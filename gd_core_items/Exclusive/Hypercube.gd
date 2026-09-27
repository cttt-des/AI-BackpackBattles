extends Item

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("replaceWithCubes", dropRes)


func replaceWithCubes(dropResult):
	pass

func getTextureSize() -> Vector2:
	return Vector2.ZERO

func _readyInit():
	._readyInit()
	connect("dropped", self, "onDropped")

