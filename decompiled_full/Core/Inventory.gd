extends Node2D

signal item_added
signal item_removed
signal item_type_changed
signal inventory_shifted

enum Tile{
	Outside = - 1, 
	PotentialSpaceHovered = 7, 
	PotentialSpace = 8, 
	Empty = 2, 
	Filled = 1, 
	HoveredOK = 6, 
	HoveredFail = 5, 
	Collision = 4, 
	HoveredOutside = 9, 
	HoveredOK_Bag = 10, 
	HoveredFail_Bag = 11
}

enum AffectedTile{
	CanAffect = 0, 
	CannotAffect = 1, 
	CanAffectSecondary = 2, 
	CannotAffectSecondary = 3, 
	CanAffectTertiary = 4, 
	CannotAffectTertiary = 5, 
	AffectsInside = 6, 
	CanAffectLightning = 7, 
	CannotAffectLightning = 8
}

const shiftSound = preload("res://Assets/Sound/Switch.wav")
const shiftCollisionAni = preload("res://Interface/InventoryBorder.tscn")

const MAX_SIZE = Vector2(10, 10)
export var inventorySize = Vector2(9, 7)
const cellSize = Vector2(80, 80)
const halfCellSize = Vector2(40, 40)
const neighborOffsets = [Vector2.ZERO, Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN]
const aroundOffsets = [Vector2.ZERO, Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN, Vector2( - 1, - 1), Vector2(1, - 1), Vector2( - 1, 1), Vector2(1, 1)]
const hoveredTiles = [Tile.HoveredOK, Tile.HoveredFail, Tile.Collision]

onready var tilemap = $TileMap
onready var aboveTilemap = $Above
onready var itemNode = get_parent()
onready var inventoryCells = tilemap.get_used_cells()


var filledCells: Dictionary
var bagCells: Dictionary
var borderCells: Dictionary
var items = []
var character = null
var curHovered: Dictionary
var recalculateQueued = false

func _ready() -> void :
	Game.connect("item_dropped", self, "onItemDropped")
	
	cleanUp()
	



	
	var upcells = []
	for x in inventorySize.x:
		upcells.push_back(Vector2(x, 0))
	borderCells[Vector2.UP] = upcells
	
	var downcells = []
	for x in inventorySize.x:
		downcells.push_back(Vector2(x, inventorySize.y - 1))
	borderCells[Vector2.DOWN] = downcells
	
	var leftcells = []
	for y in inventorySize.y:
		leftcells.push_back(Vector2(0, y))
	borderCells[Vector2.LEFT] = leftcells
	
	var rightcells = []
	for y in inventorySize.y:
		rightcells.push_back(Vector2(inventorySize.x - 1, y))
	borderCells[Vector2.RIGHT] = rightcells
	
func isInventoryCell(cell):
	return (cell.x >= 0 and cell.x < inventorySize.x and 
			cell.y >= 0 and cell.y < inventorySize.y)



func isTilePotentialSpace(tile):
	return (tile == Tile.PotentialSpace or 
			tile == Tile.PotentialSpaceHovered or 
			tile == Tile.HoveredOutside or 
			tile == Tile.HoveredOK_Bag or 
			tile == Tile.HoveredFail_Bag)

func isPotentialSpace(cell):
	return isInventoryCell(cell) and not cell in bagCells
	
	

func isItemInCell(cell):
	return cell in filledCells


func getInsideCells():
	var insideCells = []
	for cell in inventoryCells:
		if cell in bagCells:
			insideCells.push_back(cell)
	
	return insideCells


func getPlacableCells():
	if Game.inventoryEditMode == Game.InventoryEditMode.ItemLayer:
		return inventoryCells
	else:
		return getInsideCells()

func _process(delta: float) -> void :
	if Game.draggedItem:
		cleanUp()
	aboveTilemap.clear()


func recalculateTilemap():
	if not recalculateQueued:
		recalculateQueued = true
		call_deferred("actuallyRecalculateTilemap")

