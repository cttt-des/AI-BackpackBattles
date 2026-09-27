extends Item
var boostedWhetstones: = 0
var whetstoneDescriptor
var staminaReduction
var bonusDamage

func getData():
	return boostedWhetstones


func setData(data):
	if data != null:
		boostedWhetstones = data


func canAffect(item):
	return item.isWeapon() and item.isCrafted()


func onCombatStart():
	for item in getAffectedItems():
		item.changeStaminaFactor(staminaReduction)
		if item.canDamage():
			item.addBonusDamage(bonusDamage)
	activate()


func onBought():
	pass

func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == whetstoneDescriptor:
		boostedWhetstones -= 1
	

func _readyInit():
	._readyInit()
	whetstoneDescriptor = ctx.item_book.getDescriptor("Whetstone")
	staminaReduction = - getP("stamina")
	bonusDamage = getP("dam")
