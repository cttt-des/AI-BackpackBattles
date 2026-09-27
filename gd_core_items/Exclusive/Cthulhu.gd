extends Item
var affectedFood: Array
var foodSpeed
var dam

func canAffect(item):
	return item.hasType(CoreConst.Type.Food) or item.hasType(CoreConst.Type.Dark)










func onAffectedItemAdded(item, color: int):
	if item.hasType(CoreConst.Type.Food):
		item.addDynamicType(CoreConst.Type.Dark, self)


func onAffectedItemRemoved(item, color: int):
	item.removeDynamicType(CoreConst.Type.Dark, self)


func onPrepare():
	affectedFood.clear()
	for item in getAffectedItems():
		if item.hasType(CoreConst.Type.Food):
			affectedFood.push_back(item)
	
	addSpeed(foodSpeed * getNumAffectedItems())


func doCooldownEffect():
	stealLife(dam, getP_m("lifesteal") / 100.0)
	activate()
	if not affectedFood.empty():
		ctx.util.pickRandomElement(affectedFood).doCooldownEffect()

func _readyInit():
	._readyInit()
	foodSpeed = getP("speed") / 100.0
	dam = getP("dam")
