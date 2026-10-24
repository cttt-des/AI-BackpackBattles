extends Item

onready var affectedBagDescriptors = {
	ItemBook.getDescriptor("Fanny Pack"): true, 
	ItemBook.getDescriptor("Stamina Sack"): true, 
	ItemBook.getDescriptor("Potion Belt"): true, 
	ItemBook.getDescriptor("Protective Purse"): true
}

func canAffect_global(item):
	return item.descriptor in affectedBagDescriptors
