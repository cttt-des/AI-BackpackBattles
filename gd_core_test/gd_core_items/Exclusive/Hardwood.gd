extends Item
var hasCommonMeleeWeapon: = false
var numCommons: int
var commonDam

func canAffect(item):
	return item.getRarity() == CoreConst.Rarity.Common


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
	pass

func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	commonDam = getP("dam") / 100.0
