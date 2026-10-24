extends Item
class_name Bag

onready var bagTilemap = $Icon / TileMap
var bagTilemapPosition = null
onready var border = get_node_or_null("Icon/Border")

enum BagTiles{
	Default = 2, 
	CanAdd = 6, 
	CannotAdd = 5
}

var cachedAffectedInsideItems: Array
var cachedInsideItems: Array




func _ready():
	if bagTilemapPosition == null:
		bagTilemapPosition = bagTilemap.position
	bagTilemap.position = bagTilemapPosition + sprite.offset

func getHoverPriority():
	if dragged: return DRAG_PRIORITY
	else: return - 1

func isBag():
	return true

func showBagBorderForItem(item):
	return not item.isBag() and canApplyEffect(item)

func canApplyEffect(_toItem):
	return false

func canBePicked() -> bool:
	if placed and CustomRules.getCannotPickBags(): return false
	
	var bagPickable = .canBePicked()
	if Game.state == Game.State.Shop:
		return bagPickable
	
	
	if bagPickable:
		return getItemsInside().empty()
	return false

func canBeLocked() -> bool:
	if not canLockBag():
		return false
	
	if not focus:
		return false
	
	if (ownerType == Owner.PlayerInventory or 
		ownerType == Owner.PlayerStorageBox or 
		(ownerType == Owner.Socket and character() == Game.PLAYER)):
		
		if Game.state == Game.State.Combat:
			return true
		else:
			return .canBePicked()
	
	else:
		return false

func resetZ():
	if (ownerType == Owner.PlayerInventory or 
		ownerType == Owner.Opponent or 
		ownerType == Owner.BuildViewer):
		z_index = - 2
		bagTilemap.hide()
	else:
		.resetZ()

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)
	resetZ()
	
	var parent = get_parent()
	var priority = getBagLayerPriority()
	var insertIndex = parent.get_child_count()
	for i in parent.get_child_count():
		var item = parent.get_child(i)
		if Util.isBag(item):
			if item.getBagLayerPriority() > priority:
				insertIndex = i
				break
	
	if get_position_in_parent() < insertIndex:
		insertIndex -= 1
	parent.move_child(self, insertIndex)

func getBagLayerPriority() -> int:
	if getRarity() == Rarity.Unique: return 2
	if hasBagEffect(): return 1
	return 0

func hasBagEffect() -> bool:
	return border != null

func _process(delta: float) -> void :
	if dragged:
		if Game.PLAYER.INVENTORY.canAddBag(self):
			for cell in bagTilemap.get_used_cells():
				bagTilemap.set_cellv(cell, BagTiles.CanAdd)
			
		else:
			for cell in bagTilemap.get_used_cells():
				bagTilemap.set_cellv(cell, BagTiles.CannotAdd)

func reactToDropResult(result):
	.reactToDropResult(result)
	if result == DropResult.AddedToInventory:
		z_index = - 2
	
	for cell in bagTilemap.get_used_cells():
		bagTilemap.set_cellv(cell, BagTiles.Default)
	













func onRemoveFromInventory():
	bagTilemap.show()

func getTopLeftGlobal() -> Vector2:
	var topLeft = Vector2(INF, INF)
	
	for cell in getExtensionCells():
		var globalPos = collisionMap.to_global(collisionMap.map_to_world(cell))
		topLeft.x = min(globalPos.x, topLeft.x)
		topLeft.y = min(globalPos.y, topLeft.y)
	return topLeft + correction[getFaceDirection()]

func getBottomRightGlobal() -> Vector2:
	var bottomRight = Vector2( - INF, - INF)
	for cell in getExtensionCells():
		var globalPos = collisionMap.to_global(collisionMap.map_to_world(cell))
		bottomRight.x = max(globalPos.x, bottomRight.x)
		bottomRight.y = max(globalPos.y, bottomRight.y)
	return bottomRight + cellSize

func isEmpty() -> bool:
	return getItemsInside().empty()

func getItemsInside() -> Array:
	if not cachedInsideItems.empty(): return cachedInsideItems
	
	return inventory.getItemsInCells(occupiedCells)

func getEmptyCells() -> Array:
	var emptyCells = []
	for cell in occupiedCells:
		if inventory.isCellEmpty(cell):
			emptyCells.push_back(cell)
	return emptyCells

func getEmptyGlobalPositions() -> Array:
	var positions = []
	for cell in getEmptyCells():
		positions.push_back(inventory.cellToGlobalPos(cell, true))
	return positions

func getAffectedItemsInside() -> Array:
	if not placed: return []
	
	if not cachedAffectedInsideItems.empty():
		return cachedAffectedInsideItems
	
	var affected = []
	for item in getItemsInside():
		if canApplyEffect(item):
			affected.push_back(item)
		
	return affected

func previewCanAffect():
	var visuals: = {}
	
	var itemDict
	if ownerType == Owner.Opponent:
		itemDict = ItemBook.opponentItems
	else:
		itemDict = ItemBook.ownableItems
	
	var curAffected = getAffectedItemsInside()
	
	for descr in itemDict:
		for item in itemDict[descr]:
			if (item != self and 
				not item.isBag() and 
				( not item.isGem() or item.socket == null)
				and canApplyEffect(item)
				and not item in curAffected):
				
				var visual = visuals.get(item, null)
				if visual == null:
					visual = ObjectPool.instance(canAffectVisual)
					item.add_child(visual)
					
					canAffectVisuals.push_back(visual)
					visuals[item] = visual
				visual.setColorActive(visual.AffectsInside)

func prepare():
	cachedInsideItems = getItemsInside()
	
	for item in cachedInsideItems:
		if canApplyEffect(item):
			cachedAffectedInsideItems.push_back(item)
	
	.prepare()

func combatToShop():
	cachedAffectedInsideItems.clear()
	cachedInsideItems.clear()
	.combatToShop()


func getCraftableNeighbors():
	var craftableItems = []
	for item in getItemsInside():
		if item.isAvailableForCrafting():
			craftableItems.push_back(item)
	return craftableItems






	
func onItemAdded(item):
	.onItemAdded(item)
	if item in getItemsInside() and canApplyEffect(item):
		if item.placedByPlayer:
			animation.play("PlacedInBag")
		onAffectedItemInsideAdded(item)

func onAffectedItemInsideAdded(_item):
	pass

func onItemRemoved(item):
	.onItemRemoved(item)
	if item in getItemsInside() and canApplyEffect(item):
		onAffectedItemInsideRemoved(item)
		

func onAffectedItemInsideRemoved(_item):
	pass

func pushItemsInsideToStorage():
	for item in getItemsInside():
		inventory.removeItem(item)
		item.pushToStorage(Game.STORAGEBOX.center)

func onDraggedWithParentStart(bag):
	.onDraggedWithParentStart(bag)
	z_index = 0
	

func onDraggedWithParentEnd():
	.onDraggedWithParentEnd()
	if dragged:
		pass
	else:
		resetZ()

func getNumAffectedInside() -> int:
	var num = 0
	for item in getAffectedItemsInside():
		num += 1
	return num


func getNumAffectedInside_type(type: int) -> int:
	var num = 0
	for item in getAffectedItemsInside():
		num += item.getTypeMultiplicity(type)
	return num

func getBagMultiplicity(forItem) -> int:
	return 1

func discard(discardGems = true):
	if pooled:
		bagTilemap.show()
	
	.discard(discardGems)
	
