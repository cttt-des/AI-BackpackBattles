extends Item
const chargeCells = [Vector2( - 1, - 1), Vector2( - 1, - 2), 
	Vector2( - 2, - 3), Vector2( - 2, - 4), Vector2( - 1, - 5), Vector2(0, - 5)]
var flatSpeed
var speedPerTile

func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()


func onCombatStart():
	emitCharge()
	ctx.bus.emitSignal(self, "charge_emitted", [self])


func doCooldownEffect():
	if useStamina() == CoreConst.StaminaResult.Sufficient:
		emitCharge()
		ctx.bus.emitSignal(self, "charge_emitted", [self])


func emitCharge(speedFactor = 1.0):
	var event = activate()
	sendCharge(getP_m("dur"), chargeCells, speedFactor, event)


func onChargeEnteredCell(charge, cellIndex):
	changeChargedItemStat(charge, cellIndex, flatSpeed, speedPerTile)


func chargedItemStatChange(item, value):
	item.addSpeed(value)


func getTriggerPriority():
	return CoreConst.Priority.High + 5

func _readyInit():
	._readyInit()
	flatSpeed = getP("speed") / 100
	speedPerTile = getP("speed2") / 100
