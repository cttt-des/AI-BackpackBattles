extends Item
var allPotions = []
var boostedPotions: = 0
var potionSpeed

func getData():
	return boostedPotions


func setData(data):
	if data != null:
		boostedPotions = data


func onBought():
	boostedPotions = 3


func isAffectingDistinct(color = CoreConst.Affected.Primary) -> bool:
	return color == CoreConst.Affected.Primary


func canAffect(item):
	return item.hasType(CoreConst.Type.Potion)


func canAffect_global(item):
	return item.hasType(CoreConst.Type.Potion)


func onPrepare():
	addSpeed(getNumDistinctAffectedItems() * potionSpeed)
	
	allPotions.clear()
	for item in inventory.getItems():
		if item.hasType(CoreConst.Type.Potion) and item != self:
			allPotions.push_back(item)


func doCooldownEffect():
	if not allPotions.empty():
		var potionToTrigger = ctx.util.pickRandomElement(allPotions)
		potionToTrigger.triggerPotion()
		potionToTrigger.miniActivate()
	
	activate()


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr.hasType(CoreConst.Type.Potion):
		boostedPotions -= 1

func _readyInit():
	._readyInit()
	potionSpeed = getP("speed") / 100.0
