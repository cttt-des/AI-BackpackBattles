extends Bag
var cogDescriptor

func onShopEntered():
	pass

func onItemRoll(descr):
	pass

func getRelatedItems():
	return [cogDescriptor]

func _readyInit():
	._readyInit()
	cogDescriptor = ctx.item_book.getDescriptor("Cog")
