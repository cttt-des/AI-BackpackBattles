extends Weapon

const activationParticles = preload("res://Items/Exclusive/Particles/MoltenSpearActivationParticles.tscn")

onready var blockRemoval: = getP("blockremoval")
onready var heatNeeded: = int(getP("heatt"))
onready var missDamage: = int(getP("missdam"))
onready var blind: = int(getP("blind"))
onready var selfblind: = int(getP("blind_self"))
onready var fireMultiplicity: = int(getP("fire"))

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
			addBonusDamage(missDamage)
			damageRes.hit = true
			useHeat(heatNeeded)
			ObjectPool.particleOneShot(activationParticles, sprite)
	
	if damageRes.hasHit():
		inflictBlind(blind)
		selfInflictBlind(selfblind)

func onPreDealDamage_late(damageRes: DamageResult):
	removeBlock(totalBlockRemoval)

func getTypeMultiplicity(type: int) -> int:
	if type == Type.Fire:
		return fireMultiplicity
	else:
		return .getTypeMultiplicity(type)
