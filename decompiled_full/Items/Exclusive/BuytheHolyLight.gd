extends Item

onready var oilLamp = ItemBook.getDescriptor("Oil Lamp")
onready var djinnLamp = ItemBook.getDescriptor("Djinn Lamp")
onready var holySpeed: = getP("speed") / 100.0
onready var salesChance: = getP("sales") / 100.0

func canAffect(item):
	return (item.hasType(Type.Holy) and item.hasCooldown()) or isLamp(item)

func canAffect_global(item):
	return isLamp(item)

func isLamp(item) -> bool:
	return item.isA(oilLamp) or item.isA(djinnLamp)
	
func onItemInstantiated(item):
	if (placed and 
		isLamp(item) and 
		item.isOwnable()):
			item.addDynamicType(Type.Holy, self)

func onPrepare():
	for item in getAffectedItems():
		item.addSpeed(holySpeed)

func onSaleRoll(item):
	if item != null and (item.hasType(Type.Holy) or isLamp(item)):
		Game.shopSceneNode.addBonusSalesChance(salesChance)






func onAddToInventory():
	call_deferred("onAddToInventory_deferred")

func onAddToInventory_deferred():
	if isOwnedByOpponent():
		for item in getAllInInventoryOfType(oilLamp):
			item.addDynamicType(Type.Holy, self)
		for item in getAllInInventoryOfType(djinnLamp):
			item.addDynamicType(Type.Holy, self)
	
	elif ownerType == Owner.PlayerInventory:
		for item in ItemBook.getItemsOnScreenOfType(oilLamp):
			item.addDynamicType(Type.Holy, self)
		for item in ItemBook.getItemsOnScreenOfType(djinnLamp):
			item.addDynamicType(Type.Holy, self)

func onRemoveFromInventory():
	call_deferred("onRemoveFromInventory_deferred")

func onRemoveFromInventory_deferred():
	if isOwnable():
		for item in ItemBook.getItemsOnScreenOfType(oilLamp):
			item.removeDynamicType(Type.Holy, self)
		for item in ItemBook.getItemsOnScreenOfType(djinnLamp):
			item.removeDynamicType(Type.Holy, self)

func onItemRoll(descr):
	if descr.hasType(Type.Holy) or descr == oilLamp or descr == djinnLamp:
		ItemBook.multiplyWeight(1.3)
