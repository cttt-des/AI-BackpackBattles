extends Food
var speedBonusGiven = 0.0
var speedBonus
var maxSpeedBonus

func canAffect_global(item):
	return item.hasType(CoreConst.Type.Pet)


func onPrepare():
	speedBonusGiven = 0.0
	
	for item in inventory.getItems():
		if canAffect_global(item):
			item.giveDoubleActivationChance(getChance())


func doCooldownEffect():
	giveRandomBuffs(getP1())
	if speedBonusGiven < maxSpeedBonus:
		for item in getAffectedItems():
			var curBonus = min(speedBonus, maxSpeedBonus - speedBonusGiven)
			item.addSpeed(curBonus / 100)
			
		speedBonusGiven += speedBonus
	activate()


func getGatedDescriptor(rarity) -> CoreItemData:
	var itemName: String
	
	if rarity >= CoreConst.Rarity.Legendary:
		rarity = ctx.util.pickRandomElement([CoreConst.Rarity.Common, CoreConst.Rarity.Rare, CoreConst.Rarity.Epic])
	
	match rarity:
		CoreConst.Rarity.Common:
			itemName = "Rat"
		CoreConst.Rarity.Rare:
			itemName = "Squirrel"
		CoreConst.Rarity.Epic:
			itemName = "Hedgehog"
	
	return ctx.item_book.getDescriptor(itemName)

func _readyInit():
	._readyInit()
	speedBonus = getP2()
	maxSpeedBonus = getP3()
