extends Item

onready var commonDam = getP("dam") / 100.0

var hasCommonMeleeWeapon: = false
var numCommons: int

func canAffect(item):
	return item.getRarity() == Rarity.Common

func isMeleeWeapon(item):
	return item.canBeEmpowered() and item.descriptor.isMeleeWeapon()

func onPrepare():
	numCommons = 0
	for item in getAffectedItems():
		numCommons += 1
		if isMeleeWeapon(item):
			item.addBonusDamageFactor(commonDam)

func onCombatStart():
	if numCommons > 0:
		giveBlock(getBlock() * numCommons)
	
	activate()

func onItemsCounted():
	hasCommonMeleeWeapon = false
	for item in ItemBook.getOwnedItems():
		if (item.descriptor.isMeleeWeapon() and 
			item.getRarity() == Rarity.Common):
			hasCommonMeleeWeapon = true
			return

func onItemRoll(descr):
	if ( not hasCommonMeleeWeapon and 
		descr.isMeleeWeapon() and 
		descr.getRarity() == Rarity.Common):
			ItemBook.multiplyWeight(1.5)
