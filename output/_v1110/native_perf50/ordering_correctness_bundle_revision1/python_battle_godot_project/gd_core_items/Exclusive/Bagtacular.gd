extends Item
var affectedBagDescriptors

func canAffect_global(item):
	return item.descriptor in affectedBagDescriptors

func _readyInit():
	._readyInit()
	affectedBagDescriptors = {
	ctx.item_book.getDescriptor("Fanny Pack"): true, 
	ctx.item_book.getDescriptor("Stamina Sack"): true, 
	ctx.item_book.getDescriptor("Potion Belt"): true, 
	ctx.item_book.getDescriptor("Protective Purse"): true
}
