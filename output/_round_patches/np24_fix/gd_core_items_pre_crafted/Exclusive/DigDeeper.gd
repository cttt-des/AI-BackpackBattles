extends Item
var shovelDescriptor
var shovelDogDescriptor
var blind

func onCombatStart():
	inflictBlind(blind)


func canAffect_global(item):
	return item.isA(shovelDescriptor) or item.isA(shovelDogDescriptor)

func _readyInit():
	._readyInit()
	shovelDescriptor = ctx.item_book.getDescriptor("Shovel")
	shovelDogDescriptor = ctx.item_book.getDescriptor("Robodog")
	blind = int(getP("blind"))
