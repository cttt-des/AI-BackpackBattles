extends Item

func _ready():
	connect("dropped", self, "onDropped")

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("replaceWithCubes", dropRes)

func replaceWithCubes(dropResult):
	var offsets = [Vector2(0, - 100), Vector2(0, 0), 
				Vector2( - 90, 50), Vector2(90, 50)]
						
	var cubes = []
	for cubeDescriptor in ItemBook.hyperCubes:
		cubes.push_back(ItemBook.generateItem(cubeDescriptor))
	
	if wasAddedToInventory(dropResult):
		inventory.removeItem(self)
		discard(false)
		
		var cells = occupiedCells.duplicate()
		for i in 4:
			Game.playerNode.add_child(cubes[i])
			cubes[i].setFaceDirectionInstant(faceDirection)
			Game.PLAYER.INVENTORY.addItemByTopLeft(cubes[i], cells[i])
			var targetPos = global_position + 0.5 * offsets[i].rotated(rotation)
			cubes[i].moveTo(targetPos, cubes[i].global_position, 0.2)
	
	else:
		Game.STORAGEBOX.removeItem(self)
		collisionShape.disabled = true
		discard()
		

		for i in 4:
			Game.playerNode.add_child(cubes[i])
			cubes[i].setFaceDirectionInstant(faceDirection)
			var targetPos = global_position + 0.5 * offsets[i].rotated(rotation)
			cubes[i].global_position = targetPos
			cubes[i].addToStorageBox(true, true, true, targetPos)
		








	
	Game.saveRunState()
	finishReplacement()

func getTextureSize() -> Vector2:
	return sprite.texture.get_size() * Vector2(2, 2) * sprite.global_scale
