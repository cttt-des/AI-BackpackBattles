extends Weapon

func addToStorageBox(addImpulse = true, tweenBouncyness: bool = true, 
	checkCollisions = true, targetPos = global_position, speed = 1.0, secondCheck = false):
	
	var curDir = faceDirection
	if faceDirection == FaceDirection.LEFT or faceDirection == FaceDirection.RIGHT:
		setFaceDirectionInstant(FaceDirection.UP)
		.addToStorageBox(addImpulse, tweenBouncyness, checkCollisions, targetPos, speed, secondCheck)
		setFaceDirectionInstant(curDir)
		setFaceDirection(FaceDirection.UP)
	else:
		.addToStorageBox(addImpulse, tweenBouncyness, checkCollisions, targetPos, speed, secondCheck)
		
	

var blockRemoval
onready var damResistance = getP("dam")

func affectsEmpty(color):
	return true

func canAffect(item):
	return false

func onPrepare():
	blockRemoval = getP("block") * getNumEmptyAffectedCells()

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		removeBlock(blockRemoval)
		opponent().changeDamageResistance( - damResistance)
