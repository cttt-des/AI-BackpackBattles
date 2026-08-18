extends Node2D

signal state_changed
signal state_added

const undoSound = preload("res://Assets/Sound/Switch.wav")
const MAX_STATES = 100

var states: = []
var curStateIndex: = - 1
var snapshotQueued: = false
var manualSnapshots = []
var tween

onready var label = $Label
onready var animation = $AnimationPlayer
onready var leftArrow = $LeftArrow
onready var rightArrow = $RightArrow

func _ready():
	call_deferred("ready_deferred")
	manualSnapshots.resize(10)
	label.modulate.a = 0
	leftArrow.modulate.a = 0
	rightArrow.modulate.a = 0

func ready_deferred():
	Game.connect("item_dropped", self, "onItemDropped")
	Game.connect("item_crafted", self, "onItemCrafted")
	Game.PLAYER.INVENTORY.connect("inventory_shifted", self, "onInventoryShifted")
	Game.STORAGEBOX.connect("pushed_all_to_storage", self, "onPushedAllToStorage")
	Game.connect("shop_opened", self, "onShopOpened")
	Game.connect("run_over", self, "clear")
	Game.connect("fresh_run_started", self, "clear")
	
func _unhandled_input(event):
	if InputBlocker.isActive(): return
	
	if Game.state != Game.State.Shop: return
	if Game.draggedItem != null: return
	
	if Util.isActionPressed_event(event, "undo"):
		Game.setTutorialDone(Game.TutorialSteps.Undo)
		undo()
		get_tree().set_input_as_handled()
	
	elif Util.isActionPressed_event(event, "redo"):
		redo()
		get_tree().set_input_as_handled()
		
	elif event is InputEventKey and event.is_pressed():
		
		if event.scancode >= KEY_0 and event.scancode <= KEY_9:
			var index = event.scancode - KEY_0
			if event.control:
				makeManualSnapshot(index)
				get_tree().set_input_as_handled()
			else:
				if manualSnapshots[index] != null:
					restoreSnapshop(index)
					get_tree().set_input_as_handled()
					

func onItemDropped(item, _dropRes):
	if item.hasSameOrientationAsPickup():
		
		return
	queueSnapshot()

func onItemCrafted(_itemDescriptor):
	queueSnapshot()

func onInventoryShifted():
	queueSnapshot()

func onPushedAllToStorage():
	queueSnapshot()

func onShopOpened():
	queueSnapshot()

func queueSnapshot():
	if not snapshotQueued:
		snapshotQueued = true
		call_deferred("call_deferred", "makeSnapshot")
		

func makeSnapshot():
	snapshotQueued = false
	
	if Game.state != Game.State.Shop: return
	if Game.draggedItem: return
	
	Game.writeoutState()
	
	
	states.resize(curStateIndex + 2)
	if states.size() > MAX_STATES:
		states.remove(0)
		curStateIndex -= 1
	
	
	var curState = InventoryState.new()
	curStateIndex += 1
	states[curStateIndex] = curState
	
	emit_signal("state_added")

func clear():
	states.clear()
	curStateIndex = - 1
	manualSnapshots.fill(null)

func canUndo() -> bool:
	return curStateIndex >= 1

func undo():
	if canUndo():
		Game.cancelSwitch()
		curStateIndex -= 1
		states[curStateIndex].restore()
		
		Sound.playSound(undoSound, - 2, Util.rng.randf_range(1.2, 1.3))
		showLabel(true)
		Game.writeoutState()
		emit_signal("state_changed")
		

func canRedo() -> bool:
	return states.size() > curStateIndex + 1

func redo():
	if canRedo():
		Game.cancelSwitch()
		curStateIndex += 1
		states[curStateIndex].restore()
		
		Sound.playSound(undoSound, - 2, Util.rng.randf_range(0.8, 0.9))
		showLabel(false)
		Game.writeoutState()
		emit_signal("state_changed")

func makeManualSnapshot(index):
	if Game.draggedItem:
		return
	
	var curState = InventoryState.new()
	manualSnapshots[index] = curState
	Sound.playSound(undoSound, 0, 1.4)
	Util.callDelayed(Sound, "playSound", 0.1, [undoSound, 0, 1.0])
	showLabelManual(index, false)

func restoreSnapshop(index):
	Game.cancelSwitch()
	manualSnapshots[index].restore()
	Sound.playSound(undoSound, - 2, Util.rng.randf_range(1.2, 1.3))
	Game.writeoutState()
	showLabelManual(index, true)

func showLabel(undo: bool):
	label.text = String(curStateIndex + 1) + "/" + String(states.size())
	Util.killTween(tween)
	tween = create_tween().set_parallel()
	tween.tween_property(label, "modulate:a", 1.0, 0.2)
	tween.tween_property(label, "modulate:a", 0.0, 0.2).set_delay(1.2).from(1.0)
	var showArrow
	var hideArrow
	if undo:
		showArrow = leftArrow
		hideArrow = rightArrow
	else:
		showArrow = rightArrow
		hideArrow = leftArrow
	tween.tween_property(showArrow, "modulate:a", 1.0, 0.2)
	tween.tween_property(showArrow, "modulate:a", 0.0, 0.2).set_delay(1.2).from(1.0)
	tween.tween_property(hideArrow, "modulate:a", 0.0, 0.1)
	animation.play("RestoreSnapshot")

