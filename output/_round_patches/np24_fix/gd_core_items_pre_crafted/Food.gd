extends Item
class_name Food

func canAffect(item):
	return item.hasType(CoreConst.Type.Food) and item.descriptor != descriptor
	

func prepare():
	.prepare()
	addSpeed(getNumAffectedItems() * 0.1)

func _readyInit():
	._readyInit()
	pass
