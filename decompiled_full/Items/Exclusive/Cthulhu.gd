extends Item

onready var foodSpeed: = getP("speed") / 100.0
onready var dam: = getP("dam")

var affectedFood: Array

func canAffect(item):
	return item.hasType(Type.Food) or item.hasType(Type.Dark)









func onAffectedItemAdded(item, color: int):
	if item.hasType(Type.Food):
		item.addDynamicType(Type.Dark, self)

func onAffectedItemRemoved(item, color: int):
	item.removeDynamicType(Type.Dark, self)

func onPrepare():
	affectedFood.clear()
	for item in getAffectedItems():
		if item.hasType(Type.Food):
			affectedFood.push_back(item)
	
	addSpeed(foodSpeed * getNumAffectedItems())

func doCooldownEffect():
	stealLife(dam, getP_m("lifesteal") / 100.0)
	activate()
	if not affectedFood.empty():
		Util.pickRandomElement(affectedFood).doCooldownEffect()
