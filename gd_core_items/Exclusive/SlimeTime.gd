extends Item
var gooblingDescriptor

func onBought():
	pass

func doCooldownEffect():
	for item in inventory.getItems():
		if canAffect_global(item):
			item.onItemActivated(null)
	activate()


func getGatedDescriptor(_rarity) -> CoreItemData:
	return gooblingDescriptor


func canAffect_global(item):
	return item is Goobert

func _readyInit():
	._readyInit()
	gooblingDescriptor = ctx.item_book.getDescriptor("Goobling")