func actuallyRecalculateTilemap():
	recalculateQueued = false
	for cell in inventoryCells:
		if cell in filledCells:
			tilemap.set_cellv(cell, Tile.Filled)
		elif cell in bagCells:
			tilemap.set_cellv(cell, Tile.Empty)
		else:
			tilemap.set_cellv(cell, Tile.PotentialSpace)



func cleanUp():
	tilemap.modulate.a = 0.7
	
	for cell in tilemap.get_used_cells_by_id(Tile.PotentialSpaceHovered):
		if (Game.inventoryEditMode == Game.InventoryEditMode.BagLayer and 
			cell in filledCells):
			tilemap.set_cellv(cell, Tile.Filled)
		else:
			tilemap.set_cellv(cell, Tile.PotentialSpace)
	
	for cell in tilemap.get_used_cells_by_id(Tile.HoveredOutside):
		tilemap.set_cellv(cell, Tile.PotentialSpace)
	
	for cell in tilemap.get_used_cells_by_id(Tile.HoveredOK):
		if (Game.inventoryEditMode == Game.InventoryEditMode.ItemLayer and 
			not cell in bagCells):
			tilemap.set_cellv(cell, Tile.PotentialSpace)
		else:
			tilemap.set_cellv(cell, Tile.Empty)
	
	for cell in tilemap.get_used_cells_by_id(Tile.HoveredFail):
		tilemap.set_cellv(cell, Tile.Empty)
	
	for cell in tilemap.get_used_cells_by_id(Tile.Collision):
		tilemap.set_cellv(cell, Tile.Filled)
	
	for cell in tilemap.get_used_cells_by_id(Tile.HoveredOK_Bag):
		tilemap.set_cellv(cell, Tile.PotentialSpace)
	
	for cell in tilemap.get_used_cells_by_id(Tile.HoveredFail_Bag):
		if cell in filledCells:
			tilemap.set_cellv(cell, Tile.Filled)
		elif cell in bagCells:
			tilemap.set_cellv(cell, Tile.Empty)
		else:
			tilemap.set_cellv(cell, Tile.PotentialSpace)
	aboveTilemap.clear()

func canAddItemOrBag(item: Item):
	if item.isBag():
		return canAddBag(item)
	else:
		return canAddItem(item)

func canAddBag(bag, checkCollisions = true):
	var extensionPoints = bag.getExtensionPoints()
	var cells = getCellsForGlobalPositions(extensionPoints)
	if checkCollisions:
		return allCellsPotentialSpace(cells)
	else:
		for cell in cells:
			if not isInventoryCell(cell):
				return false
		return true

func canAddItem(item: Item, checkCollision = true, checkBags = true):
	var insideCells = getPlacableCells()
	var collisionPoints = item.getCollisionPoints()
	
	var cells = getCellsForGlobalPositions(collisionPoints)
	
	if checkBags:
		for cell in cells:
			if ( not cell in insideCells or 
				(checkCollision and filledCells.get(cell, null))):
				return false
	else:
		for cell in cells:
			if not isInventoryCell(cell):
				return false
	
	return true

func previewItem(item):
	if item.isBag():
		for cell in tilemap.get_used_cells_by_id(Tile.PotentialSpace):
			tilemap.set_cellv(cell, Tile.PotentialSpaceHovered)
		
	
	
	tilemap.modulate.a = 1.0
	
	var collisionPoints
	if item.isBag():
		collisionPoints = item.getExtensionPoints()
	else:
		collisionPoints = item.getCollisionPoints()
	var cells = getCellsForGlobalPositions(collisionPoints)
	
	clearHoveredCache()
	for cell in cells:
		curHovered[cell] = true
	
	if item.isBag():
		if canAddBag(item):
			for cell in cells:
				tilemap.set_cellv(cell, Tile.HoveredOK_Bag)
			return
		
		for cell in cells:
			if isInventoryCell(cell):
			
				tilemap.set_cellv(cell, Tile.HoveredFail_Bag)
		
	else:
		if canAddItem(item):
			for cell in cells:
				tilemap.set_cellv(cell, Tile.HoveredOK)
			return
		
		for cell in cells:
			if tilemap.get_cellv(cell) == Tile.PotentialSpace:
				tilemap.set_cellv(cell, Tile.HoveredOutside)
			elif tilemap.get_cellv(cell) == Tile.Filled:
				tilemap.set_cellv(cell, Tile.Collision)
			elif tilemap.get_cellv(cell) == Tile.Empty:
				tilemap.set_cellv(cell, Tile.HoveredFail)

