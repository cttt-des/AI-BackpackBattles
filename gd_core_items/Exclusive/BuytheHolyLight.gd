extends Item
var oilLamp
var djinnLamp
var holySpeed
var salesChance

func canAffect(item):
	return (item.hasType(CoreConst.Type.Holy) and item.hasCooldown()) or isLamp(item)


func canAffect_global(item):
	return isLamp(item)


func isLamp(item) -> bool:
	return item.isA(oilLamp) or item.isA(djinnLamp)
	

func onItemInstantiated(item):
	if (placed and 
		isLamp(item) and 
		item.isOwnable()):
			item.addDynamicType(CoreConst.Type.Holy, self)


func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(holySpeed)


func onSaleRoll(item):
	pass

func onAddToInventory():
	call_deferred("onAddToInventory_deferred")


func onAddToInventory_deferred():
	pass

func onRemoveFromInventory():
	call_deferred("onRemoveFromInventory_deferred")


func onRemoveFromInventory_deferred():
	pass

func onItemRoll(descr):
	pass

func _readyInit():
	._readyInit()
	oilLamp = ctx.item_book.getDescriptor("Oil Lamp")
	djinnLamp = ctx.item_book.getDescriptor("Djinn Lamp")
	holySpeed = getP("speed") / 100.0
	salesChance = getP("sales") / 100.0
