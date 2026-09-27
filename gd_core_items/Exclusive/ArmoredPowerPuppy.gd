extends "res://gd_core_items/Exclusive/PowerPuppy.gd"

func canAffect(item):
	return item.hasType(CoreConst.Type.Food) or item.hasType(CoreConst.Type.Pet)


func onPrepare():
	var numFood = 0
	var numPets = 0
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Food):
			numFood += 1
		elif item.hasType(CoreConst.Type.Pet):
			numPets += 1
	
	addSpeed((numPets * getP4() + numFood * getP5()) / 100.0)
	options = [0, 1, 2]

func _readyInit():
	._readyInit()
	pass
