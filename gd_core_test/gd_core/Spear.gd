extends Weapon
var totalBlockRemoval: int
var blockRemoval

func affectsEmpty(color):
	return true


func canAffect(item):
	return false


func onPrepare():
	totalBlockRemoval = blockRemoval * getNumEmptyAffectedCells()


func onPreDealDamage_late(damageRes: CoreDamageResult):
	
	removeBlock(totalBlockRemoval)

func _readyInit():
	._readyInit()
	blockRemoval = getP("blockremoval")
