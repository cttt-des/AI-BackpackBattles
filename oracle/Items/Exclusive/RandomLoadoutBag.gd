extends Bag



var mainBags = {
	Game.Classes.Ranger: ["Ranger Bag", "Vineweave Basket"], 
	Game.Classes.Reaper: ["Storage Coffin", "Relic Case"], 
	Game.Classes.Pyromancer: ["Fire Pit", "Portable Altar"], 
	Game.Classes.Berserker: ["Berserker Bag", "Toolbox"], 
	Game.Classes_Full.Mage: ["Scholar Bag", "Puzzlebox"], 
	Game.Classes_Full.Adventurer: ["Bag of Giving", "Sewing Case"], 
	Game.Classes_Full.Engineer: ["Engineer Box", "Engineer Bag 2"]
}

var compensationValue = {
	Game.Classes.Ranger: [0, 0], 
	Game.Classes.Reaper: [1, 0], 
	Game.Classes.Pyromancer: [2, 1], 
	Game.Classes.Berserker: [1, 0], 
	Game.Classes_Full.Mage: [0, 0], 
	Game.Classes_Full.Adventurer: [0, 0], 
	Game.Classes_Full.Engineer: [0, 0]
}

const bagRarityWeights = {
	Item.Rarity.Common: 2, 
	Item.Rarity.Rare: 0.5, 
	Item.Rarity.Epic: 0.2, 
	Item.Rarity.Legendary: 0.1, 
	Item.Rarity.Godly: 0.05, 
}

var excludeNames = [
	"Acorn Collar", 
	"Unstable Recombobulator", 
	"Draconic Orb", 
	"Stone Skin Potion", 
	"Divine Potion"
]

var bagBag = WeightedBag.new()
var pool = ItemPool.new()
var bagCells: Array

func _ready():
	Game.connect("run_started", self, "prepareParticles")
	Game.connect("pre_shop_opened_from_title", self, "shopOpened")

func addBagWherePossible(bag, startPos: Vector2):
	bag.ownerType = Owner.PlayerInventory
	Game.playerNode.add_child(bag)
	var inv = Game.PLAYER.INVENTORY
	for x in range(startPos.x, 9):
		var pos = Vector2(x, startPos.y)
		inv.orientItem(bag, pos, FaceDirection.UP)
		if inv.canAddBag(bag):
			inv.addItemByTopLeft(bag, pos)
			bagCells.append_array(bag.occupiedCells)
			bag.popIn()
			return
	Util.eassert(false)

func addItemWherePossible(item):
	item.ownerType = Owner.PlayerInventory
	Game.playerNode.add_child(item)
	var couldAdd = Game.PLAYER.INVENTORY.addItemWherePossible(item)
	if couldAdd:
		item.popIn()
	else:
		item.global_rotation = 0
		item.global_position = global_position
		item.pushToStorage()

func shopOpened():
	if ownerType != Owner.PlayerInventory:
		return
	
	inventory.removeItem(self)
	
	
	var value = 2
	
	var loadout = Util.rng.randi_range(0, 1)
	value += Game.getStartInventoryPrice(Game.curClass, loadout)
	value += compensationValue[Game.curClass][loadout]
	
	var mainBag = ItemBook.generateItem(mainBags[Game.curClass][loadout])
	addBagWherePossible(mainBag, Vector2(1, 2))
	value -= mainBag.getPrice()
	
	var bagBagWeights = {}
	for rarity in Rarity.Godly:
		for bag in ItemBook.bagsForRarity[rarity][Game.curClass]:
			bagBagWeights[bag] = bagRarityWeights[rarity]
	
	bagBag.prepare(bagBagWeights.values())
	var bag1 = ItemBook.generateItem(bagBagWeights.keys()[bagBag.roll()])
	value -= bag1.getPrice()
	addBagWherePossible(bag1, Vector2(3, 2))
	
	if Util.flip(0.7) or bagCells.size() < 10:
		var bag2
		if bagCells.size() <= 8:
			bag2 = ItemBook.generateItem("Leather Bag")
		else:
			bag2 = ItemBook.generateItem(bagBagWeights.keys()[bagBag.roll()])
		value -= bag2.getPrice()
		addBagWherePossible(bag2, Vector2(3, 2))
	
	var excludeDescriptors = {}
	for item in excludeNames:
		excludeDescriptors[ItemBook.getDescriptor(item)] = true
	
	var includeDescriptors = {}
	for gem in ItemBook.gemsForRarity[Rarity.Common]:
		includeDescriptors[gem] = true
	for amulet in ItemBook.amulets:
		includeDescriptors[amulet] = true
	
	for descriptor in ItemBook.items.values():
		if (descriptor in includeDescriptors or 
			(descriptor.isAvailableFor(Game.curClass) and 
			descriptor.rarity <= Item.Rarity.Godly and 
			not descriptor.isCraftedItem() and 
			not descriptor.isGatedItem() and 
			not descriptor.isBag() and 
			not descriptor.isTransient() and 
			not descriptor in excludeDescriptors and 
			not (descriptor.isWeapon() and descriptor.rarity >= Item.Rarity.Epic))):
			
			pool.addItem(descriptor)
	pool.pool.shuffle()
	pool.sortItems()
	
	while value > 0:
		pool.setPrice(value)
		var item = ItemBook.generateItem(pool.getRandomItemTopHeavy(0.9, 0.3))
		value -= item.getPrice()
		addItemWherePossible(item)
		
		
	
	discard()
	Game.saveRunState()
	Game.saveGame()

func prepareParticles():
	if ownerType == Owner.PlayerInventory:
		Util.callDelayed(self, "createRevealParticles", 0.4)

func createRevealParticles():
	var particles = ObjectPool.particleOneShot(Game.rainbowRevealParticles, Game.playerNode)
	particles.global_position = Vector2(400, 340)
	pass
