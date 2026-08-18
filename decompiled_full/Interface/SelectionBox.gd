extends Node2D

onready var boxVisual = $BoxVisual
onready var area = $Area2D
onready var collisionShape = $Area2D / CollisionShape2D

var withoutBags: bool
var startPoint: Vector2
var selectedInventoryItems: Array
var selectedStorageItems: Array
var spaceStateQuery: Physics2DShapeQueryParameters
var grabbingShape = CircleShape2D.new()
var startFrame: int
var startedWithLeftClick: bool


var closestItem = null

func _ready():
	Game.selectionBox = self
	set_process(false)
	boxVisual.hide()
	collisionShape.disabled = true
	
	spaceStateQuery = Physics2DShapeQueryParameters.new()
	grabbingShape.radius = 80
	spaceStateQuery.set_shape(grabbingShape)
	spaceStateQuery.collide_with_bodies = true
	spaceStateQuery.collision_layer = 8
	spaceStateQuery.exclude = get_tree().get_nodes_in_group("Wall")
	spaceStateQuery.collide_with_areas = false
	
	Game.connect("combat_start_pressed", self, "cancel")
	Game.connect("game_paused", self, "cancel")
	
func canStart() -> bool:
	return (Game.state == Game.State.Shop and 
			not Game.isMenuOpen() and 
			Game.draggedItem == null and 
			not Game.replacementPending and 
			Util.time > Game.lastItemDropTime and 
			(Game.getFocusItem() == null or not Game.getFocusItem().canBeLocked()) and 
			Input.get_current_cursor_shape() == Input.CURSOR_ARROW)


func _input(event):
	if InputBlocker.isActive(): return
	
	if (Util.isAction_event(event, "grab_item") or 
		event is InputEventScreenTouch):


		
		closestItem = null
		if event.is_pressed():
			
			if Game.isTouchScreenActive():
				
				Game.unhoverAllItems()
				
				var items = findTouchedItems(get_global_mouse_position())
				for item in items:
					item.hover()
				






func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	var leftClick = (Util.isAction_event(event, "grab_item") or 
		event is InputEventScreenTouch)
	var rightClick = Util.isAction_event(event, "lock_combining")
	
	if leftClick or rightClick:
		var curMousePos = get_global_mouse_position()
		
		if event.is_pressed():
			if Game.SELECTING: return
			
			
			if canStart():
				if Game.inventoryEditMode == Game.InventoryEditMode.BagLayer:
					withoutBags = false
				elif Game.inventoryEditMode == Game.InventoryEditMode.ItemLayer:
					withoutBags = true
				else:
					withoutBags = rightClick
				
				if withoutBags:
					boxVisual.modulate = Color(0.52, 1.2, 0.5)
				else:
					boxVisual.modulate = Color.white
				
				if CustomRules.getCannotPickBags():
					withoutBags = true
				
				startedWithLeftClick = leftClick
				
				startPoint = curMousePos
				
				
				if (curMousePos.x > 750 and 
					startedWithLeftClick and 
					findAndPickCloseItem()):
						return
				
				
				startSelecting()
				Game.cancelSwitch()
		
		else:
			if not Game.SELECTING: return
			if startedWithLeftClick != leftClick: return
			
			if not selectedInventoryItems.empty():
				var curFrame = Util.getFrameCounter_process()
				if curFrame - startFrame > 2:
					var mainBag = null
					var closestDist = 10000
					for bag in selectedInventoryItems:
						var dist = bag.global_position.distance_to(curMousePos)
						if dist < closestDist:
							closestDist = dist
							mainBag = bag
					selectedInventoryItems.erase(mainBag)
					
					Game.PLAYER.INVENTORY.startMultiSelect(mainBag, selectedInventoryItems)
					Game.setTutorialDone(Game.TutorialSteps.Selection)
				end()
				
			else:



				
				
				if (Util.time > Game.lastItemDropTime + 0.5 and 
					(startedWithLeftClick or 
						collisionShape.shape.extents.x > 30 or 
						collisionShape.shape.extents.y > 30)
					):
					
					if findAndPickCloseItem():
						return
					
					
					if not selectedStorageItems.empty():
						var closest = null
						var closestDist = 1000000
						for item in selectedStorageItems:
							var dist = item.global_position.distance_to(curMousePos)
							if dist < closestDist:
								closestDist = dist
								closest = item
						
						end()
						
						Game.disableTooltipsFor(6)
						closest.pickup()
						return
				
				
				end()
				var focusItem = Game.getFocusItem()
				if focusItem != null:
					focusItem.gainFocus()

func startSelecting():
	set_process(true)
	collisionShape.disabled = false
	area.monitoring = true
	boxVisual.show()
	Game.SELECTING = true
	startFrame = Util.getFrameCounter_process()
	InputBlocker.disableAllControls(InputBlocker.Source.BoxSelect, Game.mainNode)

