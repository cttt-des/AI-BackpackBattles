extends Weapon
var totalBlockRemoval: int
var dam
var blockRemoval
var blockFactor

func canBlock() -> bool:
	return true


func affectsEmpty(color):
	return true


func canAffect(item):
	return item.canBlock()


func onPrepare():
	totalBlockRemoval = blockRemoval * (getNumAffectedItems() + getNumEmptyAffectedCells())
	
	for item in getAffectedItems():
		item.giveBuffPower(CoreConst.EventType.Block, blockFactor)


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		addBonusDamage(dam)


func onPreDealDamage_late(damageRes: CoreDamageResult):
	
	var curBlock = opponent().getBlock()
	var toRemove = min(curBlock, totalBlockRemoval)
	removeBlock(toRemove, damageRes.event)
	var toGive = totalBlockRemoval - toRemove
	if toGive > 0:
		giveBlock(toGive, true, damageRes.event)

func _readyInit():
	._readyInit()
	dam = getP("dam")
	blockRemoval = getP("blockremoval")
	blockFactor = getP("blockfactor") / 100.0
