extends Item

onready var whetstoneDescriptor = ItemBook.getDescriptor("Whetstone")
onready var staminaReduction: = - getP("stamina")
onready var bonusDamage: = getP("dam")

var boostedWhetstones: = 0

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
	boostedWhetstones = 1
	var whetstone = ItemBook.generateAndStorageItem(whetstoneDescriptor, global_position)
	Game.saveRunState()
	activate()

func onItemRoll(descr):
	if descr == whetstoneDescriptor and boostedWhetstones > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr == whetstoneDescriptor:
		boostedWhetstones -= 1
	
