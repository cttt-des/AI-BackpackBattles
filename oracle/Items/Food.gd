extends Item
class_name Food

func canAffect(item):
	return item.hasType(Type.Food) and item.descriptor != descriptor
	
func prepare():
	.prepare()
	addSpeed(getNumAffectedItems() * 0.1)
