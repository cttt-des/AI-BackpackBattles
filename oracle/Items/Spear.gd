extends Weapon

onready var blockRemoval: = getP("blockremoval")
var totalBlockRemoval: int

func affectsEmpty(color):
	return true

func canAffect(item):
	return false

func onPrepare():
	totalBlockRemoval = blockRemoval * getNumEmptyAffectedCells()

func onPreDealDamage_late(damageRes: DamageResult):
	
	removeBlock(totalBlockRemoval)
