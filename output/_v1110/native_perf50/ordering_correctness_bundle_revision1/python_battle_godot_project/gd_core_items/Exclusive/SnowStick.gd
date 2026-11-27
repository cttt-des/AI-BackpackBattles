extends Weapon
var cold
var selfCold

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		inflictCold(cold)
		giveStacks(character(), CoreConst.EventType.Cold, selfCold)

func _readyInit():
	._readyInit()
	cold = int(getP("cold"))
	selfCold = int(getP("cold2"))
