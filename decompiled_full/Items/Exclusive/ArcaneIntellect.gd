extends Item

onready var magicSpeed: = getP("speed") / 100.0

func canAffect(item):
	return item.hasType(Type.Magic) and item.hasCooldown()

func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(magicSpeed)


func getRandomScroll():
	return ItemBook.scrolls.pick_random()

func getRandomBook():
	return ItemBook.books.pick_random()
