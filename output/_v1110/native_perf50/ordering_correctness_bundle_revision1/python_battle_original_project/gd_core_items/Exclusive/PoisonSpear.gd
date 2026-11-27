extends Weapon
var blockRemoval
var poison
var selfPoison

func affectsEmpty(color):
	return true


func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func onPrepare():
	blockRemoval = getP("blockremoval") * (getNumEmptyAffectedCells() + getNumAffectedItems())


func onPreDealDamage_late(damageRes: CoreDamageResult):
	
	inflictPoison(poison)
	selfInflictPoison(selfPoison)
	removeBlock(blockRemoval)

func _readyInit():
	._readyInit()
	poison = int(getP("poison"))
	selfPoison = int(getP("poison2"))
