extends Item

onready var snowballDescriptor = ItemBook.getDescriptor("Snowball")
const snowParticles = preload("res://Items/Exclusive/Particles/SnowParticles.tscn")

func _ready():
	connect("dropped", self, "onDropped")

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("replaceWithSnowballs", dropRes)

func replaceWithSnowballs(dropResult):
	var snowball1 = ItemBook.generateItem(snowballDescriptor)
	var snowball2 = ItemBook.generateItem(snowballDescriptor)
	
	if wasAddedToInventory(dropResult):
		var cells = occupiedCells.duplicate()
		Game.PLAYER.INVENTORY.replaceItem(self, snowball1)
		cells.erase(snowball1.occupiedCells[0])
		Game.playerNode.add_child(snowball2)
		Game.PLAYER.INVENTORY.addItemByTopLeft(snowball2, cells[0])
	else:
		Game.STORAGEBOX.removeItem(self)
		collisionShape.disabled = true
		discard()
		var offsets = [Vector2(0, - 20), Vector2(0, 20)]
		for snowballI in 2:
			var snowball = [snowball1, snowball2][snowballI]
			Game.playerNode.add_child(snowball)
			var targetPos = global_position + offsets[snowballI].rotated(rotation)
			snowball.global_position = targetPos
			snowball.addToStorageBox(true, true, true, targetPos)
	
	var particles = ObjectPool.particleOneShot(snowParticles, get_parent())
	var particlePos = global_position
	match getFaceDirection():
		FaceDirection.DOWN:
			particlePos.y += 32
		FaceDirection.UP:
			particlePos.y -= 32
	particles.global_position = particlePos
	
	Game.saveRunState()
	finishReplacement()
	
func getRecipeDescriptor():
	return snowballDescriptor
