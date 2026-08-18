extends Item

onready var freeSlotSpeed = getP("speed") / 100.0
onready var salesChance: = getP("sales") / 100.0
onready var bagWeight: = getP("bagweight")

func canAffect(item):
	return item.hasCooldown()

func affectsEmpty(color):
	return color == Affected.Secondary

func canAffect_secondary(item):
	return false

func onPrepare():
	var freeSlotSpeed_total = getNumEmptyAffectedCells(Affected.Secondary) * freeSlotSpeed
	if freeSlotSpeed_total > 0:
		for item in getAffectedItems():
			item.addSpeed(freeSlotSpeed_total)

func onSaleRoll(item):
	if item != null and item.isBag():
		Game.shopSceneNode.addBonusSalesChance(salesChance)

func onItemRoll(descr):
	if descr.isBag():
		ItemBook.multiplyWeight(bagWeight)
	
