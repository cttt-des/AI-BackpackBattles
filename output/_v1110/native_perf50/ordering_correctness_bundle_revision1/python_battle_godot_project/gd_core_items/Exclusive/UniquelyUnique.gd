extends Item
var boosted: = 0
var baseSpeed
var bonusSpeed

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
	return (item.getRarity() == CoreConst.Rarity.Unique or 
		item.isA(ctx.item_book.getDescriptor("Platin Customer Card")) or 
		item.isA(ctx.item_book.getDescriptor("Customer Card")))


func onPrepare():
	var affectedItems = getAffectedItems()
	if not affectedItems.empty():
		affectedItems[0].addSpeed(baseSpeed + getNumAffectedItems(CoreConst.Affected.Secondary) * bonusSpeed)


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == ctx.item_book.getDescriptor("Customer Card"):
		boosted -= 1

func _readyInit():
	._readyInit()
	baseSpeed = getP("speed") / 100.0
	bonusSpeed = getP("speed2") / 100.0
