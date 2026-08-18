extends Item

onready var shovelDescriptor = ItemBook.getDescriptor("Shovel")
onready var shovelDogDescriptor = ItemBook.getDescriptor("Robodog")
onready var blind: = int(getP("blind"))

func onCombatStart():
	inflictBlind(blind)

func canAffect_global(item):
	return item.isA(shovelDescriptor) or item.isA(shovelDogDescriptor)
