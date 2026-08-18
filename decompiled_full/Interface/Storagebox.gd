extends Node2D

signal pushed_all_to_storage
signal item_added
signal item_removed
signal storage_cleared

onready var area = $StorageArea
onready var box = $StorageArea / CollisionShape2D
onready var box2 = $StorageArea / CollisionShape2D2
onready var shape = box.shape
onready var shape2 = box2.shape

onready var center = $Center.global_position
onready var animation = $AnimationPlayer
onready var dustParticlesPos1 = $DustPosition1
onready var dustParticlesPos2 = $DustPosition2

const landSound = preload("res://Assets/Sound/Impact.ogg")
const dustParticlesScene = preload("res://Shader/StorageboxLandParticles.tscn")
const suggestedPositions = [
	Vector2.ZERO, Vector2(0, - 200), Vector2(0, 200), 
	Vector2( - 200, 0), Vector2(200, 0), 
	Vector2(200, - 200), Vector2(200, 200), 
	Vector2( - 200, - 200), Vector2( - 200, 200)
]

var items = []

func _ready() -> void :
	Game.STORAGEBOX = self
	Game.connect("shop_closed", self, "onShopClose")
	Game.connect("shop_opened", self, "onShopOpenFinished")
	
	
	
	Game.connect("returned_to_title", self, "deleteItems")

func getStorageRect():
	return Rect2(box.global_position - shape.extents, shape.extents * 2)

func getStorageRect2():
	return Rect2(box2.global_position - shape2.extents, shape2.extents * 2)


func hasPosition(pos):
	return getStorageRect().has_point(pos)

func isHovered():
	var pos = Game.draggedItem.global_position
	return getStorageRect().has_point(pos)


func getItems():
	return items

func getItemsAndGems() -> Array:
	var itemsAndGems = items.duplicate()
	for item in items:
		itemsAndGems.append_array(item.getGemsNoNull())
	return itemsAndGems

func getItemsAndGemsByDescriptor() -> Dictionary:
	var dict = {}
	for item in items:
		Util.dictAppend(dict, item.descriptor, item)
		for gem in item.getGemsNoNull():
			Util.dictAppend(dict, gem.descriptor, gem)
	return dict

func addItem(item):
	items.push_back(item)
	if items.size() >= 30:
		SteamHelper.unlockAchievement("FullStorage")
	
	emit_signal("item_added", item)




func removeItem(item):
	items.erase(item)
	
	emit_signal("item_removed", item)
	




func onShopClose():
	for item in items:
		item.makeNonRigidBody()
		Util.reparent(item, self)

func onShopOpenFinished():
	for item in items:
		item.makeRigidBody()
		

func deleteItems():
	
	for item in items:
		
		item.discard()
	items.clear()
	emit_signal("storage_cleared")

func pushAllToStorage():
	var nonBagItems = []
	for item in Game.PLAYER.INVENTORY.getItems():
		if not item.isBag():
			nonBagItems.push_back(item)
	pushItemsToStorage(nonBagItems)
	emit_signal("pushed_all_to_storage")
	
func pushItemsToStorage(itemList):
	var pos = center
	var itemI = 0
	for item in itemList:
		Game.PLAYER.INVENTORY.removeItem(item)
		item.pushToStorage(pos)
		pos.y -= 50
		if pos.y < - 200:
			pos.y = center.y + 300
		
		if itemI % 2 == 0:
			pos.x = center.x - 50
		else:
			pos.x = center.x + 50
		itemI += 1

func getSuggestedPosition(itemI):
	if itemI >= suggestedPositions.size(): return center
	return center + suggestedPositions[itemI] * 0.7

func shake(collisionPoint, strong: bool):
	if collisionPoint.y > 980:
		if strong:
			animation.play("ShakeCenterStrong", 0.1)
		else:
			animation.play("ShakeCenter", 0.1)
	elif collisionPoint.x < 1000:
		if strong:
			animation.play("ShakeLeftStrong", 0.1)
		else:
			animation.play("ShakeLeft", 0.1)
	else:
		if strong:
			animation.play("ShakeRightStrong", 0.1)
		else:
			animation.play("ShakeRight", 0.1)
	
func land():
	Sound.playSound(landSound, 0, Util.randPitch(0.1) + 0.1)
	animation.play(str("Landing", Util.rng.randi_range(1, 3)))
	ObjectPool.particleOneShot(dustParticlesScene, dustParticlesPos1)
	ObjectPool.particleOneShot(dustParticlesScene, dustParticlesPos2)

func checkIfItemIsInStorageArea(item):
	if not area.overlaps_body(item):
		
		if not item in area.exitTimes:
			area.onBodyExited(item)































