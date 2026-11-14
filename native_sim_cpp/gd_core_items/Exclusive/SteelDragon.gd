extends Weapon
var reflectStacks
var blockFactor
var dam

func canAffect(item):
	return item.canBeEmpowered() or item.canBlock()


func onPrepare():
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, blockFactor)


func onPreCombatStart():
	giveReflectStacks(reflectStacks)


func onCombatStart():
	for item in getAffectedItems():
		item.addBonusDamage(dam)
	activate(null, false)

func _readyInit():
	._readyInit()
	reflectStacks = int(getP("reflect"))
	blockFactor = getP("blockfactor") / 100.0
	dam = getP("dam")
