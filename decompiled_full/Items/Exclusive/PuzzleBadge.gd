extends Item

const puzzlebags = ["L", "S", "Z", "T", "J"]

onready var slowSpeed: = getP("speed") / 100.0
onready var fastSpeed: = getP("speed2") / 100.0

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
	return ItemBook.puzzleBags[rarity]

func getRelatedItems():
	return ItemBook.puzzleBags

func getRelatedItemColumns() -> int:
	return 2
