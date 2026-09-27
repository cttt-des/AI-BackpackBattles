extends Item
var amuletsBoosted = 0
var chanceAcc: = 0.0
var relatedItems
var salesChance

func canAffect(item):
	return (item.isA(ctx.item_book.getDescriptor("Magic Ring")) or 
			item.isA(ctx.item_book.getDescriptor("Superior Ring")))


func onBought():
	pass

func getData():
	return amuletsBoosted


func setData(data):
	if data != null:
		amuletsBoosted = data


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == ctx.item_book.getDescriptor("Amulet Unidentified"):
		amuletsBoosted -= 1


func onPrepare():
	for item in getAffectedItems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())
		item.changeAmplificiationChancePercent_allDebuffs(getChance())


func onSaleRoll(item):
	pass

func getRestockItem():
	pass

func getRelatedItems() -> Array:
	return relatedItems


func rollShopChance(shopChance = descriptor.shopChance) -> bool:
	if chanceAcc > ctx.rng.randf_range(85, 125):
		chanceAcc = 0
		return true
		
	var roll = .rollShopChance(shopChance)
	if roll:
		chanceAcc = 0
		return true
	else:
		chanceAcc += shopChance
		return false

func _readyInit():
	._readyInit()
	relatedItems = [
		ctx.item_book.getDescriptor("Magic Ring"), 
		ctx.item_book.getDescriptor("Amulet Unidentified"), 
		ctx.item_book.getDescriptor("Blood Amulet"), 
	]
	salesChance = getP("sales") / 100.0
