extends Item
const puzzlebags = ["L", "S", "Z", "T", "J"]
var slowSpeed
var fastSpeed

func canAffect(item):
	return item.hasCooldown()


func onPrepare():
	for item in getAffectedItems():
		item.reduceSpeed(slowSpeed)


func doCooldownEffect():
	for item in getAffectedItems():
		item.addSpeed(slowSpeed + fastSpeed)
	onAfterEffectFinished()


func getReplaceDescriptor(rarity):
	pass

func getRelatedItems():
	pass

func getRelatedItemColumns() -> int:
	return 2

func _readyInit():
	._readyInit()
	slowSpeed = getP("speed") / 100.0
	fastSpeed = getP("speed2") / 100.0