func clearHoveredCache():
	curHovered.clear()

func isHovered(cell: Vector2) -> bool:
	
	
	return cell in curHovered

var affectedItemsChecked: Array

func previewAffectedCells(item):

	
	var colors = Item.Affected.values()
	if item.isBag():
		colors = [Item.Affected.Primary]
	else:
		colors = Item.Affected.values()
	
	for color in colors:
		var tileToCells = getAffectedCells(item, color)
		for tile in tileToCells:
			for cell in tileToCells[tile]:
				aboveTilemap.set_cellv(cell, tile)
	
func getAffectedCells(item, color: int) -> Dictionary:
	var insideCells = getPlacableCells()
	
	affectedItemsChecked.clear()
	var tileToCells: = {
		AffectedTile.CanAffect + color: [], 
		AffectedTile.CannotAffect + color: [], 
		AffectedTile.AffectsInside: []
	}
	
	var affectedCells: Array
	
	if item.isBag():
		affectedCells = getCellsForGlobalPositions(item.getExtensionPoints())
	else:
		affectedCells = getCellsForGlobalPositions(item.getAffectedPoints(color))
	
	if affectedCells.empty(): return tileToCells
	
	
	affectedCells.sort_custom(CellSorter, "sort")
	var itemsChecked = []
	for cell in affectedCells:
		if cell in insideCells:
		
			var canAffect: bool
			var itemInCell = filledCells.get(cell, null)
			if itemInCell:
				if itemsChecked.has(itemInCell) and color != Item.Affected.Lightning:
					canAffect = false
				else:
					if item.isBag():
						canAffect = item.canApplyEffect(itemInCell)
					else:
						canAffect = item.canAffect_color(itemInCell, color)
						if item.isAffectingDistinct(color):
							canAffect = canAffect and isDistinct(itemInCell)
					itemsChecked.push_back(itemInCell)
					if canAffect:
						affectedItemsChecked.push_back(itemInCell)
			else:
				canAffect = item.affectsEmpty(color)
			
			if item.isBag():
				if canAffect:
					tileToCells[AffectedTile.AffectsInside].push_back(cell)
			else:
				if canAffect:
					tileToCells[AffectedTile.CanAffect + color].push_back(cell)
				else:
					tileToCells[AffectedTile.CannotAffect + color].push_back(cell)
		elif isInventoryCell(cell):
			tileToCells[AffectedTile.CannotAffect + color].push_back(cell)
	
	return tileToCells

func isDistinct(item):
	for affectedItem in affectedItemsChecked:
		if item.isA(affectedItem.descriptor):
			return false
	return true

func getAffectedPoints(item, color = Item.Affected.Primary):
	var points = []
	var tileToCells = getAffectedCells(item, color)[AffectedTile.CanAffect + color]
	for cell in tileToCells:
		points.push_back(aboveTilemap.to_global(aboveTilemap.map_to_world(cell)) + halfCellSize)
	return points









func getItems() -> Array:
	return items

func getItemsAndGems() -> Array:
	var itemsAndGems = items.duplicate()
	for item in items:
		itemsAndGems.append_array(item.getGemsNoNull())
	return itemsAndGems

func getCellsForGlobalPositions(points: Array) -> Array:
	var cells = []
	for point in points:
		cells.push_back(tilemap.world_to_map(tilemap.to_local(point)))
	return cells

func cellToGlobalPos(cell: Vector2, cellCenter: bool = false) -> Vector2:
	var pos = tilemap.global_position + cellSize * cell
	if cellCenter:
		pos += halfCellSize
	return pos

func allCellsPotentialSpace(cells: Array):
	for cell in cells:
		if not isPotentialSpace(cell):
			return false
	return true

