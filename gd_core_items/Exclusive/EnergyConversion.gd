extends Item
var stackTypes
var heat
var heatThreshold
var numBuffs
var speedPerFood

func canAffect(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	addSpeed(getNumAffectedItems() * speedPerFood)


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		if character().getHeat() >= heatThreshold:
			giveRandomBuffs(numBuffs, null, stackTypes)
		else:
			giveHeat(heat)
		
		activate()

func _readyInit():
	._readyInit()
	heat = int(getP("heat"))
	heatThreshold = int(getP("heatt"))
	numBuffs = int(getP("buffs"))
	speedPerFood = getP("speed") / 100.0
	stackTypes = CoreConst.getBuffs()
	stackTypes.erase(CoreConst.EventType.Heat)

