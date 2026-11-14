extends Item
var boosted: = 0
var sunShieldDescriptor
var sunArmorDescriptor
var holyArmorDescriptor
var shieldOfValorDescriptor
var heatPerShieldBlock

func canAffect(item):
	return item.isA(sunShieldDescriptor) or item.isA(sunArmorDescriptor)


func onBought():
	boosted = 1


func getData():
	return boosted


func setData(data):
	if data != null:
		boosted = data


func onPrepare():
	inventory.changeBuffAmplification_allItems(CoreConst.EventType.Heat, getChance2())
	
	for item in getAffectedItems():
		if item.isA(sunShieldDescriptor):
			connectForCombat(item, "blocked", "onShieldBlocked")
		else:
			connectForCombat(item, "used_heat", "onArmorUsedHeat")
	

func onArmorUsedHeat(event):
	giveBlock(getBlock(), true, event)
	miniActivate()


func onShieldBlocked(blockedDamageRes):
	if rollChance():
		giveHeat(heatPerShieldBlock)
		activate()








func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if (descr == shieldOfValorDescriptor or 
		descr == holyArmorDescriptor):
		boosted -= 1

func _readyInit():
	._readyInit()
	sunShieldDescriptor = ctx.item_book.getDescriptor("Sun Shield")
	sunArmorDescriptor = ctx.item_book.getDescriptor("Sun Armor")
	holyArmorDescriptor = ctx.item_book.getDescriptor("Holy Armor")
	shieldOfValorDescriptor = ctx.item_book.getDescriptor("Shield of Valor")
	heatPerShieldBlock = int(getP("heat"))
