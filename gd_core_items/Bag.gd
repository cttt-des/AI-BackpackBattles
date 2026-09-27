extends Item
class_name Bag
var bagTilemapPosition = null
enum BagTiles{
	Default = 2, 
	CanAdd = 6, 
	CannotAdd = 5
}
var cachedAffectedInsideItems: Array
var cachedInsideItems: Array
var bagTilemap
var border

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
	return false

func canBeLocked() -> bool:
	return false

func resetZ():
	pass

func addToInventory(_inventory, _occupiedCells: Array, _placedByPlayer: bool):
	.addToInventory(_inventory, _occupiedCells, _placedByPlayer)

func getBagLayerPriority() -> int:
	if getRarity() == CoreConst.Rarity.Unique: return 2
	if hasBagEffect(): return 1
	return 0


func hasBagEffect() -> bool:
	return border != null


func _process(delta: float) -> void :
	if dragged:
		if ctx.player.INVENTORY.canAddBag(self):
			pass
			
		else:
			pass


func reactToDropResult(result):
	.reactToDropResult(result)

func onRemoveFromInventory():
	pass


func getTopLeftGlobal() -> Vector2:
	return Vector2.ZERO

func getBottomRightGlobal() -> Vector2:
	return Vector2.ZERO

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
	pass

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
			pass
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
	pass

func onDraggedWithParentStart(bag):
	.onDraggedWithParentStart(bag)

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
		pass
	
	.discard(discardGems)
	

func _readyInit():
	._readyInit()
	if bagTilemapPosition == null:
		pass

