extends Weapon
var blockRemoval
var damResistance

func addToStorageBox(addImpulse = true, tweenBouncyness: bool = true, 
	checkCollisions = true, targetPos = null, speed = 1.0, secondCheck = false):
	
	var curDir = faceDirection
	if faceDirection == CoreConst.FaceDirection.LEFT or faceDirection == CoreConst.FaceDirection.RIGHT:
		setFaceDirectionInstant(CoreConst.FaceDirection.UP)
		.addToStorageBox(addImpulse, tweenBouncyness, checkCollisions, targetPos, speed, secondCheck)
		setFaceDirectionInstant(curDir)
		setFaceDirection(CoreConst.FaceDirection.UP)
	else:
		.addToStorageBox(addImpulse, tweenBouncyness, checkCollisions, targetPos, speed, secondCheck)
		
	


func affectsEmpty(color):
	return true


func canAffect(item):
	return false


func onPrepare():
	blockRemoval = getP("block") * getNumEmptyAffectedCells()


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		removeBlock(blockRemoval)
		opponent().changeDamageResistance( - damResistance)

func _readyInit():
	._readyInit()
	damResistance = getP("dam")
