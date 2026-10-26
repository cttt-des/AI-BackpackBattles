extends Item
const puppies = ["Courage Puppy", "Wisdom Puppy", "Power Puppy"]
var blockThreshold
var empower

func canAffect(item):
	return item.canBeEmpowered()
	

func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Pet)


func onPrepare():
	var bonusCritChance = getChance()
	bonusCritChance += getAffectedItems(CoreConst.Affected.Secondary).size() * getChance2()
	
	for item in getAffectedItems():
		item.changeCritChancePercent(bonusCritChance)


func doCooldownEffect():
	var curBlock = character().getBlock()
	
	if curBlock >= blockThreshold:
		giveEmpower(empower)
	else:
		giveBlock()
	
	activate()


func getGatedDescriptor(rarity) -> CoreItemData:
	return ctx.item_book.getDescriptor(ctx.util.pickRandomElement(puppies))

func _readyInit():
	._readyInit()
	blockThreshold = getP("blockt")
	empower = getP("empower")
