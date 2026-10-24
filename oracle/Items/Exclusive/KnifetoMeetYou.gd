extends Item

onready var daggerDescriptor = ItemBook.getDescriptor("Dagger")
onready var daggerSpeed: = getP("speed") / 100.0
onready var damFactor: = getP("dam") / 100.0
onready var speedPerDagger: = getP("speed2") / 100.0

var boosted: = 0

func onBought():
	boosted = 3

func getData():
	return boosted

func setData(data):
	if data != null:
		boosted = data

func canAffect(item):
	return item is Dagger

func onPrepare():
	for item in inventory.getItems():
		if item is Dagger:
			item.addSpeed(daggerSpeed)
	
	addSpeed(speedPerDagger * getNumAffectedItems())

func doCooldownEffect():
	for item in inventory.getItems():
		if item.canBeEmpowered():
			item.addBonusDamageFactor(damFactor)
	onAfterEffectFinished()

func onItemRoll(descr):
	if descr == daggerDescriptor and boosted > 0:
		ItemBook.multiplyWeight(1.7)

func onItemRolled(descr):
	if descr == daggerDescriptor:
		boosted -= 1

func canAffect_global(item):
	return item.canBeEmpowered()