func isItemFloating(item) -> bool:
	for cell in item.occupiedCells:
		if not cell in bagCells:
			return true
	return false

func pushFloatingItemsToStorage():
	for item in items.duplicate():
		if not item.isBag() and isItemFloating(item):
			removeItem(item)
			item.pushToStorage(Game.STORAGEBOX.center)
			continue

func tryAddItem(item: Item, hotswapAllowed: bool = true) -> int:
	var insideCells = getPlacableCells()
	
	var firstPoint: Vector2
	var firstCell: Vector2
	var cells
	var hotswap = false
	
	if item.isBag():
		var extensionPoints = item.getExtensionPoints()
		cells = getCellsForGlobalPositions(extensionPoints)
		
		for cell in cells:
			if not isInventoryCell(cell):
				return Item.DropResult.OutsideInventory
			
		
		var bagCollisions = getBagsInCells(cells)
		
		if bagCollisions.empty():
			
			pass
		else:
			if (Game.state != Game.State.Shop or 
				CustomRules.getCannotPickBags()):
				return Item.DropResult.InventoryCollision
			
			if bagCollisions.size() == 1:
				hotswap = true
				bagCollisions[0].pickup(Item.PickupType.Hotswap)
			else:
				Game.STORAGEBOX.pushItemsToStorage(bagCollisions)
			
		firstPoint = extensionPoints[0]
		firstCell = cells[0]
	
	else:
		var collisionPoints = item.getCollisionPoints()
		
		cells = getCellsForGlobalPositions(collisionPoints)
		var difToCenter = collisionPoints[0] - tilemap.to_global(tilemap.map_to_world(cells[0]) + halfCellSize)
		
		var shiftDirections
		if item.canSnap():
			shiftDirections = [Vector2.LEFT, Vector2.RIGHT, Vector2.UP, Vector2.DOWN, 
				Vector2( - 1, - 1), Vector2( - 1, 1), Vector2(1, - 1), Vector2(1, 1)]
			
			var sorter = DistanceSorter.new(difToCenter.normalized())
			shiftDirections.sort_custom(sorter, "sort")
			shiftDirections.push_front(Vector2.ZERO)
		else:
			shiftDirections = [Vector2.ZERO]
		
		
		var itemCollisions = Dictionary()
		var foundShift = null
		
		for dir in shiftDirections:
			itemCollisions.clear()
			var noCellsOutside = true
			for cell in cells:
				var shiftedCell = cell + dir
				if not shiftedCell in insideCells:
					noCellsOutside = false
					break
					
				
				var itemInCell = filledCells.get(shiftedCell, null)
				if itemInCell:
					itemCollisions[itemInCell] = true
			
			if noCellsOutside:
				foundShift = dir
				break
		
		if foundShift == null:
			return Item.DropResult.OutsideInventory
		else:
			
			for i in collisionPoints.size():
				collisionPoints[i] += foundShift * cellSize
			for i in cells.size():
				cells[i] += foundShift
			item.global_translate(foundShift * cellSize)
		
		
		if itemCollisions.empty():
			
			pass
		elif itemCollisions.size() == 1:
			var collider = itemCollisions.keys()[0]
			if hotswapAllowed:
				hotswap = true
				var hotswapItem = collider
				hotswapItem.pickup(Item.PickupType.Hotswap)
			else:
				return Item.DropResult.InventoryCollision
		else:
			if Game.state == Game.State.Shop:
				
				for collider in itemCollisions:
					removeItem(collider)
				
				addItemCells(item, cells)
				
				
				var oldPositions = Dictionary()
				for collider in itemCollisions:
					oldPositions[collider] = collider.global_position
				
				
				var freePositions = []
				for collider in itemCollisions:
					var topLeftCell = collider.getTopLeftCell()
					var faceDirection = collider.getFaceDirection()
					var options = []
					for offset in neighborOffsets:
						var offsetTopLeft = topLeftCell + offset
						orientItem(collider, offsetTopLeft, faceDirection)
						if canAddItem(collider):
							options.push_back(offsetTopLeft)
							
					freePositions.push_back([collider, options])
					
				
				
				freePositions.sort_custom(CollisionSorter, "lessOptions")
				
				var hotswapItem = null
				var pushToStorage = []
				
				for i in freePositions.size():
					var collider = freePositions[i][0]
					var options = freePositions[i][1]
					var faceDirection = collider.getFaceDirection()
					var added = false
					
					for topLeftCell in options:
						orientItem(collider, topLeftCell, faceDirection)
						if canAddItem(collider):
							added = true
							
							addItemByTopLeft(collider, topLeftCell)
							collider.moveTo(oldPositions[collider], collider.global_position)
							break
						
					if hotswapAllowed:
						if not added:
							
							if hotswapItem == null:
								hotswapItem = collider
								hotswapItem.pickup(Item.PickupType.Hotswap)
								hotswap = true
							else:
								pushToStorage.push_back(collider)
						elif i == freePositions.size() - 1 and hotswapItem == null:
							hotswapItem = collider
							hotswapItem.pickup(Item.PickupType.Hotswap)
							hotswap = true
					else:
						if not added:
							pushToStorage.push_back(collider)
					
				
				Game.STORAGEBOX.pushItemsToStorage(pushToStorage)
			else:
				return Item.DropResult.InventoryCollision
		
		firstPoint = collisionPoints[0]
		firstCell = cells[0]
	
	
	
	var dif = firstPoint - tilemap.to_global(tilemap.map_to_world(firstCell) + halfCellSize)
	item.global_translate( - dif)
	
	addItem(item, cells, true)
	
	if Game.inventoryEditMode == Game.InventoryEditMode.Default:
		pushFloatingItemsToStorage()
	
	if hotswap:
		return Item.DropResult.Hotswap
	else:
		return Item.DropResult.AddedToInventory


