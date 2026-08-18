extends Bag

onready var cogDescriptor = ItemBook.getDescriptor("Cog")

func onShopEntered():
	var cog = ItemBook.generateItem(cogDescriptor)
	placeGeneratedItem(cog, occupiedCells)
	activate()
	Game.saveRunState()

func onItemRoll(descr):
	if descr == cogDescriptor:
		ItemBook.multiplyWeight(0.0)

func getRelatedItems():
	return [cogDescriptor]
