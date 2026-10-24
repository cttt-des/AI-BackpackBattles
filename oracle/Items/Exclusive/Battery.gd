extends Item

const chargeCells = [Vector2( - 1, - 1), Vector2( - 1, - 2), Vector2( - 1, - 3), 
	Vector2( - 1, - 4), Vector2( - 1, - 5)]

onready var flatSpeed: = getP("speed") / 100
onready var speedPerTile: = getP("speed2") / 100


func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()

func onCombatStart():
	emitCharge()
	EventBus.emitSignal(self, "charge_emitted", [self])

func emitCharge(speedFactor = 1.0):
	var event = activate()
	sendCharge(getP_m("dur"), chargeCells, speedFactor, event)

func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, flatSpeed, speedPerTile)

func chargedItemStatChange(item, value):
	item.addSpeed(value)

func getTriggerPriority():
	return Priority.High + 5
