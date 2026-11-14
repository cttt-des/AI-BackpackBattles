extends Item
var active
var blockAmp
var damReduction

func onItemAdded(item):
	.onItemAdded(item)
	checkItems()


func onItemRemoved(item):
	.onItemRemoved(item)
	checkItems()


func onRemoveFromInventory():
	active = false


func checkItems():
	var numArmor = 0
	var numHelmets = 0
	var numShoes = 0
	for item in inventory.getItems():
		if item.hasType(CoreConst.Type.Armor):
			numArmor += 1
		elif item.hasType(CoreConst.Type.Helmet):
			numHelmets += 1
		elif item.hasType(CoreConst.Type.Shoes):
			numShoes += 1
	
	if numArmor == 1 and numHelmets == 1 and numShoes == 1:
		active = true
	else:
		active = false


func canAffect(item):
	return item.canBlock()


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, blockAmp)
	
	if active:
		connectForCombat(character(), "pre_take_damage", "preTakeDamage")


func preTakeDamage(damageRes: CoreDamageResult):
	if damageRes.damageSource.isAttackOrEffect():
		damageRes.applyDamageReduction(damReduction, self)


func doCooldownEffect():
	giveBlock()
	activate()

func _readyInit():
	._readyInit()
	blockAmp = getP("block") / 100.0
	damReduction = getP("damreduction")
