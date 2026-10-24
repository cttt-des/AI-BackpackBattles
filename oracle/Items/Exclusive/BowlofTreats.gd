extends Food

var speedBonusGiven = 0.0

onready var speedBonus = getP2()
onready var maxSpeedBonus = getP3()

func canAffect_global(item):
	return item.hasType(Type.Pet)

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

func getGatedDescriptor(rarity) -> ItemDescriptor:
	var itemName: String
	
	if rarity >= Rarity.Legendary:
		rarity = Util.pickRandomElement([Item.Rarity.Common, Item.Rarity.Rare, Item.Rarity.Epic])
	
	match rarity:
		Rarity.Common:
			itemName = "Rat"
		Rarity.Rare:
			itemName = "Squirrel"
		Rarity.Epic:
			itemName = "Hedgehog"
	
	return ItemBook.getDescriptor(itemName)
