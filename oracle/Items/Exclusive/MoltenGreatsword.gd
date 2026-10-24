extends "res://Items/Greatsword.gd"

const activationParticles = preload("res://Items/Exclusive/Particles/MoltenGreatswordActivationParticles.tscn")

onready var fireMultiplicity: = int(getP("fire"))
onready var heatNeeded: = int(getP("heat"))
onready var empower: = int(getP("empower"))

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if character().getHeat() >= heatNeeded:
			var event = useHeat(heatNeeded)
			giveEmpower(empower, event)
			var particles = ObjectPool.particleOneShot(activationParticles, sprite)




func getTypeMultiplicity(type: int) -> int:
	if type == Type.Fire:
		return fireMultiplicity
	else:
		return .getTypeMultiplicity(type)
