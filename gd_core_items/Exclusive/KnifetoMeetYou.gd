extends Item
var boosted: = 0
var daggerDescriptor
var daggerSpeed
var damFactor
var speedPerDagger

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
	pass

func onItemRolled(descr):
	if descr == daggerDescriptor:
		boosted -= 1


func canAffect_global(item):
	return item.canBeEmpowered()

func _readyInit():
	._readyInit()
	daggerDescriptor = ctx.item_book.getDescriptor("Dagger")
	daggerSpeed = getP("speed") / 100.0
	damFactor = getP("dam") / 100.0
	speedPerDagger = getP("speed2") / 100.0
