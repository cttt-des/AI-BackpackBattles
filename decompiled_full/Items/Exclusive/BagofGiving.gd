extends Bag

const giveSound = preload("res://Assets/Sound/Confetti3.ogg")

onready var activationParticles = $ActivationParticles
onready var maxStamina: = getP("stamina")

var filters = (ItemBook.Filter.OtherClasses + 
					ItemBook.Filter.Gated + 
					ItemBook.Filter.Crafted)

func canApplyEffect(toItem):
	return toItem.isClassItem()

func onPrepare():
	for item in getAffectedItemsInside():
		connectForCombat(item, "activated", "onItemInsideActivated")

func onItemInsideActivated(event):
	giveMaxStaminaTemporary(maxStamina, event)
	miniActivate()

func onAddToInventory():
	ItemBook.updateClass(self)

func onRemoveFromInventory():
	.onRemoveFromInventory()
	ItemBook.updateClass(self)











func onShopEntered():
	var itemPool = ItemPool.new()
	
	for descriptor in ItemBook.items.values():
		if ItemBook.canBeGenerated(descriptor, filters):
			itemPool.addItem(descriptor)
	itemPool.sortItems()

	var g = Game.getGold()
	Game.spendGold(g)
	
	var giftValue = ceil(g * getP("value"))
	itemPool.setPrice(giftValue)
	
	var bagGiven: = false
	
	while giftValue > 0:
		var giftedDescriptor
		if not bagGiven and Util.flip(0.18):
			giftedDescriptor = ItemBook.getRandomBagDescriptor()
		else:
			giftedDescriptor = itemPool.getRandomItem()
		
		if giftedDescriptor.isBag():
			bagGiven = true
		
		giftValue -= giftedDescriptor.price
		itemPool.setPrice(giftValue)
		
		var item = ItemBook.generateAndStorageItem(giftedDescriptor, global_position)
		
	activationParticles.global_rotation_degrees = 80
	activationParticles.activate()

	Sound.playSound(giveSound, - 2)
	activate()
	Game.saveRunState()

func getShopPriority() -> int:
	return Priority.Low

func getRelatedItems():
	var related = []
	for classI in Game.Classes_Full.values():
		if Game.isClassUnlocked(classI) and classI != Game.Classes_Full.Adventurer:
			related.append_array(ItemBook.getShopItemsForClass(classI))
	return related

func getRelatedItemColumns() -> int:
	return 6

func getRelatedItemHeight() -> int:
	return 110
