extends Item

onready var baseSpeed: = getP("speed") / 100.0
onready var bonusSpeed: = getP("speed2") / 100.0

var boosted: = 0

func onBought():
	boosted = 2

func getData():
	return boosted

func setData(data):
	if data != null:
		boosted = data

func canAffect(item):
	return item.hasCooldown()

func canAffect_secondary(item):
	return (item.getRarity() == Rarity.Unique or 
		item.isA(ItemBook.platinCardDescriptor) or 
		item.isA(ItemBook.customerCardDescriptor))

func onPrepare():
	var affectedItems = getAffectedItems()
	if not affectedItems.empty():
		affectedItems[0].addSpeed(baseSpeed + getNumAffectedItems(Affected.Secondary) * bonusSpeed)

func onItemRoll(descr):
	if descr == ItemBook.customerCardDescriptor and boosted > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr == ItemBook.customerCardDescriptor:
		boosted -= 1
