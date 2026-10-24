extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/PoisonSpearActivationParticles.tscn")

onready var poison: = int(getP("poison"))
onready var selfPoison: = int(getP("poison2"))

var blockRemoval

func affectsEmpty(color):
	return true

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	blockRemoval = getP("blockremoval") * (getNumEmptyAffectedCells() + getNumAffectedItems())

func onPreDealDamage_late(damageRes: DamageResult):
	
	inflictPoison(poison)
	selfInflictPoison(selfPoison)
	removeBlock(blockRemoval)
	ObjectPool.particleOneShot(activationParticles, sprite)
