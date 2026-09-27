extends Weapon
var foodSpeed
var damFactor

func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	addSpeed(foodSpeed * getNumAffectedItems())


func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		opponent().changeDamageResistance( - damFactor)

func _readyInit():
	._readyInit()
	foodSpeed = getP("speed") / 100.0
	damFactor = getP("dam")
