extends FocusGrabbingControl


var physicalItems: Array
var item = null
var defaultSize
var multiplicityLabel
var labelNode
var labelPos: Vector2
var pickingEnabled: bool
var panel

func preset():
	multiplicityLabel = $Node2D / Multiplicity
	defaultSize = rect_size
	labelNode = $Node2D
	labelPos = labelNode.position
	panel = $Panel

func _ready():
	Util.tryConnect(self, "gui_input", self, "_gui_input")
	
	

func setItems(itemList: Array, wasJustAdded: bool, itemMaxScale):
	physicalItems = itemList
	var descriptor = itemList[0].descriptor
	item = descriptor.instantiate_pooled()
	item.ownerType = item.Owner.GridStorage
	add_child(item)
	item.initGridStorageIcon()
	item.scaleToFit(rect_min_size - Vector2(2, 2), itemMaxScale)
	
	item.position = rect_min_size * 0.5
	item.position += item.getSpriteOffset() * 2.0
	
	if itemList.size() == 1:
		multiplicityLabel.hide()
	else:
		multiplicityLabel.show()
		multiplicityLabel.text = str(itemList.size())
		labelNode.position = labelPos * (rect_min_size / defaultSize)
	
	panel.modulate = Game.rarityColors[descriptor.getRarity()].lightened(0.5)
	
	setEditable()
	if Game.inventoryEditMode == Game.InventoryEditMode.BagLayer:
		if not descriptor.isBag():
			setNotEditable()
	elif Game.inventoryEditMode == Game.InventoryEditMode.ItemLayer:
		if descriptor.isBag():
			setNotEditable()
	
	if wasJustAdded:
		item.popIn(true, 1.2)
	
	
	if item.isA(ItemBook.magicRingDescriptor) or item.isA(ItemBook.superiorRingDescriptor):
		item.copyFrom(physicalItems[ - 1])

func setNotEditable():
	panel.modulate = Color(0.5, 0.5, 0.5)
	item.modulate.a = 0.5
	pickingEnabled = false
	item.disableFocus()
	item.disableTooltip()

func setEditable():
	pickingEnabled = true

func onHover():
	.onHover()
	item.hover()
	for physicalItem in physicalItems:
		physicalItem.previewFusions()

func onHoverEnd():
	.onHoverEnd()
	item.hoverEnd()

func _gui_input(event):
	if pickingEnabled and Util.isClickEvent(event):
		Game.cancelSwitch()
		var itemToPick = physicalItems.pop_back()
		itemToPick.global_position = get_global_mouse_position()
		itemToPick.show()
		itemToPick.enablePicking()
		
		itemToPick.pickup()
		Game.gridStorage.rebuild()

func returnToObjectPool():
	if item != null:
		item.discard()
	item = null
	physicalItems.clear()
	ObjectPool.returnInstance(self)
