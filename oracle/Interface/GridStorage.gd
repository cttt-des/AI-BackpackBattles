extends Node2D

signal toggled

const entryScene = preload("res://Interface/GridStorageEntry.tscn")
const itemScale = {
	3: 1.0, 
	4: 0.85, 
	5: 0.7, 
	6: 0.7, 
	7: 0.7
}

onready var scrollContainer = $ScrollContainer
onready var gridContainer = $ScrollContainer / GridContainer
onready var defaultZIndex = z_index

var rebuildQueued: bool
var newItems: Dictionary
var descriptorToEntry: Dictionary

func _ready():
	Game.gridStorage = self
	if visible:
		Game.STORAGEBOX.connect("item_added", self, "onItemAddedToStorage")
		Game.STORAGEBOX.connect("item_removed", self, "onItemRemovedFromStorage")
		Game.STORAGEBOX.connect("storage_cleared", self, "onStorageCleared")
		Game.connect("edit_mode_changed", self, "onEditModeChanged")
		Game.connect("return_to_title", self, "onReturningToTitle")
		Game.connect("shop_opened", self, "onShopEntered")
		Game.undoStack.connect("state_changed", self, "onUndoStateChanged")
		scrollContainer.connect("zoomed", self, "onZoomed")
		ObjectPool.prepare(entryScene, 30)
	hide()
	
func onItemAddedToStorage(item):
	if visible:
		item.onAddedToGridStorage()
	
	newItems[item.descriptor] = true
	rebuild()

func onItemRemovedFromStorage(item):
	if visible:
		item.onRemovedFromGridStorage()
	
	rebuild()

func onStorageCleared():
	rebuild()

func onUndoStateChanged():
	rebuild()


func rebuild():
	if not rebuildQueued:
		rebuildQueued = true
		call_deferred("actuallyRebuild")

func clear():
	descriptorToEntry.clear()
	for entry in gridContainer.get_children():
		entry.returnToObjectPool()

func actuallyRebuild():
	rebuildQueued = false
	clear()
	
	if not visible: return
	
	var itemDict = Game.STORAGEBOX.getItemsAndGemsByDescriptor()
	var scores: = {}
	for descriptor in itemDict:
		scores[descriptor] = getScore(descriptor)
	var sorted = Util.sortDict(scores)
	
	var margin = gridContainer.get("custom_constants/hseparation")
	var usableWidth = 420 - (gridContainer.columns - 1) * margin
	var widthPerEntry = usableWidth / gridContainer.columns
	
	for descriptor in sorted:
		var entry = ObjectPool.instance(entryScene)
		entry.rect_min_size.x = widthPerEntry
		entry.rect_min_size.y = entry.rect_min_size.x
		
		gridContainer.add_child(entry)
		entry.setItems(itemDict[descriptor], descriptor in newItems, 
			itemScale[gridContainer.columns])
		descriptorToEntry[descriptor] = entry
	
	newItems.clear()

func _unhandled_input(event):
	if Util.isActionPressed_event(event, "toggle_grid_storage"):
		if visible:
			close()
		else:
			open()

func open():
	show()
	for item in Game.STORAGEBOX.getItemsAndGems():
		item.onAddedToGridStorage()
	rebuild()
	scrollContainer.onOpen()
	emit_signal("toggled")

func close():
	hide()
	for item in Game.STORAGEBOX.getItemsAndGems():
		item.onRemovedFromGridStorage()
	clear()
	scrollContainer.onClose()
	emit_signal("toggled")

func getScore(descriptor) -> float:
	var score = 0
	if descriptor.isBag():
		score += 1000000
	
	score += descriptor.getRarity() * 10000
	score += descriptor.getPrice()
	score += descriptor.itemIndex * 0.0001
	
	if descriptor.isGem():
		score -= 1000000
	
	return score

func onEditModeChanged():
	rebuild()

func getProxy(forItem):
	if forItem.descriptor in descriptorToEntry:
		return descriptorToEntry[forItem.descriptor].item
	else:
		return null

func onReturningToTitle():
	z_index = 10

func onShopEntered():
	z_index = defaultZIndex

func onZoomed(amount):
	var colums = clamp(gridContainer.columns + amount, 3, 7)
	if gridContainer.columns != colums:
		gridContainer.columns = colums
		rebuild()
