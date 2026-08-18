extends Item

onready var flyAgaricDescriptor = ItemBook.getDescriptor("Fly Agaric")
onready var doomCapDescriptor = ItemBook.getDescriptor("Doom Cap")
onready var mushroomSpeed: = getP("speed") / 100.0
onready var mushroomsNeeded: = getP("num")

onready var activeLight = $Icon / Active

func onItemAdded(item):
	.onItemAdded(item)
	if isActive():
		activeLight.show()

func onItemRemoved(item):
	.onItemRemoved(item)
	if not isActive():
		activeLight.hide()

func onRemoveFromInventory():
	activeLight.hide()

func canAffect(item):
	return item.isA(flyAgaricDescriptor) or item.isA(doomCapDescriptor)

func isActive():
	var numMushrooms = ItemBook.countPlacedItemsInInventoryOfType(flyAgaricDescriptor)
	numMushrooms += ItemBook.countPlacedItemsInInventoryOfType(doomCapDescriptor)
	return numMushrooms >= mushroomsNeeded

func onShopEntered():
	if isActive():
		var mushroom = ItemBook.generateAndStorageItem(flyAgaricDescriptor, global_position)
		activate()
		Game.saveRunState()

func onCombatStart():




	
	for mushroom in getAffectedItems():
		mushroom.addSpeed(mushroomSpeed)
	
	activate()

func onItemRoll(descr):
	if descr == flyAgaricDescriptor:
		var num = ItemBook.countOwnedItemsOfType(flyAgaricDescriptor)
		num += ItemBook.countOwnedItemsOfType(doomCapDescriptor)
		if num < mushroomsNeeded:
			ItemBook.multiplyWeight(1.7)