func addItemByTopLeft(item: Item, topLeftCell: Vector2):
	
	
	
	var curPos = item.getTopLeftGlobal()
	var targetPos = tilemap.to_global(tilemap.map_to_world(topLeftCell))
	
	item.global_translate(targetPos - curPos)
	if item.isBag():
		addItem(item, getCellsForGlobalPositions(item.getExtensionPoints()), false)
	else:
		addItem(item, getCellsForGlobalPositions(item.getCollisionPoints()), false)


func addItem(item: Item, cells, placedByPlayer: bool):
	
	addItemCells(item, cells)
	recalculateTilemap()
	items.push_back(item)
	item.addToInventory(self, cells, placedByPlayer)
	Game.onInventoryChanged()
	emit_signal("item_added", item)




func addItemCells(item: Item, cells: Array):
	if item.isBag():
		for cell in cells:
			bagCells[cell] = item
	else:
		for cell in cells:
			filledCells[cell] = item

func clearItemCells(item: Item):
	for cell in item.occupiedCells:
		if item.isBag():
			if bagCells.get(cell, null) == item:
				bagCells.erase(cell)
		else:
			if filledCells.get(cell, null) == item:
				filledCells.erase(cell)
	
	recalculateTilemap()

func moveItem(item, newCells: Array):
	clearItemCells(item)


	addItemCells(item, newCells)
	recalculateTilemap()
	item.occupiedCells = newCells

func removeItem(item: Item):
	clearItemCells(item)
	items.erase(item)
	item.removeFromInventory()
	Game.onInventoryChanged()
	emit_signal("item_removed", item)

func getFreeBagCells():
	return Util.subtractDictFromArray(bagCells.keys(), filledCells)

func addItemWherePossible(item) -> bool:
	var pos = findPlaceForItem(item)
	if pos != null:
		addItemByTopLeft(item, pos)
		return true
	else:
		return false


func findPlaceForItem(item):
	var freeCells = getFreeBagCells()
	for faceDir in [Item.FaceDirection.UP, Item.FaceDirection.RIGHT]:
		for topleftCell in freeCells:
			orientItem(item, topleftCell, faceDir)
			if canAddItem(item):
				return topleftCell
	return null

