extends Item

var maxHeatReached: int

onready var manaNeeded: int = getP1()
onready var threshold1: int = getP4()
onready var threshold2: int = getP6()
onready var threshold3: int = getP8()

func _ready() -> void :
	damageSource = DamageSource.new().setItem(self)

func canAffect(item):
	return item.hasType(Type.Fire)

func onPrepare():
	addSpeed(getNumAffected_type(Type.Fire) * getP3() / 100.0)
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

