extends Item
const pets = [
	"Rat", "Squirrel", "Rat Chef", "Hedgehog", "Squirrel Archer", 
	"Hyper Hedgehog", "Carrot Goobert", "Snowmaster", "Forest Dragon", 
	"Toad", "Poison Goobert", "Poison Frog", "Ruby Chonk", "Frog Prince", 
	"Crow", "Ice Dragon", 
	"Courage Puppy", "Wisdom Puppy", "Power Puppy", 
	"Armored Courage Puppy", "Armored Wisdom Puppy", "Armored Power Puppy", 
	"Cheese Goobert", "Steel Dragon", 
	"Chili Goobert", "Fire Shelly", "Phoenix", "Phoenix2", 
	"Emerald Whelp", "Sapphire Whelp", "Amethyst Whelp", "Obsidian Dragon", 
	"Cat Spirit", "Owl Spirit", "Badger Spirit", "Cupcake Goobert", "Cupcake Dragon", 
	"Broccoli Goobert", "Dragon Knight", "Jynx Staff", 
	"Robodog", "Toast Goobert", "Mecha Bat", "Thunder Drake", 
	"Goobling", "Shelly", "Steel Goobert", "Blood Goobert", "Ruby Whelp", 
]
var petDescriptors = [[], [], [], [], []]
var salesChance

func onSaleRoll(item):
	pass

func getGatedDescriptor(rarity):
	pass

func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func doCooldownEffect():
	for item in getAffectedItems():
		item.giveDoubleActivationChance(getChance())
	
	activate()


func getRelatedItems():
	return ctx.util.flatten(petDescriptors)


func getRelatedItemColumns() -> int:
	return 6


func getRelatedItemHeight() -> int:
	return 100

func _readyInit():
	._readyInit()
	salesChance = getP("sale") / 100.0
	for pet in pets:
		var desc = ctx.item_book.getDescriptor(pet)
		if desc.isReleased():
			petDescriptors[desc.getRarity()].push_back(desc)

