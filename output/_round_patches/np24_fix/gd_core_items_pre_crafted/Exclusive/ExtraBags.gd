extends Item
var freeSlotSpeed
var salesChance
var bagWeight

func canAffect(item):
	return item.hasCooldown()


func affectsEmpty(color):
	return color == CoreConst.Affected.Secondary


func canAffect_secondary(item):
	return false


func onPrepare():
	var freeSlotSpeed_total = getNumEmptyAffectedCells(CoreConst.Affected.Secondary) * freeSlotSpeed
	if freeSlotSpeed_total > 0:
		for item in getAffectedItems():
			item.addSpeed(freeSlotSpeed_total)


func onSaleRoll(item):
	pass

func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	freeSlotSpeed = getP("speed") / 100.0
	salesChance = getP("sales") / 100.0
	bagWeight = getP("bagweight")
