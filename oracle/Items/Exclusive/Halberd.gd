extends Weapon

onready var dam: = getP("dam")
onready var blockRemoval: = getP("blockremoval")
onready var blockFactor: = getP("blockfactor") / 100.0
var totalBlockRemoval: int

func canBlock() -> bool:
	return true

func affectsEmpty(color):
	return true

func canAffect(item):
	return item.canBlock()

func onPrepare():
	totalBlockRemoval = blockRemoval * (getNumAffectedItems() + getNumEmptyAffectedCells())
	
	for item in getAffectedItems():
		item.giveBuffPower(Game.EventType.Block, blockFactor)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		addBonusDamage(dam)

func onPreDealDamage_late(damageRes: DamageResult):
	
	var curBlock = opponent().getBlock()
	var toRemove = min(curBlock, totalBlockRemoval)
	removeBlock(toRemove, damageRes.event)
	var toGive = totalBlockRemoval - toRemove
	if toGive > 0:
		giveBlock(toGive, true, damageRes.event)
