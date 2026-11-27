extends Item
var numFood: int
var foodPotionSpeed
var heat
var regen

func canAffect(item):
	return item.hasType(CoreConst.Type.Potion)


func canAffect_secondary(item):
	return item.hasType(CoreConst.Type.Food)


func onPrepare():
	numFood = getNumAffectedItems(CoreConst.Affected.Secondary)
	addSpeed(foodPotionSpeed * (getNumAffectedItems() + numFood))
	
	for item in getAffectedItems():
		connectForCombat(item, "potion_triggered", "onPotionTriggered")
	

func doCooldownEffect():
	giveHeat(heat)
	giveRegeneration(regen)
	onAfterEffectFinished()


func onPotionTriggered(_potion):
	heal(getP_m("heal") + getP_m("heal_food") * numFood)

func _readyInit():
	._readyInit()
	foodPotionSpeed = getP("speed") / 100.0
	heat = int(getP("heat"))
	regen = int(getP("regen"))
