extends Item
var magicSpeed

func canAffect(item):
	return item.hasType(CoreConst.Type.Magic) and item.hasCooldown()


func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(magicSpeed)



func getRandomScroll():
	pass

func getRandomBook():
	pass

func _readyInit():
	._readyInit()
	magicSpeed = getP("speed") / 100.0
