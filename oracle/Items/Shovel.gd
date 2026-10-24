extends Weapon

const blindParticles = preload("res://Items/Particles/DirtParticles.tscn")
const shovelSound = preload("res://Assets/Sound/Shovel.mp3")

const filters = (ItemBook.Filter.Gems
	+ ItemBook.Filter.Amulets
	+ ItemBook.Filter.OtherClasses
	+ ItemBook.Filter.Crafted)

onready var digParticles = $DigParticles
onready var spawnPos = $Position2D

var digUpBag = WeightedBag.new()
var digUpItems = {
	"Stone": 4, 
	"Garlic": 3, 
	"Blueberries": 2, 
	"Lump of Coal": 3, 
	"Pocket Sand": 3, 
	"Chipped Ruby": 1, 
	"Chipped Sapphire": 1, 
	"Chipped Emerald": 1, 
	"Chipped Topaz": 1, 
	"Chipped Amethyst": 1, 
	"Healing Herbs": 0.5, 
	"Bag of Stones": 0.5, 
	"Walrus Tusk": 0.2, 
	"Whetstone": 0.2, 
	"Piggybank": 0.2, 
	"Pan": 0.2, 
	"Customer Card": 0.2, 
	"Gloves of Haste": 0.2, 
	"Dagger": 0.2, 
	"Protective Purse": 0.1, 
	"Flawed Ruby": 0.2, 
	"Flawed Sapphire": 0.2, 
	"Flawed Emerald": 0.2, 
	"Flawed Topaz": 0.2, 
	"Flawed Amethyst": 0.2, 
}

func _ready() -> void :
	
	
	if Game.curClass == Game.Classes.Ranger:
		digUpItems["Carrot"] = 2
		digUpItems["Lucky Clover"] = 2
	elif Game.curClass == Game.Classes.Reaper:
		digUpItems["Fly Agaric"] = 2
	
	if Game.showExclusiveContent():
		digUpItems["Shiny Shell"] = 3
	
	digUpBag.prepare(digUpItems.values())

func onShopEntered():
	var dugUpItem
	if ItemBook.isItemInInventory(ItemBook.digDeeperDescriptor):
		var itemPool = ItemPool.new()
		
		var value = Util.flipWeighted([1, 2, 2, 0.5]) + 3
		
		for descriptor in ItemBook.items.values():
			if (descriptor.price == value and 
				ItemBook.canBeGenerated(descriptor, filters)):
				
				itemPool.addItem(descriptor)
		itemPool.resetPrice()
		dugUpItem = itemPool.getRandomItem()
	else:
		dugUpItem = digUpItems.keys()[digUpBag.roll()]
	
	var item = ItemBook.generateAndStorageItem(dugUpItem, spawnPos.global_position)
	activate(null, false)
	Game.saveRunState()
	digParticles.global_rotation = 0
	digParticles.activate()
	Sound.playSound(shovelSound)

func onDealtDamage(damageRes):
	if damageRes.hasHit():
		if rollChance():
			inflictBlind(1, damageRes.event)
			var particles = ObjectPool.particleOneShot(blindParticles, sprite)
			particles.position = Vector2(0, 230)
			particles.global_rotation = 0
