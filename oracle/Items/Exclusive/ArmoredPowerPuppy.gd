extends "res://Items/Exclusive/PowerPuppy.gd"

func canAffect(item):
	return item.hasType(Type.Food) or item.hasType(Type.Pet)

func onPrepare():
	var numFood = 0
	var numPets = 0
	for item in getAffectedItems():
		if item.hasType(Type.Food):
			numFood += 1
		elif item.hasType(Type.Pet):
			numPets += 1
	
	addSpeed((numPets * getP4() + numFood * getP5()) / 100.0)
	options = [0, 1, 2]
