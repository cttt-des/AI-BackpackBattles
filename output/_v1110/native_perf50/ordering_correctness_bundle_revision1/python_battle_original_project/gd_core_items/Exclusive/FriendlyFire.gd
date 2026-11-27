extends Item
var maxHeatReached: int
var manaNeeded: int
var threshold1: int
var threshold2: int
var threshold3: int

func canAffect(item):
	return item.hasType(CoreConst.Type.Fire)


func onPrepare():
	addSpeed(getNumAffected_type(CoreConst.Type.Fire) * getP3() / 100.0)
	maxHeatReached = 0
	connectForCombat(character(), "character_heat_changed", "onHeatChanged")
	

func onHeatChanged(_amount, event):
	var newMaxHeat = max(maxHeatReached, character().getHeat())
	if newMaxHeat >= threshold3 and maxHeatReached < threshold3:
		maxHeatReached = newMaxHeat
		var dam = descriptor.minDam
		var damageRes = dealEffectDamage(dam, event)
		activate()
	elif newMaxHeat >= threshold2 and maxHeatReached < threshold2:
		maxHeatReached = newMaxHeat
		giveRegeneration(getP7(), event)
		activate()
	elif newMaxHeat >= threshold1 and maxHeatReached < threshold1:
		maxHeatReached = newMaxHeat
		giveLucky(getP5(), event)
		activate()



func doCooldownEffect():
	if character().getMana() >= manaNeeded:
		useMana(manaNeeded)
		giveHeat(getP2())
	activate()

func _readyInit():
	._readyInit()
	manaNeeded = getP1()
	threshold1 = getP4()
	threshold2 = getP6()
	threshold3 = getP8()
	damageSource = CoreDamageSource.new().setItem(self)