func showLabelManual(slot, restore: bool):
	var t
	if restore:
		t = Util.tra("UI_LoadSnapshot")
	else:
		t = Util.tra("UI_SaveSnapshot")
	
	label.text = t.format({"slot": slot})
	Util.finishTween(tween)
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 1.0, 0.2)
	tween.tween_property(label, "modulate:a", 0.0, 0.2).set_delay(1).from(1.0)
	animation.play("RestoreSnapshot")

class InventoryState:
	
	var storageItems: Dictionary
	var bags: Dictionary
	var items: Dictionary
	var socketedGems: Dictionary
	var editMode: int
	
	func getTuple(item):
		return [item.getTopLeftCell(), item.getFaceDirection()]
	
	func _init():
		editMode = Game.inventoryEditMode
		var inv = Game.PLAYER.INVENTORY
		for item in inv.getItems():
			if item.isBag():
				if not CustomRules.getCannotPickBags():
					bags[item] = getTuple(item)
			else:
				items[item] = getTuple(item)
		
		for item in Game.STORAGEBOX.getItems():
			storageItems[item] = item.get_global_transform()
		
		for item in inv.getItems() + Game.STORAGEBOX.getItems():
			var socketI = 0
			for gem in item.getGems():
				if gem != null:
					socketedGems[gem] = [item, socketI, gem.getFaceDirection()]
				socketI += 1
	
		
	
	func printState():
		print("STORAGE")
		for item in storageItems:
			print(item.getName(), " ", storageItems[item])
		
		print("BAGS")
		for item in bags:
			print(item.getName(), " ", bags[item])
		
		print("INVENTORY")
		for item in items:
			print(item.getName(), " ", items[item])
		
		print("GEMS")
		for item in socketedGems:
			print(item.getName(), " ", socketedGems[item])
	
	
	func exists(item) -> bool:
		return is_instance_valid(item) and not item.sold
	
	func restore():
		Game.setInventoryEditMode(editMode)
		var leftOver: = {}
		var inv = Game.PLAYER.INVENTORY
		var invItems = inv.getItems().duplicate()
		
		
		for item in invItems:
			if item.isBag() and CustomRules.getCannotPickBags():
				continue
			
			item.onRestoreSnapshot()
			inv.removeItem(item)
			leftOver[item] = true
			
			for gem in item.getGemsNoNull():
				gem.unsocket()
				leftOver[gem] = true
		
		for item in Game.STORAGEBOX.getItems():
			item.onRestoreSnapshot()
			for gem in item.getGemsNoNull():
				gem.unsocket()
				leftOver[gem] = true
		
		for item in bags:
			if not exists(item):
				continue
				
			var topLeftCellPos = bags[item][0]
			var faceDirection = bags[item][1]
			
			if item.ownerType == Item.Owner.PlayerStorageBox:
				item.removeFromStorage()
			
			inv.orientItem(item, topLeftCellPos, faceDirection)
			if inv.canAddItemOrBag(item):
				inv.addItemByTopLeft(item, topLeftCellPos)
				leftOver.erase(item)
			
				
		
		for item in items:
			if not exists(item):
				continue
				
			var topLeftCellPos = items[item][0]
			var faceDirection = items[item][1]
			
			if item.ownerType == Item.Owner.PlayerStorageBox:
				item.removeFromStorage()
				item.ownerType = Item.Owner.Undefined
			
			if not item.visible:
				item.show()
				Game.setItemEditMode(item, false)
			
			item.scale = Vector2.ONE
			inv.orientItem(item, topLeftCellPos, faceDirection)
			
			if inv.canAddItemOrBag(item) or editMode != Game.InventoryEditMode.Default:
				inv.addItemByTopLeft(item, topLeftCellPos)
				leftOver.erase(item)
			else:
				
				leftOver[item] = true
		
		
		for gem in socketedGems:
			if not exists(gem):
				continue
			
			var item = socketedGems[gem][0]
			if not exists(item):
				continue
			
			var slotI = socketedGems[gem][1]
			var faceDir = socketedGems[gem][2]
			
			if gem.ownerType == Item.Owner.PlayerStorageBox:
				gem.removeFromStorage()
			gem.get_parent().remove_child(gem)
			item.setGem(slotI, gem)
			leftOver.erase(gem)
			
			
			if item.ownerType == Item.Owner.PlayerInventory:
				gem.onRemovedFromGridStorage()
			
		for item in storageItems:
			if not exists(item):
				continue
			
			if item.isBag() and CustomRules.getCannotPickBags():
				continue
			
			var transf: Transform2D = storageItems[item]
			if Game.STORAGEBOX.hasPosition(transf.get_origin()):
				leftOver.erase(item)
				item.set_global_transform(transf)
				if item.ownerType != Item.Owner.PlayerStorageBox:
					item.addToStorageBox(false, false, true)
			else:
				leftOver[item] = true
			
		
		var itemI = 0
		for item in leftOver:
			
			if item.ownerType == Item.Owner.PlayerStorageBox:
				item.global_position = Game.STORAGEBOX.center
				item.moveToFreeSpaceInStorage()
			else:
				var pos = Game.STORAGEBOX.getSuggestedPosition(itemI)
				item.global_position = pos
				item.addToStorageBox(false, false, true, pos)
				itemI += 1
		







