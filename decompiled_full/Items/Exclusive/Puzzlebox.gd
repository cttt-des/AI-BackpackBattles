extends Bag

const puzzlebags = ["L", "S", "Z", "T", "J"]

onready var slowSpeed: = getP("speed") / 100.0
onready var fastSpeed: = getP("speed2") / 100.0

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
	return ItemBook.puzzleBags[rarity]

func getRelatedItemColumns() -> int:
	return 2
