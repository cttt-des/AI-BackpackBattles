extends Item

const burstParticles1 = preload("res://Items/Exclusive/Particles/LootboxActivationParticles.tscn")
const burstParticles2 = preload("res://Items/Exclusive/Particles/LootboxActivationParticles2.tscn")
const treasureParticles = preload("res://Items/Exclusive/Particles/LootboxTreasureParticles.tscn")
const OFFSET = 50.0
const giveSound = preload("res://Assets/Sound/Confetti3.ogg")
const chestSound = preload("res://Assets/Sound/ChestOpening1.wav")

onready var itemValue: = int(getP("gold"))

var filters = (ItemBook.Filter.Gated + 
					ItemBook.Filter.Crafted)

func _ready():
	connect("dropped", self, "onDropped")

func onDropped(dropRes):
	if (wasAddedToInventory(dropRes) or 
		dropRes == DropResult.AddedToStorageBox):
		
		prepareReplacement()
		call_deferred("generateItems", dropRes)

func generateItems(dropResult):
	if wasAddedToInventory(dropResult):
		inventory.removeItem(self)
		discard()
	else:
		Game.STORAGEBOX.removeItem(self)
		collisionShape.disabled = true
		discard()
	
	var itemI = 0
	
	var canGenerateTreasures = ItemBook.getTreasureCapacity() > 0
	if canGenerateTreasures and rollShopChance():
		var descr = ItemBook.getRandomTreasureDescriptor(itemValue)
		var treasure = ItemBook.generateAndStorageItem(descr, global_position, 
			global_position - Vector2(0, OFFSET))
		itemI += 1
		itemValue -= treasure.getPrice()
		treasure.popIn(false, 1.5)
		Util.callDelayed(ObjectPool, "particleOneShot", 0.15, 
			[treasureParticles, get_parent(), global_position])
	
	var itemPool = ItemPool.new()
	for descriptor in ItemBook.items.values():
		if ItemBook.canBeGenerated(descriptor, filters):
			itemPool.addItem(descriptor)
	itemPool.sortItems()
	
	itemPool.setPrice(itemValue)
	var value = itemValue
	while value > 0:
		itemI += 1
		var descr = itemPool.getRandomItem()
		value -= descr.getPrice()
		itemPool.setPrice(value)
		var item = ItemBook.generateAndStorageItem(descr, global_position, 
			global_position - Vector2(0, OFFSET * itemI))
		item.popIn(false, 1.5)
		
	
	
	
	var particles1 = ObjectPool.particleOneShot(burstParticles1, get_parent(), 
		global_position)
	var particles2 = ObjectPool.particleOneShot(burstParticles2, get_parent(), 
		global_position)
	
	Sound.playSound(giveSound, - 2)
	Sound.playSound(chestSound, 2)
	Game.saveRunState()
	finishReplacement()
