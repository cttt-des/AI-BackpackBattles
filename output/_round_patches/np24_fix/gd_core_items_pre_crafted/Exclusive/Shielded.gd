extends Item
var boostedShields: = 0
var shieldOfValorDescriptor
var shieldChance
var armorSpeed

func getData():
	return boostedShields


func setData(data):
	if data != null:
		boostedShields = data


func onBought():
	boostedShields = 1


func canAffect(item):
	return item.hasType(CoreConst.Type.Shield) or (item.hasType(CoreConst.Type.Armor) and item.hasCooldown())


func onPrepare():
	for item in getAffectedItems():
		
		if item.hasType(CoreConst.Type.Shield):
			item.addBonusChance_additive(shieldChance, 0)
		
		else:
			item.addSpeed(armorSpeed)


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == shieldOfValorDescriptor:
		boostedShields -= 1

func _readyInit():
	._readyInit()
	shieldOfValorDescriptor = ctx.item_book.getDescriptor("Shield of Valor")
	shieldChance = getP("chance")
	armorSpeed = getP("speed") / 100.0
