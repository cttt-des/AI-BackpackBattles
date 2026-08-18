extends Item

onready var shieldOfValorDescriptor = ItemBook.getDescriptor("Shield of Valor")
onready var shieldChance = getP("chance")
onready var armorSpeed = getP("speed") / 100.0

var boostedShields: = 0

func getData():
	return boostedShields

func setData(data):
	if data != null:
		boostedShields = data

func onBought():
	boostedShields = 1

func canAffect(item):
	return item.hasType(Type.Shield) or (item.hasType(Type.Armor) and item.hasCooldown())

func onPrepare():
	for item in getAffectedItems():
		
		if item.hasType(Type.Shield):
			item.addBonusChance_additive(shieldChance, 0)
		
		else:
			item.addSpeed(armorSpeed)

func onItemRoll(descr):
	if descr == shieldOfValorDescriptor and boostedShields > 0:
		ItemBook.multiplyWeight(1.5)

func onItemRolled(descr):
	if descr == shieldOfValorDescriptor:
		boostedShields -= 1