static func getHorizontalCells(cells):
	var left = getCellsInLine(cells, Vector2.LEFT)
	var right = getCellsInLine(cells, Vector2.RIGHT)
	return Util.filterDuplicates(left + right)

static func getVerticalCells(cells):
	var up = getCellsInLine(cells, Vector2.UP)
	var down = getCellsInLine(cells, Vector2.DOWN)
	return Util.filterDuplicates(up + down)

static func getCellsInLine(cells, direction: Vector2, distance = 7):
	var lineCells = []
	for cell in cells:
		for offset in range(1, distance + 1):
			var neighbor = cell + direction * offset
			
			if ( not neighbor in cells and 
				not neighbor in lineCells):
				lineCells.push_back(neighbor)
			
	return lineCells
	
static func getAdjacentCells(cells):
	var adjacentCells = []
	for cell in cells:
		for offset in [Vector2.RIGHT, Vector2.LEFT, Vector2.UP, Vector2.DOWN]:
			var neighbor = cell + offset
		
			
			if ( not neighbor in cells and 
				not neighbor in adjacentCells):
				adjacentCells.push_back(neighbor)
	
	return adjacentCells


func getAdjacentItems(item):
	return getItemsInCells(getAdjacentCells(item.occupiedCells))


func isCellEmpty(cell: Vector2) -> bool:
	return cell in bagCells and not cell in filledCells

func getEmptyCellsInCells(cells):
	var num = 0
	for cell in cells:
		if isCellEmpty(cell):
			num += 1
	return num

func getItemInCell(cell: Vector2):
	return filledCells.get(cell, null)

func getItemsInCells(cells) -> Array:
	var itemsInCells = []
	for cell in cells:
		if filledCells.has(cell):
			var item = filledCells[cell]
			
			
			if not item in itemsInCells and item.placed:
				itemsInCells.push_back(item)
	
	return itemsInCells


func countItemsInCells(cells) -> Dictionary:
	var itemCounter = {}
	for cell in cells:
		if filledCells.has(cell):
			Util.dictAdd(itemCounter, filledCells[cell])
	return itemCounter

func getBagsInCells(cells):
	var bags = []
	for cell in cells:
		if bagCells.has(cell):
			var bag = bagCells[cell]
			if not bag in bags:
				bags.push_back(bag)
	
	return bags



















func deleteItems():
	var itemList = items.duplicate()
	items.clear()
	
	for item in itemList:
		item.discard()
	
	for cell in filledCells:
		tilemap.set_cellv(cell, Tile.Empty)
	filledCells.clear()
	
	bagCells.clear()
	
	cleanUp()


func reset():
	deleteItems()
	
	
	for cell in inventoryCells:
		tilemap.set_cellv(cell, Tile.PotentialSpace)
	



func replaceItem(item, newItem):
	var topLeftCell = item.getTopLeftCell()
	var faceDirection = item.getFaceDirection()
	topLeftCell += newItem.getCraftingOffset(faceDirection)
	
	removeItem(item)
	item.discard(false)
	
	newItem.ownerType = Item.Owner.PlayerInventory
	itemNode.add_child(newItem)
	
	var added = false
	for offset in aroundOffsets:
		var offsetTopLeft = topLeftCell + offset
		orientItem(newItem, offsetTopLeft, faceDirection)

		if canAddItem(newItem):
			addItemByTopLeft(newItem, offsetTopLeft)
			added = true
			break
	
	if not added:
		newItem.pushToStorage(Game.STORAGEBOX.center)
	
	return added
	


func orientItem(item, topLeftCell, faceDirection) -> void :
	item.scale = Vector2.ONE
	item.setFaceDirectionInstant(faceDirection)
	
	var curPos = item.getTopLeftGlobal()
	var targetPos = tilemap.to_global(tilemap.map_to_world(topLeftCell))
	item.global_translate(targetPos - curPos)

func orientAndAddItem(item, topLeftCell, faceDirection, checkCollision = false):
	item.ownerType = Item.Owner.PlayerInventory
	itemNode.add_child(item)
	orientItem(item, topLeftCell, faceDirection)
	
	if checkCollision and not canAddItem(item):
		item.pushToStorage(Game.STORAGEBOX.center)
	else:
		addItemByTopLeft(item, topLeftCell)


