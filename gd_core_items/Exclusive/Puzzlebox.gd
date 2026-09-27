extends Bag
const puzzlebags = ["L", "S", "Z", "T", "J"]
var slowSpeed
var fastSpeed

func canApplyEffect(toItem):
	return toItem.hasCooldown()


func onPrepare():
	for item in getAffectedItemsInside():
		item.reduceSpeed(slowSpeed)


func doCooldownEffect():
	for item in getAffectedItemsInside():
		item.addSpeed(slowSpeed + fastSpeed)
	onAfterEffectFinished()


func getReplaceDescriptor(rarity):
	pass

func getRelatedItemColumns() -> int:
	return 2

func _readyInit():
	._readyInit()
	slowSpeed = getP("speed") / 100.0
	fastSpeed = getP("speed2") / 100.0
