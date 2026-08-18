extends Item

onready var salesChance: = getP("sale") / 100.0

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

func _ready():
	for pet in pets:
		var desc = ItemBook.getDescriptor(pet)
		if desc.isReleased():
			petDescriptors[desc.getRarity()].push_back(desc)

func onSaleRoll(item):
	if item != null and item.hasType(Type.Pet):
		Game.shopSceneNode.addBonusSalesChance(salesChance)

func getGatedDescriptor(rarity):
	var pets = petDescriptors[rarity]
	pets.shuffle()
	for pet in pets:
		if pet in ItemBook.spiritCompanionDescriptors:
			if not ItemBook.canHaveMoreCompanions():
				continue
		return pet

func canAffect(item):
	return item.hasType(Type.Pet)

func doCooldownEffect():
	for item in getAffectedItems():
		item.giveDoubleActivationChance(getChance())
	
	activate()

func getRelatedItems():
	return Util.flatten(petDescriptors)

func getRelatedItemColumns() -> int:
	return 6

func getRelatedItemHeight() -> int:
	return 100
