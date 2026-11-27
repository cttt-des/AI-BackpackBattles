extends Item
var piggybankDescriptor

func onItemRoll(descr):
	pass

func canAffect(item):
	return item.canDamage()


func onPrepare():
	for item in getAffectedItems():
		item.addCritChancePercent(getChance())


func canAffect_global(item):
	return item.isA(piggybankDescriptor)

func _readyInit():
	._readyInit()
	piggybankDescriptor = ctx.item_book.getDescriptor("Piggybank")
