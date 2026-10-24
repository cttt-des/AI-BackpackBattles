extends Item

onready var piggybankDescriptor = ItemBook.getDescriptor("Piggybank")

func onItemRoll(descr):
	if descr == piggybankDescriptor:
		ItemBook.multiplyWeight(1.5)

func canAffect(item):
	return item.canDamage()

func onPrepare():
	for item in getAffectedItems():
		item.addCritChancePercent(getChance())

func canAffect_global(item):
	return item.isA(piggybankDescriptor)
