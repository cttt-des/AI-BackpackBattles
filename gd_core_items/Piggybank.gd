extends Item
var piggyPinataDescriptor
var hammerDescriptor
var thorsHammerDescriptor

func onShopEntered():
	giveGold(getP1())
	explodeRandomly()
	

func explodeRandomly():
	if not isBaseItem() and not isBoundAsIngredient() and hasPinata():
		if ctx.util.flipPercent(piggyPinataDescriptor.shopChance):
			explode()
			inventory.removeItem(self)
			discard()


func canAffect(item):
	return item.hasStartofBattle()


func onCombatStart():
	giveMaxHealth(getP_m("maxhealth") * getNumAffectedItems())
	consume()


func hasPinata() -> bool:
	return ctx.item_book.isItemInInventory(piggyPinataDescriptor)


func isSmashRecipe() -> bool:
	return (curRecipe.ingredients[0] == hammerDescriptor or 
			curRecipe.ingredients[0] == thorsHammerDescriptor)


func getFusionItemName() -> String:
	if isSmashRecipe() and hasPinata():
		return ctx.util.tr("Piggy Pinata_CRAFT")
	return .getFusionItemName()


func allowGeneratingFusionItem() -> bool:
	if isSmashRecipe() and hasPinata():
		return false
	return true


func explode():
	pass

func finishFusing():
	
	if isSmashRecipe():
		explode()
	
	.finishFusing()


func getShopPriority() -> int:
	return CoreConst.Priority.Lowest

func _readyInit():
	._readyInit()
	piggyPinataDescriptor = ctx.item_book.getDescriptor("Piggy Pinata")
	hammerDescriptor = ctx.item_book.getDescriptor("Hammer")
	thorsHammerDescriptor = ctx.item_book.getDescriptor("Thors Hammer")
