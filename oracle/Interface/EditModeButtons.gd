extends Node2D

onready var defaultButton = $Default
onready var bagLayerButton = $BagLayer
onready var itemLayerButton = $ItemLayer

func _ready():
	Game.connect("edit_mode_changed", self, "onEditModeChanged")
	defaultButton.connect("pressed", self, "onDefaultPressed")
	bagLayerButton.connect("pressed", self, "onBagLayerPressed")
	itemLayerButton.connect("pressed", self, "onItemLayerPressed")
	

func _unhandled_input(event):
	if Util.isActionPressed_event(event, "edit_all"):
		onDefaultPressed()
	elif Util.isActionPressed_event(event, "edit_bags"):
		onBagLayerPressed()
	elif Util.isActionPressed_event(event, "edit_items"):
		onItemLayerPressed()

func isInteractable() -> bool:
	return ( not InputBlocker.isActive() and 
			Game.draggedItem == null and 
			Game.isShopActive())

func onDefaultPressed():
	if not isInteractable(): return
	if Game.inventoryEditMode != Game.InventoryEditMode.Default:
		Game.setInventoryEditMode(Game.InventoryEditMode.Default)
		Game.cancelSwitch()

func onBagLayerPressed():
	if not isInteractable(): return
	if Game.inventoryEditMode != Game.InventoryEditMode.BagLayer:
		Game.setInventoryEditMode(Game.InventoryEditMode.BagLayer)
	else:
		Game.setInventoryEditMode(Game.InventoryEditMode.Default)
	Game.cancelSwitch()

func onItemLayerPressed():
	if not isInteractable(): return
	if Game.inventoryEditMode != Game.InventoryEditMode.ItemLayer:
		Game.setInventoryEditMode(Game.InventoryEditMode.ItemLayer)
	else:
		Game.setInventoryEditMode(Game.InventoryEditMode.Default)
	Game.cancelSwitch()

func onEditModeChanged():
	match Game.inventoryEditMode:
		Game.InventoryEditMode.Default:
			defaultButton.set_pressed(true)
		Game.InventoryEditMode.BagLayer:
			bagLayerButton.set_pressed(true)
		Game.InventoryEditMode.ItemLayer:
			itemLayerButton.set_pressed(true)
