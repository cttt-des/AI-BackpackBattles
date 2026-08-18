extends Sprite



onready var bag = get_parent().get_parent()

func _ready() -> void :
	if (bag.ownerType == Item.Owner.Shop or 
		bag.ownerType == Item.Owner.PlayerInventory or 
		bag.ownerType == Item.Owner.PlayerStorageBox):
		hide()
		set_process(false)
		Game.connect("item_picked_up", self, "onItemPickedUp")
		Game.connect("item_dropped", self, "onItemDropped")
	else:
		queue_free()

func onItemPickedUp():
	if bag.placed:
		show()
		if bag.showBagBorderForItem(Game.draggedItem):
			set_process(true)
		else:
			
			self_modulate = Color(1.6, 1.6, 1.6, 0.0)

func onItemDropped(_item, dropResult):
	if dropResult != Item.DropResult.Hotswap or not bag.showBagBorderForItem(Game.draggedItem):
		set_process(false)
		hide()
		

func _process(delta):
	
	self_modulate = Color(1.3, 1.3, 1.3, 1)
	
	for cell in bag.occupiedCells:
		if bag.inventory.isHovered(cell):
			self_modulate = Color(2.5, 2.5, 2.5, 1)
			break