func getRightBorder():
	var rightMostCell = - 1
	
	for cell in bagCells:
		if cell.x > rightMostCell:
			rightMostCell = cell.x
	
	if Game.inventoryEditMode != Game.InventoryEditMode.Default:
		for cell in filledCells:
			if cell.x > rightMostCell:
				rightMostCell = cell.x
	
	return tilemap.global_position.x + tilemap.map_to_world(Vector2(rightMostCell, 0)).x


func getLeftBorder():
	var leftMostCell = 10
	for cell in bagCells:
		if cell.x < leftMostCell:
			leftMostCell = cell.x
	return tilemap.global_position.x + tilemap.map_to_world(Vector2(leftMostCell, 0)).x


func getBorderCells(direction: Vector2) -> Array:
	return borderCells[direction]


func canShift(direction: Vector2):





	if CustomRules.getCannotPickBags() and Game.inventoryEditMode != Game.InventoryEditMode.ItemLayer:
		return false
	
	for cell in getBorderCells(direction):
		if Game.inventoryEditMode == Game.InventoryEditMode.ItemLayer:
			if isItemInCell(cell):
				playShiftCollisionAni(direction)
				return false
		else:
			if not isPotentialSpace(cell):
				playShiftCollisionAni(direction)
				return false
	
	return true

const shiftCollisionScale_large = Vector2(1.645, 1.36)
const shiftCollisionScale_small = Vector2(1.26, 1.36)

func playShiftCollisionAni(direction):
	var ani = ObjectPool.instance(shiftCollisionAni)
	Game.UINode.add_child(ani)
	ani.get_node("AnimationPlayer").play("Appear", - 1, 2)
	if direction == Vector2.UP:
		ani.position = Vector2(410, 50)
		ani.scale = shiftCollisionScale_large
		ani.rotation = 0
	elif direction == Vector2.DOWN:
		ani.position = Vector2(410, 636)
		ani.scale = shiftCollisionScale_large
		ani.rotation = 0
	if direction == Vector2.LEFT:
		ani.position = Vector2(40, 343)
		ani.scale = shiftCollisionScale_small
		ani.rotation = PI * 0.5
	if direction == Vector2.RIGHT:
		ani.position = Vector2(777, 343)
		ani.scale = shiftCollisionScale_small
		ani.rotation = PI * 0.5

func shift(direction: Vector2):
	Game.onInventoryShifted(direction * cellSize)
	
	for item in items:
		item.shift(direction)
	
	if Game.draggedItem and Game.draggedItem.ownerType == Item.Owner.PlayerInventory:
		Game.draggedItem.shift(direction)
	
	if Game.inventoryEditMode != Game.InventoryEditMode.BagLayer:
		var shiftedFilledCells = Dictionary()
		for cell in filledCells:
			shiftedFilledCells[cell + direction] = filledCells[cell]
		
		filledCells = shiftedFilledCells
	
	if Game.inventoryEditMode != Game.InventoryEditMode.ItemLayer:
		var shiftedBagCells = Dictionary()
		for cell in bagCells:
			shiftedBagCells[cell + direction] = bagCells[cell]
		
		bagCells = shiftedBagCells
	
	recalculateTilemap()
	
	Sound.playSound(shiftSound, - 4, Util.rng.randf_range(0.9, 1.0))
	
	emit_signal("inventory_shifted")


func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	if Game.state == Game.State.Shop:
		var shiftDir = Vector2.ZERO
		if Util.isActionPressed_event(event, "shift_up"):
			shiftDir = Vector2.UP
		if Util.isActionPressed_event(event, "shift_left"):
			shiftDir = Vector2.LEFT
		if Util.isActionPressed_event(event, "shift_right"):
			shiftDir = Vector2.RIGHT
		if Util.isActionPressed_event(event, "shift_down"):
			shiftDir = Vector2.DOWN
		
		if shiftDir != Vector2.ZERO:
			if canShift(shiftDir):
				shift(shiftDir)

