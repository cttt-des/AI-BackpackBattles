extends Item

var amuletsBoosted = 0
onready var relatedItems: = [
		ItemBook.magicRingDescriptor, 
		ItemBook.amuletDescriptor, 
		ItemBook.bloodAmuletDescriptor, 
	]

onready var salesChance: = getP("sales") / 100.0

func canAffect(item):
	return (item.isA(ItemBook.magicRingDescriptor) or 
			item.isA(ItemBook.superiorRingDescriptor))

func onBought():
	amuletsBoosted = 3
	var gem = ItemBook.generateAndStorageItem(
		ItemBook.getGemOfRarity(Rarity.Common), 
		global_position)
	gem.createGemParticles()
	activate()
	Game.saveRunState()

func getData():
	return amuletsBoosted

func setData(data):
	if data != null:
		amuletsBoosted = data

func onItemRoll(descr):
	if descr == ItemBook.amuletDescriptor and amuletsBoosted > 0:
		ItemBook.multiplyWeight(1.7)

func onItemRolled(descr):
	if descr == ItemBook.amuletDescriptor:
		amuletsBoosted -= 1

func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
		item.changeAmplificiationChancePercent_allDebuffs(getChance())

func onSaleRoll(item):
	if (item != null and (
		item.isA(ItemBook.amuletDescriptor) or 
		item.isA(ItemBook.bloodAmuletDescriptor))):
				Game.shopSceneNode.addBonusSalesChance(salesChance)


func getRestockItem():
	var items: = [
		ItemBook.magicRingDescriptor, 
		ItemBook.amuletDescriptor, 
		ItemBook.bloodAmuletDescriptor, 
	]
	var weights: = [
		100, 
		35, 
		4
	]
	
	var bag = WeightedBag.new()
	var index = bag.rollOnce(weights)
	return items[index]

func getRelatedItems() -> Array:
	return relatedItems

var chanceAcc: = 0.0

func rollShopChance(shopChance = descriptor.shopChance) -> bool:
	if chanceAcc > Util.rng.randf_range(85, 125):
		chanceAcc = 0
		return true
		
	var roll = .rollShopChance(shopChance)
	if roll:
		chanceAcc = 0
		return true
	else:
		chanceAcc += shopChance
		return false
