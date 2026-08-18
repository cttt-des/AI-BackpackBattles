extends Item

onready var gooblingDescriptor = ItemBook.getDescriptor("Goobling")

func onBought():
	var goobling = ItemBook.generateAndStorageItem(gooblingDescriptor, global_position)
	Game.saveRunState()
	activate()

func doCooldownEffect():
	for item in inventory.getItems():
		if canAffect_global(item):
			item.onItemActivated(null)
	activate()

func getGatedDescriptor(_rarity) -> ItemDescriptor:
	return gooblingDescriptor

func canAffect_global(item):
	return item is Goobert