func findAndPickCloseItem(radius = 80.0):
	
	var closeItem = findCloseItem(radius)
	if closeItem != null and closeItem.isPickingPossible():
		end()
		
		Game.disableTooltipsFor(6)
		closeItem.gainFocus()
		closeItem.pickup()
		return true
	return false
	
func findCloseItem(radius = 80.0):
	grabbingShape.radius = radius
	var spaceState = get_world_2d().get_direct_space_state()
	spaceStateQuery.transform = Transform2D(0, get_global_mouse_position())
	var restInfo = spaceState.get_rest_info(spaceStateQuery)
	if not restInfo.empty():
		var object = instance_from_id(restInfo.collider_id)
		if object is Item:
			return object
			
	return null

func findTouchedItems(atPos) -> Array:
	var spaceState = get_world_2d().get_direct_space_state()
	var results = spaceState.intersect_point(atPos, 
		32, [], 1, false, true)
	var items = []
	for result in results:
		var object = result.collider.get_parent()
		if object is Item:
			items.push_back(object)
	return items

func getScore(item):
	if item.isGem() and item.socket:
		return 2
	elif item.isBag():
		return 0
	else:
		return 1

func findTouchedItem(atPos):
	var spaceState = get_world_2d().get_direct_space_state()
	var results = spaceState.intersect_point(atPos, 
		32, [], 1, false, true)
	
	var bestMatch = null
	var bestScore = - 1
	for result in results:
		var object = result.collider.get_parent()
		if object is Item:
			var score = getScore(object)
			if score > bestScore:
				bestScore = score
				bestMatch = object
	return bestMatch








func canPickFromInventory(item) -> bool:
	if withoutBags:
		return ( not item.isBag() and 
			item.ownerType == item.Owner.PlayerInventory and 
			item.canBeDraggedWithBag())
	else:
		return (item.isBag() and 
			item.ownerType == item.Owner.PlayerInventory and 
			item.canBeDraggedWithBag())

func canPickFromStorage(item) -> bool:
	if not item.visible: return false
	
	if item.ownerType == item.Owner.PlayerStorageBox:
		if item.isBag():
			return Game.inventoryEditMode != Game.InventoryEditMode.ItemLayer
		else:
			return Game.inventoryEditMode != Game.InventoryEditMode.BagLayer
		
	return false

func onItemAreaEntered(itemArea):
	if not Game.SELECTING: return
	var item = itemArea.get_parent()
	if canPickFromInventory(item):
		selectedInventoryItems.push_back(item)
		item.setBright()
		var numItems = selectedInventoryItems.size()
		
		var pitchLoopSize = 24
		var rising = pitchLoopSize / 2
		var pitchLevel = numItems % pitchLoopSize
		if pitchLevel > rising:
			pitchLevel = pitchLoopSize - pitchLevel
		var pitch = 0.6 + pitchLevel * 0.1
		
		Sound.playSound_process(item.hoverSound, 0, pitch)
	
	elif canPickFromStorage(item):
		selectedStorageItems.push_back(item)
		

func onItemAreaExited(itemArea):
	if not Game.SELECTING: return
	var item = itemArea.get_parent()
	if canPickFromInventory(item):
		selectedInventoryItems.erase(item)
		
		item.resetBright()
	elif canPickFromStorage(item):
		selectedStorageItems.erase(item)


func cancel():
	for item in selectedInventoryItems:
		item.resetBright()
	end()

func end():
	if not Game.SELECTING: return
	set_process(false)
	boxVisual.hide()
	selectedInventoryItems.clear()
	selectedStorageItems.clear()
	Game.SELECTING = false
	collisionShape.disabled = true
	
	area.position.x = - 100000
	InputBlocker.restoreAllControls(InputBlocker.Source.BoxSelect)
	

const BOTTOM_RIGHT_BORDER = Vector2(1920, 1080)

func _process(delta):
	var curPoint = get_global_mouse_position()
	var topLeft = Vector2(min(startPoint.x, curPoint.x), min(startPoint.y, curPoint.y))
	var bottomRight = Vector2(max(startPoint.x, curPoint.x), max(startPoint.y, curPoint.y))
	
	boxVisual.rect_global_position = topLeft
	boxVisual.set_end(bottomRight)
	
	var clampedTopLeft = Vector2(min(topLeft.x, BOTTOM_RIGHT_BORDER.x), 
									min(topLeft.y, BOTTOM_RIGHT_BORDER.y))
	var clampedBottomRight = Vector2(min(bottomRight.x, BOTTOM_RIGHT_BORDER.x), 
										min(bottomRight.y, BOTTOM_RIGHT_BORDER.y))
	
	area.position = (clampedBottomRight + topLeft) * 0.5
	collisionShape.shape.extents = (clampedBottomRight - topLeft) * 0.5
	
