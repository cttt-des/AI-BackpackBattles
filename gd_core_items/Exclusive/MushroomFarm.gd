extends Item
var flyAgaricDescriptor
var doomCapDescriptor
var mushroomSpeed
var mushroomsNeeded
var activeLight

func onItemAdded(item):
	.onItemAdded(item)
	if isActive():
		pass


func onItemRemoved(item):
	.onItemRemoved(item)
	if not isActive():
		pass


func onRemoveFromInventory():
	pass


func canAffect(item):
	return item.isA(flyAgaricDescriptor) or item.isA(doomCapDescriptor)


func isActive():
	var numMushrooms = ctx.item_book.countPlacedItemsInInventoryOfType(flyAgaricDescriptor)
	numMushrooms += ctx.item_book.countPlacedItemsInInventoryOfType(doomCapDescriptor)
	return numMushrooms >= mushroomsNeeded


func onShopEntered():
	pass

func onCombatStart():




	
	for mushroom in getAffectedItems():
		mushroom.addSpeed(mushroomSpeed)
	
	activate()


func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	flyAgaricDescriptor = ctx.item_book.getDescriptor("Fly Agaric")
	doomCapDescriptor = ctx.item_book.getDescriptor("Doom Cap")
	mushroomSpeed = getP("speed") / 100.0
	mushroomsNeeded = getP("num")
