extends Item

const giveSound = preload("res://Assets/Sound/Confetti3.ogg")

var presentFilters = (ItemBook.Filter.OtherClasses + 
							ItemBook.Filter.Gated + 
							ItemBook.Filter.Crafted + 
							ItemBook.Filter.AnyRarity + 
							ItemBook.Filter.IgnoreWeight)

onready var activationParticles = $ActivationParticles




func onCombatStart():
	giveRandomBuffs(getP1())
	activate()












func onShopEntered():













	var presentPool = ItemPool.new()
	
	for descriptor in ItemBook.items.values():
		if ItemBook.canBeGenerated(descriptor, presentFilters):
			presentPool.addItem(descriptor)
	presentPool.sortItems()
	
	var g = Game.getGold()
	Game.spendGold(g)
	
	var giftValue = ceil(g * getP2())
	presentPool.setPrice(giftValue)
	
	while giftValue > 0:
		
		var giftedDescriptor
		if Util.flip(0.06):
			giftedDescriptor = ItemBook.getRandomBagDescriptor()
		else:
			giftedDescriptor = presentPool.getRandomItem()
		
		giftValue -= giftedDescriptor.price
		presentPool.setPrice(giftValue)
		
		var item = ItemBook.generateAndStorageItem(giftedDescriptor, global_position)
		
	activationParticles.global_rotation = 0
	activationParticles.activate()
	animation.play("GivePresent")
	Sound.playSound(giveSound, - 2)
	Game.saveRunState()
	
func getShopPriority() -> int:
	return Priority.Low + 1
