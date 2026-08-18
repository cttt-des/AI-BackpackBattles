extends Weapon

onready var foodSpeed: = getP("speed") / 100.0
onready var damFactor: = getP("dam")

func canAffect(item):
	return item.hasType(Type.Food)

func onPrepare():
	addSpeed(foodSpeed * getNumAffectedItems())

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		opponent().changeDamageResistance( - damFactor)
