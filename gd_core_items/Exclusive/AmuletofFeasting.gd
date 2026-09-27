extends Item
const amuletColor = Color(0.929412, 0.498039, 0.180392)
var foodSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(foodSpeed)


func getReplaceDescriptor(rarity) -> CoreItemData:
	return null

func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 4

func _readyInit():
	._readyInit()
	foodSpeed = getP("foodspeed") / 100.0
	pass

