extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/MoltenSpearActivationParticles.tscn")

onready var blockRemoval: = getP("blockremoval")
onready var missDamage: = int(getP("missdam"))
onready var heatNeeded: = int(getP("heatt"))
var totalBlockRemoval: int

func affectsEmpty(color):
	return true

func canAffect(item):
	return item.hasType(Type.Fire)

func onPrepare():
	totalBlockRemoval = blockRemoval * (getNumAffected_type(Type.Fire)
		+ getNumEmptyAffectedCells())

func onPreDealDamage_early(damageRes: DamageResult):
	if not damageRes.hasHit():
		if character().getHeat() >= heatNeeded:
			damageRes.damage += missDamage
			damageRes.hit = true
			useHeat(heatNeeded)
			ObjectPool.particleOneShot(activationParticles, sprite)

func onPreDealDamage_late(damageRes: DamageResult):
	removeBlock(totalBlockRemoval)
