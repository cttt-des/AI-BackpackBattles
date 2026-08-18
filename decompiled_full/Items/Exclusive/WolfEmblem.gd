extends Item

const puppies = ["Courage Puppy", "Wisdom Puppy", "Power Puppy"]

onready var blockThreshold = getP("blockt")
onready var empower = getP("empower")

func canAffect(item):
	return item.canBeEmpowered()
	
func canAffect_secondary(item):
	return item.hasType(Type.Pet)

func onPrepare():
	var bonusCritChance = getChance()
	bonusCritChance += getAffectedItems(Affected.Secondary).size() * getChance2()
	
	for item in getAffectedItems():
		item.changeCritChancePercent(bonusCritChance)

func doCooldownEffect():
	var curBlock = character().getBlock()
	
	if curBlock >= blockThreshold:
		giveEmpower(empower)
	else:
		giveBlock()
	
	activate()

func getGatedDescriptor(rarity) -> ItemDescriptor:
	return ItemBook.getDescriptor(Util.pickRandomElement(puppies))
