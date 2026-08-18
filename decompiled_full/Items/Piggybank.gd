extends Item

const breakSound = preload("res://Assets/Sound/JarBreaking.ogg")
const breakParticles = preload("res://Items/Particles/PiggyBreakParticles.tscn")

onready var piggyPinataDescriptor = ItemBook.getDescriptor("Piggy Pinata")
onready var hammerDescriptor = ItemBook.getDescriptor("Hammer")
onready var thorsHammerDescriptor = ItemBook.getDescriptor("Thors Hammer")

func onShopEntered():
	giveGold(getP1())
	explodeRandomly()
	
func explodeRandomly():
	if not isBaseItem() and not isBoundAsIngredient() and hasPinata():
		if Util.flipPercent(piggyPinataDescriptor.shopChance):
			explode()
			inventory.removeItem(self)
			discard()

func canAffect(item):
	return item.hasStartofBattle()

func onCombatStart():
	giveMaxHealth(getP_m("maxhealth") * getNumAffectedItems())
	consume()

func hasPinata() -> bool:
	return ItemBook.isItemInInventory(piggyPinataDescriptor)

func isSmashRecipe() -> bool:
	return (curRecipe.ingredients[0] == hammerDescriptor or 
			curRecipe.ingredients[0] == thorsHammerDescriptor)

func getFusionItemName() -> String:
	if isSmashRecipe() and hasPinata():
		return Util.tr("Piggy Pinata_CRAFT")
	return .getFusionItemName()

func allowGeneratingFusionItem() -> bool:
	if isSmashRecipe() and hasPinata():
		return false
	return true

var pinataFilter = ItemBook.Filter.Gems + ItemBook.Filter.Amulets

func explode():
	var particles = ObjectPool.particleOneShot(breakParticles, get_parent())
	particles.global_position = global_position
	Sound.playSound(breakSound)
	
	if hasPinata():
		var pool = ItemPool.new()
		for descr in ItemBook.items.values():
			if (descr != descriptor and 
				ItemBook.canBeGenerated(descr, pinataFilter)):
				
				pool.addItem(descr)
				
		pool.pool.shuffle()
		pool.sortItems()
		pool.sellPrice = true
		
		var value = 7


		while value > 0:
			pool.setPrice(value)
			var item = pool.getRandomItemTopHeavy()
			value -= item.getSellPrice()
			
			ItemBook.generateAndStorageItem(item, global_position)
		

func finishFusing():
	
	if isSmashRecipe():
		explode()
	
	.finishFusing()

func getShopPriority() -> int:
	return Priority.Lowest