func onItemDropped(_item, _dropResult):
	clearHoveredCache()

func onItemTypeChanged(item):
	emit_signal("item_type_changed", item)

var multiSelectMainItem = null
var multiSelectSubItems: Array

func startMultiSelect(mainItem: Item, selected: Array):
	multiSelectMainItem = mainItem
	multiSelectSubItems = selected
	multiSelectMainItem.pickup(Item.PickupType.MultiSelect)

func getMultiSelectItems():
	if multiSelectMainItem.isBag():
		var totalSelection = multiSelectSubItems.duplicate()
		
		if Game.inventoryEditMode == Game.InventoryEditMode.Default:
			totalSelection.append_array(multiSelectMainItem.getItemsInside())
			for bag in multiSelectSubItems:
				totalSelection.append_array(bag.getItemsInside())
		
		totalSelection = Util.filterDuplicates(totalSelection)
		return totalSelection
	else:
		return multiSelectSubItems.duplicate()




func createFromItemTuples(itemTuples: Array, ownerType: int):
	reset()
	itemTuples.sort_custom(Game.ItemSort, "sort_BagOrder")
	
	for tuple in itemTuples:
		var descriptor = tuple["d"]
		var item
		if ownerType == Item.Owner.BuildViewer:
			item = descriptor.instantiate_pooled()
		else:
			item = ItemBook.instantiateItem(descriptor)
		item.ownerType = ownerType
		itemNode.add_child(item)
		var topLeftCellPos = tuple["c"]
		var faceDirection = tuple["f"]
		item.setFaceDirectionInstant(faceDirection)
		orientItem(item, topLeftCellPos, faceDirection)
		if not canAddItemOrBag(item):
			Util.eprint("overlapping item: ", item.getName())
		addItemByTopLeft(item, topLeftCellPos)
		
		if "g" in tuple:
			var gems = tuple["g"]
			for i in gems.size():
				var gemIndex = gems[i]
				if gemIndex != RunDatabase.emptySocketId:
					var gem
					if ownerType == Item.Owner.BuildViewer:
						gem = ItemBook.getGemForIndex(gemIndex).instantiate_pooled()
					else:
						gem = ItemBook.instantiateItem(ItemBook.getGemForIndex(gemIndex))
					item.setGem(i, gem)
		
		if "pd" in tuple:
			item.setData(tuple["pd"])

func disableItemTooltips():
	for item in getItemsAndGems():
		item.disableTooltip()
		item.disableFocus()

func enableItemTooltips():
	for item in getItemsAndGems():
		item.enableTooltip()
		item.enableFocus()

func countGold() -> int:
	var g = 0
	for item in getItemsAndGems():
		g += item.descriptor.getPrice()
	return g

func countSocketedGems() -> int:
	var numGems = 0
	for item in items:
		numGems += item.getGemsNoNull().size()
	return numGems

func changeBuffPower_allItems(buffType, amount):
	for item in getItemsAndGems():
		
		item.giveBuffPower(buffType, amount)

func changeBuffAmplification_allItems(buffType, amount):
	for item in getItemsAndGems():
		
		item.changeAmplificiationChancePercent(buffType, amount)


class CellSorter:
	static func sort(cell1, cell2):
		if cell1.y == cell2.y:
			return cell1.x < cell2.x
		return cell1.y < cell2.y

class CollisionSorter:
	static func lessOptions(tuple1, tuple2):
		return tuple1[1].size() < tuple2[1].size()
	
class DistanceSorter:
	var baseOffset: Vector2
	const DIAG_PUNISH_FACTOR = 1.7
	
	func _init(_baseOffset):
		baseOffset = _baseOffset
	
	func sort(dir1: Vector2, dir2: Vector2):
		if dir1.x != 0 and dir1.y != 0: dir1 *= DIAG_PUNISH_FACTOR
		if dir2.x != 0 and dir2.y != 0: dir2 *= DIAG_PUNISH_FACTOR
		return dir1.distance_squared_to(baseOffset) < dir2.distance_squared_to(baseOffset)
		
